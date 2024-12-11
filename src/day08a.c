// day08a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Resonant Collinearity

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX_M 64
#define MAX_N 64

struct Coordinate;

typedef struct Coordinate Coordinate;

struct Coordinate
{
    size_t i;
    size_t j;
    Coordinate* nextCoordinate;
};

struct Map
{
    size_t count;
    Coordinate list[MAX_M * MAX_N];
    Coordinate* firstCoordinates[UCHAR_MAX + 1];
};

typedef struct Map Map;

static void map(Map* instance)
{
    instance->count = 0;

    memset(instance->firstCoordinates, 0, sizeof instance->firstCoordinates);
}

static void map_add(Map* instance, unsigned int k, size_t i, size_t j)
{
    Coordinate* coordinate = instance->list + instance->count;

    coordinate->i = i;
    coordinate->j = j;
    coordinate->nextCoordinate = instance->firstCoordinates[k];
    instance->firstCoordinates[k] = coordinate;
    instance->count++;
}

static size_t main_step(
    bool s[MAX_M][MAX_N],
    size_t m,
    size_t n,
    const Coordinate* coordinates)
{
    size_t result = 0;

    for (const Coordinate* p = coordinates; p; p = p->nextCoordinate)
    {
        for (const Coordinate* q = coordinates; q; q = q->nextCoordinate)
        {
            if (p == q)
            {
                continue;
            }

            size_t i = p->i + p->i - q->i;
            size_t j = p->j + p->j - q->j;

            if (i < m && j < n && !s[i][j])
            {
                s[i][j] = true;
                result++;
            }
        }
    }

    return result;
}

static void main_read(Map* f, const char buffer[MAX_N], size_t i, size_t n)
{
    for (size_t j = 0; j < n; j++)
    {
        if (buffer[j] == '.')
        {
            continue;
        }

        map_add(f, (unsigned int)buffer[j], i, j);
    }
}

int main()
{
    char buffer[MAX_N];
    size_t m = 0;
    size_t n = 0;
    Map f;

    map(&f);

    if (fgets(buffer, MAX_N, stdin))
    {
        n = strlen(buffer);

        while (n && isspace(buffer[n - 1]))
        {
            n--;
        }

        main_read(&f, buffer, m, n);

        m++;

        while (fgets(buffer, MAX_N, stdin))
        {
            if (isspace(*buffer))
            {
                break;
            }

            main_read(&f, buffer, m, n);

            m++;
        }
    }

    size_t count = 0;
    bool s[MAX_M][MAX_N] = { 0 };

    for (char c = '0'; c <= '9'; c++)
    {
        count += main_step(s, m, n, f.firstCoordinates[(unsigned int)c]);
    }

    for (char c = 'a'; c <= 'z'; c++)
    {
        count += main_step(s, m, n, f.firstCoordinates[(unsigned int)c]);
    }

    for (char c = 'A'; c <= 'Z'; c++)
    {
        count += main_step(s, m, n, f.firstCoordinates[(unsigned int)c]);
    }

    printf("%zu\n", count);

    return 0;
}
