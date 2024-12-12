// day11x.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Plutonian Pebbles

#include <math.h>
#include <stdio.h>
#ifndef DAY11
#define DAY11
#define K 25
#endif
#define MAX_LIST 10000

typedef struct Entry Entry;

struct Entry
{
    unsigned long long n;
    unsigned long long value;
    Entry* nextEntry;
};

struct Dictionary
{
    Entry* entries[K][MAX_LIST];
};

typedef struct Dictionary Dictionary;

unsigned long long dictionary_get(
    Dictionary* instance,
    unsigned int k,
    unsigned long long n)
{
    for (Entry* p = instance->entries[k][n % MAX_LIST]; p; p = p->nextEntry)
    {
        if (p->n == n)
        {
            return p->value;
        }
    }

    return 0;
}

#include <stdlib.h>

void dictionary_set(Dictionary* instance, unsigned int k, unsigned long long n, unsigned long long value)
{
    unsigned long long i = n % MAX_LIST;

    for (Entry* p = instance->entries[k][i]; p; p = p->nextEntry)
    {
        if (p->n == n)
        {
            p->value = value;

            return;
        }
    }
    
    Entry* entry = malloc(sizeof * entry);
    entry->n = n;
    entry->nextEntry = instance->entries[k][i];
    entry->value = value;
    instance->entries[k][i] = entry;
}

unsigned long long main_step(
    Dictionary* table,
    unsigned int k,
    unsigned long long n)
{
    if (k == K)
    {
        return 1;
    }

    if (n == 0)
    {
        return main_step(table, k + 1, 1);
    }

    unsigned long long result = dictionary_get(table, k, n);

    if (result)
    {
        return result;
    }

    unsigned int d = log10(n) + 1;

    if (d % 2 == 0)
    {
        unsigned long mask = pow(10, d / 2);
        unsigned long a = main_step(table, k + 1, n % mask);
        unsigned long b = main_step(table, k + 1, n / mask);

        dictionary_set(table, k, n, a + b);

        return a + b;
    }

    unsigned long a = main_step(table, k + 1, 2024 * n);

    dictionary_set(table, k, n, a);

    return a;
}

int main()
{
    unsigned long long n;
    unsigned long long sum = 0;
    // unsigned long long (*table)[MAX_LIST] = calloc(1, sizeof(unsigned long long[K][MAX_LIST]));
    Dictionary* table = calloc(1, sizeof * table);

    if (!table)
    {
        return 1;
    }

    while (scanf("%llu", &n) == 1)
    {
        sum += main_step(table, 0, n);
    }

    int totalEntries = 0;
    int maxChain = 0;
    int empty = 0;
    unsigned int maxBucket = 0;
    unsigned int minBucket = -1;
    int keys = 0;

    for (unsigned int k = 0; k < K; k++)
    {
        int any = 0;
        unsigned int entries = 0;

        for (unsigned long long i = 0; i < MAX_LIST; i++)
        {
            if (!table->entries[k][i])
            {
                empty++;

                continue;
            }

            any |= 1;
            
            int chain = 0;

            for (Entry* p = table->entries[k][i]; p; p = p->nextEntry)
            {
                entries++;
                totalEntries++;
                chain++;
            }

            if (chain > maxChain)
            {
                maxChain = chain;
            }
        }

        if (any)
        {
            keys++;
        }

        if (entries > maxBucket)
        {
            maxBucket = entries;
        }

        if (entries < minBucket)
        {
            minBucket = entries;
        }
    }

    printf("primary keys: %d / %d (%lf%%)\n", keys, K, 100 * (double)keys / K);
    printf("empty buckets: %d / %d (%lf%%)\n", empty, K * MAX_LIST, 100 * (double)empty / (K * MAX_LIST));
    printf("total entries: %d\n", totalEntries);
    printf("average chain: %lf\n", (double)totalEntries / (K * MAX_LIST - empty));
    printf("max chain: %d\n", maxChain);
    printf("min primary key: %u\n", minBucket);
    printf("average primary key: %lf\n", (double)totalEntries / keys);
    printf("max primary key: %u\n", maxBucket);
    free(table);
    printf("%llu\n", sum);

    return 0;
}
