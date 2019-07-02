#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

int main() {

	int A[10] = { 0, }; // 2진 코드를 입력받기 위한 배열
	int B[10] = { 0, }; // 2진 코드를 입력받기 위한 배열
	int k[10] = { 0, }; // 계산된 결과를 저장하기 위한 배열
	char c[10]; // 연산자를 입력받기 위한 배열
	char NAND[10] = "NAND"; // if문으로 비교하기 위한 문자열 선언
	char NOR[10] = "NOR"; // if문으로 비교하기 위한 문자열 선언
	char XOR[10] = "XOR"; // if문으로 비교하기 위한 문자열 선언

	printf("띄어쓰기를 해서 입력하세요(ex: 1 0 0 1 0 0 1 1)\n");

	printf("A입력: ");
	for (int i = 0; i < 8; i++) {
		scanf_s("%d", &A[i]);
	}

	printf("B입력: ");
	for (int i = 0; i < 8; i++) {
		scanf_s("%d", &B[i]);
	}

	printf("연산자를 입력하세요: ");
	scanf("%s", c);

	printf("\n");

	if (strcmp(c, NAND) == 0) {
		for (int i = 0; i < 8; i++) { // NAND 계산을 위한 반복문
			if (A[i] == 1 && B[i] == 1) {
				k[i] = 1;
			}
			else
				k[i] = 0;
		}

		printf("A NAND B = ");
		for (int i = 0; i < 8; i++) {
			printf("%d ", k[i]);
		}
	}
	else if (strcmp(c, NOR) == 0) {
		for (int i = 0; i < 8; i++) { // NOR 계산을 위한 반복문
			if (A[i] == 0 && B[i] == 0) {
				k[i] = 1;
			}
			else
				k[i] = 0;
		}

		printf("A NOR B = ");
		for (int i = 0; i < 8; i++) {
			printf("%d ", k[i]);
		}
	}
	else if (strcmp(c, XOR) == 0) {
		for (int i = 0; i < 8; i++) { // XOR 계산을 위한 반복문
			if (A[i] + B[i] == 1) {
				k[i] = 1;
			}
			else
				k[i] = 0;
		}

		printf("A XOR B = ");
		for (int i = 0; i < 8; i++) {
			printf("%d ", k[i]);
		}
	}
	else
		printf("잘못입력하셨습니다.");

	printf("\n");
	return 0;
}