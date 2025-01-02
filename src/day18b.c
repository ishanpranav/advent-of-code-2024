// day18a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// RAM Run

#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#ifndef DAY18
#define DAY18
#define DIMENSION 7
#endif
#define queue_is_empty(instance) ((instance)->first == -1)

struct Point
{
    unsigned int x;
    unsigned int y;
};

typedef struct Point Point;

struct DisjointSet
{
    Point parents[DIMENSION][DIMENSION];
};

struct Stack
{
    unsigned int count;
    Point items[DIMENSION * DIMENSION];
};

typedef struct DisjointSet DisjointSet;
typedef struct Stack Stack;

static void disjoint_set(DisjointSet* instance)
{
    Point u;

    for (u.x = 0; u.x < DIMENSION; u.x++)
    {
        for (u.y = 0; u.y < DIMENSION; u.y++)
        {
            instance->parents[u.x][u.y] = u;
        }
    }
}

static Point disjoint_set_find(DisjointSet* instance, Point u)
{
    Point parent = instance->parents[u.x][u.y];

    if (u.x == parent.x && u.y == parent.y)
    {
        return u;
    }

    return disjoint_set_find(instance, parent);
}

static bool disjoint_set_disjoint(DisjointSet* instance, Point u, Point v)
{
    printf("are they disjoint? (%u,%u) and (%u,%u)\n", u.x, u.y, v.x, v.y);

    printf("parent of (%u,%u): ", u.x, u.y);
    u = disjoint_set_find(instance, u);
    printf("(%u,%u)\n", u.x, u.y);
    printf("parent of (%u,%u): ", v.x, v.y);
    v = disjoint_set_find(instance, v);
    printf("(%u,%u)\n", v.x, v.y);

    return u.x != v.x || u.y != v.y;
}

static void disjoint_set_union(DisjointSet* instance, Point u, Point v)
{
    u = disjoint_set_find(instance, u);
    v = disjoint_set_find(instance, v);
    instance->parents[u.x][u.y] = v;
}

static void stack(Stack* instance)
{
    instance->count = 0;
}

static void stack_push(Stack* instance, Point item)
{
    instance->items[instance->count] = item;
    instance->count++;
}

static Point stack_pop(Stack* instance)
{
    instance->count--;

    return instance->items[instance->count];
}

static void main_step(
    DisjointSet* p,
    Point u,
    const bool set[DIMENSION][DIMENSION])
{
    Point v;

    v = u;
    v.x--;

    if (v.x < DIMENSION && !set[v.x][v.y])
    {
        disjoint_set_union(p, u, v);
    }

    v = u;
    v.x++;

    if (v.x < DIMENSION && !set[v.x][v.y])
    {
        disjoint_set_union(p, u, v);
    }

    v = u;
    v.y--;

    if (v.y < DIMENSION && !set[v.x][v.y])
    {
        disjoint_set_union(p, u, v);
    }

    v = u;
    v.y++;

    if (v.y < DIMENSION && !set[v.x][v.y])
    {
        disjoint_set_union(p, u, v);
    }
}

int main()
{
    Stack pointStack;

    stack(&pointStack);

    Point u;
    bool pointSet[DIMENSION][DIMENSION] = { 0 };

    while (scanf("%u,%u ", &u.x, &u.y) == 2)
    {
        stack_push(&pointStack, u);

        pointSet[u.x][u.y] = true;
    }

    DisjointSet p;

    disjoint_set(&p);

    for (u.x = 0; u.x < DIMENSION; u.x++)
    {
        for (u.y = 0; u.y < DIMENSION; u.y++)
        {
            if (pointSet[u.x][u.y])
            {
                continue;
            }

            main_step(&p, u, pointSet);
        }
    }

    u.x = UINT_MAX;
    u.y = UINT_MAX;

    Point s = { .x = 0, .y = 0 };
    Point t = { .x = DIMENSION - 1, .y = DIMENSION - 1 };

    while (disjoint_set_disjoint(&p, s, t))
    {
        u = stack_pop(&pointStack);
        printf("top of stack is %u,%u\n", u.x, u.y);
        pointSet[u.x][u.y] = false;

        main_step(&p, u, pointSet);
    }

    printf("%u,%u\n", u.x, u.y);

    return 0;
}
