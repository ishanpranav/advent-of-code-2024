// day03b.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Mull It Over

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 32768

int main()
{
    char buffer[BUFFER_SIZE];
    size_t read = fread(buffer, 1, BUFFER_SIZE - 1, stdin);

    buffer[read] = '\0';

    long sum = 0;
    bool seek = true;

    for (char* line = buffer; *line; )
    {
        if (!seek)
        {
            if (strncmp(line, "do()", 4) == 0)
            {
                line += 4;
                seek = true;

                continue;
            }

            line++;

            continue;
        }

        if (strncmp(line, "mul(", 4) == 0)
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

            continue;
        }

        if (strncmp(line, "don't()", 7) == 0)
        {
            line += 7;
            seek = false;

            continue;
        }

        line++;
    }

    printf("%ld\n", sum);

    return 0;
}
