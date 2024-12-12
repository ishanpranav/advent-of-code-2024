// day06b.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Guard Gallivant

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX_M 256
#define MAX_N 256

struct Matrix
{
    char items[MAX_M][MAX_N];
    size_t m;
    size_t n;
};

struct Coordinate
{
    size_t i;
    size_t j;
};

enum Hits
{
    HITS_NONE = 0,
    HITS_SPACE = 0x01,
    HITS_UP = 0x02,
    HITS_DOWN = 0x04,
    HITS_LEFT = 0x08,
    HITS_RIGHT = 0x10
};

typedef struct Coordinate Coordinate;
typedef struct Matrix Matrix;
typedef enum Hits Hits;

size_t main_step(Coordinate results[], const Matrix* a, Coordinate s)
{
    int di = -1;
    int dj = 0;
    size_t resultCount = 0;
    Hits b[MAX_M][MAX_N] = { 0 };
    Hits color = HITS_UP;

    for (;;)
    {
        if (!b[s.i][s.j])
        {
            if (results)
            {
                results[resultCount] = s;
            }

            resultCount++;
            b[s.i][s.j] = HITS_SPACE;
        }

        if (s.i + di >= a->m || s.j + dj >= a->n)
        {
            break;
        }

        while (a->items[s.i + di][s.j + dj] == '#')
        {
            if (b[s.i + di][s.j + dj] & color)
            {
                return 0;
            }

            b[s.i + di][s.j + dj] |= color;

            if (di == -1)
            {
                di = 0;
                dj = 1;
                color = HITS_RIGHT;
            }
            else if (di == 1)
            {
                di = 0;
                dj = -1;
                color = HITS_LEFT;
            }
            else if (dj == -1)
            {
                di = -1;
                dj = 0;
                color = HITS_UP;
            }
            else if (dj == 1)
            {
                di = 1;
                dj = 0;
                color = HITS_DOWN;
            }
        }

        s.i += di;
        s.j += dj;
    }

    return resultCount;
}

static void main_read(Coordinate* s, const Matrix* a)
{
    char* p = strchr(a->items[a->m], '^');

    if (p)
    {
        s->i = a->m;
        s->j = p - a->items[a->m];
    }
}

int main()
{
    Matrix a;

    a.m = 0;
    a.n = 0;

    Coordinate s = { 0 };

    if (fgets(a.items[0], MAX_N, stdin))
    {
        a.n = strlen(a.items[0]);

        while (a.n && isspace(a.items[0][a.n - 1]))
        {
            a.n--;
        }

        main_read(&s, &a);

        a.m++;

        while (fgets(a.items[a.m], MAX_N, stdin))
        {
            main_read(&s, &a);

            a.m++;
        }
    }

    Coordinate results[MAX_M * MAX_N];
    size_t resultCount = main_step(results, &a, s);
    size_t count = 0;

    for (size_t k = 0; k < resultCount; k++)
    {
        char c = a.items[results[k].i][results[k].j];

        a.items[results[k].i][results[k].j] = '#';

        if (main_step(NULL, &a, s) == 0)
        {
            count++;
        }

        a.items[results[k].i][results[k].j] = c;
    }

    printf("%zu\n", count);

    return 0;
}
