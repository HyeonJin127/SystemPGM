# 4 Week

* * *

# 파일 사용

* * *

## 목차

1. [파일 복사](#01)

2. [파일 이동](#02)

3. [파일 삭제](#03)

4. [링크](#04)

5. [파일 속성](#05)

6. [접근 권한](#06)

7. [기타 파일 속성 변경](#07)

8. [과제](#08)

* * *

<h2 id='01'>파일 복사</h2>

- 파일 복사 : `$ cp [-i] (파일1) (파일2)`
  - 파일1을 파일2에 복사한다.<br />
    ```
    $ cp cs1.txt  cs2.txt
    $ ls -l cs1.txt cs2.txt
    -rw-r--r-- 1 skrmsp0423 skrmsp0423 0 Apr  5 00:08 cs1.txt
    -rw-r--r-- 1 skrmsp0423 skrmsp0423 0 Apr  5 00:09 cs2.txt
    ```

  - 파일을 디렉터리로 복사
    - `$ cp (파일) (디렉터리)`
      - 파일을 지정된 디렉터리에 복사한다.
      ```
      $ cp cs1.txt /tmp
      skrmsp0423@DESKTOP-TOOG12Q:~/0404$ ls -l /tmp/cs1.txt
      -rw-r--r-- 1 skrmsp0423 skrmsp0423 0 Apr  5 00:18 /tmp/cs1.txt
      ```
     
    - `$ cp (파일1 ... 파일n) (디렉터리)`
      - 여러 개의 파일들을 지정된 디렉터리에 모두 복사한다.
      ```
      $ cp cs1.txt cs2.txt /tmp
      $ ls -l /tmp/cs1.txt /tmp/cs2.txt
      -rw-r--r-- 1 skrmsp0423 skrmsp0423 0 Apr  5 00:20 /tmp/cs1.txt
      -rw-r--r-- 1 skrmsp0423 skrmsp0423 0 Apr  5 00:20 /tmp/cs2.txt
      ```
    - 디렉터리 전체 복사 : `$ cp [-r] (디렉터리1) (디렉터리2)`
      - r은 리커전 옵션으로 디렉터리1 전체를 디렉터리2에 복사한다.
      ```
      $ cp -r test tmp
      $ cd tmp
      p$ ls -l
      total 0
      drwxr-xr-x 1 skrmsp0423 skrmsp0423 512 Apr  5 00:23 test
      ```

* * *

<h2 id='02'>파일 이동</h2>

- 파일 이동 : `$ mv [-i] (파일1) (파일2)`
  - 파일1의 이름을 파일2로 변경한다.
  ```
  $ mv cs2.txt cs3.txt
  $ ls -l cs2.txt cs3.txt
  ls: cannot access 'cs2.txt': No such file or directory
  -rw-r--r-- 1 skrmsp0423 skrmsp0423 0 Apr  5 00:09 cs3.txt
  ```

  - 파일을 디렉터리로 이동
    - `$ mv (파일) (디렉터리)`
      - 파일을 지정된 디렉터리로 이동한다.
      ```
      $ mv cs3.txt /tmp
      $ ls -l /tmp/cs3.txt
      -rw-r--r-- 1 skrmsp0423 skrmsp0423 0 Apr  5 00:09 /tmp/cs3.txt
      ```

    - `$ mv (파일1 ... 파일n) (디렉터리)`
      - 여러 개의 파일들을 지정된 디렉터리로 모두 이동한다.
      ```
      $ mv cs1.txt cs2.txt cs3.txt test
      ```

  - 디렉터리 이름 변경 : `$ mv (디렉터리1) (디렉터리2)`
    - 디렉터리1을 지정된 디렉터리2로 이름을 변경한다.
    ```
    $ mv test test2
    $ ls
    test2
    ```

* * *

<h2 id='03'>파일 삭제</h2>

- 파일 삭제 : `$ rm [-i] (파일)`
  - 파일(들)을 삭제한다.
  ```
  $ rm cs1.txt
  $ rm cs2.txt cs3.txt
  ```

- 디렉터리 전체 삭제 : `$ rm [-ri] (디렉터리)`
  - -r은 리커전 옵션으로 디렉터리 아래의 모든 것을 삭제한다.
  ```
  $ rm -r test
  ```

* * *

<h2 id='04'>링크</h2>

- 링크
  - `$ ln [-s] (파일1) (파일2)`
    - 파일1에 대한 새로운 이름(링크)로 파일2를 만들어 준다.
    - -s 옵션은 심볼릭 링크
   
  - `$ ln [-s] (파일1) (디렉터리)`
    - 파일1엘 대한 링크를 지정된 디렉터리에 같은 이름으로 만들어 준다.

- 하드 링크
  - 기존 파일에 대한 새로운 이름이라고 생각할 수 있다.
  - 실제로 기존 파일을 대표하는 i-노드를 가리켜 구현한다.
  ```
  $ ln hello.c hi.c
  $ ls -l
  -rw-r--r-- 2 skrmsp0423 skrmsp0423    60 Apr  5 19:40 hello.c
  -rw-r--r-- 2 skrmsp0423 skrmsp0423    60 Apr  5 19:40 hi.c
  ```

  > **If.** 이 중에 한 파일의 내용을 수정한다면?
  >  - 두 파일의 내용이 다 수정 됨.
  >    - 수정 전
  >    ```
  >    $ cat hello.c
  >    #include <stdio.h>
  >    
  >    int main() {
  >            printf("Hello World!");
  >    }
  >    $ cat hi.c
  >    #include <stdio.h>
  >
  >    int main() {
  >            printf("Hello World!");
  >    }
  >    ```
  >    
  >    - 수정 후
  >    ```
  >    $ cat hello.c
  >    #include <stdio.h>
  >   
  >    int main() {
  >            printf("Hello!");
  >    }
  >    $ cat hi.c
  >    #include <stdio.h>
  >    
  >    int main() {
  >            printf("Hello!");
  >    }
  >    ```
  
  > **If.** 이 둘 중에 한 파일을 삭제한다면?
  >  - `$ rm` 명령어로 삭제한 파일만 삭제되고 나머지 파일은 그대로 있음.
  >    - 링크로 만든 파일을 삭제한 경우
  >    ```
  >    $ rm hi.c
  >    hello.c
  >    ```
  >
  >    - 원래 파일을 삭제한 경우
  >    ```
  >    $ rm hello.c
  >    hi.c
  >    ```

  
- 심볼릭 링크
  - 다른 파일을 가리키고 있는 별도의 파일.
  - 실제 파일의 경로명을 저장하고 있는 일종의 특수 파일.
  - 이 경로명이 다른 파일에 대한 간접적인 포인터 역할을 함.
  ```
  $ ln -s hello.c hi.c
  $ ls -l
  -rw-r--r-- 1 skrmsp0423 skrmsp0423    54 Apr  5 19:45 hello.c
  lrwxrwxrwx 1 skrmsp0423 skrmsp0423     7 Apr  5 19:51 hi.c -> hello.c
  ```
  
* * *

<h2 id='05'>파일 속성</h2>

- 파일 속성
  - 블록 수, 파일 종류, 접근권한, 링크 수, 소유자 및 그룹, 수정 시간
    |파일 속성|의미|
    |---|---|
    |블록 수|K 바이트 단위로 된 블록의 개수|
    |파일 종류|일반 파일(-), 디렉터리(d), 링크(l), pipe(p), soket(s), device(b or c) etc|
    |접근 권한|소유자, 그룹, 기타 사용자의 읽기(r), 쓰기(w), 실행(x) 권한|
    |하드 링크 수|파일에 대한 하드 링크 개수|파일에 대한 소유자, 그룹, 기타 사용자의 읽기(r)/쓰기(w)/실행(x) 권한|
    |소유자 및 그룹|파일의 소유자 ID 및 소유자가 속한 그룸|
    |파일 크기|파일의 크기(바이트 단위)|
    |최종 수정 시간|파일을 생성 혹은 최후로 수정한 시간|

- 파일 종류
  - 리눅스에서 지원하는 파일 종류
    |파일 종류|표시|설명|
    |---|---|---|
    |일반파일|-|데이터를 갖고 있는 텍스트 파일 또는 이진 파일|
    |디렉터리 파일|d|디렉터리 내의 파일들의 이름들과 파일 정보를 관리하는 파일|
    |문자 장치 파일|c|문자 단위로 데이터를 전송하는 장치를 나타내는 파일|
    |블록 장치 파일|b|블록 단위로 데이터를 전송하는 장치를 나타내는 파일|
    |FIFO 파일|p|프로세스 간 통신에 사용되는 이름 있는 파이프|
    |소켓|s|네트워크를 통한 프로세스 간 통신에 사용되는 파일|
    |심볼릭 링크|l|다른 파일을 가리키는 포인터와 같은 역할을 하는 파일|

  - 파일 : `$ file`
    - 파일의 종류에 대한 자세한 정보를 출력
    ```
    $ file hello.txt
    hello.txt: ASCII text
    ```

* * *

<h2 id='06'>접근권한</h2>

- 접근권한
  - 파일에 대한 읽기(r), 쓰기(w), 실행(x) 권한
  - 소유자(owner) / 그룹(group) / 기타(others)로 구분하여 관리
    
- 예
  |접근권한|의미|
  |---|---|
  |rwxrwxrwx|소유자, 그룹, 기타 사용자 모두 읽기, 쓰기, 실행 가능|
  |rwxr-xr-x|소유자만 읽기, 쓰기, 실행 가능, <br /> 그룹, 기타 사용자는 읽기, 실행 가능|
  |rw-rw-r--|소유자와 그룹만 읽기, 쓰기 가능, <br /> 기타 사용자는 읽기만 가능|
  |rw-r--r--|소유자만 읽기, 쓰기 가능, <br /> 그룹, 기타 사용자는 읽기만 가능|
  |rw-r-----|소유자만 읽기, 쓰기 가능, <br /> 그룹은 읽기만 가능|
  |rwx------|소유자만 읽기, 쓰기, 실행 가능|
  
- 접근권한 변경 : `$ chmod [-R] (접근권한 파일 혹은 디렉터리)`
  - 파일 혹은 디렉터리의 접근권한을 변경한다. -R 옵션을 사용하면 지정된 디렉터리 아래의 모든 파일과 하위 디렉터리에 대해서도 접근권한을 변경한다.
    
- 접근권한 표현
  - 8진수
    -rwx 를 권한이 있으면 1, 없으면 0으로 표시
    |접근권한|8진수|
    |---|---|
    |rwxrwxrwx|777|
    |rwxr-xr-x|755|
    |rw-rw-r--|664|
    |rw-r--r--|644|
    |rw-r-----|640|
    |rwx------|700|
    
  - 기호
    - 기호를 이용한 접근권한 변경
      |구분|기호와 의미|
      |---|---|
      |사용자 범위|u(user: 소유자), g(group: 그룹), o(others: 기타 사용자), a(all: 모든 사용자)|
      |연산자|+(권한 추가), -(권한 제거), =(권한 설정)|
      |권한|r(읽기 권한), w(읽기 권한), x(실행 권한)|

      ```
      $ chmod g-w cs1.txt
      $ ls -l cs1.txt
      -rw-r--r-- 1 skrmsp0423 skrmsp0423 0 Apr  5 20:04 cs1.txt
      ```
      ```
      $chmod o-r cs1.txt
      $ ls -l cs1.txt
      -rw-r----- 1 skrmsp0423 skrmsp0423 0 Apr  5 20:04 cs1.txt
      ```
      ```
      $ chmod g+w,o+rw cs1.txt
      $ ls -l cs1.txt
      -rw-rw-rw- 1 skrmsp0423 skrmsp0423 0 Apr  5 20:04 cs1.txt
      ```
    
* * *

<h2 id='07'>기타 파일 속성 변경</h2>

- 소유자 변경 : `$ chown [-R] (사용자) (파일)`
  - 파일 혹은 디렉터리의 소유자를 지정된 사용자로 변경한다.
  
- 그룹 변경 : `$ chgrp [-R] (그룹) (파일 또는 디렉터리)`
  - 파일 혹은 디렉터리의 그룹을 지정된 그룹으로 변경한다.

- 최종 수정 시간 변경 : `$ touch (파일)`
  - 파일의 최종 사용 시간과 최종 수정 시간을 현재 시간으로 변경한다.
  ```
  $ ls -l cs1.txt
  -rw-rw-rw- 1 skrmsp0423 skrmsp0423 0 Apr  5 20:04 cs1.txt
  $ touch cs1.txt
  $ ls -l cs1.txt
  -rw-rw-rw- 1 skrmsp0423 skrmsp0423 0 Apr  5 21:38 cs1.txt
  ```
  
* * *

<h2 id='08'>과제</h2>

- 알파벳을 입력받아 입력 받은 알파벳이 대문자이면 소문자로, 소문자면 대문자로 변환하여 출력하고 0을 입력하면 종료되는 C언어 프로그램을 작성하라.

```C
int main() {
        char tmp;
        char ans;

        printf("문자 입력 : ");
        scanf(" %c", &tmp);

        while(true) {
                if (tmp == '0') {
                        return 0;
                }
                else if (tmp >= 'a' && tmp <= 'z') {
                        ans = tmp - 32;
                        printf("%c의 대문자는 %c입니다.\n", tmp, ans);
                } else if (tmp >= 'A' && tmp <= 'Z') {
                        ans = tmp + 32;
                        printf("%c의 소문자는 %c입니다.\n", tmp, ans);
                }

                printf("문자 입력 : ");
                scanf(" %c", &tmp);
        }

        return 0;
}
```
