#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    FILE *source_fp;
    FILE *dest_fp;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    if (argc <= 2) {
        fprintf(stderr, "cp: missing file operand\n");
        fprintf(stderr, "Try 'cp --help' for more information.\n");
        exit(EXIT_FAILURE);
    } else if (argc == 3) {
        const char *source_path = argv[1];
        const char *dest_path = argv[2];

        source_fp = fopen(source_path, "rb");
        if (source_fp == NULL) {
            perror("cp: Failed to open source file");
            exit(EXIT_FAILURE);
        }

        dest_fp = fopen(dest_path, "wb");
        if (dest_fp == NULL) {
            perror("cp: Failed to open destination file");
            fclose(source_fp);
            exit(EXIT_FAILURE);
        }

        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, source_fp)) > 0) {
            if (fwrite(buffer, 1, bytes_read, dest_fp) != bytes_read) {
                perror("cp: Failed to write to destination file");
                fclose(source_fp);
                fclose(dest_fp);
                exit(EXIT_FAILURE);
            }
        }

        if (ferror(source_fp)) {
            perror("cp: Error reading from source file");
            fclose(source_fp);
            fclose(dest_fp);
            exit(EXIT_FAILURE);
        }

        if (fclose(source_fp) == EOF) {
            perror("cp: Error closing source file");
            exit(EXIT_FAILURE);
        }
        if (fclose(dest_fp) == EOF) {
            perror("cp: Error closing destination file");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "cp: target '%s': No such file or directory\n", argv[argc-1]);
        exit(EXIT_FAILURE);
    }

    return 0;
}