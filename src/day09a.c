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

static size_t main_step(size_t* blocks, size_t blockCount)
{
    size_t left = 0;
    size_t right = blockCount - 1;
    size_t result = 0;

    while (left < right)
    {
        while (blocks[left] != SIZE_MAX)
        {
            result += left * blocks[left];
            left++;

            if (left == right)
            {
                return result;
            }
        }

        while (blocks[right] == SIZE_MAX)
        {
            right--;

            if (left == right)
            {
                return result;
            }
        }

        result += left * blocks[right];
        left++;
        right--;
    }

    if (left < blockCount && blocks[left] != SIZE_MAX)
    {
        result += left * blocks[left];
    }

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

    size_t checksum = main_step(blocks, blockCount);

    free(blocks);
    printf("%zu\n", checksum);
}
