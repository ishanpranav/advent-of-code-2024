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
#define MAX_POINTS 12
#endif
#define queue_is_empty(instance) ((instance)->first == -1)

struct Point
{
    unsigned int x;
    unsigned int y;
};

typedef struct Point Point;

struct Queue
{
    int first;
    int last;
    Point items[DIMENSION * DIMENSION];
};

typedef struct Queue Queue;

static void queue(Queue* instance)
{
    instance->first = -1;
    instance->last = -1;
}

static void queue_enqueue(Queue* instance, unsigned int x, unsigned int y)
{
    if (instance->last == -1)
    {
        instance->first = 0;
        instance->last = 0;
    }
    else if (instance->last == DIMENSION * DIMENSION - 1)
    {
        instance->last = 0;
    }
    else
    {
        instance->last++;
    }

    instance->items[instance->last].x = x;
    instance->items[instance->last].y = y;
}

static Point queue_dequeue(Queue* instance)
{
    Point result = instance->items[instance->first];

    if (instance->first == instance->last)
    {
        instance->first = -1;
        instance->last = -1;

        return result;
    }

    if (instance->first == DIMENSION * DIMENSION - 1)
    {
        instance->first = 0;

        return result;
    }

    instance->first++;

    return result;
}

static unsigned int breadth_first_search(unsigned int d[DIMENSION][DIMENSION])
{
    d[0][0] = 0;

    Queue q;

    queue(&q);
    queue_enqueue(&q, 0, 0);

    while (!queue_is_empty(&q))
    {
        Point u = queue_dequeue(&q);

        if (u.x == DIMENSION - 1 && u.y == DIMENSION - 1)
        {
            return d[u.x][u.y];
        }

        if (u.x - 1 < DIMENSION && d[u.x - 1][u.y] == UINT_MAX)
        {
            d[u.x - 1][u.y] = d[u.x][u.y] + 1;

            queue_enqueue(&q, u.x - 1, u.y);
        }

        if (u.x + 1 < DIMENSION && d[u.x + 1][u.y] == UINT_MAX)
        {
            d[u.x + 1][u.y] = d[u.x][u.y] + 1;

            queue_enqueue(&q, u.x + 1, u.y);
        }

        if (u.y - 1 < DIMENSION && d[u.x][u.y - 1] == UINT_MAX)
        {
            d[u.x][u.y - 1] = d[u.x][u.y] + 1;

            queue_enqueue(&q, u.x, u.y - 1);
        }

        if (u.y + 1 < DIMENSION && d[u.x][u.y + 1] == UINT_MAX)
        {
            d[u.x][u.y + 1] = d[u.x][u.y] + 1;

            queue_enqueue(&q, u.x, u.y + 1);
        }
    }

    return UINT_MAX;
}

int main()
{
    Point u;
    unsigned int d[DIMENSION][DIMENSION];

    for (u.x = 0; u.x < DIMENSION; u.x++)
    {
        for (u.y = 0; u.y < DIMENSION; u.y++)
        {
            d[u.x][u.y] = UINT_MAX;
        }
    }

    for (unsigned int k = 0; k < MAX_POINTS; k++)
    {
        if (scanf("%u,%u ", &u.x, &u.y) != 2)
        {
            break;
        }

        d[u.x][u.y] = 0;
    }

    printf("%d\n", breadth_first_search(d));

    return 0;
}
