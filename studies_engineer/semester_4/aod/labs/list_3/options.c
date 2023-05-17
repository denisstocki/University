#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include <libgen.h>
#include "options.h"

options_t parse_options (int argc, char *argv[]) {

    options_t result = {
        0, 0, 0, 0, 0, 
        NULL, NULL, NULL, NULL, NULL,
        0
    };
    int opt;

    while ((opt = getopt_long(argc, argv, "d:s:o:p:q:", LONG_OPTIONS, NULL)) != -1) {
        switch (opt) {
            case 'd':
                result.d_flag = true;
                result.d_val = optarg;
                break;
            case 's':
                result.ss_flag = true;
                result.ss_val = optarg;
                break;
            case 'o':
                result.oss_flag = true;
                result.oss_val = optarg;
                break;
            case 'p':
                result.p2p_flag = true;
                result.p2p_val = optarg;
                break;
            case 'q':
                result.op2p_flag = true;
                result.op2p_val = optarg;
                break;
            default:
                return result;
        }
    }

    if (result.d_flag && result.ss_flag && result.oss_flag && !result.p2p_flag && !result.op2p_flag) {
        result.option = 1;
    } else if (result.d_flag && !result.ss_flag && !result.oss_flag && result.p2p_flag && result.op2p_flag) {
        result.option = 2;
    } 

    return result;
}
