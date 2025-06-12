#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

int opt_R = 0;
int opt_h = 0;

int change_group_ownership(const char *path, gid_t new_gid, int apply_to_link);

void traverse_and_change_group(const char *base_path, gid_t new_gid, int apply_to_link);

int main(int argc, char *argv[]) {
    int opt;
    gid_t new_gid = (gid_t)-1;
    
    while ((opt = getopt(argc, argv, "Rh")) != -1) {
        switch (opt) {
            case 'R':
                opt_R = 1;
                break;
            case 'h':
                opt_h = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-Rh] GROUP FILE...\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind + 1 >= argc) {
        fprintf(stderr, "Usage: %s [-Rh] GROUP FILE...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *group_str = argv[optind];

    struct group *gr = getgrnam(group_str);
    if (gr == NULL) {
        fprintf(stderr, "%s: invalid group: '%s'\n", argv[0], group_str);
        exit(EXIT_FAILURE);
    }
    new_gid = gr->gr_gid;

    for (int i = optind + 1; i < argc; i++) {
        const char *path = argv[i];
        struct stat st;

        int stat_res;
        if (opt_h) {
            stat_res = lstat(path, &st);
        } else {
            stat_res = stat(path, &st);
        }

        if (stat_res == -1) {
            perror(path);
            continue;
        }

        if (S_ISDIR(st.st_mode) && opt_R) {
            traverse_and_change_group(path, new_gid, opt_h);
        } else {
            change_group_ownership(path, new_gid, opt_h);
        }
    }

    return 0;
}

int change_group_ownership(const char *path, gid_t new_gid, int apply_to_link) {
    int ret;
    if (apply_to_link) {
        ret = lchown(path, (uid_t)-1, new_gid);
    } else {
        ret = chown(path, (uid_t)-1, new_gid);
    }

    if (ret == -1) {
        perror(path);
        return -1;
    }
    return 0;
}

void traverse_and_change_group(const char *base_path, gid_t new_gid, int apply_to_link) {
    DIR *dir;
    struct dirent *entry;
    char full_path[1024];

    change_group_ownership(base_path, new_gid, apply_to_link);

    dir = opendir(base_path);
    if (dir == NULL) {
        perror(base_path);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(full_path, sizeof(full_path), "%s/%s", base_path, entry->d_name);

        struct stat st;
        int stat_res;
        
        if (apply_to_link) {
            stat_res = lstat(full_path, &st);
        } else {
            stat_res = stat(full_path, &st);
        }

        if (stat_res == -1) {
            perror(full_path);
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            traverse_and_change_group(full_path, new_gid, apply_to_link);
        } else {
            change_group_ownership(full_path, new_gid, apply_to_link);
        }
    }

    closedir(dir);
}