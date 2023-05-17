#include <stdio.h>
#include <stdlib.h>
#include "options.h"

int main (int argc, char *argv[]) {
    options_t opts = parse_options(argc, argv);

    if (opts.option == 1){
        printf("Programme summoned with options -d -ss -oss.\n\n");
        printf("Options values:\n\n");
        printf("-d: %s\n", opts.d_val);
        printf("-ss: %s\n", opts.ss_val);
        printf("-oss: %s\n", opts.oss_val);
    } else if (opts.option == 2) {
        printf("Programme summoned with options -d -p2p -op2p.\n\n");
        printf("Options values:\n\n");
        printf("-d: %s\n", opts.d_val);
        printf("-p2p: %s\n", opts.p2p_val);
        printf("-op2p: %s\n", opts.op2p_val);
    } else {
        fprintf(stderr, "Usage 1: %s -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res\nUsage 2: %s -d plik_z_danymi.gr -p2p pary.p2p -op2p wyniki.p2p.res", argv[0], argv[0]);
        return 1;
    }
    
    return 0;
}
