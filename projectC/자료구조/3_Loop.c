//@와 대문자 I 그리고 - 입니다
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct _stack { //스택을 활용하기 위한 구조체 선언
	int arr[MAX_SIZE]; //스택의 사이즈를 100으로 설정
	int top; //스택의 위치를 가리키는 값
}Stack;

Stack xstack; //행의 스택 값
Stack ystack; //열의 스택 값

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

	menu(); //사용자가 행렬을 선택할 수 있는 menu함수 선언

}

int menu(void) {

	FILE* stream; //파일을 불러오기 위한 변수 선언
	int k = 1; //menu함수의 while문을 실행시키기 위한 변수 선언
	char a[5]; //@가 단계별로 채워지는 것을 사용자가 보기 원하는 것을 물어보기 위한 변수
	char again[5]; //사용자가 프로그램을 다시 동작시키기 원하는지 물어보기 위한 변수
	int b, c; //사용자가 원하는 행과 열을 받기 위한 변수
	char fileName[10]; //사용자가 원하는 파일의 이름을 입력받기 위한 변수
	int i = 0; //2차원 배열의 행을 나타내기 위한 변수
	int j = 0; //2차원 배열의 열을 나타내기 위한 변수
	int columnLen = 0; //열을 나타내기 위한 변수
	int rowLen = 0; //행을 나타내기 위한 변수

	char** matrix = (char **)malloc(sizeof(char*) * 100); //열을 100사이즈로 동적할당 받는다

	while (1) { //사용자가 파일의 입력을 잘못했을 시 다시 입력하게 하기 위한 반복문이다
		printf("Enter the name of the file : ");
		scanf(" %s", &fileName);

		stream = fopen(fileName, "r"); //파일을 읽기 형식으로 불러온다

		if (stream != NULL) //사용자가 파일 이름을 정확하게 입력했을때 이 반복문을 탈출하고 다음 단계로 넘어간다
			break;

		else if (stream == NULL) //사용자가 파일 이름을 잘못 입력했을때 잘못됬다는 메시지를 보이고 다시 입력하게 한다
			printf("파일명을 다시 입력하세요\n");
	}

	while (!feof(stream)) { //문장을 다 받아올때까지 반복한다, 사용자가 파일에 저장한 행렬을 받아오기 위한 반복문
		char * line = (char*)malloc(sizeof(char) * 100); //행을 문장 단위로 저장하고 구분시키기 위해 파일을 불러오는 while문 안에서 선언
		fgets(line, 100, stream); //사이즈를 할당한 line에 문장단위로 파일을 받는다
		rowLen = strlen(line) - 1;  //열의 길이 설정
		matrix[columnLen++] = line; //행 단위로 문장을 받고 다음 배열로 넘겨준다
	}

	for (int q = 0; q < columnLen; q++) { //출력을 위한 for문, 값들 사이에 한 칸 띄우기 위해 for문으로 출력
		for (int z = 0; z <= rowLen; z++) {
			printf("%c ", matrix[q][z]);
		}
		printf("\n"); //한 행 사이의 구분
	}

	while (k) { //사용자가 행렬을 바꾸기 위한 값을 입력받고, 프로그램이 종료될때까지 메뉴를 반복하는 전체 while문

		while (1) { //사용자가 행과 열을 잘못 입력했을때 다시 입력받기 위한 예외처리
			printf("Enter the row number : ");
			scanf("%d", &b);
			if (b < columnLen) {
				break;
			}
			else {
				printf("행과 열을 다시 입력하세요(크기 오버)\n");
			}
		}

		while (1) { //사용자가 행과 열을 잘못 입력했을때 다시 입력받기 위한 예외처리
			printf("Enter the column number : ");
			scanf("%d", &c);
			if (c <= rowLen) {
				break;
			}
			else {
				printf("행과 열을 다시 입력하세요(크기 오버)\n");
			}
		}

		while (1) { //행과 열을 입력했을때 그 행렬에 이미 @가 있거나 I로 되어있을때 다시 입력받기 위한 예외처리

			if (matrix[b][c] == 'I' || matrix[b][c] == '@') {
				printf("행과 열을 다시 입력하세요(막혀있음)\n");

				printf("Enter the row number : ");
				scanf("%d", &b);

				printf("Enter the column number : ");
				scanf("%d", &c);
			}
			else
				break;
		}

		while (1) { //사용자가 행렬 변경을 단계별로 할건지 아니면 결과만 원하는지 결정하기 위한 반복문

			printf("Do you want print out step by step? <yes/no> : ");
			scanf("%s", &a);

			if (strcmp(a, "yes") == 0) { //단계별로 원할때 step함수에 들어간다
				step(matrix, b, c, columnLen, rowLen);
				break;
			}
			else if (strcmp(a, "no") == 0) { //결과만 원할때 color함수에 들어간다
				color(matrix, b, c, columnLen, rowLen);
				printout(matrix, b, c, columnLen, rowLen); //color함수에서 행렬을 변경하고 printout함수에서 출력한다
				break;
			}
			else {
				printf("다시 입력하세요\n"); //잘못입력했을때 예외처리
			}
		}

		while (1) { //사용자가 다시 행렬을 바꾸기를 원하는지 물어보기 위한 반복문

			printf("Go again? <yes/no> : ");
			scanf("%s", &again);

			if (strcmp(again, "yes") == 0) { //다시 행렬을 바꾸기를 원할때 이 while문을 탈출하고 전체 while문으로 돌아간다
				break;
			}

			else if (strcmp(again, "no") == 0) { //프로그램을 종료하고 싶을때 최종 결과를 나타내기 위한 함수와 전체 while문을 탈출하기 위해 k값 감소
				printf("Your final result is\n");
				printout(matrix, b, c, columnLen, rowLen); //결과를 나타내는 printout함수
				k--; //전체 while문을 탈출하기 위한 k값 감소
				break;
			}
			else {
				printf("다시 입력하세요\n"); //잘못입력했을때 예외처리
			}
		}
	}

	free(matrix);

	return 0;
}

void printout(char** matrix, int b, int c, int columnLen, int rowLen) { //출력을 위한 함수이다

	for (int i = 0; i < columnLen; i++) { //행렬 인자들을 한 칸 씩 띄우기위해 for문으로 출력
		for (int j = 0; j <= rowLen; j++) {
			printf("%c ", matrix[i][j]);
		}
		printf("\n"); //한 행 사이의 구분
	}
	printf("\n"); //행렬 사이의 구분
}

void step(char** matrix, int b, int c, int columnLen, int rowLen) { //행렬 변경을 단계별로 나타내기 위한 함수

	Stack xstack; //Stack구조체의 top 값을 이용해 행의 스택을 쌓는다
	Stack ystack; //Stack구조체의 top 값을 이용해 열의 스택을 쌓는다

	StackInit(&xstack); //행의 스택을 초기화한다
	StackInit(&ystack); //열의 스택을 초기화한다

	matrix[b][c] = '@'; //사용자가 처음 설정한 값에 @를 찍는다
	printout(matrix, b, c, columnLen, rowLen); //행렬의 과정을 단계별로 나타내기 위해 사용자가 처음 설정한 값을 출력한다

	while (1) { //-를 @로 채우는 과정에서 반복문(스택)을 사용하기 위한 전체 while문

		if (b != 0 && matrix[b - 1][c] != 'I' && matrix[b - 1][c] != '@') { //만약 b가 0이 아니고 위에 위치하는 행렬이 막혀있지 않을때
			StackPush(&xstack, b); //행의 스택을 가지고 들어가 스택 값을 넣는다
			StackPush(&ystack, c); //열의 스택을 가지고 들어가 스택 값을 넣는다
			matrix[--b][c] = '@'; //행의 값을 하나 감소시켜주고 '@'로 채운다
			printout(matrix, b, c, columnLen, rowLen); //단계를 출력한다
		}

		else if (c != 0 && matrix[b][c - 1] != 'I' && matrix[b][c - 1] != '@') { //만약 c가 0이 아니고 왼쪽에 위치하는 행렬이 막혀있지 않을때
			StackPush(&xstack, b); //행의 스택을 가지고 들어가 스택 값을 넣는다
			StackPush(&ystack, c); //열의 스택을 가지고 들어가 스택 값을 넣는다
			matrix[b][--c] = '@'; //열의 값을 하나 감소시켜주고 '@'로 채운다
			printout(matrix, b, c, columnLen, rowLen); //단계를 출력한다
		}

		else if (c < rowLen && matrix[b][c + 1] != 'I' && matrix[b][c + 1] != '@') { //만약 c가 열의 사이즈를 넘지 않는 범위에서 오른쪽이 막혀있지 않을때
			StackPush(&xstack, b);  //행의 스택을 가지고 들어가 스택 값을 넣는다
			StackPush(&ystack, c); //열의 스택을 가지고 들어가 스택 값을 넣는다
			matrix[b][++c] = '@'; //열의 값을 하나 증가시켜주고 '@'로 채운다
			printout(matrix, b, c, columnLen, rowLen); //단계를 출력한다
		}

		else if (b < columnLen - 1 && matrix[b + 1][c] != 'I' && matrix[b + 1][c] != '@') { //만약 b가 행의 사이즈를 넘지 않는 범위에서 위쪽이 막혀있지 않을때
			StackPush(&xstack, b); //행의 스택을 가지고 들어가 스택 값을 넣는다
			StackPush(&ystack, c); //열의 스택을 가지고 들어가 스택 값을 넣는다
			matrix[++b][c] = '@'; //행의 값을 하나 증가시키고 '@'로 채운다
			printout(matrix, b, c, columnLen, rowLen); //단계를 출력한다
		}

		else { //위에 조건들이 성립하지 않는 경우
			if (xstack.top == -1) //만약 행의 스택 값이 -1이면 탈출한다(스택을 모두 뺐다는 것을 의미)
				break;
			b = StackPop(&xstack); //행의 스택을 하나 빼준다
			c = StackPop(&ystack); //열의 스택을 하나 빼준다
		}
	}

	return;
}

void color(char** matrix, int b, int c, int columnLen, int rowLen) {

	Stack xstack; //Stack구조체의 top 값을 이용해 행의 스택을 쌓는다
	Stack ystack;//Stack구조체의 top 값을 이용해 열의 스택을 쌓는다

	StackInit(&xstack); //행의 스택을 초기화한다
	StackInit(&ystack); //열의 스택을 초기화한다

	matrix[b][c] = '@';  //사용자가 처음 설정한 값에 @를 찍는다

	while (1) { //-를 @로 채우는 과정에서 반복문(스택)을 사용하기 위한 전체 while문

		if (b != 0 && matrix[b - 1][c] != 'I' && matrix[b - 1][c] != '@') { //만약 b가 0이 아니고 위에 위치하는 행렬이 막혀있지 않을때
			StackPush(&xstack, b); //행의 스택을 가지고 들어가 스택 값을 넣는다
			StackPush(&ystack, c); //열의 스택을 가지고 들어가 스택 값을 넣는다
			matrix[--b][c] = '@'; //행의 값을 하나 감소시켜주고 '@'로 채운다
		}

		else if (c != 0 && matrix[b][c - 1] != 'I' && matrix[b][c - 1] != '@') { //만약 c가 0이 아니고 왼쪽에 위치하는 행렬이 막혀있지 않을때
			StackPush(&xstack, b); //행의 스택을 가지고 들어가 스택 값을 넣는다
			StackPush(&ystack, c); //열의 스택을 가지고 들어가 스택 값을 넣는다
			matrix[b][--c] = '@'; //열의 값을 하나 감소시켜주고 '@'로 채운다
		}

		else if (c < rowLen && matrix[b][c + 1] != 'I' && matrix[b][c + 1] != '@') { //만약 c가 열의 사이즈를 넘지 않는 범위에서 오른쪽이 막혀있지 않을때
			StackPush(&xstack, b);  //행의 스택을 가지고 들어가 스택 값을 넣는다
			StackPush(&ystack, c); //열의 스택을 가지고 들어가 스택 값을 넣는다
			matrix[b][++c] = '@'; //열의 값을 하나 증가시켜주고 '@'로 채운다
		}

		else if (b < columnLen - 1 && matrix[b + 1][c] != 'I' && matrix[b + 1][c] != '@') { //만약 b가 행의 사이즈를 넘지 않는 범위에서 위쪽이 막혀있지 않을때
			StackPush(&xstack, b); //행의 스택을 가지고 들어가 스택 값을 넣는다
			StackPush(&ystack, c); //열의 스택을 가지고 들어가 스택 값을 넣는다
			matrix[++b][c] = '@'; //행의 값을 하나 증가시키고 '@'로 채운다
		}

		else { //위에 조건들이 성립하지 않는 경우
			if (xstack.top == -1) //만약 행의 스택 값이 -1이면 탈출한다(스택을 모두 뺐다는 것을 의미)
				break;
			b = StackPop(&xstack); //행의 스택을 하나 빼준다
			c = StackPop(&ystack); //열의 스택을 하나 빼준다
		}
	}

	return;
}

void StackInit(Stack * ps) { //스택을 초기화 하기 위한 함수
	ps->top = -1; //스택 구조체의 top값을 -1로 초기화
}

void StackPush(Stack * ps, int data) { //-1로 초기화한 Stack 구조체의 top값을 이용해 스택을 쌓는다
	ps->arr[++(ps->top)] = data;
}

int StackPop(Stack * ps) { //쌓은 스택을 빼는 함수
	return ps->arr[ps->top--];
}