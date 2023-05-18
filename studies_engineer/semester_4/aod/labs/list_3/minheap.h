#ifndef MINHEAP_H
#define MINHEAP_H

struct Heap {
    int* arr;
    int size;
    int capacity;
};

typedef struct Heap Heap;

Heap* createMinHeap(int capacity);
void insert(Heap* h, int data);
int extractMin(Heap* h);
int isEmpty(Heap* h);
void freeMinHeap(Heap* h);
void printHeap(Heap* h);

#endif