#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int opt_append = 0;

int main(int argc, char *argv[]) {
    int opt;
    FILE **output_files = NULL;
    int num_output_files = 0;

    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
            case 'a':
                opt_append = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [FILE...]\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    num_output_files = argc - optind;

    if (num_output_files > 0) {
        output_files = (FILE **)malloc(sizeof(FILE *) * num_output_files);
        if (output_files == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }

        for (int i = 0; i < num_output_files; i++) {
            const char *filepath = argv[optind + i];
            const char *mode = opt_append ? "a" : "w";

            output_files[i] = fopen(filepath, mode);
            if (output_files[i] == NULL) {
                perror(filepath);
            }
        }
    }

    int ch;
    while ((ch = getchar()) != EOF) {
        if (putchar(ch) == EOF) {
            perror("putchar");
            
            break; 
        }

        for (int i = 0; i < num_output_files; i++) {
            if (output_files[i] != NULL) {
                if (fputc(ch, output_files[i]) == EOF) {
                    perror(argv[optind + i]);
                    fclose(output_files[i]);
                    output_files[i] = NULL;
                }
            }
        }
    }

    for (int i = 0; i < num_output_files; i++) {
        if (output_files[i] != NULL) {
            fclose(output_files[i]);
        }
    }
    
    if (output_files != NULL) {
        free(output_files);
    }

    return 0;
}