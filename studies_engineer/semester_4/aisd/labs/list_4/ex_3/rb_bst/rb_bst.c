#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "rb_bst.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

bool RED = true;
bool BLACK = false;

char* trace_l; 
char* trace_r; 

int comp_ints(RBTree* tree, int i1, int i2) {
    tree -> comparisons++;

    if (i1 == i2) {
        return 0;
    } else if (i1 > i2) {
        return 1;
    } else {
        return -1;
    }    
}

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
    tree -> comparisons = 0;
    tree -> reads = 0;
    tree -> assignments = 0;

    return tree;
}

Node* RBT_search(RBTree* tree, int key) {
    tree -> assignments++;
    Node* node = tree -> root;

    while (node != tree -> NIL) {
        int cmp = comp_ints(tree, key, node->key);
        
        tree -> assignments++;
        tree -> reads++;

        if (cmp == 0) {
            return node;
        } else if (cmp < 0) {
            node = node->left;
        } else {
            node = node->right;
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
    tree -> reads+=2;
    tree -> assignments+=2;

    Node *y = x -> left;

    x -> left = y -> right;

    tree -> reads++;

    if (y -> right != tree -> NIL) { 
        tree -> reads++;
        tree -> assignments++;
        y -> right -> parent = x; 
    }

    tree -> reads++;
    tree -> assignments++;

    y -> parent = x -> parent;

    tree -> reads++;

    if (x -> parent == NULL) { 
        tree -> assignments++;
        tree -> root = y; 
    }
    else if (x == x -> parent -> right) { 
        tree -> reads++;
        tree -> assignments++;
        x -> parent -> right = y; 
    }
    else { 
        tree -> reads++;
        tree -> assignments++;
        x -> parent -> left = y; 
    }
    
    tree -> assignments+=2;

    y -> right = x;
    x -> parent = y;
}

void RBT_left_rotate(Node *x, RBTree *tree) {
    tree -> reads+=2;
    tree -> assignments+=2;
    
    Node *y = x -> right;

    x -> right = y -> left;

    tree -> reads++;

    if (y -> left != tree -> NIL) { 
        tree -> reads++;
        tree -> assignments++;

        y -> left -> parent = x; 
    }

    tree -> reads++;
    tree -> assignments++;

    y -> parent = x -> parent;

    tree -> reads++;
                
    if (x -> parent == NULL) {
        tree -> assignments++;
        tree -> root = y; 
    }
    else if (x == x -> parent -> left) { 
        tree -> reads++;
        tree -> assignments++;

        x -> parent -> left = y; 
    }
    else { 
        tree -> reads++;
        tree -> assignments++;

        x -> parent -> right = y; 
    }
    
    tree -> assignments+=2;

    y -> left = x;
    x -> parent = y;
}

void RBT_transplant(Node *u, Node *v, RBTree *tree) {
    tree -> reads++;

    if (u -> parent == NULL) {
        tree -> assignments++;

        tree -> root = v;
    } else if (u == u -> parent -> left) {
        tree -> reads++;
        tree -> assignments++;

        u -> parent -> left = v;
    } else {
        tree -> reads++;
        tree -> assignments++;

        u -> parent -> right = v;
    }
    tree -> reads++;
    tree -> assignments++;

    v -> parent = u -> parent;
}

Node* RBT_find_submin(Node *node, RBTree *tree) {
    tree -> reads++;

    while (node -> left != tree -> NIL) {
        tree -> reads++;
        tree -> assignments++;

        node = node -> left;
    }

    return node;
}

void RBT_delete_fixup(Node *node, RBTree *tree) {
    while (node != tree -> root && node -> color == BLACK) {
        tree -> reads++;

        if (node == node -> parent -> left) {
            tree -> reads++;
            tree -> assignments++;

            Node *w = node -> parent -> right;
            if (w -> color == RED) {
                tree -> reads+=2;
                tree -> assignments++;

                w -> color = BLACK;
                node -> parent -> color = RED;
                RBT_left_rotate(node -> parent, tree);
                w = node -> parent -> right;
            }

            if (w -> left -> color == BLACK && w -> right -> color == BLACK) {
                tree -> reads++;
                tree -> assignments++;

                w -> color = RED;
                node = node -> parent;
            } else {
                if (w -> right -> color == BLACK) {
                    tree -> reads++;
                    tree -> assignments++;

                    w -> left -> color = BLACK;
                    w -> color = RED;
                    RBT_right_rotate(w, tree);
                    w = node -> parent -> right;
                }

                tree -> reads++;
                tree -> assignments++;

                w -> color = node -> parent -> color;
                node -> parent -> color = BLACK;
                w -> right -> color = BLACK;
                RBT_left_rotate(node -> parent, tree);
                node = tree -> root;
            }
        } else {
            tree -> reads++;
            tree -> assignments++;

            Node *w = node -> parent -> left;
            if (w -> color == RED) {
                tree -> reads+=2;
                tree -> assignments++;

                w -> color = BLACK;
                node -> parent -> color = RED;
                RBT_right_rotate(node -> parent, tree);
                w = node -> parent -> left;
            }

            if (w -> right -> color == BLACK && w -> left -> color == BLACK) {
                tree -> reads++;
                tree -> assignments++;

                w -> color = RED;
                node = node -> parent;
            } else {
                if (w -> left -> color == BLACK) {
                    tree -> reads++;
                    tree -> assignments++;

                    w -> right -> color = BLACK;
                    w -> color = RED;
                    RBT_left_rotate(w, tree);
                    w = node -> parent -> left;
                }

                tree -> reads++;
                tree -> assignments++;

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
        tree -> reads +=3;
        tree -> assignments++;

        x = z -> right;
        RBT_transplant(z, z -> right, tree);
    } else if (z -> right == tree -> NIL) {
        tree -> reads +=3;
        tree -> assignments++;

        x = z -> left;
        RBT_transplant(z, z -> left, tree);
    } else {
        tree -> reads +=5;
        tree -> assignments+=2;

        y = RBT_find_submin(z -> right, tree);
        color_y = y -> color;
        x = y -> right;

        if (y -> parent == z) {
            tree -> assignments++;

            x -> parent = y;
        } else {
            tree -> reads +=2;
            tree -> assignments+=2;

            RBT_transplant(y, y -> right, tree);
            y -> right = z -> right;
            y -> right -> parent = y;
        }

        tree -> reads++;
        tree -> assignments+=2;

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

    tree -> assignments+=2;
    tree -> reads++;

    if (comp_ints(tree, node -> key, root -> key) == -1) {
        root -> left = BST_insert(root -> left, node, tree);
        root -> left -> parent = root;
    } else {
        root -> right = BST_insert(root -> right, node, tree);
        root -> right -> parent = root;
    }
    
    return root;
}

void RBT_insert_fixup(Node *z, RBTree *tree) {
    tree -> reads++;

    while (z -> parent && z -> parent -> color == RED) {
        tree -> reads+=2;

        if (z -> parent == z -> parent -> parent -> left) { 
            tree -> assignments++;
            tree -> reads++;

            Node *y = z -> parent -> parent -> right; 

            if (y -> color == RED) { 
                tree -> assignments++;
                tree -> reads+=1;

                z -> parent -> color = BLACK;
                y -> color = BLACK;
                z -> parent -> parent -> color = RED;
                z = z -> parent -> parent;
            } else { 
                tree -> reads++;

                if (z == z -> parent -> right) { 
                    tree -> reads++;
                    tree -> assignments++;

                    z = z -> parent; 
                    RBT_left_rotate(z, tree);
                }
                tree -> reads +=1;

                z -> parent -> color = BLACK; 
                z -> parent -> parent -> color = RED; 
                RBT_right_rotate(z -> parent -> parent, tree);
            }
        } else { 
            tree -> reads++;
            tree -> assignments++;

            Node *y = z -> parent -> parent -> left; 

            if (y -> color == RED) {
                tree -> reads +=1;
                tree -> assignments++;

                z -> parent -> color = BLACK;
                y -> color = BLACK;
                z -> parent -> parent -> color = RED;
                z = z -> parent -> parent;
            } else {
                tree -> reads++;

                if (z == z -> parent -> left) {
                    tree -> reads++;
                    tree -> assignments++;

                    z = z -> parent; 
                    RBT_right_rotate(z, tree);
                }

                tree -> reads+=1;
            
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

    tree -> assignments+=3;

    z -> key = key;
    z -> parent = NULL;
    z -> left = tree -> NIL;
    z -> right = tree -> NIL;
    z -> color = RED;

    tree -> reads++;
    tree -> assignments++;

    Node* y = NULL; 
    Node* temp = tree -> root;

    while (temp != tree -> NIL) {
        tree -> assignments+=2;
        tree -> reads++;
        y = temp; 

        if(comp_ints(tree, z -> key, temp -> key) == -1) {
            temp = temp->left;
        } else {
            temp = temp -> right;
        }
    }

    tree -> assignments+=2;
    z -> parent = y;

    if(y == NULL) { 
        tree -> root = z;
    } else if(comp_ints(tree, z -> key, y -> key) == -1) {
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

void RBT_print_stats(RBTree* tree) {
    printf("COMPARISONS: %lld\n", tree -> comparisons);
    printf("HEIGHT: %d\n", RBT_height(tree));
    printf("READS: %lld\n", tree -> reads);
    printf("ASSIGNMENTS: %lld\n", tree -> assignments);
}
