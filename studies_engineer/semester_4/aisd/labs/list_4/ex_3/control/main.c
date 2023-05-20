#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../rb_bst/rb_bst.h"

int main() {
    int n;

    scanf("%d", &n);

    bool verbose = false;

    if (n <= 50) {
        verbose = true;   
    }

    RBTree* tree = RBT_create_tree();

    for (int i = 0; i < n; i++) {
        int key;
        scanf("%d", &key);
        RBT_insert(tree, key, verbose);    
        if (verbose) {
            printf("\n");
            RBT_print(tree);
        }
    }
    
    for (int i = 0; i < n; i++) {
        int key;
        scanf("%d", &key);
        RBT_delete(tree, key, verbose);
        if (verbose) {
            printf("\n");
            RBT_print(tree);
        }
    }

    return 0;
}