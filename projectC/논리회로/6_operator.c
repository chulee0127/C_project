#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

int main() {

	int A[10] = { 0, }; // 2�� �ڵ带 �Է¹ޱ� ���� �迭
	int B[10] = { 0, }; // 2�� �ڵ带 �Է¹ޱ� ���� �迭
	int k[10] = { 0, }; // ���� ����� �����ϱ� ���� �迭
	char c[10]; // �����ڸ� �Է¹ޱ� ���� �迭
	char NAND[10] = "NAND"; // if������ ���ϱ� ���� ���ڿ� ����
	char NOR[10] = "NOR"; // if������ ���ϱ� ���� ���ڿ� ����
	char XOR[10] = "XOR"; // if������ ���ϱ� ���� ���ڿ� ����

	printf("���⸦ �ؼ� �Է��ϼ���(ex: 1 0 0 1 0 0 1 1)\n");

	printf("A�Է�: ");
	for (int i = 0; i < 8; i++) {
		scanf_s("%d", &A[i]);
	}

	printf("B�Է�: ");
	for (int i = 0; i < 8; i++) {
		scanf_s("%d", &B[i]);
	}

	printf("�����ڸ� �Է��ϼ���: ");
	scanf("%s", c);

	printf("\n");

	if (strcmp(c, NAND) == 0) {
		for (int i = 0; i < 8; i++) { // NAND ����� ���� �ݺ���
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
		for (int i = 0; i < 8; i++) { // NOR ����� ���� �ݺ���
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
		for (int i = 0; i < 8; i++) { // XOR ����� ���� �ݺ���
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
		printf("�߸��Է��ϼ̽��ϴ�.");

	printf("\n");
	return 0;
}