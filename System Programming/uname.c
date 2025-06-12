#include <stdio.h>
#include <sys/utsname.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    struct utsname info;

    if (uname(&info) != 0) {
        perror("uname");
        return 1;
    }

    if (argc == 1 || (argc == 2 && strcmp(argv[1], "-s") == 0)) {
        printf("%s\n", info.sysname);
    }
    else if (argc == 2 && strcmp(argv[1], "-n") == 0) {
        printf("%s\n", info.nodename);
    }
    else if (argc == 2 && strcmp(argv[1], "-r") == 0) {
        printf("%s\n", info.release);
    }
    else if (argc == 2 && strcmp(argv[1], "-v") == 0) {
        printf("%s\n", info.version);
    }
    else if (argc == 2 && strcmp(argv[1], "-m") == 0) {
        printf("%s\n", info.machine);
    }
    else if (argc == 2 && strcmp(argv[1], "-a") == 0) {
        printf("%s %s %s %s %s %s %s GNU/Linux\n", info.sysname, info.nodename, info.release, info.version, info.machine, info.machine, info.machine);
    }
    else {
        fprintf(stderr, "Usage: %s [-snrvma]\n", argv[0]);
        return 1;
    }

    return 0;
}