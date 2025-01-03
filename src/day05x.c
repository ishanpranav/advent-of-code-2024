// day05x.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Print Queue

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef DAY05
#define DAY05
#define BUFFER_SIZE 128
#define MAX_VERTICES 128
#define EQUAL false
#endif

typedef struct Edge Edge;

struct Vertex
{
    unsigned int color;
    Edge* firstEdge;
};

typedef struct Vertex Vertex;

struct Edge
{
    unsigned int source;
    unsigned int target;
    Edge* nextEdge;
};

struct Graph
{
    unsigned int edgeCount;
    Vertex vertices[MAX_VERTICES];
    Edge edges[MAX_VERTICES * (MAX_VERTICES - 1)];
};

typedef struct Graph Graph;

static void graph(Graph* graph)
{
    graph->edgeCount = 0;

    memset(graph->vertices, 0, sizeof graph->vertices);
}

static void graph_add_edge(
    Graph* instance,
    unsigned int source,
    unsigned int target)
{
    Edge* edge = instance->edges + instance->edgeCount;

    edge->source = source;
    edge->target = target;
    edge->nextEdge = instance->vertices[source].firstEdge;
    instance->vertices[source].firstEdge = edge;
    instance->edgeCount++;
}

static bool sequence_equals(
    const unsigned int left[],
    unsigned int leftLength,
    const unsigned int right[],
    unsigned int rightLength)
{
    if (leftLength != rightLength)
    {
        return false;
    }

    for (unsigned int i = 0; i < leftLength; i++)
    {
        if (left[i] != right[i])
        {
            return false;
        }
    }

    return true;
}

static unsigned int topological_sort_component(
    unsigned int results[MAX_VERTICES],
    Graph* g,
    unsigned int u)
{
    unsigned int count = 0;

    g->vertices[u].color = 1;

    for (Edge* e = g->vertices[u].firstEdge; e; e = e->nextEdge)
    {
        if (!g->vertices[e->target].color)
        {
            count += topological_sort_component(results + count, g, e->target);
        }
    }

    g->vertices[u].color = 2;
    results[count] = u;
    count++;

    return count;
}

static unsigned int topological_sort(
    unsigned int results[MAX_VERTICES],
    const unsigned int vertices[MAX_VERTICES],
    unsigned int vertexCount,
    Graph* g)
{
    unsigned int count = 0;

    for (unsigned int i = 0; i < vertexCount; i++)
    {
        unsigned int u = vertices[i];

        if (!g->vertices[u].color)
        {
            count += topological_sort_component(results + count, g, u);
        }
    }

    return count;
}

int main()
{
    Graph parent;

    graph(&parent);

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, stdin))
    {
        if (*buffer == '\n')
        {
            break;
        }

        unsigned int u;
        unsigned int v;

        if (sscanf(buffer, "%d|%d", &v, &u) != 2)
        {
            break;
        }

        graph_add_edge(&parent, u, v);
    }

    unsigned int n = 0;

    while (fgets(buffer, BUFFER_SIZE, stdin))
    {
        unsigned int vertices[MAX_VERTICES];
        unsigned int vertexCount = 0;
        bool subset[MAX_VERTICES] = { 0 };

        for (char* p = strtok(buffer, ","); p; p = strtok(NULL, ","))
        {
            unsigned int u = atoi(p);

            subset[u] = true;
            vertices[vertexCount] = u;
            vertexCount++;
        }

        Graph subgraph;

        graph(&subgraph);

        for (Edge* e = parent.edges; e < parent.edges + parent.edgeCount; e++)
        {
            if (subset[e->source] && subset[e->target])
            {
                graph_add_edge(&subgraph, e->source, e->target);
            }
        }

        unsigned int t[MAX_VERTICES];
        unsigned int tLength = topological_sort(t, vertices, vertexCount, &subgraph);

        if (sequence_equals(vertices, vertexCount, t, tLength) == EQUAL)
        {
            n += t[tLength / 2];
        }
    }

    printf("%d\n", n);

    return 0;
}
