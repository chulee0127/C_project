#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define SIZE 8 //p, q ���� �Է� �ޱ� ���� �������� ����
#define LENGTH 8 //Table�� �迭 ����� ���� �������� ����

void print_table(double *p, double *q); //�Է� ���� p, q ���� ������ִ� �Լ�
double calcul(int i, int j, double(*c)[LENGTH], double(*w)[LENGTH], int(*r)[LENGTH]); // �ּ��� cost���� ��� �� �׿� ���� root���� ���ϴ� �Լ�
void weight_Table(double(*weight)[LENGTH]); //weight Table�� ������ִ� �Լ�
void cost_Table(double(*cost)[LENGTH]); //cost Table�� ������ִ� �Լ�
void root_Table(int(*root)[LENGTH]); //root Table�� ������ִ� �Լ�

int main() {

	double weight[LENGTH][LENGTH] = { 0 }; //weight Table�� �迭 ���� �� �ʱ�ȭ
	double cost[LENGTH][LENGTH] = { 0 }; //cost Table�� �迭 ���� �� �ʱ�ȭ
	int root[LENGTH][LENGTH] = { 0 }; // root Table�� �迭 ���� �� �ʱ�ȭ
	double p[SIZE]; //p���� �Է¹ޱ� ���� �迭 ����
	double q[SIZE + 1]; //q���� �Է¹ޱ� ���� �迭 ����
	int k = 0; //weight, cost Table�� ��ġ�� ��Ÿ���� ���� ���� ����

	p[0] = 0.00; //p[0]�� ���� 0.00�̴�

	printf("P Table �Է�\n");
	printf("p[0] = 0.00\n");

	for (int i = 1; i < SIZE; i++) //p���� �Է¹ޱ� ���� �ݺ���
	{
		printf("p[%d] = ", i);
		scanf("%lf", &p[i]);
	}

	printf("\n");
	printf("Q Table �Է�\n");

	for (int i = 0; i < SIZE; i++) //q���� �Է¹ޱ� ���� �ݺ���
	{
		printf("q[%d] = ", i);
		scanf("%lf", &q[i]);
	}

	printf("\n");

	print_table(p, q); //p, q ���� ����ϱ� ���� �Լ� ȣ��

	for (int i = 0; i <= SIZE; i++) { //weight, cost �ʱ�ȭ
		weight[i][i] = q[i]; //weight[i][i]�� q�Է�
		cost[i][i] = 0.00;
	}

	for (int a = 1; a < SIZE; a++) { //Table���� ����ϱ� ���� �ݺ���
		for (int n = 0; n < SIZE - a; n++) {
			k = n + a;
			weight[n][k] = weight[n][k - 1] + p[k] + q[k]; // weight ��� 
			cost[n][k] = calcul(n, k, cost, weight, root); // cost, root�� ����ϱ� ���� �Լ� ȣ��
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
	for (int i = 0; i <= 7; i++) { //�� ��° p, q������ ��Ÿ���� ���� �ݺ���
		printf("|%4d  ", i);
	}

	printf("|\n");
	printf("----------------------------------------------------------------\n");

	printf("P Table");
	for (int i = 0; i < SIZE; i++) { // p�� ����� ���� �ݺ���
		printf("|%5.2lf ", p[i]);
	}

	printf("|\n");
	printf("----------------------------------------------------------------\n");

	printf("Q Table");
	for (int i = 0; i < SIZE; i++) { // q�� ����� ���� �ݺ���
		printf("|%5.2lf ", q[i]);
	}

	printf("|\n");
	printf("----------------------------------------------------------------\n\n\n");
}

double calcul(int i, int j, double(*c)[LENGTH], double(*w)[LENGTH], int(*r)[LENGTH]) {

	int a = 1; //������ ���� ���� ����
	double result; //cost ���� ������ ���� ����
	double min; //�ּҰ��� �����ϱ� ���� ���� ����

	for (int k = i; k <= j; k++) {

		if (k == i)
			continue;  // 'k==i'�� �� �׳� �����Ѵ�

		else {
			result = c[i][k - 1] + c[k][j] + w[i][j];  // ������ ����� cost�� ���

			if (a) {  // �񱳸� ���� ó�� cost���� min���� �����Ѵ�
				min = result;
				a = 0;  // ó���� �� �� ������ ���� a�� ����
				r[i][j] = k;  // root�� ����
			}
			if (min > result) {  // �� �� ������ ������ ���� ���
				min = result;  // �ּҰ� ����
				r[i][j] = k;  // root�� ����
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