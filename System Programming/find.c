#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

char *g_search_name = NULL;

void find_recursive(const char *current_path) {
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char full_path[PATH_MAX];

    dir = opendir(current_path);
    if (dir == NULL) {
        fprintf(stderr, "find: '%s': %s\n", current_path, strerror(errno));
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (snprintf(full_path, sizeof(full_path), "%s/%s", current_path, entry->d_name) >= sizeof(full_path)) {
            fprintf(stderr, "find: path too long: %s/%s\n", current_path, entry->d_name);
            continue;
        }

        if (lstat(full_path, &st) == -1) {
            fprintf(stderr, "find: '%s': %s\n", full_path, strerror(errno));
            continue;
        }

        if (g_search_name != NULL) {
            if (strcmp(entry->d_name, g_search_name) == 0) {
                printf("%s\n", full_path);
            }
        } else {
            printf("%s\n", full_path);
        }

        if (S_ISDIR(st.st_mode)) {
            find_recursive(full_path);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    char *start_path = ".";
    int opt;

    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                g_search_name = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [start_path] [-n NAME]\n", argv[0]);
                fprintf(stderr, "Example: %s -n myfile.txt\n", argv[0]);
                fprintf(stderr, "Example: %s /home/user -n mydir\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    if (optind < argc) {
        start_path = argv[optind];
        if (optind + 1 < argc) {
            fprintf(stderr, "Usage: %s [start_path] [-n NAME]\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    printf("Searching in '%s' for '%s'...\n", start_path, (g_search_name ? g_search_name : "all files/directories"));

    find_recursive(start_path);

    return 0;
}