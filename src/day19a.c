// day19a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Linen Layout

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifndef DAY19
#define BUFFER_SIZE 4096
#define MAX_PREFIXES 512
#define MAX_N 64
#endif

struct Trie
{
    unsigned int count;
    char items[MAX_PREFIXES][MAX_N];
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

int main()
{
    char buffer[BUFFER_SIZE];
    unsigned int x = 0;

    if (fgets(buffer, BUFFER_SIZE, stdin))
    {
        Trie t;

        trie(&t);

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

            for (size_t k = 1; k <= n; k++)
            {
                for (unsigned int j = 0; j < t.count; j++)
                {
                    const char* a = t.items[j];
                    size_t m = strlen(a);

                    if (m > k)
                    {
                        continue;
                    }

                    if (memcmp(b + k - m, a, m) == 0)
                    {
                        d[k] |= d[k - m];
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
