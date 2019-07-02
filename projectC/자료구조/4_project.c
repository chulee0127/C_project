#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct book { //책의 제목과 재고, 가격을 저장할 자기참조구조체 선언
	char title[50];
	char qty[5];
	char price[10];
	struct book* next;
}book;

typedef struct author { //작가의 이름을 저장하고 책의 정보를 가리키는 구조체 선언
	char name[30];
	book* link;
}author;

void greeting(void);
author* readDatabase(author* theInventory);
int printMenu(void);
void displayInventory(author* a);
void displayAuthorsWork(author* theInventory);
author* addBook(author* theInventory);
void changePrice(author* theInventory);
void changeQty(author* theInventory);
void totalQty(author* theInventory);
void calculateTotalAmount(author* theInventory);

int main(void) {
	greeting(); //프로그램 사용을 반가워하는 함수

	int flag, choice; //flag는 while문의조건을 주기 위하여, choice는 사용자가 원하는 메뉴 번호를 선택했을때 그 값을 리턴하여 원하는 함수로 들어가기 위한 선언이다

	author* theInventory; //readDatabase함수에서 만든 theInventory를 저장하기 위한 변수 선언
	author a[] = { 0, }; // theInventory는 구조체를 원소로한 일차원 배열임 --> 저장할 값이 필요해서 a로 선언

	theInventory = readDatabase(&a); //readDatabase함수에 a라는 배열의 주소를 가지고 들어가, 함수안에서 theInventory에 작가와 책 관련 정보를 저장해서 가지고 나온다 그리고 theInventory에 저장

	flag = 1; //메뉴선택의 반복문을 실행하기 위한 값

	while (flag) { //사용자가 종료를 원할때까지 메뉴를 반복실행한다.

		choice = printMenu(); //사용자가 원하는 메뉴 번호를 선택하기 위한 함수

		if (choice == 1)
			displayInventory(theInventory);

		else if (choice == 2)
			displayAuthorsWork(theInventory);

		else if (choice == 3)
			addBook(theInventory);

		else if (choice == 4)
			changePrice(theInventory);

		else if (choice == 5)
			changeQty(theInventory);

		else if (choice == 6)
			totalQty(theInventory);

		else if (choice == 7)
			calculateTotalAmount(theInventory);

		else if (choice == 8) { //사용자가 종료를 원할때 프로그램을 종료한다
			printf("Thank you for using this program\n");
			flag = 0; //사용자가 종료를 원할때 메뉴 선택 반복문을 탈출하기 위한 값 설정
		}

		else
			printf("Invalid choice\n");
	}

	free(theInventory);
	return 0;
}

void greeting(void) { //사용자를 반기는 함수
	printf("Welcome to bookstore program!\n");
}

author* readDatabase(author* theInventory) { //구조체를 원소로한 theInventory를 가지고 들어온다. 이 함수에서 theInventory를 채워서 나간다
	
	int z = 0; //title[z] 책 제목을 한 글자씩 저장하기 위한 변수
	int k = 0; //stock[k] 책 재고를 한 글자씩 저장하기 위한 변수
	int l = 0; //price[l] 책 가격을 한 글자씩 저장하기 위한 변수
	int r = 0; //authorName[r] 작가 이름을 한 번에 저장하기 위한 변수
	int cnt = 0; // , 의 갯수를 구분하기 위한 변수 선언
	int num = 0; // theInventory 안의 저자 수
	char fileName[20]; //사용자가 원하는 파일의 이름을 입력받기 위한 변수
	char title[30] = { 0, }; //책 제목을 저장하기 위한 변수
	char stock[30] = { 0, }; //책의 재고를 저장하기 위한 변수
	char authorName[30] = { 0, }; //작가의 이름을 저장하기 위한 변수
	char price[10] = { 0, }; //책의 가격을 저장하기 위한 변수
	FILE* stream; //파일을 불러오기 위한 변수
	book* bk; //readDatabase함수에서 theInventory에 저장하기 전 임시로 저장하기 위해 선언
	int a = 0; //문장 단위로 받아온 line을 한 글자씩 나누기 위한 변수
	char firstName[20] = { 0, }; //작가의 firstName
	char lastName[20] = { 0, }; //작가의 lastName
	int c = 0; //사용자가 입력한 작가가 이미 존재하는지 구분하기 위한 변수

	while (1) { //사용자가 파일의 입력을 잘못했을 시 다시 입력하게 하기 위한 반복문이다
		printf("Enter the name of the file : ");
		scanf(" %s", &fileName);

		stream = fopen(fileName, "r"); //파일을 읽기 형식으로 불러온다

		if (stream != NULL) //사용자가 파일 이름을 정확하게 입력했을때 이 반복문을 탈출하고 다음 단계로 넘어간다
			break;

		else if (stream == NULL) //사용자가 파일 이름을 잘못 입력했을때 잘못됬다는 메시지를 보이고 다시 입력하게 한다
			printf("Error reading database\n");
	}

	theInventory = (author*)malloc(sizeof(author) * 100); //theInventory를 동적할당 받기 위해 선언
	char * line = (char*)malloc(sizeof(char) * 100); //파일의 책 정보를 문장 단위로 받아오기 위한 동적할당

	while (!feof(stream)) {//문장을 다 받아올때까지 반복한다

		fgets(line, 100, stream); //line에 책 정보를 문장 단위로 받아온다

		k = 0, l = 0, z = 0, a = 0, r = 0, cnt = 0;   //반복문 변수 초기화

		memset(authorName, 0, strlen(authorName)); // 작가의 이름을 새로 받기 위해 초기화
		memset(title, 0, strlen(title)); //책 제목을 새로 받기 위해 초기화
		memset(price, 0, strlen(price)); //책 가격을 새로 받기 위해 초기화
		memset(stock, 0, strlen(stock)); //책 재고를 새로 받기 위해 초기화

		while (1) { // ,가 0개 또는 1개 있을 경우 

			if (cnt == 2) { //두번째 콤마를 만났을때에 책 정보로 넘어간다
				a++; // , 를 제외하고 책 정보를 저장하기 위해 하나 넘어간다
				break;
			}

			authorName[r++] = line[a++]; // 성과 이름을 합쳐서 authorName에 저장

			if (line[a] == ',') { // , 를 만났을때 cnt변수를 하나 더해서 구분
				cnt++;
			}
		}

		while (1) { // 책 제목을 저장하고 세번째 , 를 만나면 재고로 넘어간다

			if (cnt == 3)
				break;

			title[z++] = line[a++];

			if (line[a] == ',') { // , 를 만났을때 cnt변수를 하나 더해서 구분
				cnt++;
				a++;
			}
		}

		while (1) { // 책 재고를 저장하고 네번째 , 를 만나면 가격으로 넘어간다

			stock[k++] = line[a++];

			if (line[a] == ',') { // , 를 만났을때 cnt변수를 하나 더해서 구분
				cnt++;
				a++;
			}

			if (cnt == 4)
				break;
		}

		while (1) { //가격을 저장하고 줄바꿈일때에 반복문 탈출

			price[l++] = line[a++];

			if (line[a] == 10)
				break;
		}

		bk = (book *)malloc(sizeof(book) * 100); // 임시로 책 관련 정보를 저장하기 위해서 readDatabase함수에서 선언한 구조체 변수를 동적할당 받는다
		strcpy(bk->title, title); //bk->title에 책 제목을 복사한다
		strcpy(bk->qty, stock); //bk->qty에 책 재고를 복사한다
		strcpy(bk->price, price); //bk->price에 책 가격을 복사한다
		bk->next = NULL; //bk->next가 가리키는 링크는 널이다
		c = 0; //줄바꿈을 할 때마다 작가의 이름이 같은지 확인하기 위해 선언

		for (int b = 0; b < num; b++) { //b가 0부터, 저장된 작가의 수까지 작가의 이름이 같은지 비교하기 위한 for문
			if (strcmp(theInventory[b].name, authorName) == 0) {
				c = 1; //만약에 작가이름이 같다면 c=1로 선언하여 작가 이름이 같다는걸 표시
				bk->next = theInventory[b].link; //bk구조체의 다음 노드에 같은 작가 배열 링크를 연결
				theInventory[b].link = bk; //같은 작가 배열 링크에 책 정보를 넣는다
				break; //작가이름이 같을 경우 리스트에 저장했기 때문에 굳이 남아있는 비교를 할 필요가 없어서 for문 탈출
			}
		}

		if (c == 0) { //만약 작가의 이름이 다르다면 새로운 배열에 작가의 이름과 정보를 저장한다.
			theInventory[num].link = NULL; //작가 배열 처음 링크에 NULL값을 넣어준다. 왜냐하면 나는 작품 정보를 역순으로 저장 할 것이기 때문이다
			strcpy(theInventory[num].name, authorName); //배열에 작가 이름을 넣어준다
			theInventory[num++].link = bk; //작가 배열이 가리키는 링크가 책 정보를 가리키게 하고 다음 작가를 받을수 있게 num값을 하나 올려준다
		}
	}

	theInventory[num].link = NULL; //마지막 theInventory값에 널값

	return theInventory; //readDatabase함수에서 만든 구조체를 main함수로 가지고 나간다
}

int printMenu(void) { //사용자가 원하는 메뉴 번호를 선택하기 위한 함수이다

	int a; //번호를 고르기 위한 변수

	printf("--------------------------------\n");
	printf("Enter 1 to dispaly the inventory\n");
	printf("Enter 2 to dispaly the books by one author\n");
	printf("Enter 3 to add a book\n");
	printf("Enter 4 to change the price\n");
	printf("Enter 5 to change the qty on hand\n");
	printf("Enter 6 to view the total number of books in the inventory\n");
	printf("Enter 7 to see the total amount of the entire inventory\n");
	printf("Enter 8 to exit\n");

	while (1) {

		while (getchar() != '\n'); //문자열 오류 방지

		printf("Enter your choice : ");
		scanf("%d", &a);

		if (a == 1 || a == 2 || a == 3 || a == 4 || a == 5 || a == 6 || a == 7 || a == 8) { //메뉴번호 고를때의 예외처리
			break;
		}

		else {
			printf("원하는 메뉴 번호를 다시 입력하세요\n");
		}
	}

	return a; //사용자가 고른 메뉴 번호를 가지고 나간다
}

void displayInventory(author* a) { //책의 정보를 사용자에게 보여주기 위한 함수

	int i = 0; //작가가 저장된 배열을 표현하기 위한 변수

	book * tmp = NULL; //연결된 링크의 정보를 직접 바꾸는게 아니라 임시로 구조체를 선언해서 링크에 연결 된대로 출력하기 위해 선언

	while (1) { //작가의 정보를 보여주기 위한 while문

		printf("--------------------------------\n");
		printf("The author is : %s\n", a[i].name); //작가의 이름을 출력

		tmp = a[i].link; //작가의 이름에 연결된 링크를 tmp가 가리키게 한다

		printf("--------------------------------\n");

		while (tmp != NULL) { //해당 작가의 정보들을 출력
			printf("\tThe title is : %s\n\tThe qty is : %s\n\tThe price is : %s\n", tmp->title, tmp->qty, tmp->price);
			printf("--------------------------------\n");
			tmp = tmp->next;
		}
		i++; //다음 작가로 넘어감

		if (a[i].link == NULL) //만약 작가배열이 NULL이면 while문 탈출
			break;
	}
}

void displayAuthorsWork(author* theInventory) {

	int a = 0; //작가의 수
	int num = 0; // 작가가 저장된 배열번호를 나타내기 위한 변수 선언
	char firstName[20] = { 0, }; //사용자가 입력하는 firstName
	char lastName[20] = { 0, };  //사용자가 입력하는 lastName
	char buf[100] = { 0, };   //사용자가 나눠서 입력한 firstName과 lastName을 합치기 위한 변수
	book * tmp = NULL; //책 정보들을 출력할때 임시로 구조체를 선언해서 연결된 링크대로 출력한다
	int count = 0; //연결된 리스트의 갯수
	book * temp; //정렬을 하기위한 구조체 선언
	int i, j; //정렬을 하기위한 변수

	while (1) { //작가가 몇 명인지 세기위한 반복문
		while (theInventory[a].link != NULL) {
			a++;
		}
		break;
	}
	a--; //작가의 수를 정확하게 맞춰주기 위해 마지막에 하나 감소

	while (1) { //작가의 이름을 잘못 입력했을때의 예외처리

		memset(buf, 0, strlen(buf)); // 작가의 이름을 잘못 입력했을 때 초기화하고 새로 받는다
		memset(lastName, 0, strlen(lastName)); // 작가의 이름을 잘못 입력했을 때 초기화하고 새로 받는다
		memset(firstName, 0, strlen(firstName)); // 작가의 이름을 잘못 입력했을 때 초기화하고 새로 받는다
		num = 0; // 작가의 이름을 잘못 입력했을 때 초기화하고 새로 받는다

		printf("Enter the author's firstname : ");
		scanf("%s", &firstName);

		printf("Enter the author's lastname : ");
		scanf("%s", &lastName);

		sprintf(buf, "%s,%s", lastName, firstName); //사용자가 입력한 작가의 이름을 하나로 합쳐준다

		while (1) { //사용자가 찾는 작가가 있을때 이 반복문과 전체 반복문을 탈출한다
			if (_stricmp(buf, theInventory[num].name) == 0) //사용자가 입력한 작가의 이름이 있을때 이 반복문을 탈출한다
				break;
			else { //배열에 있는 저장된 작가를 모두 비교하기 위해 배열값을 하나 올려준다
				num++;
			}

			if (num > a) { //사용자가 입력한 작가의 이름이 없을 때
				printf("작가의 정보가 존재하지 않습니다\n");
				break;
			}
		}

		if (_stricmp(buf, theInventory[num].name) == 0)
			break; //작가 이름 입력받는 전체 반복문 탈출
	}

	tmp = theInventory[num].link; //해당 작가의 연결된 책 정보들을 직접 바꾸는게 아니라 임시로 출력 해주기 위해 선언
								  //num은 위에 반복문에서 사용자가 입력한 해당 작가이므로 배열번호를 가져온다
	while (tmp != NULL) { //연결된 리스트의 갯수를 파악한다
		count++;
		tmp = tmp->next;
	}

	book ** tmpbook = (book **)malloc(sizeof(book*) * count); //정렬을 하기 위한 동적할당

	tmp = theInventory[num].link;

	for (a = 0; a < count; a++) { //연결된 리스트의 수만큼 tmp에 저장
		tmpbook[a] = tmp;
		tmp = tmp->next;
	}

	for (i = 0; i<count - 1; i++)//비교횟수는 데이터갯수-1, 자기 자신과는 비교 하지 않음 
	{
		for (j = 0; j<count - 1; j++)
		{
			if (strcmp(tmpbook[j]->title, tmpbook[j + 1]->title) > 0)
			{
				temp = tmpbook[j];//뒷자리의 수가 더 크면 교체 
				tmpbook[j] = tmpbook[j + 1];
				tmpbook[j + 1] = temp;
			}
		}
	}

	for (i = 0; i<count; i++) { //해당 작가의 정보들을 출력
		printf("--------------------------------\n");
		printf("\tThe title is : %s\n\tThe qty is : %s\n\tThe price is : %s\n", tmpbook[i]->title, tmpbook[i]->qty, tmpbook[i]->price);
		printf("--------------------------------\n");
	}

	return;
}

author* addBook(author* theInventory) {

	char firstName[20] = { 0, }; //작가의 firstName을 받는다
	char lastName[20] = { 0, };  //작가의 lastName을 받는다
	char buf[100] = { 0, }; //사용자가 입력한 작가의 이름을 합치기 위한 변수
	int num = 0; //작가가 존재하는 배열의 번호
	char title[200] = { 0, }; //책 제목을 입력 받는 변수
	char qty[10]; //책 재고를 입력 받는 변수
	char price[100]; //책 가격을 입력받는 변수
	char buf2[100] = { 0, }; //책의 qty와 price를 입력받는 변수
	int state = 0; //사용자가 입력한 작가의 존재 유무
	book * tmp = NULL; //사용자가 입력한 책 제목을 비교할때 원문을 바꾸지 않기 위해서
	char* ex; // .을 구분하기 위한 변수
	char* ex2; // .을 구분하기 위한 변수

	book* bk; //책의 정보를 링크로 연결시키기 위한 구조체 선언
	bk = (book *)malloc(sizeof(book) * 100); //책의 정보를 저장하기 위한 구조체에 동적할당을 한다

	while (1) { //작가의 이름을 잘못 입력했을때의 예외처리

		printf("Enter the author's firstname : ");
		scanf("%s", &firstName);

		printf("Enter the author's lastname : ");
		scanf("%s", &lastName);

		sprintf(buf, "%s,%s", lastName, firstName); //작가의 이름을 합친다

		while (theInventory[num].link != NULL) { //사용자가 찾는 작가가 없을때까지 반복한다
			if (_stricmp(buf, theInventory[num].name) == 0) { //사용자가 입력한 작가의 이름이 있을때 이 반복문을 탈출한다
				state = 1; // 작가가 존재하는 경우 state = 1
				break;
			}

			num++; //다음 작가로 넘어감
		}

		break; //작가 이름 입력받는 전체 반복문 탈출
	}

	while (getchar() != '\n');

	while (1) { //책의 제목을 저장하기 위한 반복문

		memset(title, 0, strlen(title)); //사용자가 책 제목을 잘못 입력했을 때 다시 받아야된다
		tmp = NULL; //사용자가 책 제목을 잘못 입력했을 때 다시 받아야된다

		printf("Enter the title : ");
		fgets(title, 200, stdin); //두번째 들어왔을 때 못읽음
		title[strlen(title) - 1] = 0;

		if (state == 1) { //사용자가 입력한 작가가 존재할 때

			tmp = theInventory[num].link;
			while (1) { //만약 사용자가 입력한 책이 이미 있으면 다시 입력하게 한다
				if (tmp != NULL && _stricmp(tmp->title, title) == 0) {
					printf("This book is already in the Inventory and cannot be added again\n");
					break;
				}
				else {
					tmp = tmp->next; //책의 다음 리스트로 넘어간다
					if (tmp == NULL)
						break; //사용자가 입력한 책 제목이 겹치지 않으므로 반복문 탈출
				}
			}
			if (tmp->title == NULL) //전체 반복문 탈출
				break;
		}

		else if (state == 0) { //작가 이름이 없으면 책도 새로운 정보라는 얘기이므로 책 제목을 입력받고 바로 전체 while문 탈출
			break;
		}
	}

	strcpy(bk->title, title); //입력받은 책 제목을 bk->title에 책 제목을 복사한다

	while (1) { //재고를 받을때 예외처리를 위한 반복문

		printf("Enter the qty : ");
		scanf("%s", qty);

		ex2 = strchr(qty, '.'); //문자열로 받고 실수를 구분하기 위해 .을 찾는다

		if (atoi(qty) > 0 && ex2 == NULL) { //정수로 바꿨을때 양수이거나 .이 없다 즉, 실수가 아닐때 탈출한다
			break;
		}
		else {
			continue;
		}
	}

	sprintf(buf2, "%s", qty);
	strcpy(bk->qty, buf2); //bk->qty에 qty를 복사

	while (1) {

		printf("Enter the price : ");
		scanf("%s", price);

		ex = strchr(price, '.'); //문자열로 받고 실수를 구분하기 위해 .을 찾는다

		if (atof(price) <= 0 || ex == NULL || strlen(ex) != 3) { //실수로 바꿨을때 음수이거나 정수이거나 소수점둘째자리가 아니면 반복한다
			continue;
		}
		else
			break;
	}

	sprintf(buf2, "%s", price);
	strcpy(bk->price, buf2); //bk->price에 책 가격을 복사

	bk->next = NULL; //bk->next가 가리키는 링크는 널이다

	if (state == 1) {
		bk->next = theInventory[num].link; //bk구조체의 다음 노드에 같은 작가 배열 링크를 연결
		theInventory[num].link = bk; //같은 작가 배열 링크에 책 정보를 넣는다
	}

	else
	{
		strcpy(theInventory[num].name, buf); //배열에 작가 이름을 넣어준다
		theInventory[num++].link = bk; //작가 배열이 가리키는 링크가 책 정보를 가리키게 하고 다음 작가를 받을수 있게 num값을 하나 올려준다
		theInventory[num].link = NULL; //마지막 작가 배열 링크에 널을 넣어준다
	}

	return theInventory;
}

void changePrice(author* theInventory) {

	int a = 0; //작가의 수
	char firstName[20] = { 0, }; //작가의 firstName을 받는다
	char lastName[20] = { 0, };  //작가의 lastName을 받는다
	char buf[100] = { 0, }; //사용자가 입력한 작가의 이름을 합치기 위한 변수
	int num = 0; //작가가 존재하는 배열의 번호
	char title[200] = { 0, }; //책 제목을 입력 받는 변수
	char tmpprice[100]; //가격을 임시저장하기 위한 변수
	char price[100]; //책 가격을 입력받는 변수
	book * tmp = NULL; //사용자가 입력한 책 제목을 비교할때 원문을 바꾸지 않기 위해서
	char* ex; // . 구분하기 위한 변수

	while (1) { //작가가 몇 명인지 세기위한 반복문
		while (theInventory[a].link != NULL) {
			a++;
		}
		break;
	}
	a--; //작가의 수를 정확하게 맞춰주기 위해 마지막에 하나 감소

	while (1) { //작가의 이름을 잘못 입력했을때의 예외처리

		memset(buf, 0, strlen(buf)); // 작가의 이름을 잘못 입력했을 때 초기화하고 새로 받는다
		memset(lastName, 0, strlen(lastName)); // 작가의 이름을 잘못 입력했을 때 초기화하고 새로 받는다
		memset(firstName, 0, strlen(firstName)); // 작가의 이름을 잘못 입력했을 때 초기화하고 새로 받는다
		num = 0; // 작가의 이름을 잘못 입력했을 때 초기화하고 새로 받는다

		printf("Enter the author's firstname : ");
		scanf("%s", &firstName);

		printf("Enter the author's lastname : ");
		scanf("%s", &lastName);

		sprintf(buf, "%s,%s", lastName, firstName); //사용자가 입력한 작가의 이름을 하나로 합쳐준다

		while (1) { //사용자가 찾는 작가가 있을때 이 반복문과 전체 반복문을 탈출한다
			if (_stricmp(buf, theInventory[num].name) == 0) //사용자가 입력한 작가의 이름이 있을때 이 반복문을 탈출한다
				break;
			else { //배열에 있는 저장된 작가를 모두 비교하기 위해 배열값을 하나 올려준다
				num++;
			}

			if (num > a) { //사용자가 입력한 작가의 이름이 없을 때
				printf("작가의 정보가 존재하지 않습니다\n");
				break;
			}
		}

		if (_stricmp(buf, theInventory[num].name) == 0)
			break; //작가 이름 입력받는 전체 반복문 탈출
		else
			continue;
	}

	while (getchar() != '\n'); //문자열 오류 방지

	while (1) { //책의 제목을 저장하기 위한 반복문

		memset(title, 0, strlen(title)); //사용자가 책 제목을 잘못 입력했을 때 다시 받아야된다
		tmp = NULL; //사용자가 책 제목을 잘못 입력했을 때 다시 받아야된다

		printf("Enter the title : ");
		fgets(title, 200, stdin);  //책의 제목을 띄어쓰기도 받기위해 fgets사용
		title[strlen(title) - 1] = 0; //책 제목 배열의 사이즈를 맞춰준다

		tmp = theInventory[num].link;

		while (1) { //사용자가 입력한 책 제목이 존재하면 가격을 바꾸기 위해 반복문 탈출
			if (tmp != NULL && _stricmp(tmp->title, title) == 0) {
				break;
			}
			else {
				tmp = tmp->next;
				if (tmp == NULL) {
					printf("책 정보가 존재하지 않습니다\n");
					break; //사용자가 입력한 책 제목이 없으므로 책 제목을 다시 입력함
				}
			}
		}

		if (tmp != NULL && _stricmp(tmp->title, title) == 0) //사용자가 입력한 책 제목이 같을 때 전체 반복문 탈출
			break;
		else
			continue;
	}

	while (1) {

		printf("Enter the price : ");
		scanf("%s", price);

		ex = strchr(price, '.'); //문자열로 받고 실수를 구분하기 위해 .을 찾는다

		if (atof(price) <= 0 || ex == NULL || strlen(ex) != 3) { //실수로 바꿨을때 음수이거나 정수이거나 소수점둘째자리가 아니면 반복한다
			continue;
		}
		else
			break;
	}
	

	printf("Price will be updated from %s to %s\n", theInventory[num].link->price, price);

	sprintf(tmpprice, "%s", price); //수정한 가격을 저장
	strcpy(tmp->price, tmpprice);

	return;
}

void changeQty(author* theInventory) {

	char* ex; // . 구분하기 위한 변수
	int a = 0; //작가의 수
	char firstName[20] = { 0, }; //작가의 firstName을 받는다
	char lastName[20] = { 0, };  //작가의 lastName을 받는다
	char buf[100] = { 0, }; //사용자가 입력한 작가의 이름을 합치기 위한 변수
	int num = 0; //작가가 존재하는 배열의 번호
	char title[200] = { 0, }; //책 제목을 입력 받는 변수
	char tmpqty[100]; //재고 임시 저장 변수
	char qty[10]; //책 재고
	book * tmp = NULL; //사용자가 입력한 책 제목을 비교할때 원문을 바꾸지 않기 위해서

	while (1) { //작가가 몇 명인지 세기위한 반복문
		while (theInventory[a].link != NULL) {
			a++;
		}
		break;
	}
	a--; //작가의 수를 정확하게 맞춰주기 위해 마지막에 하나 감소

	while (1) { //작가의 이름을 잘못 입력했을때의 예외처리

		memset(buf, 0, strlen(buf)); // 작가의 이름을 잘못 입력했을 때 초기화하고 새로 받는다
		memset(lastName, 0, strlen(lastName)); // 작가의 이름을 잘못 입력했을 때 초기화하고 새로 받는다
		memset(firstName, 0, strlen(firstName)); // 작가의 이름을 잘못 입력했을 때 초기화하고 새로 받는다
		num = 0; // 작가의 이름을 잘못 입력했을 때 초기화하고 새로 받는다

		printf("Enter the author's firstname : ");
		scanf("%s", &firstName);

		printf("Enter the author's lastname : ");
		scanf("%s", &lastName);

		sprintf(buf, "%s,%s", lastName, firstName); //사용자가 입력한 작가의 이름을 하나로 합쳐준다

		while (1) { //사용자가 찾는 작가가 있을때 이 반복문과 전체 반복문을 탈출한다
			if (_stricmp(buf, theInventory[num].name) == 0) //사용자가 입력한 작가의 이름이 있을때 이 반복문을 탈출한다
				break;
			else { //배열에 있는 저장된 작가를 모두 비교하기 위해 배열값을 하나 올려준다
				num++;
			}

			if (num > a) { //사용자가 입력한 작가의 이름이 없을 때
				printf("작가의 정보가 존재하지 않습니다\n");
				break;
			}
		}

		if (_stricmp(buf, theInventory[num].name) == 0)
			break; //작가 이름 입력받는 전체 반복문 탈출
		else
			continue;
	}

	while (getchar() != '\n'); //문자열 오류 방지

	while (1) { //책의 제목을 저장하기 위한 반복문

		memset(title, 0, strlen(title)); //사용자가 책 제목을 잘못 입력했을 때 다시 받아야된다
		tmp = NULL; //사용자가 책 제목을 잘못 입력했을 때 다시 받아야된다

		printf("Enter the title : ");
		fgets(title, 200, stdin); //책의 제목을 띄어쓰기도 받기위해 fgets사용
		title[strlen(title) - 1] = 0; //책 제목의 배열 사이즈를 맞춰준다

		tmp = theInventory[num].link; //직접 가리키면 본문을 옮기게 되므로 tmp사용

		while (1) { //사용자가 입력한 책 제목이 존재하면 가격을 바꾸기 위해 반복문 탈출
			if (tmp != NULL && _stricmp(tmp->title, title) == 0) {
				break;
			}
			else {
				tmp = tmp->next;
				if (tmp == NULL) {
					printf("책 정보가 존재하지 않습니다\n");
					break; //사용자가 입력한 책 제목이 없으므로 책 제목을 다시 입력함
				}
			}
		}

		if (tmp != NULL && _stricmp(tmp->title, title) == 0) //사용자가 입력한 책 제목이 같을 때 전체 반복문 탈출
			break;
		else
			continue;
	}

	while (1) { //재고를 받을때 예외처리를 위한 반복문
		
		printf("Enter the qty : ");
		scanf("%s", qty);

		ex = strchr(qty, '.'); //문자열로 받고 실수를 구분하기 위해 .을 찾는다

		if (atoi(qty) > 0 && ex == NULL) { //정수로 바꿨을때 양수이거나 .이 없다 즉, 실수가 아닐때 탈출한다
			break;
		}
		else {
			continue;
		}
	}

	printf("Price will be updated from %s to %s\n", theInventory[num].link->qty, qty);

	sprintf(tmpqty, "%s", qty); //수정한 재고를 저장
	strcpy(tmp->qty, tmpqty);

	return;
}

void totalQty(author* theInventory) {

	int a = 0; //작가의 수
	int total = 0; //재고의 총 합
	book* tmp; //재고를 가리키기 위한 포인터

	while (1) { //작가가 몇 명인지 세기위한 반복문
		while (theInventory[a].link != NULL) {
			a++;
		}
		break;
	}

	for (int i = 0; i <= a; i++) { //작가의 수만큼 반복한다
		tmp = theInventory[i].link;
		while (tmp != NULL) {
			total = total + atoi(tmp->qty); //재고를 더해준다
			tmp = tmp->next; //다음 링크를 가리킨다
		}
	}

	printf("The total number of book is %d\n", total);

	return;
}

void calculateTotalAmount(author* theInventory) {

	int a = 0; //작가의 수
	double total = 0; //가격의 총합
	book* tmp; //가격을 가리키기 위한 포인터

	while (1) { //작가가 몇 명인지 세기위한 반복문
		while (theInventory[a].link != NULL) {
			a++;
		}
		break;
	}

	for (int i = 0; i <= a; i++) { //작가의 수 만큼 반복한다
		tmp = theInventory[i].link;
		while (tmp != NULL) {
			total = total + (atof(tmp->price)); //가격을 더한다
			tmp = tmp->next; //다음 링크를 가리킨다
		}
	}

	printf("The total value of the inventory is $%.2lf\n", total);

	return;
}