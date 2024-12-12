// day09a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Disk Fragmenter

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef DAY09
#define DAY09
#define BUFFER_SIZE 32768
#endif

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
    size_t checksum = 0;
    size_t offset = 0;
    unsigned int needed = buffer[right] - '0';

    while (left < right)
    {
        unsigned int size = buffer[left] - '0';

        checksum += left * (size * (offset + offset + size - 1));
        offset += size;

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

            if (needed < available)
            {
                size = needed;
            }
            else
            {
                size = available;
            }

            checksum += right * (size * (offset + offset + size - 1));
            offset += size;
            available -= size;
            needed -= size;
        }
    }

    checksum += right * (needed * (offset + offset + needed - 1));
    offset += needed;
    
    printf("%zu\n", checksum / 4);

    return 0;
}
