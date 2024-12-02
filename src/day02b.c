// day02b.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Red-Nosed Reports

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 32
#define MAX_LENGTH 8

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

static bool main_step(int items[MAX_LENGTH], unsigned int length)
{
    int sign = 0;

    for (unsigned int j = 1; j < length; j++)
    {
        int difference = items[j] - items[j - 1];
        unsigned int absoluteDifference = abs(difference);

        if (absoluteDifference < 1 || absoluteDifference > 3)
        {
            return false;
        }

        int signDifference = sgn(difference);

        if (sign)
        {
            if (signDifference != sign)
            {
                return false;
            }
        }
        else
        {
            sign = signDifference;
        }
    }

    return true;
}

int main()
{
    int items[MAX_LENGTH];
    char buffer[BUFFER_SIZE];
    unsigned int count = 0;

    while (fgets(buffer, sizeof buffer, stdin))
    {
        char* line = buffer;
        int offset;
        unsigned int length = 0;

        while (sscanf(line, "%d%n", items + length, &offset) == 1)
        {
            line += offset;
            length++;
        }

        if (main_step(items, length))
        {
            count++;
        }
    }

    printf("%u\n", count);

    return 0;
}
