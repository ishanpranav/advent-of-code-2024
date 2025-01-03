// day22a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Monkey Market

#include <stdio.h>
#define MASK 0xffffffl

int main()
{
    unsigned long long n;
    unsigned long long sum = 0;

    while (scanf("%llu", &n) == 1)
    {
        for (unsigned int i = 0; i < 2000; i++)
        {
            n = (n ^ (n << 6)) & MASK;
            n = (n ^ (n >> 5)) & MASK;
            n = (n ^ (n << 11)) & MASK;
        }

        sum += n;
    }

    printf("%llu\n", sum);

    return 0;
}
