// day07b.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Bridge Repair

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#ifndef DAY07
#define DAY07
#define BUFFER_SIZE 64
#define MAX_N 16
#endif

unsigned long long concat(unsigned long long left, unsigned long long right)
{
    return left * pow(10, (unsigned int)log10(right) + 1) + right;
}

static bool main_step(
    unsigned long long x, 
    unsigned long long y, 
    unsigned int s[MAX_N],
    unsigned int n)
{
    if (n == 0)
    {
        return x == y;
    }

    if (y > x)
    {
        return false;
    }

    return main_step(x, y + s[0], s + 1, n - 1) ||
        main_step(x, y * s[0], s + 1, n - 1) ||
        main_step(x, concat(y, s[0]), s + 1, n - 1);
}

int main()
{
    unsigned long long sum = 0;
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, stdin))
    {
        const char* line = buffer;
        int offset;
        long long x;

        if (sscanf(line, "%llu:%n", &x, &offset) != 1)
        {
            continue;
        }

        line += offset;

        unsigned int s[MAX_N];
        unsigned int n = 0;

        while (sscanf(line, "%u%n", s + n, &offset) == 1)
        {
            n++;
            line += offset;
        }

        if (main_step(x, 0, s, n))
        {
            sum += x;
        }
    }

    printf("%llu\n", sum);

    return 0;
}
