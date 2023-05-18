#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int main(int argc, char **argv) {

    if (argc != 2){
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    assert(n > 0);

    srand(time(NULL));

    printf("%d\n", n);

    for (int i = 0; i < 2 * n; i++) {
        printf("%d ", rand() % (2 * n));
    }

    return 0;
}