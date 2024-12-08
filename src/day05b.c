// day05b.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Print Queue

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTICES 128
#define MAX_EDGES 2048
#define BUFFER_SIZE 128

struct Edge;

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
    Edge edges[MAX_EDGES];
};

struct Stack
{
    unsigned int size;
    unsigned int vertices[MAX_VERTICES];
};

typedef struct Graph Graph;
typedef struct Stack Stack;

static void graph(Graph* g)
{
    g->edgeCount = 0;

    memset(g->vertices, 0, MAX_VERTICES * sizeof * g->vertices);
}

static void graph_add_edge(Graph* g, unsigned int u, unsigned int v)
{
    Edge* edge = g->edges + g->edgeCount;

    edge->source = u;
    edge->target = v;
    edge->nextEdge = g->vertices[u].firstEdge;
    g->vertices[u].firstEdge = edge;
    g->edgeCount++;
}

static void stack(Stack* s)
{
    s->size = 0;
}

static void stack_push(Stack* s, unsigned int v)
{
    s->vertices[s->size] = v;
    s->size++;
}

static int stack_peek(const Stack* s)
{
    return s->vertices[s->size - 1];
}

static void stack_pop(Stack* s)
{
    s->size--;
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

static unsigned int graph_sort_component(
    unsigned int results[MAX_VERTICES], 
    Graph* g, 
    unsigned int u)
{
    if (g->vertices[u].color)
    {
        return 0;
    }

    Stack s;

    stack(&s);
    stack_push(&s, u);

    unsigned int count = 0;

    while (s.size)
    {
        unsigned int u = stack_peek(&s);

        switch (g->vertices[u].color)
        {
        case 0:
            g->vertices[u].color = 1;

            for (Edge* e = g->vertices[u].firstEdge; e; e = e->nextEdge)
            {
                if (!g->vertices[e->target].color)
                {
                    stack_push(&s, e->target);
                }
            }
            continue;

        case 1:
            g->vertices[u].color = 2;
            results[count] = u;
            count++;
            break;
        }

        stack_pop(&s);
    }

    return count;
}

static unsigned int graph_sort(
    unsigned int results[MAX_VERTICES],
    unsigned int vertices[MAX_VERTICES],
    unsigned int vertexCount,
    Graph* g)
{
    unsigned int count = 0;

    for (unsigned int i = 0; i < vertexCount; i++)
    {
        count += graph_sort_component(results + count, g, vertices[i]);
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

        for (char* tok = strtok(buffer, ","); tok; tok = strtok(NULL, ","))
        {
            unsigned int u = strtol(tok, NULL, 10);

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
        unsigned int tLength = graph_sort(t, vertices, vertexCount, &subgraph);

        if (!sequence_equals(vertices, vertexCount, t, tLength))
        {
            n += t[tLength / 2];
        }
    }

    printf("%d\n", n);

    return 0;
}
