#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int opt_l = 0;
int opt_w = 0;
int opt_c = 0;

typedef struct {
    long lines;
    long words;
    long bytes;
} file_stats_t;

void calculate_file_stats(FILE *file_ptr, const char *filename, file_stats_t *stats_out) {
    int ch;
    long lines = 0;
    long words = 0;
    long bytes = 0;
    int in_word = 0;

    while ((ch = fgetc(file_ptr)) != EOF) {
        bytes++;

        if (ch == '\n') {
            lines++;
        }

        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
            in_word = 0;
        } else if (in_word == 0) {
            words++;
            in_word = 1;
        }
    }

    stats_out->lines = lines;
    stats_out->words = words;
    stats_out->bytes = bytes;
}

int main(int argc, char *argv[]) {
    int opt;
    file_stats_t total_stats = {0, 0, 0}; 
    int has_files_to_process = 0;

    while ((opt = getopt(argc, argv, "lwc")) != -1) {
        switch (opt) {
            case 'l': opt_l = 1; break;
            case 'w': opt_w = 1; break;
            case 'c': opt_c = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-lwc] [FILE...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (!opt_l && !opt_w && !opt_c) {
        opt_l = 1;
        opt_w = 1;
        opt_c = 1;
    }

    if (optind == argc) {
        has_files_to_process = 1;
        file_stats_t current_file_stats;
        calculate_file_stats(stdin, "", &current_file_stats);

        if (opt_l) printf("%7ld", current_file_stats.lines);
        if (opt_w) printf("%8ld", current_file_stats.words);
        if (opt_c) printf("%8ld", current_file_stats.bytes);
        printf("\n");

    } else {
        has_files_to_process = 1;
        int files_processed_count = 0;

        for (int i = optind; i < argc; i++) {
            const char *filepath = argv[i];
            FILE *fp = fopen(filepath, "r");
            if (fp == NULL) {
                perror(filepath);
                continue;
            }

            file_stats_t current_file_stats;
            calculate_file_stats(fp, filepath, &current_file_stats);
            fclose(fp);

            if (opt_l) printf("%7ld", current_file_stats.lines);
            if (opt_w) printf("%8ld", current_file_stats.words);
            if (opt_c) printf("%8ld", current_file_stats.bytes);
            printf(" %s\n", filepath);

            total_stats.lines += current_file_stats.lines;
            total_stats.words += current_file_stats.words;
            total_stats.bytes += current_file_stats.bytes;
            files_processed_count++;
        }

        if (files_processed_count > 1) {
            if (opt_l) printf("%7ld", total_stats.lines);
            if (opt_w) printf("%8ld", total_stats.words);
            if (opt_c) printf("%8ld", total_stats.bytes);
            printf(" total\n");
        }
    }

    return 0;
}