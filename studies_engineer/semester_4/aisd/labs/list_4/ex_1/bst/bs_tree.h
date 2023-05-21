#ifndef BS_TREE_H
#define BS_TREE_H

typedef struct node Node;
typedef struct bstree BSTree;

struct node {
    int key;
    Node* left;
    Node* right;
};

struct bstree {
    Node* root;
    int size;
    long long comparisons;
    long long reads;
    long long assignments;
};

BSTree* BST_create_tree();
void BST_insert(BSTree* tree, int key, bool verbose);
int BST_delete(BSTree* tree, int key, bool verbose);
int BST_height(BSTree* tree);
void BST_print(BSTree* tree);
void BST_print_stats(BSTree* tree);

#endif
