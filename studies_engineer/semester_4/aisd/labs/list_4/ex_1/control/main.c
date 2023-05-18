#include <stdio.h>
#include "../bst/bs_tree.h"

int main() {

    int n;

    scanf("%d", &n);

    BSTree* tree = BST_create_tree();

    for (int i = 0; i < n; i++) {
        int key;
        scanf("%d", &key);
        BST_insert(tree, key);    
        printf("\n");
        BST_print(tree);
    }
    
    for (int i = 0; i < n; i++) {
        int key;
        scanf("%d", &key);
        BST_delete(tree, key);
        printf("\n");
        BST_print(tree);
    }

    return 0;
}