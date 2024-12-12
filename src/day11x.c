// day11x.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Plutonian Pebbles

#include <math.h>
#include <stdio.h>
#ifndef DAY11
#define DAY11
#define K 25
#endif
#define MAX_LIST 2 << 20

unsigned long list[MAX_LIST][K];
unsigned long count = 0;

unsigned long main_step(unsigned long n, unsigned int k)
{
    if (k == 0)
    {
        return 1;
    }

    if (n == 0)
    {
        return main_step(1, k - 1);
    }

    if (n < MAX_LIST && list[n][k] != 0)
    {
        return list[n][k];
    }

    unsigned int d = log10(n) + 1;

    if (d % 2 == 0)
    {
        unsigned long mask = pow(10, d / 2);
        unsigned long a = main_step(n % mask, k - 1);
        unsigned long b = main_step(n / mask, k - 1);

        if (n < MAX_LIST)
        {
            list[n][k] = a + b;
        }

        return a + b;
    }

    unsigned long a = main_step(2024 * n, k - 1);

    if (n < MAX_LIST)
    {
        list[n][k] = a;
    }

    return a;
}

int main()
{
    unsigned long n;
    unsigned long sum = 0;

    while (scanf("%lu", &n) == 1)
    {
        sum += main_step(n, K);
    }

    printf("%lu\n", sum);

    return 0;
}
