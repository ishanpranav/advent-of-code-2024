// day16b.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Reindeer Maze

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef DAY16
#define DAY16
#define MAX_M 256
#define MAX_N 256
#endif

enum Direction
{
    DIRECTION_UP = 0,
    DIRECTION_DOWN = 2,
    DIRECTION_LEFT = 3,
    DIRECTION_RIGHT = 1,
    MAX_DIRECTION = 4
};

typedef enum Direction Direction;
typedef struct Coordinate Coordinate;

struct Coordinate
{
    Direction direction;
    size_t priority;
    size_t i;
    size_t j;
};

struct Entry
{
    bool reachable;
    size_t distances[MAX_DIRECTION];
};

typedef struct Entry Entry;

struct Grid
{
    char items[MAX_M][MAX_N];
    size_t m;
    size_t n;
    Coordinate s;
    Coordinate t;
};

struct PriorityQueue
{
    size_t count;
    size_t capacity;
    Coordinate* items;
};

struct Table
{
    size_t reachable;
    Entry* entries;
};

typedef struct Grid Grid;
typedef struct PriorityQueue PriorityQueue;
typedef struct Table Table;

static int priority_queue(PriorityQueue* instance, size_t capacity)
{
    if (capacity < 4)
    {
        capacity = 4;
    }

    instance->items = malloc((capacity + 1) * sizeof * instance->items);

    if (!instance->items)
    {
        return -1;
    }

    instance->count = 0;
    instance->capacity = capacity;

    return 0;
}

static int priority_queue_ensure_capacity(
    PriorityQueue* instance,
    size_t capacity)
{
    if (instance->capacity >= capacity)
    {
        return 0;
    }

    size_t newCapacity = instance->capacity * 2;

    if (capacity > newCapacity)
    {
        newCapacity = capacity;
    }

    Coordinate* items = instance->items;
    Coordinate* newItems = realloc(
        items,
        (newCapacity + 1) * sizeof * newItems);

    if (!newItems)
    {
        return -1;
    }

    instance->capacity = newCapacity;
    instance->items = newItems;

    return 0;
}

static int priority_queue_enqueue(PriorityQueue* instance, Coordinate item)
{
    int ex = priority_queue_ensure_capacity(instance, instance->count + 1);

    if (ex)
    {
        return ex;
    }

    instance->count++;

    size_t i = instance->count;

    while (i != 1 && item.priority < instance->items[i / 2].priority)
    {
        size_t j = i / 2;

        instance->items[i] = instance->items[j];
        i = j;
    }

    instance->items[i] = item;

    return 0;
}

static Coordinate priority_queue_dequeue(PriorityQueue* instance)
{
    size_t i = 1;
    size_t child = 2;
    Coordinate result = instance->items[1];

    instance->items[0] = instance->items[instance->count];

    while (child < instance->count)
    {
        if (child < instance->count - 1 &&
            instance->items[child].priority >
            instance->items[child + 1].priority)
        {
            child++;
        }

        if (instance->items[0].priority <= instance->items[child].priority)
        {
            break;
        }

        instance->items[i] = instance->items[child];
        i = child;
        child *= 2;
    }

    instance->items[i] = instance->items[0];
    instance->count--;

    return result;
}

static void priority_queue_clear(PriorityQueue* instance)
{
    instance->count = 0;
}

static void finalize_priority_queue(PriorityQueue* instance)
{
    priority_queue_clear(instance);
    free(instance->items);

    instance->items = NULL;
    instance->capacity = 0;
}

static Coordinate coordinate_add(Coordinate u, int di)
{
    switch (u.direction)
    {
    case DIRECTION_UP:
        u.i -= di;
        break;

    case DIRECTION_DOWN:
        u.i += di;
        break;

    case DIRECTION_LEFT:
        u.j -= di;
        break;

    case DIRECTION_RIGHT:
        u.j += di;
        break;

    default: exit(EXIT_FAILURE);
    }

    return u;
}

static Coordinate coordinate_rotate_left(Coordinate u)
{
    if (u.direction == 0)
    {
        u.direction = MAX_DIRECTION - 1;
    }
    else
    {
        u.direction--;
    }

    return u;
}

static Coordinate coordinate_rotate_right(Coordinate u)
{
    if (u.direction == MAX_DIRECTION - 1)
    {
        u.direction = 0;
    }
    else
    {
        u.direction++;
    }

    return u;
}

static size_t dijkstra(Table* w, PriorityQueue* q, const Grid* a)
{
    Coordinate s = a->s;

    s.priority = 0;
    w->entries[s.i * a->n + s.j].distances[s.direction] = s.priority;

    priority_queue_enqueue(q, s);

    size_t min = SIZE_MAX;

    while (q->count)
    {
        Coordinate u = priority_queue_dequeue(q);

        if (min <= u.priority)
        {
            continue;
        }

        if (u.i == a->t.i && u.j == a->t.j)
        {
            min = u.priority;
        }

        Coordinate v = coordinate_add(u, 1);

        if (a->items[v.i][v.j] != '#')
        {
            v.priority++;

            size_t* p = &w->entries[v.i * a->n + v.j].distances[v.direction];

            if (v.priority < *p)
            {
                *p = v.priority;

                if (priority_queue_enqueue(q, v))
                {
                    exit(EXIT_FAILURE);
                }
            }
        }

        v = coordinate_rotate_left(u);
        v.priority += 1000;

        if (v.priority < w->entries[v.i * a->n + v.j].distances[v.direction])
        {
            w->entries[v.i * a->n + v.j].distances[v.direction] = v.priority;

            if (priority_queue_enqueue(q, v))
            {
                exit(EXIT_FAILURE);
            }
        }

        v = coordinate_rotate_right(u);
        v.priority += 1000;

        if (v.priority < w->entries[v.i * a->n + v.j].distances[v.direction])
        {
            w->entries[v.i * a->n + v.j].distances[v.direction] = v.priority;

            if (priority_queue_enqueue(q, v))
            {
                exit(EXIT_FAILURE);
            }
        }
    }

    return min;
}

static void depth_first_search(Table* w, Coordinate u, const Grid* a)
{
    if (!w->entries[u.i * a->n + u.j].reachable)
    {
        w->entries[u.i * a->n + u.j].reachable = true;
        w->reachable++;
    }

    if (u.i == a->s.i && u.j == a->s.j)
    {
        return;
    }

    Coordinate v = coordinate_add(u, -1);

    if (a->items[v.i][v.j] != '#')
    {
        v.priority--;

        if (v.priority == w->entries[v.i * a->n + v.j].distances[v.direction])
        {
            depth_first_search(w, v, a);

            w->entries[v.i * a->n + v.j].distances[v.direction] = SIZE_MAX;
        }
    }

    v = coordinate_rotate_left(u);
    v.priority -= 1000;

    if (v.priority == w->entries[v.i * a->n + v.j].distances[v.direction])
    {
        depth_first_search(w, v, a);

        w->entries[v.i * a->n + v.j].distances[v.direction] = SIZE_MAX;
    }

    v = coordinate_rotate_right(u);
    v.priority -= 1000;

    if (v.priority == w->entries[v.i * a->n + v.j].distances[v.direction])
    {
        depth_first_search(w, v, a);

        w->entries[v.i * a->n + v.j].distances[v.direction] = SIZE_MAX;
    }
}

static Coordinate grid_find(const Grid* a, char value)
{
    Coordinate u;

    u.j = 0;

    for (u.i = 0; u.i < a->m; u.i++)
    {
        char* p = strchr(a->items[u.i], value);

        if (p)
        {
            u.j = p - a->items[u.i];

            break;
        }
    }

    return u;
}

int main()
{
    Grid a;

    a.m = 0;
    a.n = 0;

    if (fgets(a.items[0], MAX_N, stdin))
    {
        a.n = strlen(a.items[0]);

        while (a.n && isspace(a.items[0][a.n - 1]))
        {
            a.n--;
        }

        a.m++;

        while (fgets(a.items[a.m], MAX_N, stdin))
        {
            a.m++;
        }
    }

    a.s = grid_find(&a, 'S');
    a.s.direction = DIRECTION_RIGHT;
    a.t = grid_find(&a, 'E');

    Table w;

    w.reachable = 0;
    w.entries = malloc(a.m * a.n * sizeof * w.entries);

    if (!w.entries)
    {
        return EXIT_FAILURE;
    }

    for (size_t k = 0; k < a.m * a.n; k++)
    {
        w.entries[k].reachable = false;

        for (Direction d = 0; d < MAX_DIRECTION; d++)
        {
            w.entries[k].distances[d] = SIZE_MAX;
        }
    }

    PriorityQueue q;

    if (priority_queue(&q, 0))
    {
        return EXIT_FAILURE;
    }

    size_t min = dijkstra(&w, &q, &a);

    for (a.t.direction = 0; a.t.direction < MAX_DIRECTION; a.t.direction++)
    {
        if (w.entries[a.t.i * a.n + a.t.j].distances[a.t.direction] == min)
        {
            a.t.priority = min;

            depth_first_search(&w, a.t, &a);
        }
    }

    printf("%zu\n", w.reachable);
    free(w.entries);
    finalize_priority_queue(&q);

    return EXIT_SUCCESS;
}
