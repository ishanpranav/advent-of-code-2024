// day02a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Red-Nosed Reports

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef DAY02
#define DAY02
#define BUFFER_SIZE 32
#endif

static int sgn(int x)
{
    if (x < 0)
    {
        return -1;
    }

    if (x > 0)
    {
        return 1;
    }

    return 0;
}

static bool main_step(const char* line)
{
    int l[2];
    unsigned int offset;

    if (sscanf(line, "%d%n", l, &offset) != 1)
    {
        return true;
    }

    line += offset;

    int s = 0;

    while (sscanf(line, "%d%n", l + 1, &offset) == 1)
    {
        int difference = l[1] - l[0];
        int absolute = abs(difference);

        if (absolute < 1 || absolute > 3)
        {
            return false;
        }

        int sign = sgn(difference);

        if (s)
        {
            if (sign != s)
            {
                return false;
            }
        }
        else
        {
            s = sign;
        }

        line += offset;
        l[0] = l[1];
    }

    return true;
}

int main()
{
    char buffer[BUFFER_SIZE];
    unsigned int n = 0;

    while (fgets(buffer, sizeof buffer, stdin))
    {
        if (main_step(buffer))
        {
            n++;
        }
    }

    printf("%u\n", n);

    return 0;
}
