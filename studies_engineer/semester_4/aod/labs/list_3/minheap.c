#include <stdio.h>
#include <stdlib.h>
#include "minheap.h"

Heap* createMinHeap(int capacity) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->size = 0;
    h->capacity = capacity;
    h->arr = (int*)malloc(capacity * sizeof(int));
    return h;
}

void insertHelper(Heap* h, int index) {
    int parent = (index - 1) / 2;
    if (h->arr[parent] > h->arr[index]) {
        int temp = h->arr[parent];
        h->arr[parent] = h->arr[index];
        h->arr[index] = temp;
        insertHelper(h, parent);
    }
}

void heapify(Heap* h, int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;

    if (left >= h->size || left < 0)
        left = -1;
    if (right >= h->size || right < 0)
        right = -1;

    if (left != -1 && h->arr[left] < h->arr[index])
        min = left;
    if (right != -1 && h->arr[right] < h->arr[min])
        min = right;

    if (min != index) {
        int temp = h->arr[min];
        h->arr[min] = h->arr[index];
        h->arr[index] = temp;
        heapify(h, min);
    }
}

void insert(Heap* h, int data) {
    if (h->size < h->capacity) {
        h->arr[h->size] = data;
        insertHelper(h, h->size);
        h->size++;
    }
}

void printHeap(Heap* h) {
    for (int i = 0; i < h -> size; i++) {
        printf("%d ", h -> arr[i]);
    }
    printf("\n");
}

int extractMin(Heap* h) {
    int deleteItem;
    if (h->size == 0) {
        printf("\nHeap is empty.");
        return -999;
    }
    deleteItem = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    heapify(h, 0);
    return deleteItem;
}

int isEmpty(Heap* h) {
    return h->size == 0;
}

void freeMinHeap(Heap* h) {
    free(h->arr);
    free(h);
}