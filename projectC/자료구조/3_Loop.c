//@�� �빮�� I �׸��� - �Դϴ�
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct _stack { //������ Ȱ���ϱ� ���� ����ü ����
	int arr[MAX_SIZE]; //������ ����� 100���� ����
	int top; //������ ��ġ�� ����Ű�� ��
}Stack;

Stack xstack; //���� ���� ��
Stack ystack; //���� ���� ��

void StackInit(xstack);
void StackInit(ystack);
void StackPush(xstack, b);
void StackPush(ystack, c);
int StackPop(xstack);
int StackPop(ystack);

int menu(void);
void step(char** matrix, int b, int c, int columnLen, int rowLen);
void printout(char** matrix, int b, int c, int columnLen, int rowLen);
void color(char** matrix, int b, int c, int columnLen, int rowLen);

int main() {

	menu(); //����ڰ� ����� ������ �� �ִ� menu�Լ� ����

}

int menu(void) {

	FILE* stream; //������ �ҷ����� ���� ���� ����
	int k = 1; //menu�Լ��� while���� �����Ű�� ���� ���� ����
	char a[5]; //@�� �ܰ躰�� ä������ ���� ����ڰ� ���� ���ϴ� ���� ����� ���� ����
	char again[5]; //����ڰ� ���α׷��� �ٽ� ���۽�Ű�� ���ϴ��� ����� ���� ����
	int b, c; //����ڰ� ���ϴ� ��� ���� �ޱ� ���� ����
	char fileName[10]; //����ڰ� ���ϴ� ������ �̸��� �Է¹ޱ� ���� ����
	int i = 0; //2���� �迭�� ���� ��Ÿ���� ���� ����
	int j = 0; //2���� �迭�� ���� ��Ÿ���� ���� ����
	int columnLen = 0; //���� ��Ÿ���� ���� ����
	int rowLen = 0; //���� ��Ÿ���� ���� ����

	char** matrix = (char **)malloc(sizeof(char*) * 100); //���� 100������� �����Ҵ� �޴´�

	while (1) { //����ڰ� ������ �Է��� �߸����� �� �ٽ� �Է��ϰ� �ϱ� ���� �ݺ����̴�
		printf("Enter the name of the file : ");
		scanf(" %s", &fileName);

		stream = fopen(fileName, "r"); //������ �б� �������� �ҷ��´�

		if (stream != NULL) //����ڰ� ���� �̸��� ��Ȯ�ϰ� �Է������� �� �ݺ����� Ż���ϰ� ���� �ܰ�� �Ѿ��
			break;

		else if (stream == NULL) //����ڰ� ���� �̸��� �߸� �Է������� �߸���ٴ� �޽����� ���̰� �ٽ� �Է��ϰ� �Ѵ�
			printf("���ϸ��� �ٽ� �Է��ϼ���\n");
	}

	while (!feof(stream)) { //������ �� �޾ƿö����� �ݺ��Ѵ�, ����ڰ� ���Ͽ� ������ ����� �޾ƿ��� ���� �ݺ���
		char * line = (char*)malloc(sizeof(char) * 100); //���� ���� ������ �����ϰ� ���н�Ű�� ���� ������ �ҷ����� while�� �ȿ��� ����
		fgets(line, 100, stream); //����� �Ҵ��� line�� ��������� ������ �޴´�
		rowLen = strlen(line) - 1;  //���� ���� ����
		matrix[columnLen++] = line; //�� ������ ������ �ް� ���� �迭�� �Ѱ��ش�
	}

	for (int q = 0; q < columnLen; q++) { //����� ���� for��, ���� ���̿� �� ĭ ���� ���� for������ ���
		for (int z = 0; z <= rowLen; z++) {
			printf("%c ", matrix[q][z]);
		}
		printf("\n"); //�� �� ������ ����
	}

	while (k) { //����ڰ� ����� �ٲٱ� ���� ���� �Է¹ް�, ���α׷��� ����ɶ����� �޴��� �ݺ��ϴ� ��ü while��

		while (1) { //����ڰ� ��� ���� �߸� �Է������� �ٽ� �Է¹ޱ� ���� ����ó��
			printf("Enter the row number : ");
			scanf("%d", &b);
			if (b < columnLen) {
				break;
			}
			else {
				printf("��� ���� �ٽ� �Է��ϼ���(ũ�� ����)\n");
			}
		}

		while (1) { //����ڰ� ��� ���� �߸� �Է������� �ٽ� �Է¹ޱ� ���� ����ó��
			printf("Enter the column number : ");
			scanf("%d", &c);
			if (c <= rowLen) {
				break;
			}
			else {
				printf("��� ���� �ٽ� �Է��ϼ���(ũ�� ����)\n");
			}
		}

		while (1) { //��� ���� �Է������� �� ��Ŀ� �̹� @�� �ְų� I�� �Ǿ������� �ٽ� �Է¹ޱ� ���� ����ó��

			if (matrix[b][c] == 'I' || matrix[b][c] == '@') {
				printf("��� ���� �ٽ� �Է��ϼ���(��������)\n");

				printf("Enter the row number : ");
				scanf("%d", &b);

				printf("Enter the column number : ");
				scanf("%d", &c);
			}
			else
				break;
		}

		while (1) { //����ڰ� ��� ������ �ܰ躰�� �Ұ��� �ƴϸ� ����� ���ϴ��� �����ϱ� ���� �ݺ���

			printf("Do you want print out step by step? <yes/no> : ");
			scanf("%s", &a);

			if (strcmp(a, "yes") == 0) { //�ܰ躰�� ���Ҷ� step�Լ��� ����
				step(matrix, b, c, columnLen, rowLen);
				break;
			}
			else if (strcmp(a, "no") == 0) { //����� ���Ҷ� color�Լ��� ����
				color(matrix, b, c, columnLen, rowLen);
				printout(matrix, b, c, columnLen, rowLen); //color�Լ����� ����� �����ϰ� printout�Լ����� ����Ѵ�
				break;
			}
			else {
				printf("�ٽ� �Է��ϼ���\n"); //�߸��Է������� ����ó��
			}
		}

		while (1) { //����ڰ� �ٽ� ����� �ٲٱ⸦ ���ϴ��� ����� ���� �ݺ���

			printf("Go again? <yes/no> : ");
			scanf("%s", &again);

			if (strcmp(again, "yes") == 0) { //�ٽ� ����� �ٲٱ⸦ ���Ҷ� �� while���� Ż���ϰ� ��ü while������ ���ư���
				break;
			}

			else if (strcmp(again, "no") == 0) { //���α׷��� �����ϰ� ������ ���� ����� ��Ÿ���� ���� �Լ��� ��ü while���� Ż���ϱ� ���� k�� ����
				printf("Your final result is\n");
				printout(matrix, b, c, columnLen, rowLen); //����� ��Ÿ���� printout�Լ�
				k--; //��ü while���� Ż���ϱ� ���� k�� ����
				break;
			}
			else {
				printf("�ٽ� �Է��ϼ���\n"); //�߸��Է������� ����ó��
			}
		}
	}

	free(matrix);

	return 0;
}

void printout(char** matrix, int b, int c, int columnLen, int rowLen) { //����� ���� �Լ��̴�

	for (int i = 0; i < columnLen; i++) { //��� ���ڵ��� �� ĭ �� �������� for������ ���
		for (int j = 0; j <= rowLen; j++) {
			printf("%c ", matrix[i][j]);
		}
		printf("\n"); //�� �� ������ ����
	}
	printf("\n"); //��� ������ ����
}

void step(char** matrix, int b, int c, int columnLen, int rowLen) { //��� ������ �ܰ躰�� ��Ÿ���� ���� �Լ�

	Stack xstack; //Stack����ü�� top ���� �̿��� ���� ������ �״´�
	Stack ystack; //Stack����ü�� top ���� �̿��� ���� ������ �״´�

	StackInit(&xstack); //���� ������ �ʱ�ȭ�Ѵ�
	StackInit(&ystack); //���� ������ �ʱ�ȭ�Ѵ�

	matrix[b][c] = '@'; //����ڰ� ó�� ������ ���� @�� ��´�
	printout(matrix, b, c, columnLen, rowLen); //����� ������ �ܰ躰�� ��Ÿ���� ���� ����ڰ� ó�� ������ ���� ����Ѵ�

	while (1) { //-�� @�� ä��� �������� �ݺ���(����)�� ����ϱ� ���� ��ü while��

		if (b != 0 && matrix[b - 1][c] != 'I' && matrix[b - 1][c] != '@') { //���� b�� 0�� �ƴϰ� ���� ��ġ�ϴ� ����� �������� ������
			StackPush(&xstack, b); //���� ������ ������ �� ���� ���� �ִ´�
			StackPush(&ystack, c); //���� ������ ������ �� ���� ���� �ִ´�
			matrix[--b][c] = '@'; //���� ���� �ϳ� ���ҽ����ְ� '@'�� ä���
			printout(matrix, b, c, columnLen, rowLen); //�ܰ踦 ����Ѵ�
		}

		else if (c != 0 && matrix[b][c - 1] != 'I' && matrix[b][c - 1] != '@') { //���� c�� 0�� �ƴϰ� ���ʿ� ��ġ�ϴ� ����� �������� ������
			StackPush(&xstack, b); //���� ������ ������ �� ���� ���� �ִ´�
			StackPush(&ystack, c); //���� ������ ������ �� ���� ���� �ִ´�
			matrix[b][--c] = '@'; //���� ���� �ϳ� ���ҽ����ְ� '@'�� ä���
			printout(matrix, b, c, columnLen, rowLen); //�ܰ踦 ����Ѵ�
		}

		else if (c < rowLen && matrix[b][c + 1] != 'I' && matrix[b][c + 1] != '@') { //���� c�� ���� ����� ���� �ʴ� �������� �������� �������� ������
			StackPush(&xstack, b);  //���� ������ ������ �� ���� ���� �ִ´�
			StackPush(&ystack, c); //���� ������ ������ �� ���� ���� �ִ´�
			matrix[b][++c] = '@'; //���� ���� �ϳ� ���������ְ� '@'�� ä���
			printout(matrix, b, c, columnLen, rowLen); //�ܰ踦 ����Ѵ�
		}

		else if (b < columnLen - 1 && matrix[b + 1][c] != 'I' && matrix[b + 1][c] != '@') { //���� b�� ���� ����� ���� �ʴ� �������� ������ �������� ������
			StackPush(&xstack, b); //���� ������ ������ �� ���� ���� �ִ´�
			StackPush(&ystack, c); //���� ������ ������ �� ���� ���� �ִ´�
			matrix[++b][c] = '@'; //���� ���� �ϳ� ������Ű�� '@'�� ä���
			printout(matrix, b, c, columnLen, rowLen); //�ܰ踦 ����Ѵ�
		}

		else { //���� ���ǵ��� �������� �ʴ� ���
			if (xstack.top == -1) //���� ���� ���� ���� -1�̸� Ż���Ѵ�(������ ��� ���ٴ� ���� �ǹ�)
				break;
			b = StackPop(&xstack); //���� ������ �ϳ� ���ش�
			c = StackPop(&ystack); //���� ������ �ϳ� ���ش�
		}
	}

	return;
}

void color(char** matrix, int b, int c, int columnLen, int rowLen) {

	Stack xstack; //Stack����ü�� top ���� �̿��� ���� ������ �״´�
	Stack ystack;//Stack����ü�� top ���� �̿��� ���� ������ �״´�

	StackInit(&xstack); //���� ������ �ʱ�ȭ�Ѵ�
	StackInit(&ystack); //���� ������ �ʱ�ȭ�Ѵ�

	matrix[b][c] = '@';  //����ڰ� ó�� ������ ���� @�� ��´�

	while (1) { //-�� @�� ä��� �������� �ݺ���(����)�� ����ϱ� ���� ��ü while��

		if (b != 0 && matrix[b - 1][c] != 'I' && matrix[b - 1][c] != '@') { //���� b�� 0�� �ƴϰ� ���� ��ġ�ϴ� ����� �������� ������
			StackPush(&xstack, b); //���� ������ ������ �� ���� ���� �ִ´�
			StackPush(&ystack, c); //���� ������ ������ �� ���� ���� �ִ´�
			matrix[--b][c] = '@'; //���� ���� �ϳ� ���ҽ����ְ� '@'�� ä���
		}

		else if (c != 0 && matrix[b][c - 1] != 'I' && matrix[b][c - 1] != '@') { //���� c�� 0�� �ƴϰ� ���ʿ� ��ġ�ϴ� ����� �������� ������
			StackPush(&xstack, b); //���� ������ ������ �� ���� ���� �ִ´�
			StackPush(&ystack, c); //���� ������ ������ �� ���� ���� �ִ´�
			matrix[b][--c] = '@'; //���� ���� �ϳ� ���ҽ����ְ� '@'�� ä���
		}

		else if (c < rowLen && matrix[b][c + 1] != 'I' && matrix[b][c + 1] != '@') { //���� c�� ���� ����� ���� �ʴ� �������� �������� �������� ������
			StackPush(&xstack, b);  //���� ������ ������ �� ���� ���� �ִ´�
			StackPush(&ystack, c); //���� ������ ������ �� ���� ���� �ִ´�
			matrix[b][++c] = '@'; //���� ���� �ϳ� ���������ְ� '@'�� ä���
		}

		else if (b < columnLen - 1 && matrix[b + 1][c] != 'I' && matrix[b + 1][c] != '@') { //���� b�� ���� ����� ���� �ʴ� �������� ������ �������� ������
			StackPush(&xstack, b); //���� ������ ������ �� ���� ���� �ִ´�
			StackPush(&ystack, c); //���� ������ ������ �� ���� ���� �ִ´�
			matrix[++b][c] = '@'; //���� ���� �ϳ� ������Ű�� '@'�� ä���
		}

		else { //���� ���ǵ��� �������� �ʴ� ���
			if (xstack.top == -1) //���� ���� ���� ���� -1�̸� Ż���Ѵ�(������ ��� ���ٴ� ���� �ǹ�)
				break;
			b = StackPop(&xstack); //���� ������ �ϳ� ���ش�
			c = StackPop(&ystack); //���� ������ �ϳ� ���ش�
		}
	}

	return;
}

void StackInit(Stack * ps) { //������ �ʱ�ȭ �ϱ� ���� �Լ�
	ps->top = -1; //���� ����ü�� top���� -1�� �ʱ�ȭ
}

void StackPush(Stack * ps, int data) { //-1�� �ʱ�ȭ�� Stack ����ü�� top���� �̿��� ������ �״´�
	ps->arr[++(ps->top)] = data;
}

int StackPop(Stack * ps) { //���� ������ ���� �Լ�
	return ps->arr[ps->top--];
}