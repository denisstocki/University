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
};

BSTree* BST_create_tree();
void BST_insert(BSTree* tree, int key);
int BST_delete(BSTree* tree, int key);
int BST_height(BSTree* tree);
void BST_print(BSTree* tree);

#endif
