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
    unsigned int i;
    unsigned int j;
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
    unsigned int m = 0;

    if (fgets(a.items[0], MAX_N, stdin))
    {
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

    for (unsigned int i = 0; i < m; i++)
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

    unsigned long sum = 0;

    for (unsigned int i = 0; i < m; i++)
    {
        for (const char* p = a.items[i]; *p; p++)
        {
            if (*p == 'O')
            {
                sum += i * 100 + (p - a.items[i]);
            }
        }
    }

    printf("%lu\n", sum);

    return 0;
}
