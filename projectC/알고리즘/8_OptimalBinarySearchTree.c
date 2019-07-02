#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define SIZE 8 //p, q 값을 입력 받기 위한 전역변수 선언
#define LENGTH 8 //Table의 배열 사이즈를 위한 전역변수 선언

void print_table(double *p, double *q); //입력 받은 p, q 값을 출력해주는 함수
double calcul(int i, int j, double(*c)[LENGTH], double(*w)[LENGTH], int(*r)[LENGTH]); // 최소의 cost깂을 계산 및 그에 따른 root값을 구하는 함수
void weight_Table(double(*weight)[LENGTH]); //weight Table을 출력해주는 함수
void cost_Table(double(*cost)[LENGTH]); //cost Table을 출력해주는 함수
void root_Table(int(*root)[LENGTH]); //root Table을 출력해주는 함수

int main() {

	double weight[LENGTH][LENGTH] = { 0 }; //weight Table의 배열 선언 및 초기화
	double cost[LENGTH][LENGTH] = { 0 }; //cost Table의 배열 선언 및 초기화
	int root[LENGTH][LENGTH] = { 0 }; // root Table의 배열 선언 및 초기화
	double p[SIZE]; //p값을 입력받기 위한 배열 선언
	double q[SIZE + 1]; //q값을 입력받기 위한 배열 선언
	int k = 0; //weight, cost Table의 위치를 나타내기 위한 변수 선언

	p[0] = 0.00; //p[0]의 값은 0.00이다

	printf("P Table 입력\n");
	printf("p[0] = 0.00\n");

	for (int i = 1; i < SIZE; i++) //p값을 입력받기 위한 반복문
	{
		printf("p[%d] = ", i);
		scanf("%lf", &p[i]);
	}

	printf("\n");
	printf("Q Table 입력\n");

	for (int i = 0; i < SIZE; i++) //q값을 입력받기 위한 반복문
	{
		printf("q[%d] = ", i);
		scanf("%lf", &q[i]);
	}

	printf("\n");

	print_table(p, q); //p, q 값을 출력하기 위한 함수 호출

	for (int i = 0; i <= SIZE; i++) { //weight, cost 초기화
		weight[i][i] = q[i]; //weight[i][i]에 q입력
		cost[i][i] = 0.00;
	}

	for (int a = 1; a < SIZE; a++) { //Table값을 계산하기 위한 반복문
		for (int n = 0; n < SIZE - a; n++) {
			k = n + a;
			weight[n][k] = weight[n][k - 1] + p[k] + q[k]; // weight 계산 
			cost[n][k] = calcul(n, k, cost, weight, root); // cost, root를 계산하기 위한 함수 호출
		}
	}

	printf("weight Table\n");
	weight_Table(weight);

	printf("cost Table\n");
	cost_Table(cost);

	printf("root Table\n");
	root_Table(root);

	return 0;
}

void print_table(double* p, double* q) {

	printf("       ");
	for (int i = 0; i <= 7; i++) { //몇 번째 p, q값인지 나타내기 위한 반복문
		printf("|%4d  ", i);
	}

	printf("|\n");
	printf("----------------------------------------------------------------\n");

	printf("P Table");
	for (int i = 0; i < SIZE; i++) { // p값 출력을 위한 반복문
		printf("|%5.2lf ", p[i]);
	}

	printf("|\n");
	printf("----------------------------------------------------------------\n");

	printf("Q Table");
	for (int i = 0; i < SIZE; i++) { // q값 출력을 위한 반복문
		printf("|%5.2lf ", q[i]);
	}

	printf("|\n");
	printf("----------------------------------------------------------------\n\n\n");
}

double calcul(int i, int j, double(*c)[LENGTH], double(*w)[LENGTH], int(*r)[LENGTH]) {

	int a = 1; //연산을 위한 변수 선언
	double result; //cost 값을 저장할 변수 선언
	double min; //최소값을 저장하기 위한 변수 선언

	for (int k = i; k <= j; k++) {

		if (k == i)
			continue;  // 'k==i'일 때 그냥 진행한다

		else {
			result = c[i][k - 1] + c[k][j] + w[i][j];  // 각각의 경우의 cost를 계산

			if (a) {  // 비교를 위해 처음 cost값을 min으로 설정한다
				min = result;
				a = 0;  // 처음에 한 번 실행을 위해 a값 변경
				r[i][j] = k;  // root값 설정
			}
			if (min > result) {  // 비교 후 기존의 값보다 작을 경우
				min = result;  // 최소값 변경
				r[i][j] = k;  // root값 변경
			}
		}
	}

	return min;
}

void weight_Table(double(*weight)[LENGTH])
{
	int k;

	printf("---------------------------------------------------------\n");

	for (int i = 0; i < LENGTH; i++) {
		for (k = 0; k < i; k++)
			printf("|      ");

		for (int j = 0; j < LENGTH - k; j++) {
			if (i > 0)
				printf("|%6.2lf", weight[i][j + i]);
			else {
				printf("|%6.2lf", weight[i][j]);
			}
		}

		printf("|\n---------------------------------------------------------\n");
	}

	printf("\n");
}

void cost_Table(double(*cost)[LENGTH]) {

	int k;

	printf("---------------------------------------------------------\n");

	for (int i = 0; i < LENGTH; i++) {
		for (k = 0; k < i; k++)
			printf("|      ");

		for (int j = 0; j < LENGTH - k; j++) {
			if (i > 0)
				printf("|%6.2lf", cost[i][j + i]);
			else {

				printf("|%6.2lf", cost[i][j]);
			}
		}

		printf("|\n---------------------------------------------------------\n");
	}

	printf("\n");
}

void root_Table(int(*root)[LENGTH]) {

	int k;

	printf("---------------------------------------------------------\n");

	for (int i = 0; i < LENGTH; i++) {
		for (k = 0; k < i; k++)
			printf("|      ");

		for (int j = 0; j < LENGTH - k; j++) {
			if (i > 0)
				printf("|%6d", root[i][j + i]);
			else {

				printf("|%6d", root[i][j]);
			}
		}

		printf("|\n---------------------------------------------------------\n");
	}

	printf("\n");
}