#include <stdio.h>

int main() {
	char num[100];
	char name[100];

	printf("학번을 입력하시오. : ");
	scanf("%s", num);

	printf("이름을 입력하시오. : ");
	scanf("%s", name);

	printf("학번 :%s, 이름 : %s\n", num, name);
}
