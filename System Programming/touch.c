#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "블라");
        exit(EXIT_FAILURE);
    }

    int status = EXIT_SUCCESS;

    for (int i = 1; i < argc; i++) {
        const char *filename = argv[i];
        struct stat st;
        int file_exists = 0;
        int fd;

        if (stat(filename, &st) == 0) {
            file_exists = 1;
        } else {
            if (errno != ENOENT) {
                perror(filename);
                status = EXIT_FAILURE;
                continue;
            }
        }

        if (file_exists) {
            struct timeval current_times[2];

            if (gettimeofday(&current_times[0], NULL) == -1) {
                perror("gettimeofday");
                status = EXIT_FAILURE;
                continue;
            }
            current_times[1] = current_times[0];

            if (utimes(filename, current_times) == -1) {
                perror(filename);
                status = EXIT_FAILURE;
            }
        } else {
            fd = open(filename, O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IWOTH);
            if (fd == -1) {
                perror(filename);
                status = EXIT_FAILURE;
            } else {
                close(fd);
            }
        }
    }

    return status;
}