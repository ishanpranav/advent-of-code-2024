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

    unsigned int d = log10(n) + 1;

    if (d % 2 == 0)
    {
        unsigned long mask = pow(10, d / 2);
        unsigned long a = main_step(n % mask, k - 1);
        unsigned long b = main_step(n / mask, k - 1);

        return a + b;
    }

    return main_step(2024 * n, k - 1);
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
