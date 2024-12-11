// day09a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Disk Fragmenter

// NOTE: With `MAX_READ = 32768` and `MAX_BLOCKS = (MAX_READ * 9)`, the program
// cannot be stored on the stack.

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_READ 32768
#define MAX_BLOCKS (MAX_READ * 9)

static void main_update(
    size_t* checksum,
    size_t* offset,
    size_t id,
    unsigned int size)
{
    size_t k = *offset;

    *checksum += id * (size * (k + k + size - 1)) / 2;
    *offset = k + size;
}

static size_t main_step(char buffer[MAX_READ], size_t read)
{
    size_t left = 0;
    size_t right = read - 2 + (read % 2);
    unsigned int needed = buffer[right] - '0';
    size_t offset = 0;
    size_t result = 0;

    while (left < right)
    {
        main_update(&result, &offset, left / 2, buffer[left] - '0');

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

            main_update(&result, &offset, right / 2, size);

            available -= size;
            needed -= size;
        }
    }

    main_update(&result, &offset, right / 2, needed);

    return result;
}

int main()
{
    char buffer[MAX_READ];
    size_t read = fread(buffer, 1, MAX_READ, stdin);

    while (read && isspace(buffer[read - 1]))
    {
        read--;
    }

    size_t* blocks = malloc(MAX_BLOCKS * sizeof * blocks);

    if (!blocks)
    {
        return 1;
    }

    size_t id = 0;
    size_t blockCount = 0;

    for (size_t i = 0; i < read; i++)
    {
        for (char j = 0; j < buffer[i] - '0'; j++)
        {
            blocks[blockCount] = id;
            blockCount++;
        }

        id++;
        i++;

        if (i >= read)
        {
            break;
        }

        for (char j = 0; j < buffer[i] - '0'; j++)
        {
            blocks[blockCount] = SIZE_MAX;
            blockCount++;
        }
    }

    size_t checksum = main_step(buffer, read);

    free(blocks);
    printf("%zu\n", checksum);
}
