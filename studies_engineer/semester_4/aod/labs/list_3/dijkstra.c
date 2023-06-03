#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "options.h"
#include "graph.h"
#include "minheap.h"

typedef struct {
    char **lines;
    size_t count;
} LinesArray;

void sp_time_problem(options_t, char *);
int open_file(LinesArray *, char *, char *, char);
void find_all_sp(Graph* graph, int source);

int main (int argc, char *argv[]) {

    options_t opts = parse_options(argc, argv);

    if (opts.option == 1){
        printf("\n");
        printf("Programme summoned with options -d --ss --oss.\n");
        printf("\n");
        printf("Options values:\n");
        printf("\n");
        printf("-d: %s\n", opts.d_val);
        printf("--ss: %s\n", opts.ss_val);
        printf("--oss: %s\n", opts.oss_val);
        printf("\n");
        sp_time_problem(opts, argv[0]);
    } else if (opts.option == 2) {
        printf("\n");
        printf("Programme summoned with options -d --p2p --op2p.\n");
        printf("\n");
        printf("Options values:\n");
        printf("\n");
        printf("-d: %s\n", opts.d_val);
        printf("--p2p: %s\n", opts.p2p_val);
        printf("--op2p: %s\n", opts.op2p_val);
        printf("\n");
    } else {
        fprintf(stderr, "Usage 1: %s -d plik_z_danymi.gr --ss zrodla.ss --oss wyniki.ss.res\nUsage 2: %s -d plik_z_danymi.gr --p2p pary.p2p --op2p wyniki.p2p.res\n", argv[0], argv[0]);
        return 1;
    }
    
    return 0;
}

void sp_time_problem(options_t opts, char *programme_name) {

    LinesArray lines_d = {NULL, 0};
    LinesArray lines_ss = {NULL, 0};
    LinesArray lines_oss = {NULL, 0};

    if (open_file(&lines_d, opts.d_val, programme_name, 'r') == -1
        || open_file(&lines_ss, opts.ss_val, programme_name, 'r') == -1
    ) {
        return;
    }

    int i;
    int num_vertexes, num_edges;

    printf("------------------Scanning------------------\n");

    for (i = 0; i < lines_d.count; i++) {
        printf("%s", lines_d.lines[i]);
        if (strncmp(lines_d.lines[i], "p sp", 4) == 0) {
            sscanf(lines_d.lines[i], "p sp %d %d", &num_vertexes, &num_edges);  
            break;
        }
    }

    printf("------------------Scanning------------------\n");
    printf("\n");

    Graph* graph = create_graph(num_vertexes);

    int counter_a = 0;
    int src, dest, cost;

    printf("------------------Scanning------------------\n");

    i++;
    while (counter_a < num_edges) {
        printf("%s", lines_d.lines[i]);
        if (strncmp(lines_d.lines[i], "a ", 2) == 0) {
            sscanf(lines_d.lines[i], "a %d %d %d", &src, &dest, &cost);
            add_edge(graph, src, dest, cost);
            counter_a++;
        }
        i++;
    }

    printf("------------------Scanning------------------\n");
    printf("\n");
    
    print_graph(graph);

    int num_sources;

    printf("------------------Scanning------------------\n");

    for (i = 0; i < lines_ss.count; i++) {
        printf("%s", lines_ss.lines[i]);
        if (strncmp(lines_ss.lines[i], "p aux sp ss ", 12) == 0) {
            sscanf(lines_ss.lines[i], "p aux sp ss %d", &num_sources);
            break;
        }
    }

    printf("------------------Scanning------------------\n");
    printf("\n");
    
    int counter_sources = 0;
    int *sources = (int*) malloc(num_sources * sizeof(int));

    printf("------------------Scanning------------------\n");

    while (counter_sources < num_sources) {
        printf("%s", lines_ss.lines[i]);
        if (strncmp(lines_ss.lines[i], "s ", 2) == 0) {
            int source;
            sscanf(lines_ss.lines[i], "s %d", &source);
            sources[counter_sources] = source;
            counter_sources++;
        }
        i++;
    }

    printf("------------------Scanning------------------\n");
    printf("\n");

    for (int i = 0; i < num_sources; i++) {
        printf("------------------Source%i------------------\n", i + 1);
        printf("SOURCE: %d\n", sources[i]);
        find_all_sp(graph, sources[i]);
        printf("\n");
    }
}

void find_all_sp(Graph* graph, int source) {
    int* distance = (int*) malloc((graph -> count_vertexes + 1) * sizeof(int));
    int* visited = (int*) malloc((graph -> count_vertexes + 1) * sizeof(int));

    Heap* minheap = createMinHeap(graph -> count_vertexes);

    for (int i = 1; i <= graph -> count_vertexes; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }
    
    distance[source] = 0;

    insert(minheap, source);

    while (minheap -> size > 0) {
        printHeap(minheap);
        printf("Extracting minimum\n");
        int u = extractMin(minheap);
        printf("Marking visited, minimum: %d\n", u);
        visited[u] = 1;

        Vertex* current = graph -> adjacency_list[u];

        printf("Iterating over neigbours\n");
        while (current != NULL) {
            printf("Neighbour %d\n", current -> value);
            int v = current -> value;
            int weight = current -> weight;
            printf("Checking better distance\n");
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                printf("Assigning new distance\n");
                distance[v] = distance[u] + weight;
            }

            printf("Checking if visited\n");
            if (!visited[v]) {
                printf("Assigning if not visited\n");
                insert(minheap, v);
                printf("Inserting into heap\n");
            }
            
            current = current -> next;
        }
    }
    printf("Heap is empty\n");

    printf("------------------ Paths ------------------\n");
    printf("Source: %d\n", source);
    printf("\n");

    for (int i = 1; i < graph -> count_vertexes + 1; i++) {
        printf("Cost for vertex: %d is: %d\n", i, distance[i]);
    }
    
    printf("------------------ Paths ------------------\n");
    printf("\n");
    
    free(distance);
    free(visited);
    freeMinHeap(minheap);
}

int open_file(LinesArray *lines_array, char *file_name, char *programme_name, char mode) {

    FILE *file = fopen(file_name, &mode);

    if (file == NULL) {
        fprintf(stderr, "%s: file could not be opened %s\n", programme_name, file_name);
        return -1;
    }
    
    char *line = NULL;
    size_t line_length = 0;

    while (getline(&line, &line_length, file) != -1) {
        lines_array -> count++;
        lines_array -> lines = realloc(lines_array -> lines, lines_array -> count * sizeof(char *));
        lines_array -> lines[lines_array -> count - 1] = line;
        line = NULL;
        line_length = 0;
    }

    return 1;
}
