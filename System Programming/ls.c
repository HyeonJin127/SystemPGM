#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

int opt_a = 0;
int opt_F = 0;

void list_directory(const char *path);
void print_file_with_indicator(const char *filepath, const char *filename);

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "aF")) != -1) {
        switch (opt) {
            case 'a': 
                opt_a = 1;
                break;
            case 'F':
                opt_F = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-aF] [directory]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    const char *dir_path = (optind < argc) ? argv[optind] : ".";

    list_directory(dir_path);
    
    return 0;
}

void list_directory(const char *path) {
    DIR *dp;
    struct dirent *entry;
    char fullpath[1024];

    dp = opendir(path);
    if (dp == NULL) {
        perror("ls");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (!opt_a && (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || entry->d_name[0] == '.')) {
            continue;
        }

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (opt_F) {
            print_file_with_indicator(fullpath, entry->d_name);
        } else {
            printf("%s  ", entry->d_name);
        }
    }
    printf("\n");

    if (closedir(dp) == -1) {
        perror("ls");
        exit(EXIT_FAILURE);
    }
}

void print_file_with_indicator(const char *filepath, const char *filename) {
    struct stat st;
    char indicator = ' ';

    if (lstat(filepath, &st) == -1) {
        perror("lstat");
        printf("%s  ", filename);
        return;
    }

    if (S_ISDIR(st.st_mode)) {
        indicator = '/';
    } else if (S_ISLNK(st.st_mode)) {
        indicator = '@';
    } else if (S_ISFIFO(st.st_mode)) {
        indicator = '|';
    } else if (S_ISSOCK(st.st_mode)) {
        indicator = '=';
    } else if (S_ISREG(st.st_mode)) {
        if ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH)) {
            indicator = '*';
        }
    }

    printf("%s%c  ", filename, indicator);
}