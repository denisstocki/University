#include <stdio.h>
#include <stdbool.h>
#include "../bst/bs_tree.h"

int main() {

    int n;

    scanf("%d", &n);

    bool verbose = false;

    if (n <= 50) {
        verbose = true;   
    }

    BSTree* tree = BST_create_tree();

    for (int i = 0; i < n; i++) {
        int key;
        scanf("%d", &key);
        BST_insert(tree, key, verbose);    
        if (verbose) {
            printf("\n");
            BST_print(tree);
        }
    }
    
    for (int i = 0; i < n; i++) {
        int key;
        scanf("%d", &key);
        BST_delete(tree, key, verbose);
        if (verbose) {
            printf("\n");
            BST_print(tree);
        }
    }

    BST_print_stats(tree);

    return 0;
}