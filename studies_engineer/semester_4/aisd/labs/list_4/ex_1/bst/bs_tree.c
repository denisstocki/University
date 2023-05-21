#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "bs_tree.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

char* left_trace; 
char* right_trace; 

int comp_ints(BSTree* tree, int i1, int i2) {
    tree -> comparisons++;

    if (i1 == i2) {
        return 0;
    } else if (i1 > i2) {
        return 1;
    } else {
        return -1;
    }    
}

BSTree* BST_create_tree() {
    BSTree* tree = (BSTree*) malloc(sizeof(BSTree));

    tree -> root = NULL;
    tree -> size = 0;
    tree -> comparisons = 0;

    return tree;
}

Node* BST_find_submin(Node* node, BSTree* tree) {
    tree -> reads++;

    while (node -> left != NULL) {
        tree -> reads++;
        tree -> assignments++;

        node = node -> left;
    }
    
    return node;
}

Node* BST_delete_handler(Node* node, int key, bool *found, BSTree* tree) {
    if (node == NULL) {
        return NULL;
    } else if (comp_ints(tree, key, node -> key) == -1) {
        tree -> assignments++;
        tree -> reads++;

        node -> left = BST_delete_handler(node -> left, key, found, tree);
    } else if (comp_ints(tree, key, node -> key) == 1) {
        tree -> assignments++;
        tree -> reads++;

        node -> right = BST_delete_handler(node -> right, key, found, tree);
    } else {
        *found = true;

        tree -> reads+=2;
        tree -> assignments++;

        if (node -> left == NULL && node -> right == NULL) {
            free(node);
            node = NULL;
        } else if (node -> left == NULL) {
            Node* temp = node;
            node = node -> right;
            free(temp);
        } else if (node -> right == NULL) {
            Node* temp = node;
            node = node -> left;
            free(temp);
        } else {
            Node* min_r = BST_find_submin(node -> right, tree);
            node -> key = min_r -> key;
            node -> right = BST_delete_handler(node -> right, min_r -> key, found, tree);
        } 
    }
    
    return node;
}

int BST_delete(BSTree* tree, int key, bool verbose) {
    if (tree -> root == NULL) {
        if (verbose) {
            printf("DELETE: %d (TREE IS EMPTY)\n", key);
        }
        return 0;
    }
    
    bool found = false;

    tree -> root = BST_delete_handler(tree -> root, key, &found, tree);

    if (found) {
        if (verbose) {
            printf("DELETE: %d\n", key);
        }
        tree -> size--;
        return 1;
    } else {
        if (verbose) {
            printf("DELETE: %d (NO SUCH ELEMENT)\n", key);
        }
        return -1;
    }
}

int BST_height_handler(Node* node) {
    if (node == NULL) {
        return -1;
    } else {
        int h_left = BST_height_handler(node -> left);
        int h_right = BST_height_handler(node -> right);
        return 1 + MAX(h_left, h_right);
    }
}

int BST_height(BSTree* tree) {
    return 1 + BST_height_handler(tree -> root);
}

void BST_insert_handler(Node** node, int key, BSTree* tree) {
    if (*node == NULL) {
        tree -> assignments+=3;

        *node = (Node*) malloc(sizeof(Node));
        (*node) -> key = key;
        (*node) -> left = NULL;
        (*node) -> right = NULL;
    } else {
        tree -> reads++;

        if (comp_ints(tree, key, (*node) -> key) == -1) {
            BST_insert_handler(&(*node) -> left, key, tree);
        } else {
            BST_insert_handler(&(*node) -> right, key, tree);
        }
    }
}

void BST_insert(BSTree* tree, int key, bool verbose) {
    if (verbose) {
        printf("INSERT: %d\n", key);
    }

    BST_insert_handler(&(tree -> root), key, tree);
    tree -> size++;
}

void BST_print_handler(Node* root, int depth, char prefix){
    if (root == NULL) {
        return;
    }
        
    if (root -> left != NULL) {
        BST_print_handler(root -> left, depth + 1, '/');
    }
    
    if (prefix == '/') {
        left_trace[depth - 1] = '|';
    }
    
    if (prefix == '\\') {
        right_trace[depth - 1] = ' ';
    }
    
    if (depth == 0) {
        printf("-");
    }

    if (depth > 0) {
        printf(" ");
    }

    for (int i = 0; i < depth - 1; i++) {
        if (left_trace[i] == '|' || right_trace[i] == '|') {
            printf("| ");
        } else {
            printf("  ");
        }
    }

    if (depth > 0) {
        printf("%c-", prefix);
    }
     
    printf("[%d]\n", root -> key);
    left_trace[depth] = ' ';

    if (root -> right != NULL) {
        right_trace[depth] = '|';
        BST_print_handler(root -> right, depth + 1, '\\');
    }
}

void BST_print(BSTree* tree) {
    left_trace = malloc((tree -> size) * sizeof(char));
    right_trace = malloc((tree -> size) * sizeof(char));

    for (int i = 0; i <= tree -> size; i++) {
        left_trace[i] = ' ';
        left_trace[i] = ' ';
    }

    printf("------------------ Tree ------------------\n");
    BST_print_handler(tree -> root, 0, '-');
    printf("------------------ Tree ------------------\n");
    printf("\n");
}

void BST_print_stats(BSTree* tree) {
    printf("COMPARISONS: %lld\n", tree -> comparisons);
    printf("HEIGHT: %d\n", BST_height(tree));
    printf("READS: %lld\n", tree -> reads);
    printf("ASSIGNMENTS: %lld\n", tree -> assignments);
}
