// day03a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Mull It Over

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef DAY03
#define DAY03
#define BUFFER_SIZE 32768
#endif

int main()
{
    char buffer[BUFFER_SIZE];
    size_t read = fread(buffer, 1, BUFFER_SIZE - 1, stdin);

    buffer[read] = '\0';

    char* line = buffer;
    long sum = 0;

    while ((line = strstr(line, "mul(")))
    {
        line += 4;

        long x = strtol(line, &line, 10);

        if (*line != ',')
        {
            continue;
        }

        line++;

        long y = strtol(line, &line, 10);

        if (*line != ')')
        {
            continue;
        }

        sum += x * y;
    }

    printf("%ld\n", sum);

    return 0;
}
