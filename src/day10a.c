// day10a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Hoof It

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define MAX_M 8
#define MAX_N 8

int main()
{
    char a[MAX_M][MAX_N];
    size_t m = 0;
    size_t n = 0;
    size_t s = 0;

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

    for (size_t s = 0; i < )

    printf("%zu\n", x);

    return 0;
}
