#ifndef RB_BST_H
#define RB_BST_H

#include <stdbool.h>

typedef struct node Node;
typedef struct tree RBTree;

struct node {
    int key;
    Node* parent;
    Node* left;
    Node* right;
    bool color;
};

struct tree {
    Node* root;
    Node* NIL;
    int size;
    long long comparisons;
};

RBTree* RBT_create_tree();
void RBT_insert(RBTree* tree, int key, bool verbose);
int RBT_delete(RBTree* tree, int key, bool verbose);
int RBT_height(RBTree* tree);
void RBT_print(RBTree* tree);
void RBT_print_stats(RBTree* tree);

#endif
