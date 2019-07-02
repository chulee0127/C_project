#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

int main() {

	int Quiz4[9] = { 0, }; // 2진수를 입력받기 위한 배열
	int Quiz4_1[9] = { 0, }; // 그레이코드 값을 입력받기 위한 배열
	int arr[9] = { 0, }; // 2진수를 그레이코드로 바꿔주기 위한 배열
	int arr2[9] = { 0, }; // 그레이코드를 2진수로 바꿔주기 위한 배열

	printf("4번 문제, 2진수를 입력하세요(띄어쓰기 해서 입력할 것)\n");
	printf("입력 예시: 1 0 0 1 0 1 0\n");
	printf("2진수 입력: ");

	for (int i = 0; i < 7; i++) { // 입력받은 2진수를 배열에 저장하기 위해 반복문으로 입력 받는다
		scanf_s("%d", &Quiz4[i]);
	}

	arr[0] = Quiz4[0]; // 처음 값은 동일
	for (int i = 0; i < 7; i++) { // 2진수를 그레이코드로 바꿔주는 반복문
		arr[i+1] = Quiz4[i] + Quiz4[i+1];
		if (arr[i] > 1)
			arr[i] = 0;
	}

	printf("\n그레이코드 출력: ");
	for (int i = 0; i < 7; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n\n4번 문제,그레이코드 값을 입력하세요(띄어쓰기 해서 입력할 것)\n");
	printf("입력 예시: 1 0 1 1 1 0 1\n");
	printf("그레이코드 입력: ");

	for (int i = 0; i < 7; i++) { // 입력받은 그레이코드를 배열에 저장하기 위해 반복문으로 입력 받는다
		scanf_s("%d", &Quiz4_1[i]);
	}

	arr2[0] = Quiz4_1[0]; // 처음 값은 동일
	for (int i = 0; i < 7; i++) { // 그레이코드를 2진수로 바꿔주는 반복문
		arr2[i + 1] = arr2[i] + Quiz4_1[i + 1];
		if (arr2[i+1] > 1)
			arr2[i+1] = 0;
	}

	printf("\n2진수 출력: ");
	for (int i = 0; i < 7; i++) {
		printf("%d ", arr2[i]);
	}
	printf("\n");

	return 0;
}