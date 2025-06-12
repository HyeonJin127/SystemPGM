#include <stdio.h>
#include <unistd.h> // gethostname 함수 사용하기 위해
#include <limits.h>
#include <errno.h>

int main() {
    char hostname[HOST_NAME_MAX + 1];

    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("%s\n", hostname);
    } else {
        perror("hostname");
        return 1;
    }

    return 0;
}