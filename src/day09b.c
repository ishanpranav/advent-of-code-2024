// day09a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Disk Fragmenter

// Algorithm: https://github.com/maneatingape/advent-of-code-rust

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef DAY09
#define DAY09
#define BUFFER_SIZE 32768
#endif

struct PriorityQueue
{
    size_t count;
    size_t capacity;
    size_t* items;
};

typedef struct PriorityQueue PriorityQueue;

static int priority_queue(PriorityQueue* instance, size_t capacity)
{
    if (capacity < 4)
    {
        capacity = 4;
    }

    instance->items = malloc((capacity + 1) * sizeof * instance->items);

    if (!instance->items)
    {
        return -1;
    }

    instance->count = 0;
    instance->capacity = capacity;

    return 0;
}

static size_t priority_queue_peek(const PriorityQueue* instance)
{
    return instance->items[1];
}

static int priority_queue_ensure_capacity(
    PriorityQueue* instance,
    size_t capacity)
{
    if (instance->capacity >= capacity)
    {
        return 0;
    }

    size_t newCapacity = instance->capacity * 2;

    if (capacity > newCapacity)
    {
        newCapacity = capacity;
    }

    size_t* items = instance->items;
    size_t* newItems = realloc(items, (newCapacity + 1) * sizeof * newItems);

    if (!newItems)
    {
        return -1;
    }

    instance->capacity = newCapacity;
    instance->items = newItems;

    return 0;
}

static int priority_queue_enqueue(PriorityQueue* instance, size_t item)
{
    int ex = priority_queue_ensure_capacity(instance, instance->count + 1);

    if (ex)
    {
        return ex;
    }

    instance->count++;

    size_t i = instance->count;

    while (i != 1 && item < instance->items[i / 2])
    {
        size_t j = i / 2;

        instance->items[i] = instance->items[j];
        i = j;
    }

    instance->items[i] = item;

    return 0;
}

static void priority_queue_dequeue(PriorityQueue* instance)
{
    size_t i = 1;
    size_t child = 2;

    instance->items[0] = instance->items[instance->count];

    while (child < instance->count)
    {
        if (child < instance->count - 1 &&
            instance->items[child] > instance->items[child + 1])
        {
            child++;
        }

        if (instance->items[0] <= instance->items[child])
        {
            break;
        }

        instance->items[i] = instance->items[child];
        i = child;
        child *= 2;
    }

    instance->items[i] = instance->items[0];
    instance->count--;
}

static void priority_queue_clear(PriorityQueue* instance)
{
    instance->count = 0;
}

static void finalize_priority_queue(PriorityQueue* instance)
{
    priority_queue_clear(instance);
    free(instance->items);

    instance->items = NULL;
    instance->capacity = 0;
}

int main()
{
    char buffer[BUFFER_SIZE];
    size_t read = fread(buffer, 1, BUFFER_SIZE, stdin);
    struct PriorityQueue queues[9];

    while (read && isspace(buffer[read - 1]))
    {
        read--;
    }

    for (unsigned int i = 1; i <= 9; i++)
    {
        if (priority_queue(queues + i - 1, 0))
        {
            return EXIT_FAILURE;
        }
    }

    size_t offset = 0;
    size_t left = 0;

    while (left < read)
    {
        offset += buffer[left] - '0';
        left++;

        if (left == read)
        {
            break;
        }

        unsigned int size = buffer[left] - '0';

        if (size)
        {
            PriorityQueue* queue = queues + size - 1;

            if (priority_queue_ensure_capacity(queue, queue->count + 1))
            {
                return EXIT_FAILURE;
            }

            queue->items[queue->count] = offset;
            queue->count++;
        }

        offset += size;
        left++;
    }

    size_t right = read - 2 + (read % 2);
    size_t checksum = 0;

    while (right != SIZE_MAX)
    {
        unsigned int size = buffer[right] - '0';

        offset -= size;

        size_t nextOffset = offset;
        size_t nextIndex = SIZE_MAX;

        for (unsigned int i = size; i < 10; i++)
        {
            if (queues[i - 1].count)
            {
                size_t minOffset = priority_queue_peek(queues + i - 1);

                if (minOffset < nextOffset)
                {
                    nextOffset = minOffset;
                    nextIndex = i;
                }
            }
        }

        checksum += right * (size * (nextOffset + nextOffset + size - 1));

        if (nextIndex != SIZE_MAX)
        {
            priority_queue_dequeue(queues + nextIndex - 1);

            size_t to = nextIndex - size;

            if (to)
            {
                if (priority_queue_enqueue(queues + to - 1, nextOffset + size))
                {
                    return EXIT_FAILURE;
                }
            }
        }

        right--;

        if (right == SIZE_MAX)
        {
            break;
        }

        offset -= buffer[right] - '0';
        right--;
    }

    printf("%zu\n", checksum / 4);

    for (unsigned int i = 1; i <= 9; i++)
    {
        finalize_priority_queue(queues + i - 1);
    }

    return EXIT_SUCCESS;
}
