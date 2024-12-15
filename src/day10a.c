// day10b.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Hoof It

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifndef DAY10
#define DAY10
#define MAX_M 64
#define MAX_N 64
#endif

struct Matrix
{
    char items[MAX_M][MAX_N];
    size_t m;
    size_t n;
};

typedef struct Matrix Matrix;

static size_t depth_first_search(
    bool d[MAX_M][MAX_N],
    const Matrix* a,
    size_t i,
    size_t j)
{
    char w = a->items[i][j];

    if (w == '9')
    {
        return 1;
    }

    size_t result = 0;

    if (i - 1 < a->m && !d[i - 1][j] && a->items[i - 1][j] - w == 1)
    {
        d[i - 1][j] = true;
        result += depth_first_search(d, a, i - 1, j);
    }

    if (i + 1 < a->m && !d[i + 1][j] && a->items[i + 1][j] - w == 1)
    {
        d[i + 1][j] = true;
        result += depth_first_search(d, a, i + 1, j);
    }

    if (j - 1 < a->n && !d[i][j - 1] && a->items[i][j - 1] - w == 1)
    {
        d[i][j - 1] = true;
        result += depth_first_search(d, a, i, j - 1);
    }

    if (j + 1 < a->n && !d[i][j + 1] && a->items[i][j + 1] - w == 1)
    {
        d[i][j + 1] = true;
        result += depth_first_search(d, a, i, j + 1);
    }

    return result;
}

int main()
{
    Matrix a;

    a.m = 0;
    a.n = 0;

    if (fgets(a.items[0], MAX_N, stdin))
    {
        a.n = strlen(a.items[0]);

        while (a.n && isspace(a.items[0][a.n - 1]))
        {
            a.n--;
        }

        a.m++;

        while (fgets(a.items[a.m], MAX_N, stdin))
        {
            a.m++;
        }
    }

    size_t x = 0;

    for (size_t i = 0; i < a.m; i++)
    {
        for (size_t j = 0; j < a.n; j++)
        {
            if (a.items[i][j] != '0')
            {
                continue;
            }

            bool d[MAX_M][MAX_N] = { 0 };

            x += depth_first_search(d, &a, i, j);
        }
    }

    printf("%zu\n", x);

    return 0;
}
