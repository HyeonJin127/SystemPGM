#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH_LEN 4096
#define MAX_CMD_LEN 256

int main(int argc, char *argv[]) {
    char *path_env;
    char *path_copy;
    char *dir;
    char full_path[MAX_PATH_LEN + MAX_CMD_LEN + 2];

    if (argc != 2) {
        exit(EXIT_FAILURE);
    }

    const char *command_name = argv[1];

    path_env = getenv("PATH");
    if (path_env == NULL) {
        fprintf(stderr, "Error: PATH environment variable not set.\n");
        exit(EXIT_FAILURE);
    }

    path_copy = strdup(path_env);
    if (path_copy == NULL) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    dir = strtok(path_copy, ":");

    while (dir != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command_name);

        if (access(full_path, F_OK | X_OK) == 0) {
            printf("%s\n", full_path);
            free(path_copy);
            return 0;
        }

        dir = strtok(NULL, ":");
    }

    fprintf(stderr, "%s not found in PATH\n", command_name);
    free(path_copy);
    return 1;
}