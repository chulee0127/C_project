#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

int main() {

	char input_char = "";
	int input_ascii = 0;

	printf("**���� �Ǵ� ���ڸ� �ƽ�Ű�ڵ� ������ ��ȯ**\n");
	printf("���� �Ǵ� ���ڸ� �Է��ϼ���: ");
	scanf_s("%c", &input_char);

	printf("�ƽ�Ű �ڵ� ��: %d\n", input_char);

	printf("\n**�ƽ�Ű�ڵ� ���� �ش� ���� �Ǵ� ���ڷ� ��ȯ**\n");
	printf("�ƽ�Ű�ڵ� ���� �Է��ϼ���: ");
	scanf_s("%d", &input_ascii);

	printf("�ش� ���� �Ǵ� ����: %c\n", input_ascii);

	return 0;
}