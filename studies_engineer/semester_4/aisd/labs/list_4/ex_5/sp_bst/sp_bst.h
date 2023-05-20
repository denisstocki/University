#ifndef SP_BST_H
#define SP_BST_H

#include <stdbool.h>

typedef struct sptree SPTree;
typedef struct node Node;

struct node {
    int key;
    Node* left;
    Node* right;
};

struct sptree {
    Node* root;
    int size;
};

SPTree* SPT_create_tree();
void SPT_insert(SPTree* tree, int key, bool verbose);
int SPT_delete(SPTree* tree, int key, bool verbose);
int SPT_height(SPTree* tree);
void SPT_print(SPTree* tree);

#endif
