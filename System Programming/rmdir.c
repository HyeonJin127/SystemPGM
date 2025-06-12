#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory_name(s)>\n", argv[0]);
        fprintf(stderr, "Note: Only empty directories can be removed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        const char *dir_to_remove = argv[i];

        if (rmdir(dir_to_remove) != 0) {
            perror("rmdir");
            return 1;
        }
    }

    return 0;
}