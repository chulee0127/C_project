#include <stdio.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

int main() {

	int Quiz1 = 0; // 10진수를 입력받을 변수
	int Quiz1_1 = 0; // 2진수값을 구하고 나면 Quiz1 값이 0이 되므로 16진수 값을 구하기 위해 Quiz1_1에 다시 한 번 저장
	int arr[20] = { 0, }; // 2진수 값을 저장할 배열
	int arr2[20] = { 0 , }; // 2의 보수 값을 저장할 배열
	int a = 0; // 2진수값을 저장할 배열의 인덱스값을 조절할 변수
	int b = 0; // 2의 보수를 저장할 배열의 인덱스값을 조절할 변수
	int c = 0; // 16진수를 저장할 배열의 인덱스값을 조절할 변수
	int k = 0;
	char string[20] = { 0, }; // 16진수의 값을 저장할 배열

	printf("1번 문제, 1027을 입력하세요: ");
	scanf_s("%d", &Quiz1);

	Quiz1_1 = Quiz1;
	
	while (1){ // 2진수 값을 구하기 위한 반복문
		arr[a] = Quiz1 % 2; // 나머지 1을 배열에 저장
		Quiz1 = Quiz1 / 2; // Quiz1을 2로 나누고 몫을 Quiz1에 저장      

		a++; // 배열의 인덱스 하나씩 증가

		if (Quiz1 == 0)
			break;
	}
	
	printf("\n2진수 값 출력: ");
	for (int i = a - 1; i >= 0; i--) // 2진수 값을 출력하는 반복문(역순)
	{
		printf(" %d", arr[i]);
	}

	printf("\n\n2의 보수값 출력: ");

	for (int i = a-1; i >=0; i--) { // 1의 보수로 전환하기 위한 반복문
		if (arr[i] == 0) {
			arr2[b] = 1;
			b++;
		}
		else if (arr[i] == 1) {
			arr2[b] = 0;
			b++;
		}
	}
	arr2[a - 1] = arr2[a - 1] + 1; // 1의 보수 값을 구한 후 +1

	for (int i = 0; i < a; i++) { // 2의 보수 값을 저장한 arr2배열을 차례로 출력하는 반복문
		printf(" %d", arr2[i]);
	}

	Quiz1 = Quiz1_1; // 2진수 값을 구할때 Quiz1이 0이 되므로 Quiz1_1에 임시저장했던 값을 다시 넣어준다

	printf("\n\n16진수 값 출력: ");

	while (1){ // 16진수 값을 구하기 위한 반복문
		k = Quiz1 % 16; // 16으로 나누었을 때 나머지를 구함

		if (k < 10) { // 나머지가 10보다 작으면 숫자 0의 ASCII 코드 값 48과 나머지를 더함
			string[c] = 48 + k;
		}
		else { // 나머지가 10보다 크거나 같으면 나머지에서 10을 뺀 값과 대문자 A의 ASCII 코드 값 65를 더함			
			string[c] = 65 + (k - 10);
		}

		Quiz1 = Quiz1 / 16; // Quiz1을 16으로 나누고 몫을 Quiz1에 저장

		c++;

		if (Quiz1 == 0)
			break;
	}

	for (int i = c - 1; i >= 0; i--){ // 16진수 값을 출력하기 위한 반복문(역순)
		printf(" %c", string[i]);
	}

	printf("\n");

	return 0;
}