#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define BUF_SIZE 100

int input_vertax(int vertax); //������ ������ �Է¹ޱ� ���� �Լ�
int input_edge(int vertax, int edge); //������ ������ �Է¹ޱ� ���� �Լ�
void find_Bridge(int matrix[BUF_SIZE][BUF_SIZE], int visit[BUF_SIZE], int vertax, int menu); //Bridge�� ã�� �Լ�
void init_Visit(int visit[BUF_SIZE]); //�湮����� �ʱ�ȭ �ϱ� ���� �Լ�
void DFS(int matrix[BUF_SIZE][BUF_SIZE], int visit[BUF_SIZE], int v, int vertax); //���� �켱 Ž���� ���� �Լ�
int check_Visit(int visit[BUF_SIZE], int vertax); //�湮 ����� �˻��ϴ� �Լ�

int arr[BUF_SIZE][2]; //Bridge�� ���θ� �ӽ÷� ������ �迭 ����
int num = 0; //arr�迭�� ����

int main() {

	int vertax = 0; //������ ������ �Է� �ޱ����� ����
	int edge = 0; //������ ������ �Է� �ޱ����� ����
	int k = 1; //������ �� ������ �Է� �ޱ����� ����
	int matrix[BUF_SIZE][BUF_SIZE]; //���⼺�� ���� ��� ������ ������ �迭 ����
	int visit[BUF_SIZE]; //�湮 ������ ������ �迭 ����
	int point1 = 0; //������ ���� ����
	int point2 = 0; //������ ���� ����
	int check = 0; //ture ,false �� ����� ���� ����
	char a = { 0 }; //�޴� ��ư�� �Է� �ޱ����� ���� ����
	int menu = 0; //1���� 2���� �����ϱ� ���� ���� ����

	vertax = input_vertax(vertax); //������ ������ �Է¹ޱ� ���� �Լ� ȣ��
	printf("\n");
	edge = input_edge(vertax, edge); //������ ������ �Է¹ޱ� ���� �Լ� ȣ��
	printf("\n");

	for (int i = 0; i < vertax; i++) { //�Է��� (���� ����)^2 ��ŭ �迭 �ʱ�ȭ
		for (int j = 0; j < vertax; j++) {
			matrix[i][j] = 0;
		}
	}

	while (1) { //������ �� ������ �Է¹ޱ� ���� �ݺ���

		printf("������ %d�� �� ������ �Է��Ͻÿ� : ", k);
		scanf("%d %d", &point1, &point2);

		k = k + 1; //������ �Է� �޾��� �� �ϳ� ������Ų��

		matrix[point1][point2] = 1; //���⼺�� ���� ������ (n,n) ������ ��Ī ���� (n,m) = (m,n)
		matrix[point2][point1] = 1; //���⼺�� ���� ������ (n,n) ������ ��Ī

		if (k > edge) //k�� ������ �������� �������ٸ� ������ �Է��� �� ���� ���̹Ƿ� ���ѷ��� Ż��
			break;
	}

	while (a != 'q') { //�޴� �Է��� �ޱ����� �ݺ���

		menu = 0;

		printf("\n������ �Ͻðڽ��ϱ�?\n�긮�� ��ü ����(1)\n���� �긴�� �׽�Ʈ(2)\n����(q)\n");
		scanf(" %c", &a);

		switch (a) {
		case '1': //�׷��� �� ��� ������ ���� Bridge(������)���θ� ����Ѵ�
			menu = 1;
			find_Bridge(matrix, visit, vertax, menu);
			break;

		case '2': //�׷����� Bridge ���θ� ���ù޾Ƽ� ����Ѵ�
			menu = 2;
			find_Bridge(matrix, visit, vertax, menu);
			printf("�׽�Ʈ�� �� ������ �� ������ �Է��Ͻÿ�: ");
			scanf("%d %d", &point1, &point2);

			for (int i = 0; i < num; i++) { //arr�� ��ȿ�� ���� �ִ� ��ŭ �ݺ��Ѵ�
				if (arr[i][0] == point1 && arr[i][1] == point2 || arr[i][0] == point2 && arr[i][1] == point1) { //Bridge���� arr�� �ִ� ���
					check = 1;
				}
			}

			if (check == 1) {
				printf("(%d,%d) ������ Bridge �Դϴ�.\n", point1, point2);
			}
			else {
				printf("(%d,%d) ������ Bridge�� �ƴմϴ�.\n", point1, point2);
			}

			check = 0;
			break;

		case 'q':
			printf("����\n");
			break;

		default:
			printf("�߸� �Է��Ͽ����ϴ�.\n");
			break;
		}
	}

	return 0;
}

int input_vertax(int vertax) {

	printf("������ ������ �Է��Ͻÿ� : ");
	scanf("%d", &vertax);

	if (vertax <= 0 || vertax > BUF_SIZE) { //����ó��, ������ ������ 0������ ��� �Ǵ� �迭�� ����� �Ѿ ���
		while (1) { //���� ������ 0���� Ŭ�� ���� ���� ����
			printf("�Է��� �߸��Ǿ����ϴ�.\n");
			printf("������ ������ �Է��Ͻÿ� : ");
			scanf("%d", &vertax);

			if (vertax > 0 && vertax <= BUF_SIZE) { //������ ������ 0���� ũ�� �迭�� ������� ���� ��� �ݺ����� Ż���Ѵ�
				break;
			}
		}
	}

	return vertax;
}

int input_edge(int vertax, int edge) {

	printf("������ ������ �Է��Ͻÿ� : ");
	scanf("%d", &edge);

	if (0 >= edge || edge > vertax * 2) { //����ó��, ������ ������ 0������ ��� �Ǵ� ������ ������ 2�踦 �Ѵ� ���
		while (1) {
			printf("�Է��� �߸��Ǿ����ϴ�.\n");
			printf("������ ������ �Է��Ͻÿ� : ");
			scanf("%d", &edge);

			if (0 < edge && edge <= vertax * 2)
				break;
		}
	}

	return edge;
}

void find_Bridge(int matrix[BUF_SIZE][BUF_SIZE], int visit[BUF_SIZE], int vertax, int menu) {

	int check; //ture, false ���� ����� ���� ����
	int count[BUF_SIZE]; //���� ��带 �˱� ���� �迭

	num = 0;

	for (int i = 0; i < BUF_SIZE; i++) { //0���� �ʱ�ȭ �ϱ� ���� �ݺ���
		count[i] = 0;
	}

	for (int i = 0; i < vertax; i++) {
		for (int j = 0; j < vertax; j++) {
			count[i] = matrix[i][j] + count[i]; //matrix�� ���� ���� 1�� ��� ������ �Ѱ� -> ���� ���
		}
	}

	for (int i = 0; i < vertax; i++) {
		for (int j = i; j < vertax; j++) {
			if (matrix[i][j] == 1) {   //������ ������ �Ǿ��ִٸ�
				matrix[i][j] = 0;      //������ �ӽ÷� ����
				init_Visit(visit);     //visit�迭 �ʱ�ȭ
				DFS(matrix, visit, i, vertax); //i�� ���� ���� �켱 Ž��
				check = check_Visit(visit, vertax); //i�� ���� ���� �켱 Ž�� �� �湮�� ���� ��ȸ

				if (count[i] == 1 || count[j] == 1) { //���� ����� ���
					check = 1;
				}

				if (check == 1 && menu == 1) { //���� ����̰ų� ������ ������ ��� ������ �湮�� ������ ���
					printf("(%d, %d) ������ Bridge�� �ƴմϴ�.\n", i, j);
				}

				else { //���ܳ�尡 �ƴϰ� ������ ������ �� ��� ������ �湮���� ���ϴ� ���
					if (menu == 1) //1���� ���� �Ǿ��� ���� ����Ѵ�
						printf("(%d, %d) ������ Bridge �Դϴ�.\n", i, j);

					arr[num][0] = i; //������ �� �� ������ �ӽ� ����
					arr[num++][1] = j; //������ �� �� ������ �ӽ� ����
				}
				matrix[i][j] = 1; //�ӽ÷� ���� ������ �����Ѵ�
			}
		}
	}

}

void init_Visit(int visit[BUF_SIZE]) {

	for (int i = 0; i < BUF_SIZE; i++) {
		visit[i] = -1; //������ 0�� �ֱ� ������ -1�� �ʱ�ȭ�Ѵ�
	}
}

void DFS(int matrix[BUF_SIZE][BUF_SIZE], int visit[BUF_SIZE], int v, int vertax) {

	visit[v] = 1; //�湮 ����� �޸��Ѵ�

	for (int i = 0; i < vertax; i++) { //���� ũ�⸸ŭ �ݺ��ϱ� ���� for��
		if (matrix[v][i] == 1 && visit[i] != 1) { //������ ������ �Ǿ��ְ� ���� �� ������ �湮�� ���� �ʾ��� ���
			DFS(matrix, visit, i, vertax); // �ش� ������ �湮�Ѵ�
		}
	}

}

int check_Visit(int visit[BUF_SIZE], int vertax) {

	int check = 1;

	for (int i = 0; i < vertax; i++) { // visit�� ũ�⸸ŭ �ݺ��Ѵ�
		if (visit[i] == 1) { // i ������ �湮�� �� ���
			check = check && 1; // �������� and�� check���� �����Ѵ�
		}
		else {
			check = check && 0; //�ϳ��� �����̶� �湮�� ���ߴٸ� check = 0
		}
	}

	return check;
}