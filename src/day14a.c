// day14a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Restroom Redoubt

#include <stdio.h>
#ifndef DAY14
#define DAY14
#define MAX_X 11
#define MAX_Y 7
#endif
#define T 100

struct Vector
{
    int x;
    int y;
};

typedef struct Vector Vector;

static int mod(int dividend, int divisor) 
{
    int result = dividend % divisor;

    if (result < 0)
    {
        if (divisor < 0)
        {
            return result - divisor;
        }

        return result + divisor;
    }
    
    return result;
}

int main()
{
    Vector s;
    Vector v;
    unsigned int counts[4] = { 0 };

    while (scanf("p=%d,%d v=%d,%d ", &s.x, &s.y, &v.x, &v.y) == 4)
    {
        s.x = mod(s.x + v.x * T, MAX_X);
        s.y = mod(s.y + v.y * T, MAX_Y);

        if (s.x < MAX_X / 2 && s.y < MAX_Y / 2)
        {
            counts[0]++;
        }
        else if (s.x < MAX_X / 2 && s.y > MAX_Y / 2)
        {
            counts[1]++;
        }
        else if (s.x > MAX_X / 2 && s.y < MAX_Y / 2)
        {
            counts[2]++;
        }
        else if (s.x > MAX_X / 2 && s.y > MAX_Y / 2)
        {
            counts[3]++;
        }
    }

    unsigned long product = counts[0];

    for (unsigned int i = 1; i < 4; i++)
    {
        product *= counts[i];
    }

    printf("%lu\n", product);

    return 0;
}
