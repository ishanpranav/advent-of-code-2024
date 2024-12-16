// day16a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Reindeer Maze

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#ifndef DAY16
#define DAY16
#define MAX_M 32
#define MAX_N 32
#endif

struct Coordinate
{
    size_t i;
    size_t j;
};

typedef struct Coordinate Coordinate;

struct Grid
{
    char items[MAX_M][MAX_N];
};

typedef struct Grid Grid;

static Coordinate main_find(const Grid* a, size_t m, char value)
{
    Coordinate u = { 0 };

    for (; u.i < m; u.i++)
    {
        char* p = strchr(a->items[u.i], value);

        if (p)
        {
            u.j = p - a->items[u.i];

            return u;
        }
    }

    return u;
}

int main()
{
    Grid a;
    size_t m = 0;
    size_t n = 0;

    if (fgets(a.items[0], MAX_N, stdin))
    {
        n = strlen(a.items[0]);

        while (n && isspace(a.items[0][n - 1]))
        {
            n--;
        }

        m++;

        while (fgets(a.items[m], MAX_N, stdin))
        {
            if (isspace(*a.items[m]))
            {
                break;
            }

            m++;
        }
    }

    Coordinate s = main_find(&a, m, 'S');
    Coordinate t = main_find(&a, m, 'E');

    printf("%d s = (%zu, %zu), t = (%zu, %zu)\n", 0, s.i, s.j, t.i, t.j);

    return 0;
}
