#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

int main() {

	int Quiz2 = 0; // 첫 번째 정수를 입력받기 위한 변수
	int Quiz2_1 = 0; // 두 번째 정수를 입력받기 위한 변수
	char c = ""; // 연산자를 입력받기 위한 변수

	int k = 0; // 연산자를 입력받아 두 정수의 연산 결과를 계산하고, 자릿수를 계산하기 위한 변수
	int k_1 = 0; // 출력할때 이미 사용한 k값 대신 사용하기 위한 임시변수
	int z = 0; // 자릿수를 구하기 위한 변수

	int b = 1; // 입력받은 10진수를 한자리씩 떼어낼 때 사용하기 위한 변수
	int d = 0; // b를 계산하기 위한 변수

	printf("2번 문제, 첫 번째 정수를 입력하세요: ");
	scanf_s("%d", &Quiz2);

	printf("두 번째 정수를 입력하세요: ");
	scanf_s("%d", &Quiz2_1);

	getchar();
	printf("연산자를 입력하세요(+ or -): ");
	scanf_s("%c", &c);

	if (c == '+') {
		k = Quiz2 + Quiz2_1;
	}
	else if (c == '-') {
		k = Quiz2 - Quiz2_1;
	}
	else
		printf("연산자를 잘못입력하셨습니다.\n");

	if (k == 0) { // k가 0이면 BCD코드는 0000
		printf("정답: 0000\n");
		return 0;
	}

	k_1 = k; // 자릿수를 구할때 k값을 사용하므로 다른 k_1에 값을 임시저장한다
	
	while (1) { // 자릿수를 구하기 위한 반복문
		if (k != 0){
			z++;
			k = k / 10;
		}
		else break;
	}

	for (int i = 1; i < z; i++) {// b에 자리수만큼 10을 곱한수를 넣는다
		b *= 10;
	}

	printf("\n정답: ");
	for (int i = 1; i <= z; i++) {// 자리수만큼 반복한다
		d = k_1 / b; // 제일 큰자리의 숫자부터 하나씩 끊은 정수를 d에 입력

		int flag=1;
		
		for(int j = 3; j >= 0;j--){ // 최대 쉬프트 넘버: 여기서는 2자리 이상의 10진수는 취급하지 않으므로
			if(d & (flag << j))
				printf("1");

			else printf("0");
		}

		k_1 = k_1 - d * b; // 이미 출력한 자리의 숫자를 빼서 없앤다
		b /= 10; // 자리수가 하나 줄었으므로 10으로 한번 나눈다
	}

	printf("\n");

	return 0;
}