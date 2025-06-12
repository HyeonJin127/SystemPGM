#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "chmod: missing operand\nTry 'chmod --help' for more information.\n");
        exit(EXIT_FAILURE);
    }

    const char *perms_str = argv[1];
    mode_t new_mode;

    char *endptr;
    new_mode = (mode_t)strtol(perms_str, &endptr, 8);

    if (*endptr != '\0' || endptr == perms_str) {
        fprintf(stderr, "chmod: invalid mode: '%s'\n", perms_str);
        exit(EXIT_FAILURE);
    }

    if (new_mode < 0 || new_mode > 07777) {
        fprintf(stderr, "chmod: mode out of range: '%s' (0-7777 octal expected)\n", perms_str);
        exit(EXIT_FAILURE);
    }

    for (int i = 2; i < argc; i++) {
        const char *path_to_change = argv[i];

        if (chmod(path_to_change, new_mode) != 0) {
            perror("chmod");
            return 1;
        }
    }    

    return 0;
}