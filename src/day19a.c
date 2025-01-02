// day19a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Linen Layout

#include <stdlib.h>

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifndef DAY19
#define BUFFER_SIZE 4096
#define MAX_N 64
#endif

typedef struct Trie Trie;

struct Trie
{
    bool leaf;
    Trie* children[26];
};

static void trie_add(Trie* instance, const char* item)
{
    Trie* current = instance;

    for (; *item; item++)
    {
        unsigned int index = *item - 'a';

        if (!current->children[index])
        {
            Trie* child = calloc(1, sizeof * child);

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

    if (fgets(buffer, BUFFER_SIZE, stdin))
    {
        Trie t = { 0 };

        for (char* p = strtok(buffer, ", \r\n"); p; p = strtok(NULL, ", \r\n"))
        {
            trie_add(&t, p);
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
                    current = current->children[(unsigned int)(b[i + k] - 'a')];

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
