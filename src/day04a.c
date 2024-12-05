// day04a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Ceres Search

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

typedef struct Matrix Matrix;

static bool main_step(Matrix* a, size_t i, size_t j, int di, int dj)
{
    for (char* p = "XMAS"; *p; p++)
    {
        if (i >= a->m || j >= a->n || a->items[i][j] != *p)
        {
            return false;
        }

        i += di;
        j += dj;
    }

    return true;
}

int main()
{
    Matrix a;
    
    a.m = 0;
    a.n = 0;

    if (fgets(a.items[0], MAX_N, stdin))
    {
        a.m++;
        a.n = strlen(a.items[0]);

        while (a.n > 0 && isspace(a.items[0][a.n - 1]))
        {
            a.n--;
        }

        while (fgets(a.items[a.m], MAX_N, stdin))
        {
            a.m++;
        }
    }

    size_t count = 0;

    for (size_t i = 0; i < a.m; i++)
    {
        for (size_t j = 0; j < a.n; j++)
        {
            if (main_step(&a, i, j, 1, 0))
            {
                count++;
            }

            if (main_step(&a, i, j, -1, 0))
            {
                count++;
            }

            if (main_step(&a, i, j, 0, -1))
            {
                count++;
            }

            if (main_step(&a, i, j, 0, 1))
            {
                count++;
            }

            if (main_step(&a, i, j, 1, 1))
            {
                count++;
            }

            if (main_step(&a, i, j, 1, -1))
            {
                count++;
            }

            if (main_step(&a, i, j, -1, 1))
            {
                count++;
            }

            if (main_step(&a, i, j, -1, -1))
            {
                count++;
            }
        }
    }

    printf("%zu\n", count);

    return 0;
}
