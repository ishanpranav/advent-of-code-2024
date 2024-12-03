// day02b.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Red-Nosed Reports

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 32
#define MAX_LENGTH 8

struct List
{
    unsigned int length;
    int items[MAX_LENGTH];
};

typedef struct List List;

static void list_remove_at(List* result, const List* instance, unsigned int i)
{
    const int* items = instance->items;
    int length = instance->length;

    memcpy(result->items, items, i * sizeof * items);
    memcpy(result->items + i, items + i + 1, (length - i) * sizeof * items);

    result->length = length - 1;
}

static int sgn(int x)
{
    if (x < 0)
    {
        return -1;
    }

    if (x > 0)
    {
        return 1;
    }

    return 0;
}

static unsigned int main_step(List* l)
{
    if (!l->length)
    {
        return 0;
    }

    int s = 0;

    for (unsigned int i = 1; i < l->length; i++)
    {
        int difference = l->items[i] - l->items[i - 1];
        unsigned int absolute = abs(difference);

        if (absolute < 1 || absolute > 3)
        {
            return i;
        }

        int sign = sgn(difference);

        if (s)
        {
            if (sign != s)
            {
                return i;
            }
        }
        else
        {
            s = sign;
        }
    }

    return 0;
}

int main()
{
    char buffer[BUFFER_SIZE];
    unsigned int count = 0;

    while (fgets(buffer, sizeof buffer, stdin))
    {
        char* line = buffer;
        List l;
        int offset;

        l.length = 0;

        while (sscanf(line, "%d%n", l.items + l.length, &offset) == 1)
        {
            line += offset;
            l.length++;
        }

        unsigned int i = main_step(&l);

        if (i == 0)
        {
            count++;

            continue;
        }

        List copy;

        list_remove_at(&copy, &l, i - 1);

        if (main_step(&copy) == 0)
        {
            count++;

            continue;
        }

        list_remove_at(&copy, &l, i);

        if (main_step(&copy) == 0)
        {
            count++;
        }
    }

    printf("%u\n", count);

    return 0;
}
