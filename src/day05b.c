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
    int color;
    Edge* firstEdge;
};

typedef struct Vertex Vertex;

struct Edge
{
    int source;
    int target;
    Edge* nextEdge;
};

struct Graph
{
    int edgeCount;
    Vertex vertices[MAX_VERTICES];
    Edge edges[MAX_EDGES];
};

struct Stack
{
    int size;
    int vertices[MAX_VERTICES];
};

typedef struct Graph Graph;
typedef struct Stack Stack;

static void graph(Graph* g)
{
    g->edgeCount = 0;

    memset(g->vertices, 0, MAX_VERTICES * sizeof * g->vertices);
}

static void graph_add_edge(Graph* g, int u, int v)
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

static void stack_push(Stack* s, int v)
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
    const int* left,
    int leftLength,
    const int* right,
    int rightLength)
{
    if (leftLength != rightLength)
    {
        return false;
    }

    for (int i = 0; i < leftLength; i++)
    {
        if (left[i] != right[i])
        {
            return false;
        }
    }

    return true;
}

static int graph_sort_component(int results[MAX_VERTICES], Graph* g, int u)
{
    if (g->vertices[u].color)
    {
        return 0;
    }

    Stack s;

    stack(&s);
    stack_push(&s, u);

    int count = 0;

    while (s.size)
    {
        int u = stack_peek(&s);

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

static int graph_sort(
    int results[MAX_VERTICES],
    int vertices[MAX_VERTICES],
    int vertexCount,
    Graph* g)
{
    int count = 0;

    for (int i = 0; i < vertexCount; i++)
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

        int u;
        int v;

        if (sscanf(buffer, "%d|%d", &v, &u) != 2)
        {
            break;
        }

        graph_add_edge(&parent, u, v);
    }

    int n = 0;

    while (fgets(buffer, BUFFER_SIZE, stdin))
    {
        int vertices[MAX_VERTICES];
        int vertexCount = 0;
        bool subset[MAX_VERTICES] = { 0 };

        for (char* tok = strtok(buffer, ","); tok; tok = strtok(NULL, ","))
        {
            int u = strtol(tok, NULL, 10);

            subset[u] = true;
            vertices[vertexCount] = u;
            vertexCount++;
        }

        Graph subgraph;

        graph(&subgraph);

        for (const Edge* e = parent.edges; e < parent.edges + parent.edgeCount; e++)
        {
            if (subset[e->source] && subset[e->target])
            {
                graph_add_edge(&subgraph, e->source, e->target);
            }
        }

        int t[MAX_VERTICES];
        int tLength = graph_sort(t, vertices, vertexCount, &subgraph);

        if (!sequence_equals(vertices, vertexCount, t, tLength))
        {
            n += t[tLength / 2];
        }
    }

    printf("%d\n", n);

    return 0;
}
