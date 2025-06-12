#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main() {
    char *cwd_path;

    cwd_path = getcwd(NULL, 0);

    if (cwd_path != NULL) {
        printf("%s\n", cwd_path);

        free(cwd_path);
    } else {
        perror("pwd");
        return 1;
    }

    return 0;
}