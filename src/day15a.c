// day15a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Warehouse Woes

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#ifndef DAY15
#define DAY15
#define MAX_M 64
#define MAX_N 64
#define BUFFER_SIZE 1024
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
};

typedef struct Grid Grid;

static void main_move(Grid* a, int di, int dj)
{
    switch (a->items[a->s.i + di][a->s.j + dj])
    {
    case '#': return;

    case '.':
        a->s.i += di;
        a->s.j += dj;
        break;

    case 'O':
    {
        Coordinate t = a->s;

        do
        {
            t.i += di;
            t.j += dj;
        }
        while (a->items[t.i + di][t.j + dj] == 'O');

        if (a->items[t.i + di][t.j + dj] != '.')
        {
            return;
        }

        a->items[t.i + di][t.j + dj] = 'O';
        a->s.i += di;
        a->s.j += dj;
        a->items[a->s.i][a->s.j] = '.';
    }
    break;
    }
}

static void main_step(Grid* a, char opcode)
{
    switch (opcode)
    {
    case '^':
        main_move(a, -1, 0);
        break;

    case 'v':
        main_move(a, 1, 0);
        break;

    case '<':
        main_move(a, 0, -1);
        break;

    case '>':
        main_move(a, 0, 1);
        break;
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

    for (size_t i = 0; i < m; i++)
    {
        char* p = strchr(a.items[i], '@');

        if (p)
        {
            *p = '.';
            a.s.i = i;
            a.s.j = p - a.items[i];

            break;
        }
    }

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, stdin))
    {
        for (const char* p = buffer; *p; p++)
        {
            main_step(&a, *p);
        }
    }

    size_t sum = 0;

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (a.items[i][j] == 'O')
            {
                sum += i * 100 + j;
            }
        }
    }

    printf("%zu\n", sum);

    return 0;
}
