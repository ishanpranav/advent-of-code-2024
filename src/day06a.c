// day06a.c
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
    size_t m;
    size_t n;
    char items[MAX_M][MAX_N];
};

struct Coordinate
{
    size_t i;
    size_t j;
};

typedef struct Matrix Matrix;
typedef struct Coordinate Coordinate;

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

    int di = -1;
    int dj = 0;
    size_t k = 0;
    bool b[MAX_M][MAX_N] = { 0 };

    for (;;)
    {
        if (!b[s.i][s.j])
        {
            k++;
            b[s.i][s.j] = true;
        }

        if (s.i + di >= a.m || s.j + dj >= a.n)
        {
            break;
        }

        while (a.items[s.i + di][s.j + dj] == '#')
        {
            if (di == 1)
            {
                di = 0;
                dj = -1;
            }
            else if (di == -1)
            {
                di = 0;
                dj = 1;
            }
            else if (dj == 1)
            {
                di = 1;
                dj = 0;
            }
            else if (dj == -1)
            {
                di = -1;
                dj = 0;
            }
        }

        s.i += di;
        s.j += dj;
    }

    printf("%zu\n", k);

    return 0;
}
