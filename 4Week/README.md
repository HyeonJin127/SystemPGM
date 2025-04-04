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

- 파일 복사 : `$ cp`
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
     
    - `$ cp 파일1 ... 파일n 디렉터리`
      - 여러 개의 파일들을 지정된 디렉터리에 모두 복사한다.
      ```
      $ cp cs1.txt cs2.txt /tmp
      $ ls -l /tmp/cs1.txt /tmp/cs2.txt
      -rw-r--r-- 1 skrmsp0423 skrmsp0423 0 Apr  5 00:20 /tmp/cs1.txt
      -rw-r--r-- 1 skrmsp0423 skrmsp0423 0 Apr  5 00:20 /tmp/cs2.txt
      ```
    - 디렉터리 전체 복사 : `$ cp -r`
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

- 파일 이동 : `$ mv (파일1) (파일2)`
  - 파일1의 이름을 파일2로 변경한다.
  ```
  $ mv cs2.txt cs3.txt
  $ ls -l cs2.txt cs3.txt
  ls: cannot access 'cs2.txt': No such file or directory
  -rw-r--r-- 1 skrmsp0423 skrmsp0423 0 Apr  5 00:09 cs3.txt
  ```
  
* * *

- 파일 속성
  |파일 속성|의미|
  |---|---|
  |블록 수|K 바이트 단위로 된 블록의 개수|
  |파일 종류|일반 파일(-), 디렉터리(d), 링크(l), pipe(p), soket(s), device(b or c) etc|
  |접근 권한|소유자, 그룹, 기타 사용자의 읽기(r), 쓰기(w), 실행(x) 권한|
  |하드 링크 수|파일에 대한 하드 링크 개수|
  |소유자 및 그룹|
  |파일 크기|
  |최종 수정 시간|

- 파일 : `$ file`
  - 파일의 종류에 대한 자세한 정보를 출력

- 

* * *

<h2 id='mission'>과제</h2>

- 알파벳을 입력받아 입력 받은 알파벳이 대문자이면 소문자로, 소문자면 대문자로 변환하여 출력하고 0을 입력하면 종료되는 C언어 프로그램을 작성하라.

```
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
