#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "options.h"

typedef struct {
    char **lines;
    size_t count;
} LinesArray;

void sp_time_problem(options_t, char *);
int open_file(LinesArray *, char *, char *, char);

int main (int argc, char *argv[]) {

    options_t opts = parse_options(argc, argv);

    if (opts.option == 1){
        printf("Programme summoned with options -d --ss --oss.\n\n");
        printf("Options values:\n\n");
        printf("-d: %s\n", opts.d_val);
        printf("--ss: %s\n", opts.ss_val);
        printf("--oss: %s\n", opts.oss_val);
        sp_time_problem(opts, argv[0]);
    } else if (opts.option == 2) {
        printf("Programme summoned with options -d --p2p --op2p.\n\n");
        printf("Options values:\n\n");
        printf("-d: %s\n", opts.d_val);
        printf("--p2p: %s\n", opts.p2p_val);
        printf("--op2p: %s\n", opts.op2p_val);
    } else {
        fprintf(stderr, "Usage 1: %s -d plik_z_danymi.gr --ss zrodla.ss --oss wyniki.ss.res\nUsage 2: %s -d plik_z_danymi.gr --p2p pary.p2p --op2p wyniki.p2p.res\n", argv[0], argv[0]);
        return 1;
    }
    
    return 0;
}

void sp_time_problem(options_t opts, char *programme_name) {

    LinesArray lines_d = {NULL, 0};
    LinesArray lines_ss = {NULL, 0};
    LinesArray lines_oss = {NULL, 0};

    if (open_file(&lines_d, opts.d_val, programme_name, "r") == -1
        || open_file(&lines_ss, opts.ss_val, programme_name, "r") == -1
    ) {
        return;
    }
}

int open_file(LinesArray *lines_array, char *file_name, char *programme_name, char mode) {

    FILE *file = fopen(file_name, mode);

    if (file == NULL) {
        fprintf(stderr, "%s: file could not be opened %s\n", programme_name, file_name);
        return -1;
    }
    
    char *line = NULL;
    size_t line_length = 0;

    while (getline(&line, &line_length, file) != -1) {
        lines_array -> count++;
        lines_array -> lines = realloc(lines_array -> lines, lines_array -> count * sizeof(char *));
        lines_array -> lines[lines_array -> count - 1] = line;
        line = NULL;
        line_length = 0;
    }

    return 1;
}
