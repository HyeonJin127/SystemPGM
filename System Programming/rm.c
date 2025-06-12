#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "rm: missing operand\nTry 'rm --help' for more information.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        const char *file_to_remove = argv[i];

        if (unlink(file_to_remove) != 0) {
            perror("rm");
            return 1;
        }
    }

    return 0;
}