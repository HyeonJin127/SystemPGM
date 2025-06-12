#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "mv: missing file operand\n");
        fprintf(stderr, "Try 'mv --help' for more information.\n");
        exit(EXIT_FAILURE);
    }

    const char *source_path = argv[1];
    const char *dest_path = argv[2];

    if (rename(source_path, dest_path) != 0) {
        perror("mv");
        return 1;
    }

    return 0;
}