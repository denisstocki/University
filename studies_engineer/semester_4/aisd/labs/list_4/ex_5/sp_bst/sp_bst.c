#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sp_bst.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

char* trace_l; 
char* trace_r; 

int comp_ints(SPTree* tree, int i1, int i2) {
    tree -> comparisons++;

    if (i1 == i2) {
        return 0;
    } else if (i1 > i2) {
        return 1;
    } else {
        return -1;
    }    
}

SPTree* SPT_create_tree() {
    SPTree* tree = (SPTree*) malloc(sizeof(SPTree));

    tree -> root = NULL;
    tree -> size = 0;

    return tree;
}

Node* SPT_create_node(int key, Node* left, Node* right) {
    Node* node = (Node*) malloc(sizeof(Node));

    node -> key = key;
    node -> left = left;
    node -> right = right;

    return node;
}

int SPT_height_handler(Node* node) {
    if (node == NULL){
        return -1;
    } else {
        int height_l = SPT_height_handler(node -> left);
        int height_r = SPT_height_handler(node -> right);
        return 1 + MAX(height_l, height_r);
    }
}

int SPT_height(SPTree* tree) {
    return 1 + SPT_height_handler(tree -> root);
}

Node* SPT_right_rotate(Node* x) {
    Node* y = x -> left;

    x -> left = y -> right;
    y -> right = x;

    return y;
}
 
Node* SPT_left_rotate(Node* x) {
    Node* y = x -> right;

    x -> right = y -> left;
    y -> left = x;

    return y;
}

Node* SPT_splay(Node* node, int key, SPTree* tree) {

    if (node == NULL || comp_ints(tree, node -> key, key) == 0) {
        return node;
    }
    
    if (comp_ints(tree, key, node -> key) == -1){
        if (node -> left == NULL) { return node; }
        
        if (comp_ints(tree, node -> left -> key, key) == 1) {
            node -> left -> left = SPT_splay(node -> left -> left, key, tree);
            node = SPT_right_rotate(node);
        } else {
            node -> left -> right = SPT_splay(node -> left -> right, key, tree);
            if (node -> left -> right != NULL) { node -> left = SPT_left_rotate(node -> left); }
        }
        
        return (node -> left == NULL) ? node : SPT_right_rotate(node);
    } else {
        if (node -> right == NULL) { return node; }
    
        if (comp_ints(tree, node -> right -> key, key) == 1) {
            node -> right -> left = SPT_splay(node -> right -> left, key, tree);
 
            if (node -> right -> left != NULL) { node -> right = SPT_right_rotate(node -> right); }
        } else {
            node -> right -> right = SPT_splay(node -> right -> right, key, tree);
            node = SPT_left_rotate(node);
        }
    
        return (node -> right == NULL) ? node : SPT_left_rotate(node);
    }
}

int SPT_delete(SPTree* tree, int key, bool verbose) {

    if (tree -> root == NULL) {
        if (verbose) {
            printf("DELETE: %d (TREE IS EMPTY)\n", key);
        }
        return -1;
    }
    
    tree -> root = SPT_splay(tree -> root, key, tree);

    if (comp_ints(tree, key, tree -> root -> key) != 0) {
        if (verbose) {
            printf("DELETE: %d (NO SUCH ELEMENT)\n", key);
        }
        return -1;
    }
    
    Node* temp;

    if (!(tree -> root -> left)) {
        temp = tree -> root;
        tree -> root = tree -> root -> right;
    } else {
        temp = tree -> root;
        tree -> root = SPT_splay(tree -> root -> left, key, tree);
        tree -> root -> right = temp -> right;
    }
    
    free(temp);

    if (verbose) {
        printf("DELETE: %d\n", key);
    }

    return 1;
}

void SPT_insert(SPTree* tree, int key, bool verbose) {

    if (verbose) {
        printf("INSERT: %d\n", key);
    }

    Node* node = SPT_create_node(key, NULL, NULL);

    if (tree -> root == NULL){
        tree -> root = node;
        return;
    }

    tree -> root = SPT_splay(tree -> root, key, tree);

    if (comp_ints(tree, key, tree -> root -> key) == -1) {
        node -> left = tree -> root -> left;
        node -> right = tree -> root;
        tree -> root -> left = NULL;
    } else {
        node -> right = tree -> root -> right;
        node -> left = tree -> root;
        tree -> root -> right = NULL;
    }

    tree -> root = node;
}

void SPT_print_handler(Node* root, int depth, char prefix, SPTree *tree){
    if (root == NULL) { return; }
        
    if (root -> left != NULL) { SPT_print_handler(root -> left, depth + 1, '/', tree); }
    
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
     
    if (root == NULL) {
        printf("[NULL]\n");    
    } else {
        printf("[%d]\n", root -> key);
    }
    
    trace_l[depth] = ' ';

    if (root -> right != NULL) {
        trace_r[depth] = '|';
        SPT_print_handler(root -> right, depth + 1, '\\', tree);
    }
}

void SPT_print(SPTree* tree) {
    trace_l = malloc((tree -> size) * sizeof(char));
    trace_r = malloc((tree -> size) * sizeof(char));

    for (int i = 0; i <= tree -> size; i++) {
        trace_l[i] = ' ';
        trace_l[i] = ' ';
    }

    printf("------------------ Tree ------------------\n");
    SPT_print_handler(tree -> root, 0, '-', tree);
    printf("------------------ Tree ------------------\n");
    printf("\n");
}

void SPT_print_stats(SPTree* tree) {
    printf("COMPARISONS: %lld\n", tree -> comparisons);
    printf("HEIGHT: %d\n", SPT_height(tree));
}
