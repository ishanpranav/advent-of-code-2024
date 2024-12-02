// day01a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Historian Hysteria

#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1024

static int main_compare(const void* p, const void* q)
{
    long a = *(const long*)p;
    long b = *(const long*)q;

    if (a < b)
    {
        return -1;
    }

    if (a > b)
    {
        return 1;
    }

    return 0;
}

int main()
{
    long a[MAX_N];
    long b[MAX_N];
    unsigned int n = 0;

    while (scanf("%ld %ld ", a + n, b + n) == 2)
    {
        n++;
    }

    qsort(a, n, sizeof * a, main_compare);
    qsort(b, n, sizeof * b, main_compare);
    
    unsigned long sum = 0;

    for (unsigned int i = 0; i < n; i++)
    {
        sum += labs(a[i] - b[i]);
    }

    printf("%lu\n", sum);

    return 0;
}
