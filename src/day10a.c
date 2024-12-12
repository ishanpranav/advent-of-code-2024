// day10a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Hoof It

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX_M 64
#define MAX_N 64

struct Coordinate
{
    size_t i;
    size_t j;
};

typedef struct Coordinate Coordinate;

struct Stack
{
    Coordinate vertices[MAX_M * MAX_N];
    size_t size;
};

typedef struct Stack Stack;

static void stack(Stack* s)
{
    s->size = 0;
}

static void stack_push(Stack* s, size_t i, size_t j)
{
    s->vertices[s->size].i = i;
    s->vertices[s->size].j = j;
    s->size++;
}

static Coordinate stack_pop(Stack* s)
{
    s->size--;

    return s->vertices[s->size];
}

int main()
{
    char a[MAX_M][MAX_N];
    size_t m = 0;
    size_t n = 0;

    if (fgets(a[0], MAX_N, stdin))
    {
        n = strlen(a[0]);

        while (n && isspace(a[0][n - 1]))
        {
            n--;
        }

        m++;

        while (fgets(a[m], MAX_N, stdin))
        {
            m++;
        }
    }

    size_t x = 0;

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (a[i][j] != '0')
            {
                continue;
            }

            Stack s;

            stack(&s);
            stack_push(&s, i, j);

            bool d[MAX_M][MAX_N] = { 0 };
            Coordinate parent[MAX_M][MAX_N];

            for (size_t ii = 0; ii < m; ii++) {
                for (size_t jj = 0; jj < n; jj++) {
                    parent[ii][jj].i = -1;
                }
            }

            while (s.size)
            {
                Coordinate u = stack_pop(&s);
                char w = a[u.i][u.j];

                if (w == '9')
                {
                    Coordinate v = parent[u.i][u.j];

                    printf("(%zu, %zu)", u.i, u.j);
                    while (v.i != (size_t)-1) {
                        printf(" <- (%zu, %zu)", v.i, v.j);
                        v = parent[v.i][v.j];
                    }
                    printf("\n");

                    x++;
                }

                if (u.i - 1 < m && a[u.i - 1][u.j] - w == 1 && !d[u.i - 1][u.j])
                {
                    stack_push(&s, u.i - 1, u.j);

                    d[u.i - 1][u.j] = true;
                    parent[u.i - 1][u.j] = u;
                }

                if (u.i + 1 < m && a[u.i + 1][u.j] - w == 1 && !d[u.i + 1][u.j])
                {
                    stack_push(&s, u.i + 1, u.j);

                    d[u.i + 1][u.j] = true;
                    parent[u.i + 1][u.j] = u;
                }

                if (u.j - 1 < n && a[u.i][u.j - 1] - w == 1 && !d[u.i][u.j - 1])
                {
                    stack_push(&s, u.i, u.j - 1);

                    d[u.i][u.j - 1] = true;
                    parent[u.i][u.j - 1] = u;
                }

                if (u.j + 1 < n && a[u.i][u.j + 1] - w == 1 && !d[u.i][u.j + 1])
                {
                    stack_push(&s, u.i, u.j + 1);

                    d[u.i][u.j + 1] = true;
                    parent[u.i][u.j + 1] = u;
                }
            }
        }
    }

    printf("%zu\n", x);

    return 0;
}