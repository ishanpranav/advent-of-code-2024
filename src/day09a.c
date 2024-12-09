// day09a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Disk Fragmenter

#include <stdint.h> // size_max
#include <stdio.h>
#include <stdlib.h> // deque
#define BUFFER_SIZE 32768

struct Entry;

typedef struct Entry Entry;

struct Entry
{
    size_t id;
    Entry* next;
    Entry* previous;
};

struct Deque
{
    // size_t count;
    Entry* first;
    Entry* last;
};

typedef struct Deque Deque;

void deque_add_last(Deque* instance, size_t id)
{
    Entry* added = malloc(sizeof * added);

    added->id = id;
    added->next = NULL;
    added->previous = instance->last;

    if (instance->last)
    {
        instance->last->next = added;
    }
    else
    {
        instance->first = added;
    }

    instance->last = added;
    // instance->count++;
}

void deque_remove_first(Deque* instance)
{
    if (!instance->first)
    {
        return;
    }

    Entry* removed = instance->first;

    instance->first = instance->first->next;

    if (instance->first)
    {
        instance->first->previous = NULL;
    }
    else
    {
        instance->last = NULL;
    }

    free(removed);

    // instance->count--;
}

void deque_remove_last(Deque* instance)
{
    if (!instance->last)
    {
        return;
    }

    Entry* removed = instance->last;

    instance->last = instance->last->previous;

    if (instance->last)
    {
        instance->last->next = NULL;
    }
    else
    {
        instance->first = NULL;
    }

    free(removed);

    // instance->count--;
}

int main()
{
    char buffer[BUFFER_SIZE];
    size_t read = fread(buffer, 1, BUFFER_SIZE - 1, stdin);

    buffer[read] = '\0';

    Deque blocks = { 0 };
    size_t id = 0;

    for (size_t i = 0; i < read; i++)
    {
        for (char j = 0; j < buffer[i] - '0'; j++)
        {
            deque_add_last(&blocks, id);
        }

        id++;
        i++;
        
        if (i >= read)
        {
            break;
        }

        for (char j = 0; j < buffer[i] - '0'; j++)
        {
            deque_add_last(&blocks, SIZE_MAX);
        }
    }

    size_t i = 0;
    size_t checksum = 0;

    while (blocks.first)
    {
        size_t id = blocks.first->id;

        deque_remove_first(&blocks);

        while (id == SIZE_MAX && blocks.last)
        {
            id = blocks.last->id;

            deque_remove_last(&blocks);
        }

        if (id != SIZE_MAX)
        {
            checksum += i * id;
            i++;
        }
    }

    printf("%zu\n", checksum);
}
