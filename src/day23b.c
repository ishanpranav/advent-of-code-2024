// day23b.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// LAN Party

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef DAY23
#define DAY23
#define MAX_EDGES 4096
#endif

enum Subset
{
    SUBSET_NONE = 0,
    SUBSET_P = 1,
    SUBSET_R = 2,
    SUBSET_X = 3
};

typedef enum Subset Subset;
typedef struct Edge Edge;

struct Vertex
{
    bool edges[26][26];
    Edge* firstEdge;
};

typedef struct Vertex Vertex;

struct Edge
{
    unsigned char source[2];
    unsigned char target[2];
    Edge* nextEdge;
};

struct Graph
{
    unsigned int edgeCount;
    Edge edges[MAX_EDGES * 2];
    Vertex vertices[26][26];
};

struct Clique
{
    unsigned char vertices[26 * 26][2];
    unsigned int count;
};

typedef struct Clique Clique;

struct BronKerbosch
{
    unsigned int xCount;
    Clique p;
    Clique r;
    Subset subsets[26][26];
};

typedef struct Graph Graph;
typedef struct BronKerbosch BronKerbosch;

static void graph(Graph* instance)
{
    instance->edgeCount = 0;

    memset(instance->vertices, 0, sizeof instance->vertices);
}

static void graph_add_edge(
    Graph* instance,
    unsigned char source[2],
    unsigned char target[2])
{
    instance->vertices[source[0]][source[1]].edges[target[0]][target[1]] = true;

    Edge* edge = instance->edges + instance->edgeCount;

    memcpy(edge->source, source, 2);
    memcpy(edge->target, target, 2);

    edge->nextEdge = instance->vertices[source[0]][source[1]].firstEdge;
    instance->vertices[source[0]][source[1]].firstEdge = edge;
    instance->edgeCount++;
}

static void bron_kerbosch(Clique* result, BronKerbosch value, const Graph* g)
{
    if (!value.p.count && !value.xCount)
    {
        if (value.r.count > result->count)
        {
            memcpy(result, &value.r, sizeof * result);
        }

        return;
    }

    while (value.p.count)
    {
        value.p.count--;

        unsigned char u[2];

        memcpy(u, value.p.vertices[value.p.count], 2);

        BronKerbosch clone;

        clone.p.count = 0;
        clone.xCount = 0;

        memcpy(
            clone.r.vertices,
            value.r.vertices,
            value.r.count * sizeof * clone.r.vertices);
        memcpy(clone.r.vertices[value.r.count], u, 2);

        clone.r.count = value.r.count + 1;

        memset(clone.subsets, 0, sizeof clone.subsets);

        const Vertex* source = g->vertices[u[0]] + u[1];

        for (const Edge* e = source->firstEdge; e; e = e->nextEdge)
        {
            switch (value.subsets[e->target[0]][e->target[1]])
            {
            case SUBSET_P:
                memcpy(clone.p.vertices[clone.p.count], e->target, 2);

                clone.subsets[e->target[0]][e->target[1]] = SUBSET_P;
                clone.p.count++;
                break;

            case SUBSET_X:
                clone.subsets[e->target[0]][e->target[1]] = SUBSET_X;
                clone.xCount++;
                break;

            default: break;
            }
        }

        bron_kerbosch(result, clone, g);

        value.subsets[u[0]][u[1]] = SUBSET_X;
        value.xCount++;
    }
}

static int compare(const void* left, const void* right)
{
    const char* p = left;
    const char* q = right;

    return memcmp(p, q, 2);
}

int main()
{
    unsigned char u[2];
    unsigned char v[2];
    Graph g;

    graph(&g);

    BronKerbosch value;

    value.p.count = 0;
    value.r.count = 0;
    value.xCount = 0;

    memset(value.subsets, 0, sizeof value.subsets);

    while (scanf("%c%c-%c%c ", u, u + 1, v, v + 1) == 4)
    {
        u[0] -= 'a';
        u[1] -= 'a';
        v[0] -= 'a';
        v[1] -= 'a';

        graph_add_edge(&g, u, v);
        graph_add_edge(&g, v, u);

        if (value.subsets[u[0]][u[0]] == SUBSET_NONE)
        {
            memcpy(value.p.vertices[value.p.count], u, 2);

            value.subsets[u[0]][u[0]] = SUBSET_P;
            value.p.count++;
        }

        if (value.subsets[v[0]][v[1]] == SUBSET_NONE)
        {
            memcpy(value.p.vertices[value.p.count], v, 2);

            value.subsets[v[0]][v[1]] = SUBSET_P;
            value.p.count++;
        }
    }

    Clique max;

    max.count = 0;

    bron_kerbosch(&max, value, &g);
    qsort(max.vertices, max.count, 2, compare);

    if (max.count)
    {
        printf("%c%c", max.vertices[0][0] + 'a', max.vertices[0][1] + 'a');

        for (unsigned int i = 1; i < max.count; i++)
        {
            printf(",%c%c", max.vertices[i][0] + 'a', max.vertices[i][1] + 'a');
        }

        printf("\n");
    }

    return 0;
}
