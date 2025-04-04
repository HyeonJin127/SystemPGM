# 5 Week

* * *

## 과제

### 문제

0 ~ 255 사이의 수를 입력 받아 2진수로 출력하고, 1의 개수가 몇 개 인지 출력하고, 8비트 중에 상위 4비트를 출력하는 프로그램을 C로 작성
위를 생성형 AI를 이용해 프로그래밍.

* * *

### 코드

생성형 AI인 Chat GPT 를 이용해 나온 코드
```C
#include <stdio.h>

int main() {
    int num;

    // 사용자로부터 입력 받기
    printf("0~255 사이의 정수를 입력하세요: ");
    scanf("%d", &num);

    // 입력값 범위 확인
    if (num < 0 || num > 255) {
        printf("입력값이 범위를 벗어났습니다.\n");
        return 1;
    }

    // 8비트 이진수 출력 및 1의 개수 세기
    int count = 0;
    printf("8비트 2진수: ");
    for (int i = 7; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
        if (bit == 1) {
            count++;
        }
    }
    printf("\n");

    // 1의 개수 출력
    printf("1의 개수: %d개\n", count);

    // 상위 4비트 출력
    int upper4 = (num >> 4) & 0x0F;  // 상위 4비트 추출
    printf("상위 4비트: ");
    for (int i = 3; i >= 0; i--) {
        printf("%d", (upper4 >> i) & 1);
    }
    printf("\n");

    return 0;
}
```   

* * *

### 코드 실행 후 

```
skrmsp0423@DESKTOP-TOOG12Q:~/0404$ ./mission
0~255 사이의 정수를 입력하세요: 127
8비트 2진수: 01111111
1의 개수: 7개
상위 4비트: 0111
```
```
skrmsp0423@DESKTOP-TOOG12Q:~/0404$ ./mission
0~255 사이의 정수를 입력하세요: 88
8비트 2진수: 01011000
1의 개수: 3개
상위 4비트: 0101
```
