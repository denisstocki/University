#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../sp_bst/sp_bst.h"

int main() {
    int n;

    scanf("%d", &n);

    bool verbose = false;

    if (n <= 50) {
        verbose = true;   
    }

    SPTree* tree = SPT_create_tree();

    for (int i = 0; i < n; i++) {
        int key;
        scanf("%d", &key);
        SPT_insert(tree, key, verbose);    
        if (verbose) {
            printf("\n");
            SPT_print(tree);
        }
    }
    
    for (int i = 0; i < n; i++) {
        int key;
        scanf("%d", &key);
        SPT_delete(tree, key, verbose);
        if (verbose) {
            printf("\n");
            SPT_print(tree);
        }
    }

    return 0;
}