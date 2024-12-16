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
    Coordinate s;
    Coordinate t;
};

typedef struct Grid Grid;

static void main_read(Grid* a, size_t i, size_t j)
{
    char* p = strchr(a->items[i], 'S');
    char* q = strchr(a->items[i], 'E');

    if (p)
    {
        a->s.i = i;
        a->s.j = p - a->items[i];
    }

    if (q)
    {
        a->t.i = i;
        a->t.j = q - a->items[i];
    }
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


    printf("%d\n", 0);

    return 0;
}
