#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "rb_bst.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

bool RED = true;
bool BLACK = false;

char* trace_l; 
char* trace_r; 

RBTree* RBT_create_tree() {
    RBTree *tree = (RBTree*) malloc(sizeof(RBTree));
    Node *nil = (Node*) malloc(sizeof(Node));

    nil -> key = 0;
    nil -> color = BLACK;
    nil -> parent = NULL;
    nil -> left = NULL;
    nil -> right = NULL;

    tree -> NIL = nil;
    tree -> root = tree -> NIL;
    tree -> size = 0;

    return tree;
}

Node* RBT_search(RBTree* tree, int key) {
    Node* node = tree -> root;

    while (node != tree -> NIL && key != node -> key) {
        if (key < node -> key) {
            node = node -> left;
        } else {
            node = node -> right;
        }
    }

    return node;
}

Node* RBT_copy_node(Node *node) {
    Node *result = (Node*) malloc(sizeof(Node));

    result -> key = node -> key;
    result -> parent = node -> parent;
    result -> left = node -> left;
    result -> right = node -> right;
    result -> color = node -> color;

    return result;
}

void RBT_right_rotate(Node *x, RBTree *tree) {
    Node *y = x -> left;

    x -> left = y -> right;

    if (y -> right != tree -> NIL) { y -> right -> parent = x; }

    y -> parent = x -> parent;

    if (x -> parent == NULL) { tree -> root = y; }
    else if (x == x -> parent -> right) { x -> parent -> right = y; }
    else { x -> parent -> left = y; }
    
    y -> right = x;
    x -> parent = y;
}

void RBT_left_rotate(Node *x, RBTree *tree) {
    Node *y = x -> right;

    x -> right = y -> left;

    if (y -> left != tree -> NIL) { y -> left -> parent = x; }

    y -> parent = x -> parent;

    if (x -> parent == NULL) { tree -> root = y; }
    else if (x == x -> parent -> left) { x -> parent -> left = y; }
    else { x -> parent -> right = y; }
    
    y -> left = x;
    x -> parent = y;
}

void RBT_transplant(Node *u, Node *v, RBTree *tree) {
    if (u -> parent == NULL) {
        printf("SIEMA\n");
        tree -> root = v;
    } else if (u == u -> parent -> left) {
        u -> parent -> left = v;
    } else {
        u -> parent -> right = v;
    }
    v -> parent = u -> parent;
}

Node* RBT_find_submin(Node *node, RBTree *tree) {

    while (node -> left != tree -> NIL) {
        node = node -> left;
    }

    return node;
}

void RBT_delete_fixup(Node *node, RBTree *tree) {
    while (node != tree -> root && node -> color == BLACK) {
        if (node == node -> parent -> left) {
            Node *w = node -> parent -> right;
            if (w -> color == RED) {
                w -> color = BLACK;
                node -> parent -> color = RED;
                RBT_left_rotate(node -> parent, tree);
                w = node -> parent -> right;
            }

            if (w -> left -> color == BLACK && w -> right -> color == BLACK) {
                w -> color = RED;
                node = node -> parent;
            } else {
                if (w -> right -> color == BLACK) {
                    w -> left -> color = BLACK;
                    w -> color = RED;
                    RBT_right_rotate(w, tree);
                    w = node -> parent -> right;
                }

                w -> color = node -> parent -> color;
                node -> parent -> color = BLACK;
                w -> right -> color = BLACK;
                RBT_left_rotate(node -> parent, tree);
                node = tree -> root;
            }
        } else {
            Node *w = node -> parent -> left;
            if (w -> color == RED) {
                w -> color = BLACK;
                node -> parent -> color = RED;
                RBT_right_rotate(node -> parent, tree);
                w = node -> parent -> left;
            }

            if (w -> right -> color == BLACK && w -> left -> color == BLACK) {
                w -> color = RED;
                node = node -> parent;
            } else {
                if (w -> left -> color == BLACK) {
                    w -> right -> color = BLACK;
                    w -> color = RED;
                    RBT_left_rotate(w, tree);
                    w = node -> parent -> left;
                }

                w -> color = node -> parent -> color;
                node -> parent -> color = BLACK;
                w -> left -> color = BLACK;
                RBT_right_rotate(node -> parent, tree);
                node = tree -> root;
            }
        }
    }

    node -> color = BLACK;
}

int RBT_delete(RBTree* tree, int key, bool verbose) {

    if (tree -> root == tree -> NIL) {
        if (verbose) {
            printf("DELETE: TREE IS EMPTY\n");   
        }
        return -1;
    }

    Node *z = RBT_search(tree, key);

    if (z == tree -> NIL) {
        if (verbose) {
            printf("DELETE: %d (NO SUCH ELEMENT)\n", key);
        }
        return -1;
    }

    Node *y = z;
    Node *x;
    
    bool color_y = y -> color;

    if (z -> left == tree -> NIL) {
        x = z -> right;
        RBT_transplant(z, z -> right, tree);
    } else if (z -> right == tree -> NIL) {
        x = z -> left;
        RBT_transplant(z, z -> left, tree);
    } else {
        y = RBT_find_submin(z -> right, tree);
        color_y = y -> color;
        x = y -> right;

        if (y -> parent == z) {
            x -> parent = y;
        } else {
            RBT_transplant(y, y -> right, tree);
            y -> right = z -> right;
            y -> right -> parent = y;
        }

        RBT_transplant(z, y, tree);
        y -> left = z -> left;
        y -> left -> parent = y;
        y -> color = z -> color;
    }

    if (color_y == BLACK) {
        RBT_delete_fixup(x, tree);
    }

    if (verbose) {
        printf("DELETE: %d\n", key);
    }

    tree -> size--;
    return 1;
}

int RBT_height_handler(Node* node, RBTree *tree) {
    if (node == tree -> NIL) {
        return -1;
    } else {
        int h_left = RBT_height_handler(node -> left, tree);
        int h_right = RBT_height_handler(node -> right, tree);
        return 1 + MAX(h_left, h_right);
    }
}

int RBT_height(RBTree* tree) {
    return 1 + RBT_height_handler(tree -> root, tree);
}

Node* BST_insert(Node *root, Node *node, RBTree *tree) {
    if (root == tree -> NIL) {
        return node;
    }

    if (node -> key < root -> key) {
        root -> left = BST_insert(root -> left, node, tree);
        root -> left -> parent = root;
    } else {
        root -> right = BST_insert(root -> right, node, tree);
        root -> right -> parent = root;
    }
    
    return root;
}

void RBT_insert_fixup(Node *z, RBTree *tree) {
    while (z -> parent && z -> parent -> color == RED) {
        if (z -> parent == z -> parent -> parent -> left) { 

            Node *y = z -> parent -> parent -> right; 

            if (y -> color == RED) { 
                z -> parent -> color = BLACK;
                y -> color = BLACK;
                z -> parent -> parent -> color = RED;
                z = z -> parent -> parent;
            } else { 
                if (z == z -> parent -> right) { 
                    z = z -> parent; 
                    RBT_left_rotate(z, tree);
                }
      
                z -> parent -> color = BLACK; 
                z -> parent -> parent -> color = RED; 
                RBT_right_rotate(z -> parent -> parent, tree);
            }
        } else { 
            Node *y = z -> parent -> parent -> left; 

            if (y -> color == RED) {
                z -> parent -> color = BLACK;
                y -> color = BLACK;
                z -> parent -> parent -> color = RED;
                z = z -> parent -> parent;
            } else {
                if (z == z -> parent -> left) {
                    z = z -> parent; 
                    RBT_right_rotate(z, tree);
                }

                z -> parent -> color = BLACK; 
                z -> parent -> parent -> color = RED; 
                RBT_left_rotate(z -> parent -> parent, tree);
            }
        }
    }
    tree -> root -> color = BLACK;
}

void RBT_insert(RBTree* tree, int key, bool verbose) {

    if (verbose) {
        printf("INSERT: %d\n", key);
    }
    
    Node* z = (Node*) malloc(sizeof(Node));

    z -> key = key;
    z -> parent = NULL;
    z -> left = tree -> NIL;
    z -> right = tree -> NIL;
    z -> color = RED;

    Node* y = NULL; 
    Node* temp = tree -> root;

    while (temp != tree -> NIL) {
        y = temp; 
        if(z -> key < temp -> key) {
            temp = temp->left;
        } else {
            temp = temp -> right;
        }
    }

    z -> parent = y;

    if(y == NULL) { 
        tree -> root = z;
    } else if(z -> key < y -> key) {
        y -> left = z;
    } else {
        y -> right = z;
    }

    RBT_insert_fixup(z, tree);
    tree -> size++;
}

void RBT_print_handler(Node* root, int depth, char prefix, RBTree *tree){
    if (root == NULL) { return; }
        
    if (root -> left != NULL) { RBT_print_handler(root -> left, depth + 1, '/', tree); }
    
    if (prefix == '/') { trace_l[depth - 1] = '|'; }
    
    if (prefix == '\\') { trace_r[depth - 1] = ' '; }
    
    if (depth == 0) { printf("-"); }

    if (depth > 0) { printf(" "); }

    for (int i = 0; i < depth - 1; i++) {
        if (trace_l[i] == '|' || trace_r[i] == '|') {
            printf("| ");
        } else {
            printf("  ");
        }
    }

    if (depth > 0) { printf("%c-", prefix); }
     
    if (root == tree -> NIL) {
        printf("[NIL]\n");    
    } else {
        printf("[%d,%d]\n", root -> key, root -> color);
    }
    
    trace_l[depth] = ' ';

    if (root -> right != NULL) {
        trace_r[depth] = '|';
        RBT_print_handler(root -> right, depth + 1, '\\', tree);
    }
}

void RBT_print(RBTree* tree) {
    trace_l = malloc((tree -> size) * sizeof(char));
    trace_r = malloc((tree -> size) * sizeof(char));

    for (int i = 0; i <= tree -> size; i++) {
        trace_l[i] = ' ';
        trace_l[i] = ' ';
    }

    printf("------------------ Tree ------------------\n");
    RBT_print_handler(tree -> root, 0, '-', tree);
    printf("------------------ Tree ------------------\n");
    printf("\n");
}