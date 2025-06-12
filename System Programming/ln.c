#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int opt_s = 0;

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "s")) != -1) {
        switch (opt) {
            case 's':
                opt_s = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-s] <source> <destination>\n", argv[0]);
                fprintf(stderr, "   or: %s [-s] <source>... <directory>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind + 1 >= argc) {
        fprintf(stderr, "Usage: %s [-s] <source> <destination>\n", argv[0]);
        fprintf(stderr, "   or: %s [-s] <source>... <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *destination_arg = argv[argc - 1];

    struct stat dest_st;
    int is_destination_dir = 0;

    if (stat(destination_arg, &dest_st) == 0 && S_ISDIR(dest_st.st_mode)) {
        is_destination_dir = 1;
    }

    for (int i = optind; i < argc - (is_destination_dir ? 0 : 1); i++) {
        const char *source = argv[i];
        char destination_path[1024];

        if (is_destination_dir) {
            const char *base_name = strrchr(source, '/');
            if (base_name == NULL) {
                base_name = source;
            } else {
                base_name++;
            }
            snprintf(destination_path, sizeof(destination_path), "%s/%s", destination_arg, base_name);
        } else {
            if (argc - optind > 2) {
                fprintf(stderr, "%s: target '%s' is not a directory\n", argv[0], destination_arg);
                exit(EXIT_FAILURE);
            }
            strncpy(destination_path, destination_arg, sizeof(destination_path) - 1);
            destination_path[sizeof(destination_path) - 1] = '\0';
        }

        int ret;
        if (opt_s) {
            ret = symlink(source, destination_path);
        } else {
            ret = link(source, destination_path);
        }

        if (ret == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}