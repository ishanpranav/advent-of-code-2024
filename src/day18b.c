// day18a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// RAM Run

#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#ifndef DAY18
#define DAY18
#define N 7
#endif

struct Point
{
    unsigned int x;
    unsigned int y;
};

typedef struct Point Point;

struct DisjointSubset
{
    unsigned int count;
    Point parent;
};

typedef struct DisjointSubset DisjointSubset;

struct DisjointSet
{
    DisjointSubset subsets[N][N];
};

struct Stack
{
    unsigned int count;
    Point items[N * N];
};

typedef struct DisjointSet DisjointSet;
typedef struct Stack Stack;

static void disjoint_set(DisjointSet* instance)
{
    Point u;

    for (u.x = 0; u.x < N; u.x++)
    {
        for (u.y = 0; u.y < N; u.y++)
        {
            instance->subsets[u.x][u.y].count = 1;
            instance->subsets[u.x][u.y].parent = u;
        }
    }
}

static Point disjoint_set_find(DisjointSet* instance, Point u)
{
    Point* parent = &instance->subsets[u.x][u.y].parent;

    if (u.x != parent->x || u.y != parent->y)
    {
        *parent = disjoint_set_find(instance, *parent);
    }

    return *parent;
}

static bool disjoint_set_disjoint(DisjointSet* instance, Point u, Point v)
{
    u = disjoint_set_find(instance, u);
    v = disjoint_set_find(instance, v);

    return u.x != v.x || u.y != v.y;
}

static void disjoint_set_union(DisjointSet* instance, Point u, Point v)
{
    u = disjoint_set_find(instance, u);
    v = disjoint_set_find(instance, v);

    if (u.x == v.x && u.y == v.y)
    {
        return;
    }

    DisjointSubset* uSet = instance->subsets[u.x] + u.y;
    DisjointSubset* vSet = instance->subsets[v.x] + v.y;

    if (uSet->count < vSet->count)
    {
        uSet->parent = v;
        vSet->count += uSet->count;
    }
    else
    {
        vSet->parent = u;
        uSet->count += vSet->count;
    }
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
    const bool set[N][N])
{
    Point v;

    v = u;
    v.x--;

    if (v.x < N && !set[v.x][v.y])
    {
        disjoint_set_union(p, u, v);
    }

    v = u;
    v.x++;

    if (v.x < N && !set[v.x][v.y])
    {
        disjoint_set_union(p, u, v);
    }

    v = u;
    v.y--;

    if (v.y < N && !set[v.x][v.y])
    {
        disjoint_set_union(p, u, v);
    }

    v = u;
    v.y++;

    if (v.y < N && !set[v.x][v.y])
    {
        disjoint_set_union(p, u, v);
    }
}

int main()
{
    Stack pointStack;

    stack(&pointStack);

    Point u;
    bool pointSet[N][N] = { 0 };

    while (scanf("%u,%u ", &u.x, &u.y) == 2)
    {
        stack_push(&pointStack, u);

        pointSet[u.x][u.y] = true;
    }

    DisjointSet p;

    disjoint_set(&p);

    for (u.x = 0; u.x < N; u.x++)
    {
        for (u.y = 0; u.y < N; u.y++)
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
    Point t = { .x = N - 1, .y = N - 1 };

    while (disjoint_set_disjoint(&p, s, t))
    {
        u = stack_pop(&pointStack);
        pointSet[u.x][u.y] = false;

        main_step(&p, u, pointSet);
    }

    printf("%u,%u\n", u.x, u.y);

    return 0;
}
