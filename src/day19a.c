// day19a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Linen Layout

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifndef DAY19
#define BUFFER_SIZE 32
#define MAX_PREFIXES 8
#define MAX_PREFIX_LENGTH 4
#endif

struct Trie
{
    unsigned int count;
    char items[MAX_PREFIXES][MAX_PREFIX_LENGTH];
};

typedef struct Trie Trie;

static void trie(Trie* instance)
{
    instance->count = 0;
}

static void trie_add(Trie* instance, char* item)
{
    strcpy(instance->items[instance->count], item);

    instance->count++;
}

static bool main_step(const char b[BUFFER_SIZE], size_t n, const Trie* t)
{
    bool d[BUFFER_SIZE];

    d[0] = 1;

    memset(d + 1, 0, n * sizeof * d);

    for (size_t i = 0; i < n; i++)
    {
        if (!d[i])
        {
            continue;
        }

        for ()
        {

        }
    }

    return d[n - 1];
}

int main()
{
    char buffer[BUFFER_SIZE];

    if (!fgets(buffer, BUFFER_SIZE, stdin))
    {
        return 1;
    }

    Trie t;

    trie(&t);

    for (char* p = strtok(buffer, ","); p; p = strtok(NULL, ","))
    {
        trie_add(&t, p);
    }

    unsigned int k = 0;

    while (fgets(buffer, BUFFER_SIZE, stdin))
    {
        size_t n = strlen(buffer);

        while (n && isspace(buffer[n - 1]))
        {
            n--;
        }

        if (!n)
        {
            continue;
        }

        if (main_step(buffer, n, &t))
        {
            k++;
        }
    }

    printf("%u\n", k);

    return 0;
}
