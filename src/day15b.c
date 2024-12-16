// day15a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Warehouse Woes

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#ifndef DAY15
#define DAY15
#define MAX_M 64
#define MAX_N 128
#define BUFFER_SIZE 1024
#endif

struct Coordinate
{
    size_t i;
    size_t j;
};

typedef struct Coordinate Coordinate;

struct Matrix
{
    char items[MAX_M][MAX_N];
    size_t m;
    size_t n;
    Coordinate s;
};

typedef struct Matrix Matrix;

static void main_update(Matrix* a, size_t i, size_t j, int di)
{
    if (a->items[i][j] == ']')
    {
        j--;
    }

    if (a->items[i + di][j] == '[' && a->items[i + di][j + 1] == ']')
    {
        main_update(a, i + di, j, di);
    }

    if (a->items[i + di][j] == ']')
    {
        main_update(a, i + di, j - 1, di);
    }

    if (a->items[i + di][j + 1] == '[')
    {
        main_update(a, i + di, j + 1, di);
    }

    a->items[i][j] = '.';
    a->items[i][j + 1] = '.';
    a->items[i + di][j] = '[';
    a->items[i + di][j + 1] = ']';
}

static bool main_test(const Matrix* a, size_t i, size_t j, int di)
{
    if (a->items[i][j] == ']')
    {
        j--;
    }

    char left = a->items[i + di][j];
    char right = a->items[i + di][j + 1];

    if (left == '#' || right == '#')
    {
        return false;
    }

    if (left == '.' && right == '.')
    {
        return true;
    }

    if (left == '[' && main_test(a, i + di, j, di))
    {
        return true;
    }

    if (left == '.' && right == '[' && main_test(a, i + di, j + 1, di))
    {
        return true;
    }

    if (left == ']' && right == '.' && main_test(a, i + di, j - 1, di))
    {
        return true;
    }

    return left == ']' && right == '[' &&
        main_test(a, i + di, j + 1, di) &&
        main_test(a, i + di, j - 1, di);
}

static void main_read(Matrix* a)
{
    char* p = strchr(a->items[a->m], '@');

    if (p)
    {
        a->s.i = a->m;
        a->s.j = p - a->items[a->m];
        *p = '.';
    }
}

static void main_move_row(Matrix* a, int di)
{
    switch (a->items[a->s.i + di][a->s.j])
    {
    case '#': return;

    case '.':
        a->s.i += di;
        break;

    case '[':
    case ']':
        if (main_test(a, a->s.i + di, a->s.j, di))
        {
            main_update(a, a->s.i + di, a->s.j, di);

            a->s.i += di;
        }
        break;
    }
}

static void main_move_column(Matrix* a, int dj)
{
    switch (a->items[a->s.i][a->s.j + dj])
    {
    case '#': return;

    case '.':
        a->s.j += dj;
        break;

    case '[':
    case ']':
    {
        char* items = a->items[a->s.i];
        size_t j = a->s.j;
        size_t count = 0;

        do
        {
            j += dj;
            count++;
        }
        while (items[j + dj] == '[' || items[j + dj] == ']');

        if (items[j + dj] != '.')
        {
            return;
        }

        for (size_t k = j; k != a->s.j; k -= dj)
        {
            items[k + dj] = items[k];
        }

        a->s.j += dj;
        items[a->s.j] = '.';
    }
    break;
    }
}

static void main_step(Matrix* a, char opcode)
{
    switch (opcode)
    {
    case '^':
        main_move_row(a, -1);
        break;

    case 'v':
        main_move_row(a, 1);
        break;

    case '<':
        main_move_column(a, -1);
        break;

    case '>':
        main_move_column(a, 1);
        break;
    }
}

int main()
{
    Matrix a;

    a.m = 0;
    a.n = 0;

    if (fgets(a.items[0], MAX_N / 2, stdin))
    {
        a.n = strlen(a.items[0]);

        while (a.n && isspace(a.items[0][a.n - 1]))
        {
            a.n--;
        }

        main_read(&a);

        a.m++;

        while (fgets(a.items[a.m], MAX_N / 2, stdin))
        {
            if (isspace(*a.items[a.m]))
            {
                break;
            }

            main_read(&a);

            a.m++;
        }
    }

    a.s.j *= 2;

    for (size_t i = 0; i < a.m; i++)
    {
        for (size_t j = a.n - 1; j != SIZE_MAX; j--)
        {
            if (a.items[i][j] == 'O')
            {
                a.items[i][2 * j] = '[';
                a.items[i][2 * j + 1] = ']';
            }
            else
            {
                a.items[i][2 * j] = a.items[i][j];
                a.items[i][2 * j + 1] = a.items[i][j];
            }
        }
    }

    a.n *= 2;

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, stdin))
    {
        for (const char* p = buffer; *p; p++)
        {
            main_step(&a, *p);
        }
    }

    size_t sum = 0;

    for (size_t i = 0; i < a.m; i++)
    {
        for (size_t j = 0; j < a.n; j++)
        {
            if (a.items[i][j] == '[')
            {
                sum += i * 100 + j;
            }
        }
    }

    printf("%zu\n", sum);

    return 0;
}
