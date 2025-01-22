// day24a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Crossed Wires

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef DAY24
#define DAY24
#define BUFFER_SIZE 16
#define MAX_VERTICES 10240
#endif

enum Opcode
{
    OPCODE_EQUAL,
    OPCODE_AND,
    OPCODE_OR,
    OPCODE_XOR
};

typedef enum Opcode Opcode;

struct Entry
{
    char value;
    char left[3];
    char right[3];
    char name[3];
    Opcode opcode;
};

typedef struct Entry Entry;

struct Dictionary
{
    unsigned int count;
    Entry entries[MAX_VERTICES];
};

typedef struct Dictionary Dictionary;

static char dictionary_get(Dictionary* instance, const char name[3])
{
    for (unsigned int i = 0; i < instance->count; i++)
    {
        if (memcmp(instance->entries[i].name, name, 3) == 0)
        {
            return instance->entries[i].value;
        }
    }

    return CHAR_MAX;
}

static void dictionary_add(Dictionary* instance, const char name[3], char value)
{
    memcpy(&instance->entries[instance->count].name, name, 3);

    instance->entries[instance->count].value = value;
    instance->count++;
}

static void dictionary_set(Dictionary* instance, const char name[3], char value)
{
    for (unsigned int i = 0; i < instance->count; i++)
    {
        if (memcmp(instance->entries[i].name, name, 3) == 0)
        {
            instance->entries[i].value = value;

            return;
        }
    }

    dictionary_add(instance, name, value);
}

static Opcode opcode(const char* value)
{
    if (strcmp(value, "AND") == 0)
    {
        return OPCODE_AND;
    }

    if (strcmp(value, "OR") == 0)
    {
        return OPCODE_OR;
    }

    if (strcmp(value, "XOR") == 0)
    {
        return OPCODE_XOR;
    }

    return OPCODE_EQUAL;
}

int main()
{
    char buffer[BUFFER_SIZE];
    char u[3];
    Dictionary nodes;

    nodes.count = 0;

    while (fgets(buffer, BUFFER_SIZE, stdin))
    {
        int value;

        if (sscanf(buffer, "%c%c%c: %d", u, u + 1, u + 2, &value) != 4)
        {
            break;
        }

        dictionary_add(&nodes, u, value);
    }

    char opstring[4];
    char v[3];
    char w[3];

    while (scanf("%c%c%c %s %c%c%c -> %c%c%c ",
        u, u + 1, u + 2,
        opstring,
        v, v + 1, v + 2,
        w, w + 1, w + 2) == 10)
    {
        if (w[0] == 'z')
        {
            dfs(&nodes);
        }
    }

    unsigned int x = 0;

    // for (unsigned int i = 0; i < n; i++)
    // {
    //     printf("%c%c%c: %d\n",
    //         vertices[i].name[0],
    //         vertices[i].name[1],
    //         vertices[i].name[2],
    //         vertices[i].value);
    // }

    printf("%u\n", x);

    return 0;
}
