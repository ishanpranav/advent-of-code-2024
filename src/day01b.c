// day01a.c
// Licensed under the MIT license.
// Copyright (c) 2024-2025 Ishan Pranav

// Historian Histeria

#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1024
#define MAX_VALUE 131072

int main()
{
    long a[MAX_N];
    long b[MAX_N];
    unsigned int c[MAX_VALUE] = { 0 };
    unsigned int n = 0;

    while (scanf("%ld %ld ", a + n, b + n) == 2)
    {
        c[b[n]]++;
        n++;
    }

    unsigned long sum = 0;

    for (unsigned int i = 0; i < n; i++)
    {
        sum += a[i] * c[a[i]];
    }

    printf("%lu\n", sum);

    return 0;
}
