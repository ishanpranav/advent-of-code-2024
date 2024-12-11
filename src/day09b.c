// day09a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Disk Fragmenter

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 32768

typedef int (*Comparer)(const void* left, const void* right);

struct PriorityQueue
{
    int (*priorityComparer)(const void* left, const void* right);
    
    void* items;
    void* priorities;
    size_t itemSize;
    size_t prioritySize;
    size_t count;
    size_t capacity;
};

typedef struct PriorityQueue* PriorityQueue;

int priority_queue(
    PriorityQueue instance,
    size_t itemSize,
    size_t prioritySize,
    size_t capacity,
    Comparer priorityComparer)
{
    if (capacity < 4)
    {
        capacity = 4;
    }

    instance->items = malloc((capacity + 1) * itemSize);

    if (!instance->items)
    {
        return -1;
    }

    instance->priorities = malloc((capacity + 1) * prioritySize);

    if (!instance->priorities)
    {
        free(instance->items);

        return -1;
    }

    instance->itemSize = itemSize;
    instance->prioritySize = prioritySize;
    instance->count = 0;
    instance->capacity = capacity;
    instance->priorityComparer = priorityComparer;

    return 0;
}

int priority_queue_ensure_capacity(
    PriorityQueue instance,
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

    void* newItems = realloc(
        instance->items,
        (newCapacity + 1) * instance->itemSize);

    if (!newItems)
    {
        return -1;
    }

    void* newPriorities = realloc(
        instance->priorities,
        (newCapacity + 1) * instance->prioritySize);

    if (!newPriorities)
    {
        instance->items = realloc(
            instance->items,
            (instance->capacity + 1) * instance->itemSize);

        return -1;
    }

    instance->capacity = newCapacity;
    instance->items = newItems;
    instance->priorities = newPriorities;

    return 0;
}

int priority_queue_enqueue(
    PriorityQueue instance,
    void* item,
    void* priority)
{
    int ex = priority_queue_ensure_capacity(
        instance,
        instance->count + 1);

    if (ex)
    {
        return ex;
    }

    instance->count++;

    char* p = instance->items;
    char* q = instance->priorities;
    size_t i = instance->count;
    size_t itemSize = instance->itemSize;
    size_t prioritySize = instance->prioritySize;
    Comparer compare = instance->priorityComparer;

    while (i != 1 && compare(priority, q + (i / 2) * prioritySize) < 0)
    {
        size_t j = i / 2;

        memcpy(p + i * itemSize, p + j * itemSize, itemSize);
        memcpy(q + i * prioritySize, q + j * prioritySize, prioritySize);

        i = j;
    }

    if (item)
    {
        memcpy(p + i * itemSize, item, instance->itemSize);
    }

    if (priority)
    {
        memcpy(q + i * prioritySize, priority, instance->prioritySize);
    }

    return 0;
}

bool priority_queue_try_dequeue(
    PriorityQueue instance,
    void* item,
    void* priority)
{
    size_t i = 1;
    size_t child = 2;

    if (!instance->count)
    {
        return false;
    }

    char* p = instance->items;
    char* q = instance->priorities;
    size_t itemSize = instance->itemSize;
    size_t prioritySize = instance->prioritySize;
    Comparer compare = instance->priorityComparer;

    if (item)
    {
        memcpy(item, p + itemSize, itemSize);
    }

    if (priority)
    {
        memcpy(priority, q + prioritySize, prioritySize);
    }

    memcpy(p, p + instance->count * itemSize, itemSize);
    memcpy(q, q + instance->count * prioritySize, prioritySize);

    while (child < instance->count)
    {
        if (child < instance->count - 1 && compare(
            q + child * prioritySize, 
            q + (child + 1) * prioritySize) > 0)
        {
            child++;
        }

        if (compare(q, q + child * prioritySize) <= 0)
        {
            break;
        }

        memcpy(p + i * itemSize, p + child * itemSize, itemSize);
        memcpy(q + i * prioritySize, q + child * prioritySize, prioritySize);

        i = child;
        child *= 2;
    }

    memcpy(p + i * itemSize, p, itemSize);
    memcpy(q + i * prioritySize, q, prioritySize);

    instance->count--;

    return true;
}

void priority_queue_clear(PriorityQueue instance)
{
    instance->count = 0;
}

void finalize_priority_queue(PriorityQueue instance)
{
    priority_queue_clear(instance);
    free(instance->items);
    free(instance->priorities);

    instance->items = NULL;
    instance->itemSize = 0;
    instance->priorities = NULL;
    instance->prioritySize = 0;
    instance->capacity = 0;
    instance->priorityComparer = NULL;
}

static int cmp(const void* left, const void* right) 
{
    size_t p = *(const size_t*)left;
    size_t q = *(const size_t*)right;

    if (p < q) { return -1; }
    if (p > q) { return 1; }

    return 0;
}

int main()
{
    char buffer[BUFFER_SIZE];
    size_t read = fread(buffer, 1, BUFFER_SIZE, stdin);
    struct PriorityQueue queues[10];

    while (read && isspace(buffer[read - 1]))
    {
        read--;
    }

    for (unsigned int i = 0; i < 10; i++)
    {
        priority_queue(queues + i, sizeof(size_t), sizeof(size_t), 0, cmp);
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
            priority_queue_enqueue(queues + size, &offset, &offset);
        }
        
        offset += size;
        left++;
    }

    size_t right = read - 2 + (read % 2);
    size_t checksum = 0;

    while (right != SIZE_MAX)
    {
        unsigned int s = buffer[right] - '0';

        offset -= s;

        size_t nextOffset = offset;
        size_t nextIndex = SIZE_MAX;

        for (unsigned int i = s; i < 10; i++)
        {
            if (queues[i].count)
            {
                size_t* items = (size_t*)queues[i].items + 1;

                if (*items < nextOffset)
                {
                    nextOffset = *items;
                    nextIndex = i;
                }
            }
        }

        checksum += (right / 2) * (s * (nextOffset + nextOffset + s - 1)) / 2;

        if (nextIndex != SIZE_MAX)
        {
            priority_queue_try_dequeue(queues + nextIndex, NULL, NULL);

            unsigned long long to = nextIndex - s;
        
            if (to > 0)
            {
                size_t value = nextOffset + s;
    
                priority_queue_enqueue(queues + to, &value, &value);
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

    printf("%zu\n", checksum);

    return 0;
}
