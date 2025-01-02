// day12a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Garden Groups

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifndef DAY12
#define DAY12
#define MAX_M 256
#define MAX_N 256
#endif

struct Matrix
{
    char items[MAX_M][MAX_N];
    size_t m;
    size_t n;
};

struct Shape
{
    size_t area;
    size_t perimeter;
};

typedef struct Matrix Matrix;
typedef struct Shape Shape;

static Shape depth_first_search(
    bool d[MAX_M][MAX_N],
    const Matrix* a,
    size_t i,
    size_t j)
{
    char w = a->items[i][j];
    Shape result = { .area = 1 };

    if (i - 1 >= a->m || a->items[i - 1][j] != w)
    {
        result.perimeter++;
    }

    if (i + 1 >= a->m || a->items[i + 1][j] != w)
    {
        result.perimeter++;
    }

    if (j - 1 >= a->n || a->items[i][j - 1] != w)
    {
        result.perimeter++;
    }

    if (j + 1 >= a->n || a->items[i][j + 1] != w)
    {
        result.perimeter++;
    }

    if (i - 1 < a->m && !d[i - 1][j] && a->items[i - 1][j] == w)
    {
        d[i - 1][j] = true;

        Shape shape = depth_first_search(d, a, i - 1, j);

        result.area += shape.area;
        result.perimeter += shape.perimeter;
    }

    if (i + 1 < a->m && !d[i + 1][j] && a->items[i + 1][j] == w)
    {
        d[i + 1][j] = true;

        Shape shape = depth_first_search(d, a, i + 1, j);

        result.area += shape.area;
        result.perimeter += shape.perimeter;
    }

    if (j - 1 < a->n && !d[i][j - 1] && a->items[i][j - 1] == w)
    {
        d[i][j - 1] = true;

        Shape shape = depth_first_search(d, a, i, j - 1);

        result.area += shape.area;
        result.perimeter += shape.perimeter;
    }

    if (j + 1 < a->n && !d[i][j + 1] && a->items[i][j + 1] == w)
    {
        d[i][j + 1] = true;

        Shape shape = depth_first_search(d, a, i, j + 1);

        result.area += shape.area;
        result.perimeter += shape.perimeter;
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

    size_t result = 0;
    bool d[MAX_M][MAX_N];

    for (size_t i = 0; i < a.m; i++)
    {
        memset(d[i], 0, sizeof * d[i] * a.n);
    }

    for (size_t i = 0; i < a.m; i++)
    {
        for (size_t j = 0; j < a.n; j++)
        {
            if (!d[i][j])
            {
                d[i][j] = true;

                Shape shape = depth_first_search(d, &a, i, j);

                result += shape.area * shape.perimeter;
            }
        }
    }

    printf("%zu\n", result);

    return 0;
}
