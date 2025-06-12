#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>

int main() {
    uid_t uid;
    struct passwd *pw;
    
    uid = getuid();

    pw = getpwuid(uid);

    if (pw != NULL) {
        printf("%s\n", pw->pw_name);
    } else {
        perror("whoami");
        return 1;
    }

    return 0;
}