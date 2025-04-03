#include <stdio.h>
#include <stdbool.h>

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