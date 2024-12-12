// day11x.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Plutonian Pebbles

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef DAY11
#define DAY11
#define K 25
#define MAX_LOAD_FACTOR 1.0
#endif
#define HASH_PRIMES_COUNT 26

typedef struct Entry Entry;

struct Entry
{
    unsigned long long key;
    unsigned long long value;
    Entry* nextEntry;
};

struct Dictionary
{
    Entry** entries;
    size_t count;
    size_t capacity;
};

typedef struct Dictionary Dictionary;

/** See https://planetmath.org/goodhashtableprimes. */
static const size_t HASH_PRIMES[HASH_PRIMES_COUNT] = 
{
    53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157l, 98317l,
    196613l, 393241l, 786433l, 1572869l, 3145739l, 6291469l, 12582917l,
    25165843l, 50331653l, 100663319l, 201326611l, 402653189l, 805306457l,
    1610612741l
};

static size_t binary_search_min(size_t min, const size_t* items, size_t length)
{
    if (!length)
    {
        return min;
    }

    size_t left = 0;
    size_t right = length - 1;

    while (left < right)
    {
        size_t index = left + (right - left) / 2;

        if (items[index] < min)
        {
            left = index + 1;
        }
        else if (items[index] > min)
        {
            right = index;
        }
        else
        {
            return items[index];
        }
    }

    return items[right];
}

static size_t dictionary_min_capacity(size_t capacity)
{
    if (capacity < HASH_PRIMES[0])
    {
        return HASH_PRIMES[0];
    }

    return capacity;
}

static size_t dictionary_new_capacity(size_t count, size_t capacity)
{
    capacity *= 1.5;

    size_t prime = binary_search_min(capacity, HASH_PRIMES, HASH_PRIMES_COUNT);
    
    if (prime > capacity)
    {
        capacity = prime;
    }

    if (count > capacity)
    {
        return count;
    }

    return capacity;
}

static int dictionary(Dictionary* instance, size_t capacity)
{
    instance->capacity = dictionary_min_capacity(capacity);
    instance->entries = calloc(instance->capacity, sizeof * instance->entries);

    if (!instance->entries)
    {
        return -1;
    }

    instance->count = 0;

    return 0;
}

static unsigned long long dictionary_get(
    const Dictionary* instance,
    unsigned long long key)
{
    size_t i = key % instance->capacity;

    for (Entry* entry = instance->entries[i]; entry; entry = entry->nextEntry)
    {
        if (entry->key == key)
        {
            return entry->value;
        }
    }

    return 0;
}

static void dictionary_clear(Dictionary* instance)
{
    for (size_t i = 0; i < instance->capacity; i++)
    {
        Entry* current = instance->entries[i];

        while (current)
        {
            Entry* next = current->nextEntry;

            free(current);

            current = next;
        }

        instance->entries[i] = NULL;
    }

    instance->count = 0;
}

static void finalize_dictionary(Dictionary* instance)
{
    dictionary_clear(instance);
    free(instance->entries);

    instance->entries = NULL;
    instance->capacity = 0;
}

static int dictionary_copy(Dictionary* result, const Dictionary* instance);

static int dictionary_set(
    Dictionary* instance, 
    unsigned long long key, 
    unsigned long long value)
{
    size_t i = key % instance->capacity;
    size_t chainLength = 0;
    Entry** p;

    for (p = instance->entries + i; *p; p = &(*p)->nextEntry)
    {
        chainLength++;

        if ((*p)->key == key)
        {
            (*p)->value = value;

            return 0;
        }
    }

    Entry* entry = malloc(sizeof * entry);

    if (!entry)
    {
        return -1;
    }

    entry->key = key;
    entry->value = value;
    entry->nextEntry = NULL;
    *p = entry;
    instance->count++;

    if ((double)instance->count / instance->capacity > MAX_LOAD_FACTOR)
    {
        Dictionary clone;

        if (dictionary_copy(&clone, instance))
        {
            return 0;
        }

        finalize_dictionary(instance);
        
        *instance = clone;
    }

    return 0;
}

static int dictionary_copy(Dictionary* result, const Dictionary* instance)
{
    size_t capacity = instance->capacity;
    size_t newCapacity = dictionary_new_capacity(instance->count, capacity);
    int ex = dictionary(result, newCapacity);

    if (ex)
    {
        return ex;
    }

    for (size_t i = 0; i < capacity; i++)
    {
        for (Entry* p = instance->entries[i]; p; p = p->nextEntry)
        {
            ex = dictionary_set(result, p->key, p->value);

            if (ex)
            {
                finalize_dictionary(result);

                return ex;
            }
        }
    }

    return 0;
}

static unsigned long long main_step(
    Dictionary tables[K],
    unsigned int k,
    unsigned long long n)
{
    if (k == 0)
    {
        return 1;
    }

    if (n == 0)
    {
        return main_step(tables, k - 1, 1);
    }

    unsigned long long result = dictionary_get(tables + k - 1, n);

    if (result)
    {
        return result;
    }

    unsigned int d = log10(n) + 1;

    if (d % 2 == 0)
    {
        unsigned long mask = pow(10, d / 2);
        unsigned long a = main_step(tables, k - 1, n % mask);
        unsigned long b = main_step(tables, k - 1, n / mask);

        dictionary_set(tables + k - 1, n, a + b);

        return a + b;
    }

    unsigned long a = main_step(tables, k - 1, 2024 * n);

    dictionary_set(tables + k - 1, n, a);

    return a;
}

int main()
{
    unsigned long long n;
    unsigned long long sum = 0;
    Dictionary tables[K];

    for (unsigned int k = 0; k < K; k++)
    {
        if (dictionary(tables + k, 0))
        {
            return 1;
        }
    }

    while (scanf("%llu", &n) == 1)
    {
        sum += main_step(tables, K, n);
    }

    for (unsigned int k = 0; k < K; k++)
    {
        finalize_dictionary(tables + k);
    }

    printf("%llu\n", sum);

    return 0;
}
