// day04b.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Ceres Search

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifndef DAY04
#define DAY04
#define MAX_M 256
#define MAX_N 256
#endif

struct Matrix
{
    char items[MAX_M][MAX_N];
    size_t m;
    size_t n;
};

typedef struct Matrix Matrix;

static bool main_step(const Matrix* a, size_t i, size_t j, int di, int dj)
{
    for (const char* p = "MAS"; *p; p++)
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

static size_t main_count(const Matrix* a)
{
    if (a->m < 3 || a->n < 3)
    {
        return 0;
    }

    size_t count = 0;

    for (size_t i = 1; i < a->m - 1; i++)
    {
        for (size_t j = 1; j < a->n - 1; j++)
        {
            if (main_step(a, i - 1, j - 1, 1, 1) +
                main_step(a, i - 1, j + 1, 1, -1) +
                main_step(a, i + 1, j - 1, -1, 1) +
                main_step(a, i + 1, j + 1, -1, -1) == 2)
            {
                count++;
            }
        }
    }

    return count;
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

        while (a.n && isspace(a.items[0][a.n - 1]))
        {
            a.n--;
        }

        while (fgets(a.items[a.m], MAX_N, stdin))
        {
            a.m++;
        }
    }

    printf("%zu\n", main_count(&a));

    return 0;
}
