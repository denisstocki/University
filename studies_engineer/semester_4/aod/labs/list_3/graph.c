#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Vertex* create_vertex(int value, int weight) {
    Vertex* vertex = (Vertex*) malloc(sizeof(Vertex));

    vertex -> value = value;
    vertex -> weight = weight;
    vertex -> next = NULL;

    return vertex;
}

Graph* create_graph(int size) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));

    graph -> count_vertexes = size;
    graph -> adjacency_list = (Vertex**) malloc(size * sizeof(Vertex*));

    for (int i = 0; i < size; i++) {
        graph -> adjacency_list[i] = NULL;
    }
    
    return graph;
}

void add_edge(Graph* graph, int src, int dest, int weight) {
    Vertex* vertex_new = create_vertex(dest, weight);

    vertex_new -> next = graph -> adjacency_list[src];

    graph -> adjacency_list[src] = vertex_new;
}

void print_graph(Graph* graph) {
    printf("------------------ Graph ------------------\n");
    for (int i = 1; i < graph -> count_vertexes; i++) {
        printf("Vertex %d: ", i);
        Vertex* vertex_current = graph -> adjacency_list[i];
        while (vertex_current != NULL) {
            printf("(V: %d, C: %d) ", vertex_current -> value, vertex_current -> weight);
            vertex_current = vertex_current -> next;
        }
        printf("\n");
    }
    printf("------------------ Graph ------------------\n");
    printf("\n");
}

void free_graph(Graph* graph) {
    for (int i = 0; i < graph -> count_vertexes; i++) {
        Vertex* vertex_current = graph -> adjacency_list[i];
        while (vertex_current != NULL) {
            Vertex* vertex_temp = vertex_current;
            vertex_current = vertex_current -> next;
            free(vertex_temp);
        }
    }
    free(graph -> adjacency_list);
    free(graph);
}
