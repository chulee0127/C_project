#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define BUF_SIZE 100

int input_vertax(int vertax); //정점의 갯수를 입력받기 위한 함수
int input_edge(int vertax, int edge); //간선의 갯수를 입력받기 위한 함수
void find_Bridge(int matrix[BUF_SIZE][BUF_SIZE], int visit[BUF_SIZE], int vertax, int menu); //Bridge를 찾는 함수
void init_Visit(int visit[BUF_SIZE]); //방문기록을 초기화 하기 위한 함수
void DFS(int matrix[BUF_SIZE][BUF_SIZE], int visit[BUF_SIZE], int v, int vertax); //깊이 우선 탐색을 위한 함수
int check_Visit(int visit[BUF_SIZE], int vertax); //방문 기록을 검사하는 함수

int arr[BUF_SIZE][2]; //Bridge의 여부를 임시로 저장할 배열 선언
int num = 0; //arr배열의 인자

int main() {

	int vertax = 0; //정점의 갯수를 입력 받기위한 변수
	int edge = 0; //간선의 갯수를 입력 받기위한 변수
	int k = 1; //간선의 양 끝점을 입력 받기위한 변수
	int matrix[BUF_SIZE][BUF_SIZE]; //방향성이 없는 모든 간선을 저장할 배열 선언
	int visit[BUF_SIZE]; //방문 내역을 저장할 배열 선언
	int point1 = 0; //간선을 만들 정점
	int point2 = 0; //간선을 만들 정점
	int check = 0; //ture ,false 를 대신할 변수 선언
	char a = { 0 }; //메뉴 버튼을 입력 받기위한 변수 선언
	int menu = 0; //1번과 2번을 구분하기 위한 변수 선언

	vertax = input_vertax(vertax); //정점의 갯수를 입력받기 위한 함수 호출
	printf("\n");
	edge = input_edge(vertax, edge); //간선의 갯수를 입력받기 위한 함수 호출
	printf("\n");

	for (int i = 0; i < vertax; i++) { //입력한 (정점 갯수)^2 만큼 배열 초기화
		for (int j = 0; j < vertax; j++) {
			matrix[i][j] = 0;
		}
	}

	while (1) { //간선의 양 끝점을 입력받기 위한 반복문

		printf("간선의 %d의 양 끝점을 입력하시오 : ", k);
		scanf("%d %d", &point1, &point2);

		k = k + 1; //간선을 입력 받았을 때 하나 증가시킨다

		matrix[point1][point2] = 1; //방향성이 없기 때문에 (n,n) 축으로 대칭 따라서 (n,m) = (m,n)
		matrix[point2][point1] = 1; //방향성이 없기 때문에 (n,n) 축으로 대칭

		if (k > edge) //k가 간선의 갯수보다 많아진다면 간선의 입력을 다 받은 것이므로 무한루프 탈출
			break;
	}

	while (a != 'q') { //메뉴 입력을 받기위한 반복문

		menu = 0;

		printf("\n무엇을 하시겠습니까?\n브리지 전체 나열(1)\n간선 브릿지 테스트(2)\n종료(q)\n");
		scanf(" %c", &a);

		switch (a) {
		case '1': //그래프 내 모든 간선에 대한 Bridge(단절선)여부를 출력한다
			menu = 1;
			find_Bridge(matrix, visit, vertax, menu);
			break;

		case '2': //그래프의 Bridge 여부를 선택받아서 출력한다
			menu = 2;
			find_Bridge(matrix, visit, vertax, menu);
			printf("테스트를 할 간선의 양 끝점을 입력하시오: ");
			scanf("%d %d", &point1, &point2);

			for (int i = 0; i < num; i++) { //arr의 유효한 값이 있는 만큼 반복한다
				if (arr[i][0] == point1 && arr[i][1] == point2 || arr[i][0] == point2 && arr[i][1] == point1) { //Bridge값이 arr에 있는 경우
					check = 1;
				}
			}

			if (check == 1) {
				printf("(%d,%d) 간선은 Bridge 입니다.\n", point1, point2);
			}
			else {
				printf("(%d,%d) 간선은 Bridge가 아닙니다.\n", point1, point2);
			}

			check = 0;
			break;

		case 'q':
			printf("종료\n");
			break;

		default:
			printf("잘못 입력하였습니다.\n");
			break;
		}
	}

	return 0;
}

int input_vertax(int vertax) {

	printf("정점의 개수를 입력하시오 : ");
	scanf("%d", &vertax);

	if (vertax <= 0 || vertax > BUF_SIZE) { //예외처리, 정점의 갯수가 0이하인 경우 또는 배열의 사이즈를 넘어선 경우
		while (1) { //정점 갯수가 0보다 클때 까지 무한 루프
			printf("입력이 잘못되었습니다.\n");
			printf("정점의 개수를 입력하시오 : ");
			scanf("%d", &vertax);

			if (vertax > 0 && vertax <= BUF_SIZE) { //정점의 개수가 0보다 크고 배열의 사이즈보다 작은 경우 반복문을 탈출한다
				break;
			}
		}
	}

	return vertax;
}

int input_edge(int vertax, int edge) {

	printf("간선의 갯수를 입력하시오 : ");
	scanf("%d", &edge);

	if (0 >= edge || edge > vertax * 2) { //예외처리, 간선의 갯수가 0이하인 경우 또는 정점의 갯수에 2배를 넘는 경우
		while (1) {
			printf("입력이 잘못되었습니다.\n");
			printf("간선의 갯수를 입력하시오 : ");
			scanf("%d", &edge);

			if (0 < edge && edge <= vertax * 2)
				break;
		}
	}

	return edge;
}

void find_Bridge(int matrix[BUF_SIZE][BUF_SIZE], int visit[BUF_SIZE], int vertax, int menu) {

	int check; //ture, false 값을 대신할 변수 선언
	int count[BUF_SIZE]; //말단 노드를 알기 위한 배열

	num = 0;

	for (int i = 0; i < BUF_SIZE; i++) { //0으로 초기화 하기 위한 반복문
		count[i] = 0;
	}

	for (int i = 0; i < vertax; i++) {
		for (int j = 0; j < vertax; j++) {
			count[i] = matrix[i][j] + count[i]; //matrix의 가로 값이 1인 경우 연결이 한개 -> 말단 노드
		}
	}

	for (int i = 0; i < vertax; i++) {
		for (int j = i; j < vertax; j++) {
			if (matrix[i][j] == 1) {   //간선이 연결이 되어있다면
				matrix[i][j] = 0;      //간선을 임시로 지움
				init_Visit(visit);     //visit배열 초기화
				DFS(matrix, visit, i, vertax); //i에 대한 깊이 우선 탐색
				check = check_Visit(visit, vertax); //i에 대한 깊이 우선 탐색 후 방문한 정점 조회

				if (count[i] == 1 || count[j] == 1) { //말단 노드인 경우
					check = 1;
				}

				if (check == 1 && menu == 1) { //말단 노드이거나 간선을 지워도 모든 정점에 방문이 가능한 경우
					printf("(%d, %d) 간선은 Bridge가 아닙니다.\n", i, j);
				}

				else { //말단노드가 아니고 간선을 지웠을 때 어느 정점에 방문하지 못하는 경우
					if (menu == 1) //1번이 선택 되었을 때만 출력한다
						printf("(%d, %d) 간선은 Bridge 입니다.\n", i, j);

					arr[num][0] = i; //간선의 양 끝 정점을 임시 저장
					arr[num++][1] = j; //간선의 양 끝 정점을 임시 저장
				}
				matrix[i][j] = 1; //임시로 지운 간선을 복구한다
			}
		}
	}

}

void init_Visit(int visit[BUF_SIZE]) {

	for (int i = 0; i < BUF_SIZE; i++) {
		visit[i] = -1; //정점에 0이 있기 때문에 -1로 초기화한다
	}
}

void DFS(int matrix[BUF_SIZE][BUF_SIZE], int visit[BUF_SIZE], int v, int vertax) {

	visit[v] = 1; //방문 기록을 메모한다

	for (int i = 0; i < vertax; i++) { //정점 크기만큼 반복하기 위한 for문
		if (matrix[v][i] == 1 && visit[i] != 1) { //간선이 연결이 되어있고 아직 그 정점에 방문을 하지 않았을 경우
			DFS(matrix, visit, i, vertax); // 해당 정점을 방문한다
		}
	}

}

int check_Visit(int visit[BUF_SIZE], int vertax) {

	int check = 1;

	for (int i = 0; i < vertax; i++) { // visit의 크기만큼 반복한다
		if (visit[i] == 1) { // i 정점에 방문을 한 경우
			check = check && 1; // 논리연산자 and로 check값을 저장한다
		}
		else {
			check = check && 0; //하나의 정점이라도 방문을 안했다면 check = 0
		}
	}

	return check;
}