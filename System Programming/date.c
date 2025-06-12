#include <stdio.h>
#include <time.h>

int main() {
    time_t now;

    struct tm *info;
    char buffer[80];

    time(&now);
    info = localtime(&now);

    // %a : 요일
    // %b : 월
    // %d : 일
    // %H : 24시간 기준 시간
    // %M : 분
    // %S : 초
    // %Z : 시간대 이름
    // %Y : 4자리 연도
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Z %Y", info);

    printf("%s\n", buffer);

    return 0;
}