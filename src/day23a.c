// day23a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// LAN Party

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifndef DAY23
#define DAY23
#define MAX_EDGES 4096
#endif

typedef struct Edge Edge;

struct Vertex
{
    bool visited;
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

typedef struct Graph Graph;

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

int main()
{
    unsigned char u[2];
    unsigned char v[2];
    Graph g;

    graph(&g);

    while (scanf("%c%c-%c%c ", u, u + 1, v, v + 1) == 4)
    {
        u[0] -= 'a';
        u[1] -= 'a';
        v[0] -= 'a';
        v[1] -= 'a';

        graph_add_edge(&g, u, v);
        graph_add_edge(&g, v, u);
    }

    unsigned int n = 0;

    for (Vertex* u = g.vertices['t' - 'a']; u < g.vertices['u' - 'a']; u++)
    {
        u->visited = true;

        for (const Edge* e = u->firstEdge; e; e = e->nextEdge)
        {
            for (const Edge* f = e->nextEdge; f; f = f->nextEdge)
            {
                const Vertex* v = g.vertices[e->target[0]] + e->target[1];
                const Vertex* w = g.vertices[f->target[0]] + f->target[1];

                if (!v->visited && !w->visited &&
                    v->edges[f->target[0]][f->target[1]])
                {
                    n++;
                }
            }
        }
    }

    printf("%u\n", n);

    return 0;
}
