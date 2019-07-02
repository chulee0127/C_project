#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable : 4996)

int readData(void); //사용자가 원하는 갯수만큼의 난수를 생성하기 위한 함수
void menu(void); //메뉴를 선택할 수 있는 메뉴 함수
void searchNumber(int a); //사용자가 몇번째로 원하는 숫자를 찾기 위한 함수

int main(){

	menu(); //처음 시작을 알리는 메뉴함수 호출

	return 0;
}

int readData(void) //난수를 생성하기 위한 함수이고 menu함수에서 호출한다
{
	FILE *stream;//파일 입출력을 위한 변수
	int a;//몇개의 난수를 생성할지 정하기 위한 변수
	int* array;//난수의 갯수만큼 동적할당을 받기위한 변수

	printf("몇 개의 난수를 원하십니까? : ");
	scanf("%d", &a);
	printf("%d개의 난수가 생성되어 data.dat에 저장되었습니다.\n", a);

	array = (int*)malloc(sizeof(int)*a); //난수의 갯수 a개만큼 메모리 동적 할당

	stream = fopen("data.dat", "w"); //파일을 쓰기형식으로 불러온다
	if (stream == NULL) { //파일을 불러올수 없을때를 대비하는 if문
		printf("Write Error!!\n"); //파일을 불러올 수 없을 때 에러메시지
		return 0;
	}

	srand((unsigned)time(NULL)); //양의 정수를 시간 단위로 해서 난수를 생성하는 함수

	for (int i = 1; i <= a; i++) { //사용자가 원하는 갯수만큼 난수를 받기위한 반복문
		fprintf(stream, "%d\t", rand()); //파일에 난수를 저장한다
		if ( i % 10 == 0 ) { //10개의 숫자가 들어오면 줄바꿈을 한다
			fprintf(stream, "\n");
		}
	}

	free(array);
	fclose(stream);
	return a; //입력받은 난수의 갯수를 리턴해서 가져간다. 왜냐하면 menu함수에서 searchNumber함수를 호출할때 난수의 갯수를 가지고 들어가서 사용하기 때문
}

void menu(void) {
	int a = 0; //a는 메뉴함수를 위한 반복문에서 메뉴 번호를 입력받는 변수이다. 0으로 초기화 해준 이유는 처음에 들어갈 때 4번이 아니면 되기 때문이다. 꼭 0일 필요도 없다
	int c; //readData함수에서 생성한 난수의 갯수를 가지고 들어오기 위한 변수이다. 갯수를 c에다 저장해 searchNumer함수에 가지고 들어간다
	char g; // g는 메뉴 1번을 입력했을 때 y or n 을 입력받기 위한 char형 변수
	int b = 0; //b가 0일 때 난수를 생성하지 않은 상태를 나타내고 만약 난수를 생성했으면 b는 1로 변한다 즉, 난수의 생성 상태를 표현하기 위한 변수이다. 메뉴 번호를 고를 때 예외처리를 위한 변수이다

	while (a != 4) { //a에 4를 입력받게 되면 프로그램을 종료시켜야 하기 때문에 while문 조건에 4가 아니여야된다는 조건을 생성
		             //사용자가 프로그램을 종료 시키기 전까지 메뉴창이 닫히면 안되기 때문에 사용자가 종료를 원할 때까지 메뉴 창을 띄어놓기 위한 반복문
		printf("메뉴\n1.난수 생성\n2.오름차순 순번찾기\n3.정렬\n4.프로그램 종료\n");
		printf("원하는 메뉴 번호를 입력하세요 : ");
		scanf("%d", &a);

		if (a == 1 && b != 1) { //만약 난수 생성을 원하고 난수가 생성되지 않은 상태 즉, 처음에 난수를 만들기 위해서 들어와야하는 if문이다
			printf("난수를 생성하시겠습니까?<y/n> : ");
			scanf(" %c", &g);
			if (g == 'y') { // 난수가 생성되지 않은 상태에서 사용자가 난수 생성을 원한다
				c = readData(); //readData함수로 들어가 난수를 생성해 파일을 저장하고 생성한 난수의 갯수만을 가지고 나온다
				b = 1; //readData함수에서 난수를 생성했기 때문에 b를 1로 선언해 난수가 생성되었음을 알린다
			}
			else if (g == 'n' && b != 1) { //난수 생성을 하지 않은 상태에서 난수를 생성하기 원하지 않을 때 난수가 생성되지 않았음을 알려준다
				printf("난수가 생성되지 않았습니다.\n");
				printf("원하는 메뉴 번호를 다시 입력하세요.\n");
			}
			else if (g == 'n' && b == 1) { //난수를 생성한 상태에서 난수 생성을 원하지 않을때 이미 난수가 생성되었음을 알려준다
				printf("이미 난수가 생성되었습니다.\n");
				printf("원하는 메뉴 번호를 다시 입력하세요\n");
			}
			else { //그밖에 예외처리를 위한 else문
				printf("원하는 메뉴 번호를 다시 입력하세요.\n");
			}
		}
		else if (a == 1 && b == 1) { //난수가 생성된 상태에서 난수 생성을 원할때 난수가 이미 생성되었음을 알려준다
			printf("난수가 이미 생성되었습니다.\n");
			printf("원하는 메뉴를 다시 입력하세요.\n");
		}
		else if (a == 2) { //사용자가 메뉴번호 2번을 선택했을 때 숫자찾기로 넘어가거나 난수가 생성되지 않았을 경우를 대비하기 위한 if문
			if (b == 1) { //난수가 생성되었을 때 searchNumber함수로 들어가 사용자가 원하는 숫자를 찾는다
				searchNumber(c); //readData함수에서 가지고 나온 생성된 난수의 갯수 c를 가지고 searchNumber함수로 들어간다
			}
			else { //난수가 생성되지 않았을 경우 난수 먼저 생성하라고 얘기해준다
				printf("난수가 생성되지 않았습니다.\n");
				printf("원하는 메뉴 번호를 다시 입력하세요.\n");
			}
		}
		else if (a == 3) { //정렬하기 위한 메뉴번호이다 과제에서 빼주셨습니다
			if (b == 1) { //난수가 생성되고 정렬을 원하는 경우
				printf("과제에서 빼주셨습니다.\n");
			}
			else { //난수가 생성되지 않았을 경우
				printf("난수가 생성되지 않았습니다.\n");
				printf("원하는 메뉴 번호를 다시 입력하세요.\n");
			}
		}
		else if (a == 4) { //사용자가 프로그램 종료를 원할때 미련없이 프로그램을 종료한다.
			break;
		}
		else { //그밖에 예외처리를 위한 else문
			printf("원하는 메뉴 번호를 다시 입력하세요\n");
		}
	}
}

void searchNumber(int a) { //사용자가 원하는 숫자를 찾기위한 함수, readData함수에서 생성한 난수의 갯수를 가지고 들어온다
	int* array; //파일에 저장한 수들을 다시 불러와 배열에 저장하기위해 동적할당을 받는다 즉, 동적할당에 필요한 변수 선언
	int t; //사용자가 몇 번째 오름차순을 원하는지 입력받기 위한 변수
	int prev = 0; //최솟값 이전의 최솟값을 저장하기 위한 변수이다
	int firstData = 999999; //최솟값을 찾기 위해 수들을 비교할때 처음 기준이 되는 수(가장 큰 수로 선언)
	int k; //사용자가 원하는 데이터가 몇 번째에 위치하는지 표시하기 위한 변수
	FILE* stream; //파일에 저장한 난수들을 불러오기 위해 선언

	printf("몇번째 오름순번의 수를 찾으세요? ");
	scanf("%d", &t);

	array = (int*)malloc(sizeof(int)*a); //파일에서 불러온 난수들을 배열에 저장하기 위해 동적할당을 받는다
	
	stream = fopen("data.dat", "r"); //파일을 읽기 형식으로 선언

	for (int i = 0; i < a; i++) { //파일에 있는 난수들을 배열에 저장한다
		fscanf(stream, " %d", &array[i]);
	}

	for (int j = 0; j < t; j++) { //사용자가 몇 번째로 작은 숫자를 찾기 원하는지 즉, 몇 번째로 원하는 것만큼 작은 값을 찾는다
		for (int i = 0; i < a; i++) { //배열에서 최솟값을 찾는다 조건은, 전에 찾았던 최솟값보다는 크다
			if (firstData > array[i] && array[i] > prev) { //prev에다가 이전에 최솟값을 저장하고 그거보다 하나 큰 최솟값을 찾는다
				firstData = array[i]; //만약 난수가 firstData초기값 혹은 이전의 배열보다 작다면 그 값을 firstData에 저장한다
				k = i; // k번째 위치한 데이터가 사용자가 원하는 수다
			}
		}
		prev = firstData; //최솟값을 prev에 저장한다
		firstData = 999999; //최솟값을 다시 찾기 위하여 초기값으로 설정
	}

	printf("%d번째 최소값 : %d 데이터 %d 번째에 있습니다.\n", t, prev, k + 1);

	free(array);
	fclose(stream);
}