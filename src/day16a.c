// day16a.c
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

struct Coordinate
{
    Direction direction;
    size_t priority;
    size_t i;
    size_t j;
};

typedef struct Coordinate Coordinate;

struct Grid
{
    char items[MAX_M][MAX_N];
    size_t m;
    size_t n;
    Coordinate s;
};

struct PriorityQueue
{
    size_t count;
    size_t capacity;
    Coordinate* items;
};

typedef struct Grid Grid;
typedef struct PriorityQueue PriorityQueue;

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

static Coordinate priority_queue_peek(const PriorityQueue* instance)
{
    return instance->items[1];
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

static void priority_queue_dequeue(PriorityQueue* instance)
{
    size_t i = 1;
    size_t child = 2;

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

static size_t dijkstra(size_t* w, PriorityQueue* q, const Grid* a)
{
    for (size_t k = 0; k < a->m * a->n * MAX_DIRECTION; k++)
    {
        w[k] = SIZE_MAX;
    }

    {
        Coordinate s = a->s;

        s.priority = 0;

        priority_queue_enqueue(q, s);
    }

    while (q->count)
    {
        Coordinate u = priority_queue_peek(q);

        priority_queue_dequeue(q);

        if (a->items[u.i][u.j] == 'E')
        {
            return u.priority;
        }

        size_t k = (u.i * a->n + u.j) * MAX_DIRECTION + u.direction;

        if (w[k] <= u.priority)
        {
            continue;
        }

        w[k] = u.priority;

        Coordinate v = u;

        switch (u.direction)
        {
        case DIRECTION_UP:
            v.i--;
            break;

        case DIRECTION_DOWN:
            v.i++;
            break;

        case DIRECTION_LEFT:
            v.j--;
            break;

        case DIRECTION_RIGHT:
            v.j++;
            break;

        default:
            exit(EXIT_FAILURE);
        }

        if (a->items[v.i][v.j] != '#')
        {
            v.priority++;

            if (priority_queue_enqueue(q, v))
            {
                exit(EXIT_FAILURE);
            }
        }

        v = u;
        v.priority += 1000;

        if (v.direction == MAX_DIRECTION - 1)
        {
            v.direction = 0;
        }
        else
        {
            v.direction++;
        }

        if (priority_queue_enqueue(q, v))
        {
            exit(EXIT_FAILURE);
        }

        v = u;
        v.priority += 1000;

        if (v.direction == 0)
        {
            v.direction = MAX_DIRECTION - 1;
        }
        else
        {
            v.direction--;
        }

        if (priority_queue_enqueue(q, v))
        {
            exit(EXIT_FAILURE);
        }
    }

    return SIZE_MAX;
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

    a.s.j = 0;
    a.s.direction = DIRECTION_RIGHT;

    for (a.s.i = 0; a.s.i < a.m; a.s.i++)
    {
        char* p = strchr(a.items[a.s.i], 'S');

        if (p)
        {
            a.s.j = p - a.items[a.s.i];

            break;
        }
    }

    PriorityQueue q;

    if (priority_queue(&q, 0))
    {
        return EXIT_FAILURE;
    }

    size_t* w = malloc(a.m * a.n * MAX_DIRECTION * sizeof * w);

    printf("%zu\n", dijkstra(w, &q, &a));
    finalize_priority_queue(&q);
    free(w);

    return EXIT_SUCCESS;
}
