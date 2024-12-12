// day11x.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Plutonian Pebbles

#include <stdio.h>
#ifndef DAY11
#define DAY11
#define N 25
#endif

unsigned long main_step(unsigned long n)
{
    
}

int main()
{
    unsigned long n;
    unsigned long sum = 0;

    while (scanf("%u", &n) == 1)
    {
        sum += main_step(n);
    }

    printf("%u\n", sum);

    return 0;
}
