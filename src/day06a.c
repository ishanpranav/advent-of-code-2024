// day06a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Guard Gallivant

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX_M 256
#define MAX_N 256

int main()
{
    char a[MAX_M][MAX_N];
    size_t m = 0;
    size_t n = 0;
    size_t i = 0;
    size_t j = 0;

    if (fgets(a[0], MAX_N, stdin))
    {
        n = strlen(a[0]);

        while (n && isspace(a[0][n - 1]))
        {
            n--;
        }

        m++;

        while (fgets(a[m], MAX_N, stdin))
        {
            char* p = strchr(a[m], '^');

            if (p)
            {
                i = m;
                j = p - a[m];
            }

            m++;
        }
    }

    int di = -1;
    int dj = 0;
    size_t k = 0;
    bool b[MAX_M][MAX_N] = { 0 };

    for (;;)
    {
        if (!b[i][j])
        {
            k++;
            b[i][j] = true;
        }

        if (i + di >= m || j + dj >= n)
        {
            break;
        }

        while (a[i + di][j + dj] == '#')
        {
            if (di == 1)
            {
                di = 0;
                dj = -1;
            }
            else if (di == -1)
            {
                di = 0;
                dj = 1;
            }
            else if (dj == 1)
            {
                di = 1;
                dj = 0;
            }
            else if (dj == -1)
            {
                di = -1;
                dj = 0;
            }
        }

        i += di;
        j += dj;
    }

    printf("%zu\n", k);

    return 0;
}
