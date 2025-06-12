#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;

    if (argc == 1) {
        fprintf(stderr, "missing operand");
        fprintf(stderr, "Try 'mkdir --help' for more information.");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 1; i < argc; i++) {
        const char *dir_name = argv[i];
    
        if (mkdir(dir_name, mode) != 0) {
            perror("mkdir");
            return 1;
        }
    }

    return 0;
}