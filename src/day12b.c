// day12b.c
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
    size_t m;
    size_t n;
    char items[MAX_M][MAX_N];
};

struct Shape
{
    size_t area;
    size_t edges;
};

typedef struct Matrix Matrix;
typedef struct Shape Shape;

static Shape depth_first_search(
    bool d[MAX_M][MAX_N],
    const Matrix* a,
    size_t i,
    size_t j)
{
    size_t m = a->m;
    size_t n = a->n;
    char w = a->items[i][j];
    bool up = i - 1 < m && a->items[i - 1][j] == w;
    bool upLeft = i - 1 < m && j - 1 < n && a->items[i - 1][ j - 1] == w;
    bool upRight = i - 1 < m && j + 1 < n && a->items[i - 1][j + 1] == w;
    bool left = j - 1 < n && a->items[i][j - 1] == w;
    bool right = j + 1 < n && a->items[i][j + 1] == w;
    bool down = i + 1 < m && a->items[i + 1][j] == w;
    bool downLeft = i + 1 < m && j - 1 < n && a->items[i + 1][j - 1] == w;
    bool downRight = i + 1 < m && j + 1 < n && a->items[i + 1][j + 1] == w;

    Shape result = { .area = 1 };

    if ((!up && !right) || (up && right && !upRight))
    {
        result.edges++;
    }

    if ((!up && !left) || (up && left &&!upLeft))
    {
        result.edges++;    
    }

    if ((!down && !right) || (down && right && !downRight))
    {
        result.edges++;
    }
    
    if ((!down && !left) || (down && left && !downLeft))
    {
        result.edges++;
    }

    if (up && !d[i - 1][j])
    {
        d[i - 1][j] = true;

        Shape shape = depth_first_search(d, a, i - 1, j);

        result.area += shape.area;
        result.edges += shape.edges;
    }

    if (down && !d[i + 1][j])
    {
        d[i + 1][j] = true;

        Shape shape = depth_first_search(d, a, i + 1, j);

        result.area += shape.area;
        result.edges += shape.edges;
    }

    if (left && !d[i][j - 1])
    {
        d[i][j - 1] = true;

        Shape shape = depth_first_search(d, a, i, j - 1);

        result.area += shape.area;
        result.edges += shape.edges;
    }

    if (right && !d[i][j + 1])
    {
        d[i][j + 1] = true;

        Shape shape = depth_first_search(d, a, i, j + 1);

        result.area += shape.area;
        result.edges += shape.edges;
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
    bool d[MAX_M][MAX_N] = { 0 };

    for (size_t i = 0; i < a.m; i++)
    {
        for (size_t j = 0; j < a.n; j++)
        {
            if (!d[i][j])
            {
                d[i][j] = true;

                Shape shape = depth_first_search(d, &a, i, j);

                result += shape.area * shape.edges;
            }
        }
    }

    printf("%zu\n", result);

    return 0;
}
