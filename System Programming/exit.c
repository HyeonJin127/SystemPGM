#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int exit_status = EXIT_SUCCESS;

    if (argc > 1) {
        char *endptr;
        long status_val;

        status_val = strtol(argv[1], &endptr, 10);

        if (endptr == argv[1] || *endptr != '\0' || (status_val == 0 && errno != 0)) {
            fprintf(stderr, "%s: '%s': numeric argument required\n", argv[0], argv[1]);
            exit(EXIT_FAILURE); 
        }

        exit_status = (int)(status_val % 256);
        if (exit_status < 0) {
            exit_status += 256;
        }
    }

    exit(exit_status);

    return EXIT_SUCCESS;
}