#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <errno.h>

const char* get_file_type_string(mode_t mode) {
    if (S_ISREG(mode)) return "regular file";
    if (S_ISDIR(mode)) return "directory";
    if (S_ISLNK(mode)) return "symbolic link";
    if (S_ISFIFO(mode)) return "FIFO";
    if (S_ISCHR(mode)) return "character device";
    if (S_ISBLK(mode)) return "block device";
    if (S_ISSOCK(mode)) return "socket";
    return "unknown";
}

void get_permissions_string(mode_t mode, char *perms_str) {
    perms_str[0] = S_ISDIR(mode) ? 'd' :
                   S_ISLNK(mode) ? 'l' :
                   S_ISCHR(mode) ? 'c' :
                   S_ISBLK(mode) ? 'b' :
                   S_ISFIFO(mode) ? 'p' :
                   S_ISSOCK(mode) ? 's' : '-';
    
    perms_str[1] = (mode & S_IRUSR) ? 'r' : '-';
    perms_str[2] = (mode & S_IWUSR) ? 'w' : '-';
    perms_str[3] = (mode & S_IXUSR) ? 'x' : '-';

    perms_str[4] = (mode & S_IRGRP) ? 'r' : '-';
    perms_str[5] = (mode & S_IWGRP) ? 'w' : '-';
    perms_str[6] = (mode & S_IXGRP) ? 'x' : '-';

    perms_str[7] = (mode & S_IROTH) ? 'r' : '-';
    perms_str[8] = (mode & S_IWOTH) ? 'w' : '-';
    perms_str[9] = (mode & S_IXOTH) ? 'x' : '-';
    
    if (mode & S_ISUID) perms_str[3] = (perms_str[3] == 'x') ? 's' : 'S';
    if (mode & S_ISGID) perms_str[6] = (perms_str[6] == 'x') ? 's' : 'S';
    if (mode & S_ISVTX) perms_str[9] = (perms_str[9] == 'x') ? 't' : 'T';

    perms_str[10] = '\0';
}

void print_file_info(const char *filepath) {
    struct stat st;
    
    int stat_result = stat(filepath, &st); 

    if (stat_result == -1) {
        perror(filepath);
        return;
    }

    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);

    const char *username = (pw != NULL) ? pw->pw_name : "UNKNOWN_USER";
    const char *groupname = (gr != NULL) ? gr->gr_name : "UNKNOWN_GROUP";

    char perms_str[11];
    get_permissions_string(st.st_mode, perms_str);

    printf("  File: '%s'", filepath);

    printf("\n");

    printf("  Size: %-10lld\tBlocks: %-10lld IO Block: %-6ld %s\n",
           (long long)st.st_size,
           (long long)st.st_blocks,
           (long)st.st_blksize,
           get_file_type_string(st.st_mode));

    printf("Device: %llxh/%lldd\tInode: %-10lld  Links: %-5lu\n",
           (long long)st.st_dev, (long long)st.st_dev,
           (long long)st.st_ino,
           (unsigned long)st.st_nlink);

    printf("Access: (%04o/%s)  Uid: (%5d/%-8s)   Gid: (%5d/%-8s)\n",
           st.st_mode & 07777, perms_str,
           (int)st.st_uid, username,
           (int)st.st_gid, groupname);

    char time_str[256];

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S.000000000 %z", localtime(&st.st_atim.tv_sec));
    printf("Access: %s\n", time_str);

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S.000000000 %z", localtime(&st.st_mtim.tv_sec));
    printf("Modify: %s\n", time_str);

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S.000000000 %z", localtime(&st.st_ctim.tv_sec));
    printf("Change: %s\n", time_str);
    
    printf("\n");
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s FILE...\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) { 
        print_file_info(argv[i]);
    }

    return 0;
}