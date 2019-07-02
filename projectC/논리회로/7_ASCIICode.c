#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

int main() {

	char input_char = "";
	int input_ascii = 0;

	printf("**문자 또는 숫자를 아스키코드 값으로 변환**\n");
	printf("문자 또는 숫자를 입력하세요: ");
	scanf_s("%c", &input_char);

	printf("아스키 코드 값: %d\n", input_char);

	printf("\n**아스키코드 값을 해당 문자 또는 숫자로 변환**\n");
	printf("아스키코드 값을 입력하세요: ");
	scanf_s("%d", &input_ascii);

	printf("해당 문자 또는 숫자: %c\n", input_ascii);

	return 0;
}