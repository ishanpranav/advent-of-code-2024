// day19a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Linen Layout

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifndef DAY19
#define DAY19
#define BUFFER_SIZE 4096
#define MAX_N 64
#define POOL_SIZE 1024
#endif

enum Color
{
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_WHITE,
    COLOR_BLACK,
    MAX_COLOR
};

typedef struct Trie Trie;

struct Trie
{
    bool leaf;
    Trie* children[MAX_COLOR];
};

struct TriePool
{
    unsigned int count;
    Trie items[POOL_SIZE];
};

typedef enum Color Color;
typedef struct TriePool TriePool;

static Color color(char value)
{
    switch (value)
    {
    case 'r': return COLOR_RED;
    case 'g': return COLOR_GREEN;
    case 'u': return COLOR_BLUE;
    case 'b': return COLOR_BLACK;
    case 'w': return COLOR_WHITE;
    default: return MAX_COLOR;
    }
}

static void trie_pool(TriePool* instance)
{
    instance->count = 0;
}

static void trie_add(Trie* instance, TriePool* pool, const char* item)
{
    Trie* current = instance;

    for (; *item; item++)
    {
        unsigned int index = color(*item);

        if (!current->children[index])
        {
            Trie* child = pool->items + pool->count;

            memset(child, 0, sizeof * child);

            pool->count++;
            current->children[index] = child;
        }

        current = current->children[index];
    }

    current->leaf = true;
}

int main()
{
    char buffer[BUFFER_SIZE];
    unsigned int x = 0;
    TriePool pool;

    trie_pool(&pool);

    if (fgets(buffer, BUFFER_SIZE, stdin))
    {
        Trie t = { 0 };

        for (char* p = strtok(buffer, ", \r\n"); p; p = strtok(NULL, ", \r\n"))
        {
            trie_add(&t, &pool, p);
        }

        char b[MAX_N];

        while (fgets(b, MAX_N, stdin))
        {
            size_t n = strlen(b);

            while (n && isspace(b[n - 1]))
            {
                n--;
            }

            if (!n)
            {
                continue;
            }

            bool d[MAX_N];

            d[0] = true;

            memset(d + 1, 0, n * sizeof * d);

            for (size_t i = 0; i < n; i++)
            {
                if (!d[i])
                {
                    continue;
                }

                const Trie* current = &t;

                for (size_t k = 0; k < n - i; k++)
                {
                    current = current->children[color(b[i + k])];

                    if (!current)
                    {
                        break;
                    }

                    if (current->leaf)
                    {
                        d[i + k + 1] |= d[i];
                    }
                }
            }

            if (d[n])
            {
                x++;
            }
        }
    }

    printf("%u\n", x);

    return 0;
}
