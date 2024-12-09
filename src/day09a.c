// day09a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Disk Fragmenter

// NOTE: With `MAX_BLOCKS = 32768` and `MAX_IDS = (MAX_BLOCKS * 9)`, the program
// cannot be stored on the stack.

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_BLOCKS 32768
#define MAX_IDS (MAX_BLOCKS * 9)

struct Deque
{
    size_t ids[MAX_IDS];
    size_t* first;
    size_t* last;
};

typedef struct Deque Deque;

static Deque* deque()
{
    Deque* result = malloc(sizeof * result);

    result->first = NULL;
    result->last = NULL;

    return result;
}

static void deque_add_last(Deque* instance, size_t id)
{
    if (!instance->last)
    {
        instance->first = instance->ids;
        instance->last = instance->ids;
    }
    else if (instance->last == instance->ids + MAX_IDS - 1)
    {
        instance->last = instance->ids;
    }
    else
    {
        instance->last++;
    }

    *instance->last = id;
}

static void deque_remove_first(Deque* instance)
{
    if (instance->first == instance->last)
    {
        instance->first = NULL;
        instance->last = NULL;
        
        return;
    }

    if (instance->first == instance->ids + MAX_IDS - 1)
    {
        instance->first = instance->ids;

        return;
    }

    instance->first++;
}

static void deque_remove_last(Deque* instance)
{
    if (instance->last == instance->first)
    {
        instance->first = NULL;
        instance->last = NULL;
        
        return;
    }

    if (instance->last == instance->ids)
    {
        instance->last = instance->ids + MAX_IDS - 1;

        return;
    }

    instance->last--;
}

int main()
{
    char buffer[MAX_BLOCKS];
    size_t read = fread(buffer, 1, MAX_BLOCKS, stdin);
    Deque* blocks = deque();

    if (!blocks)
    {
        return 1;
    }

    size_t id = 0;

    for (size_t i = 0; i < read; i++)
    {
        for (char j = 0; j < buffer[i] - '0'; j++)
        {
            deque_add_last(blocks, id);
        }

        id++;
        i++;
        
        if (i >= read)
        {
            break;
        }

        for (char j = 0; j < buffer[i] - '0'; j++)
        {
            deque_add_last(blocks, SIZE_MAX);
        }
    }

    size_t offset = 0;
    size_t checksum = 0;

    while (blocks->first)
    {
        size_t id = *blocks->first;

        deque_remove_first(blocks);

        while (id == SIZE_MAX && blocks->last)
        {
            id = *blocks->last;

            deque_remove_last(blocks);
        }

        if (id != SIZE_MAX)
        {
            checksum += offset * id;
            offset++;
        }
    }

    free(blocks);
    printf("%zu\n", checksum);
}
