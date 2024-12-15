// day11x.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Plutonian Pebbles

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef DAY11
#define DAY11
#define K 25
#define K_PRIME 101
#define MIN_CAPACITY 0
#define MIN_BUCKET_COUNT 0
#define MAX_LOAD_FACTOR 1.0
#endif
#define HASH_PRIMES_COUNT 26
#define hash(k, n) (n * K_PRIME + k)

typedef struct Entry Entry;

struct Entry
{
    unsigned int k;
    unsigned long long n;
    unsigned long long value;
    size_t nextEntry;
};

struct Dictionary
{
    Entry* entries;
    size_t* buckets;
    size_t count;
    size_t capacity;
    size_t bucketCount;
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

static size_t dictionary_next_prime(size_t count, size_t capacity)
{
    capacity *= 2;

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

static int dictionary(Dictionary* instance, size_t capacity, size_t bucketCount)
{
    if (capacity < 4)
    {
        capacity = 4;
    }

    instance->capacity = capacity;
    instance->entries = malloc(capacity * sizeof * instance->entries);

    if (!instance->entries)
    {
        return -1;
    }

    if (bucketCount < HASH_PRIMES[0])
    {
        bucketCount = HASH_PRIMES[0];
    }

    instance->bucketCount = bucketCount;
    instance->buckets = calloc(bucketCount, sizeof * instance->buckets);

    if (!instance->buckets)
    {
        free(instance->entries);

        return -1;
    }

    instance->count = 0;

    return 0;
}

static unsigned long long dictionary_get(
    const Dictionary* instance,
    unsigned int k,
    unsigned long long n)
{
    size_t i = hash(k, n) % instance->bucketCount;
    const size_t* buckets = instance->buckets;
    const Entry* entries = instance->entries;

    for (size_t p = buckets[i]; p; p = entries[p].nextEntry)
    {
        if (entries[p].k == k && entries[p].n == n)
        {
            return entries[p].value;
        }
    }

    return 0;
}

static void dictionary_clear(Dictionary* instance)
{
    instance->count = 0;
}

static void finalize_dictionary(Dictionary* instance)
{
    dictionary_clear(instance);
    free(instance->entries);
    free(instance->buckets);

    instance->entries = NULL;
    instance->capacity = 0;
    instance->buckets = NULL;
    instance->bucketCount = 0;
}

static int dictionary_ensure_capacity(Dictionary* instance, size_t capacity)
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

    Entry* entries = instance->entries;
    Entry* newEntries = realloc(entries, newCapacity * sizeof * newEntries);

    if (!newEntries)
    {
        return -1;
    }

    instance->capacity = newCapacity;
    instance->entries = newEntries;

    return 0;
}

static int dictionary_rehash(Dictionary* instance)
{
    size_t bucketCount = instance->bucketCount;
    size_t newBucketCount = dictionary_next_prime(instance->count, bucketCount);
    size_t* buckets = instance->buckets;
    size_t* newBuckets = realloc(buckets, newBucketCount * sizeof * buckets);

    if (!newBuckets)
    {
        return -1;
    }

    memset(newBuckets, 0, newBucketCount * sizeof * newBuckets);

    instance->bucketCount = newBucketCount;
    instance->buckets = newBuckets;

    Entry* entries = instance->entries;

    for (size_t p = 1; p <= instance->count; p++)
    {
        size_t i = hash(entries[p].k, entries[p].n) % newBucketCount;

        entries[p].nextEntry = newBuckets[i];
        newBuckets[i] = p;
    }

    return 0;
}

static int dictionary_set(
    Dictionary* instance,
    unsigned int k,
    unsigned long long n,
    unsigned long long value)
{
    if ((double)instance->count / instance->bucketCount > MAX_LOAD_FACTOR)
    {
        int ex = dictionary_rehash(instance);

        if (ex)
        {
            return ex;
        }
    }

    size_t i = hash(k, n) % instance->bucketCount;
    Entry* entries = instance->entries;

    for (size_t p = instance->buckets[i]; p; p = entries[p].nextEntry)
    {
        if (entries[p].k == k && entries[p].n == n)
        {
            entries[p].value = value;

            return 0;
        }
    }

    int ex = dictionary_ensure_capacity(instance, instance->count + 2);

    if (ex)
    {
        return ex;
    }

    Entry* entry = instance->entries + instance->count + 1;

    entry->k = k;
    entry->n = n;
    entry->value = value;
    entry->nextEntry = instance->buckets[i];
    instance->buckets[i] = instance->count + 1;
    instance->count++;

    return 0;
}

static unsigned long long main_step(
    Dictionary* table,
    unsigned int k,
    unsigned long long n)
{
    if (k == 0)
    {
        return 1;
    }

    if (n == 0)
    {
        return main_step(table, k - 1, 1);
    }

    unsigned long long result = dictionary_get(table, k - 1, n);

    if (result)
    {
        return result;
    }

    unsigned int d = log10(n) + 1;

    if (d % 2 == 0)
    {
        unsigned long mask = pow(10, d / 2);
        unsigned long a = main_step(table, k - 1, n % mask);
        unsigned long b = main_step(table, k - 1, n / mask);

        if (dictionary_set(table, k - 1, n, a + b))
        {
            exit(EXIT_FAILURE);
        }

        return a + b;
    }

    unsigned long a = main_step(table, k - 1, 2024 * n);

    if (dictionary_set(table, k - 1, n, a))
    {
        exit(EXIT_FAILURE);
    }

    return a;
}

int main()
{
    Dictionary table;

    if (dictionary(&table, MIN_CAPACITY, MIN_BUCKET_COUNT))
    {
        return EXIT_FAILURE;
    }

    unsigned long long n;
    unsigned long long sum = 0;

    while (scanf("%llu", &n) == 1)
    {
        sum += main_step(&table, K, n);
    }

    printf("%llu\n", sum);
    finalize_dictionary(&table);

    return EXIT_SUCCESS;
}
