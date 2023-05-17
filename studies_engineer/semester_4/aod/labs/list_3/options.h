#pragma once

#include <getopt.h>
#include <stdbool.h>

typedef struct {
    bool d_flag;
    bool ss_flag;
    bool oss_flag;
    bool p2p_flag;
    bool op2p_flag;

    char *d_val;
    char *ss_val;
    char *oss_val;
    char *p2p_val;
    char *op2p_val;

    int option;
} options_t;

static struct option LONG_OPTIONS[] = {
    {"ss", required_argument, 0, 'q'},
    {"oss", required_argument, 0, 'w'},
    {"p2p", required_argument, 0, 'e'},
    {"op2p", required_argument, 0, 'r'},
    {0, 0, 0, 0}
};

options_t parse_options(int argc, char *argv[]);
