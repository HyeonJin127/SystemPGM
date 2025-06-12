#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

#define READ_BUFFER_SIZE 4096 

int opt_b = 0;

void identify_file_type(const char *filepath, const char *filename) {
    struct stat st;
    char buffer[READ_BUFFER_SIZE];
    ssize_t bytes_read;
    int fd = -1;

    if (lstat(filepath, &st) == -1) {
        perror(filename);
        return;
    }

    if (!opt_b) {
        printf("%s: ", filename);
    }

    if (S_ISDIR(st.st_mode)) {
        printf("directory\n");
        return;
    } else if (S_ISLNK(st.st_mode)) {
        char link_target[1024];
        ssize_t len = readlink(filepath, link_target, sizeof(link_target) - 1);
        if (len != -1) {
            link_target[len] = '\0';
            printf("symbolic link to %s\n", link_target);
        } else {
            perror("readlink failed");
            printf("symbolic link\n");
        }
        return;
    } else if (S_ISCHR(st.st_mode)) {
        printf("character special\n");
        return;
    } else if (S_ISBLK(st.st_mode)) {
        printf("block special\n");
        return;
    } else if (S_ISFIFO(st.st_mode)) {
        printf("fifo (named pipe)\n");
        return;
    } else if (S_ISSOCK(st.st_mode)) {
        printf("socket\n");
        return;
    }

    fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        if (errno == EACCES) {
             printf("regular file (permission denied)\n");
        } else {
             perror("open failed");
             printf("regular file\n");
        }
    }

    bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("read failed");
        printf("regular file\n");
        close(fd);
        return;
    }
    close(fd);

    if (bytes_read < sizeof(buffer)) {
        buffer[bytes_read] = '\0';
    } else {
        buffer[sizeof(buffer) - 1] = '\0';
    }

    if (st.st_size == 0) {
        printf("empty\n");
        return;
    }

    if (bytes_read >= 2 && buffer[0] == '#' && buffer[1] == '!') {
        char *newline = strchr(buffer + 2, '\n');
        if (newline != NULL) {
            *newline = '\0';
            printf("script, interpreter %s\n", buffer + 2);
        } else {
            printf("script\n");
        }
        return;
    }

    if (bytes_read >= 4 && 
        buffer[0] == 0x7F && buffer[1] == 'E' && 
        buffer[2] == 'L' && buffer[3] == 'F') {
        printf("ELF %d-bit %s executable\n", 
               (bytes_read > 4 && buffer[4] == 1) ? 32 : 64,
               (bytes_read > 5 && buffer[5] == 1) ? "LSB" : "MSB");
        return;
    }

    int is_text = 1;
    for (ssize_t i = 0; i < bytes_read; ++i) {
        if (buffer[i] < 0x20 && buffer[i] != 0x09 && buffer[i] != 0x0A && buffer[i] != 0x0D) {
            is_text = 0;
            break;
        }
        if (buffer[i] > 0x7E) {
            is_text = 0;
            break;
        }
    }

    if (is_text) {
        if (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
            printf("ASCII text executable\n");
        } else {
            printf("ASCII text\n");
        }
        return;
    }

    printf("data\n");
}

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "b")) != -1) {
        switch (opt) {
            case 'b':
                opt_b = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-b] <file_name(s)>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind == argc) {
        fprintf(stderr, "Usage: %s <file_name(s)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        identify_file_type(argv[i], argv[i]);
    }

    return 0;
}