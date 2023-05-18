#ifndef GRAPH_H
#define GRAPH_H

typedef struct Vertex {
    int value;
    int weight;
    struct Vertex* next;
} Vertex;

typedef struct Graph {
    int count_vertexes;
    Vertex** adjacency_list;
} Graph;

Vertex* create_vertex(int value, int weight);
Graph* create_graph(int size);
void add_edge(Graph* graph, int src, int dest, int weight);
void print_graph(Graph* graph);
void free_graph(Graph* graph);

#endif
