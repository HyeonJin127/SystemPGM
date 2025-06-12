#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[BUFSIZ];
    size_t bytes_read;
    int status = EXIT_SUCCESS;

    if (argc < 2) {
        while ((bytes_read = fread(buffer, 1, BUFSIZ, stdin)) > 0) {
            if (fwrite(buffer, 1, bytes_read, stdout) != bytes_read) {
                perror("cat: Error writing to stdout");
                status = EXIT_FAILURE;
                break;
            }
        }
        if (ferror(stdin)) {
            perror("cat: Error reading from stdin");
            status = EXIT_FAILURE;
        }
        return status;
    }

    for (int i = 1; i < argc; i++) {
        const char *file_path = argv[i];

        fp = fopen(file_path, "r");
        if (fp == NULL) {
            perror("cat");
            status = EXIT_FAILURE;
            continue;
        }

        while ((bytes_read = fread(buffer, 1, BUFSIZ, fp)) > 0) {
            if (fwrite(buffer, 1, bytes_read, stdout) != bytes_read) {
                perror("cat: Error writing to stdout");
                status = EXIT_FAILURE;
                break;
            }
        }

        if (ferror(fp)) {
            perror("cat: Error reading from file");
            status = EXIT_FAILURE;
        }

        if (fclose(fp) == EOF) {
            perror("cat: Error closing file");
            status = EXIT_FAILURE;
        }
    }

    return status;
}