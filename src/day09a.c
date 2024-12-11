// day09a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Disk Fragmenter

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 32768

static void main_step(
    size_t* checksum,
    size_t* offset,
    size_t id,
    unsigned int size)
{
    size_t k = *offset;

    *checksum += id * (size * (k + k + size - 1)) / 2;
    *offset = k + size;
}

int main()
{
    char buffer[BUFFER_SIZE];
    size_t read = fread(buffer, 1, BUFFER_SIZE, stdin);

    while (read && isspace(buffer[read - 1]))
    {
        read--;
    }

    size_t left = 0;
    size_t right = read - 2 + (read % 2);
    unsigned int needed = buffer[right] - '0';
    size_t offset = 0;
    size_t checksum = 0;

    while (left < right)
    {
        main_step(&checksum, &offset, left / 2, buffer[left] - '0');

        unsigned int available = buffer[left + 1] - '0';

        left += 2;

        while (available > 0)
        {
            if (needed == 0)
            {
                if (left == right)
                {
                    break;
                }

                right -= 2;
                needed = buffer[right] - '0';
            }

            size_t size;

            if (needed < available)
            {
                size = needed;
            }
            else
            {
                size = available;
            }

            main_step(&checksum, &offset, right / 2, size);

            available -= size;
            needed -= size;
        }
    }

    main_step(&checksum, &offset, right / 2, needed);
    printf("%zu\n", checksum);

    return 0;
}
