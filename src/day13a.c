// day13a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Claw Contraption

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifndef DAY13
#define DAY13
#define N 2
#define BUFFER_SIZE 256
#endif

static void swap_row(double a[N][N + 1], unsigned int i, unsigned int j)
{
    for (unsigned int k = 0; k < N + 1; k++)
    {
        double x = a[i][k];

        a[i][k] = a[j][k];
        a[j][k] = x;
    }
}

static unsigned int forward_elimination(double a[N][N + 1])
{
    for (unsigned int k = 0; k < N; k++)
    {
        unsigned int i_max = k;
        double v_max = a[i_max][k];

        for (unsigned int i = k + 1; i < N; i++)
        {
            if (fabs(a[i][k]) > v_max)
            {
                v_max = a[i][k];
                i_max = i;
            }
        }

        if (!a[k][i_max])
        {
            return k;
        }

        if (i_max != k)
        {
            swap_row(a, k, i_max);
        }

        for (int i = k + 1; i < N; i++)
        {
            double f = a[i][k] / a[k][k];

            for (int j = k + 1; j < N + 1; j++)
            {
                a[i][j] -= a[k][j] * f;
            }

            a[i][k] = 0;
        }
    }

    return N;
}

static void back_substitution(double x[N], double a[N][N + 1])
{
    for (unsigned int i = N - 1; i != UINT_MAX; i--)
    {
        x[i] = a[i][N];

        for (unsigned int j = i + 1; j < N; j++)
        {
            x[i] -= a[i][j] * x[j];
        }
        
        x[i] /= a[i][i];
    }
}

static bool integer_solution(double x[N], const int a[N][N + 1])
{
    for (unsigned int i = 0; i < N; i++)
    {
        x[i] = round(x[i]);
    }

    for (unsigned int i = 0; i < N; i++)
    {
        int left = 0;

        for (unsigned int j = 0; j < N; j++)
        {
            left += x[j] * a[i][j];
        }

        if (left != a[i][N])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    char buffer[BUFFER_SIZE];
    long result[N] = { 0 };

    while (fgets(buffer, BUFFER_SIZE, stdin))
    {
        int ia[N][N + 1];

        if (sscanf(buffer, "Button A: X+%d, Y+%d", ia[0], ia[1]) != 2)
        {
            continue;
        }

        if (!fgets(buffer, BUFFER_SIZE, stdin))
        {
            break;
        }

        if (sscanf(buffer, "Button B: X+%d, Y+%d", ia[0] + 1, ia[1] + 1) != 2)
        {
            continue;
        }

        if (!fgets(buffer, BUFFER_SIZE, stdin))
        {
            break;
        }

        if (sscanf(buffer, "Prize: X=%d, Y=%d", ia[0] + N, ia[1] + N) != 2)
        {
            continue;
        }

        double a[N][N + 1];

        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = 0; j < N + 1; j++)
            {
                a[i][j] = ia[i][j];
            }
        }

        if (forward_elimination(a) != N)
        {
            continue;
        }

        double x[N];

        back_substitution(x, a);

        if (!integer_solution(x, ia))
        {
            continue;
        }

        result[0] += x[0];
        result[1] += x[1];
    }

    printf("%ld\n", 3 * result[0] + result[1]);

    return 0;
}
