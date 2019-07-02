#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *link;
}node;			//노드 타입 정의

void makeList(node **);	// 리스트 생성 함수. 전달인자: 헤더 포인터의 포인터
void viewList(node *);	// 리스트 출력 함수
node * findLast(node *);	 /* 리스트 마지막 노드를 찾는 함수로 그 노드의 포인터 리턴
							 전달인자 : 헤더 포인터 값 */

int findPosition(node *, node **, node **, int);
/* 입력 데이터와 같은 데이터를 포함하는 노드의 포인터 및 그 이전 노드의 포인터를 찾는 함수.
전달인자: 헤더포인터, 이전노드 포인터, 타깃 포인터, 찾기 원하는 데이터 */

void insertList(node **, node *, int);
/* 리스트 삽입함수  전달인자: 헤터 포인터의 포인터, 타깃 포인터, 삽입데이터 */

void deleteList(node **, node *, node *);
/* 리스트 삭제함수 전달인자: 헤더 포인터의 포인터, 이전포인터, 타깃포인터 */

/* 타깃 포인터는 findPosition에서 원하는 데이터의 위치 이며 이전 포인터는 그 노드의 이전 노드의 포인터임 */

void main() {
	node *head = NULL;
	node *pre = NULL;
	node *targetPtr = NULL;
	int newData, target;
	int found;

	// 노드 생성
	makeList(&head);

	// 생성된 리스트 출력
	viewList(head);

	fflush(stdin);

	// 데이터 삽입
	printf("Enter data to insert :\n");
	scanf("%d", &newData);

	printf("어디 다음에 삽입할까요 : < 처음에 입력을 원하면 -1 입력>\n");
	scanf("%d", &target);

	if (target == -1) {  //만약 target이 -1이면 원하는 데이터를 처음에 입력한다
		targetPtr = NULL;
		insertList(&head, targetPtr, newData);
	}
	else { //원하는 데이터를 원하는 위치에 넣기위한 else문
		found = 0;
		found = findPosition(head, &pre, &targetPtr, target);
		if (found == 1) //findPosition에서 1이 리턴되면 찾는 데이터가 있다는 뜻이다. 즉, insertList함수로 들어가서 원하는 위치에 데이터를 삽입한다
			insertList(&head, targetPtr, newData);
		else //findPosition에서 1이 아닌 다른 수가 리턴되면 원하는 위치에 데이터가 존재하지 않는다.
			printf("There is no %d in the list\n", target);
	}

	viewList(head); //삽입된 데이터를 보여주기 위한 함수

	// delete list
	printf("Enter data to delete from list\n");
	scanf("%d", &target);

	printf("targeted data is %d\n", target);

	found = 0;
	found = findPosition(head, &pre, &targetPtr, target);

	printf("data is %d in the list\n", found);

	printf("found data is %d\n", targetPtr->data);
	if (found == 1)
		deleteList(&head, pre, targetPtr);
	else
		printf("There is no %d in the list\n", target);

	// View list data
	viewList(head);
}

node * findLast(node* hptr) {
	/*만약 헤더가 널이 아니면 마지막 노드까지 포인터 이동
	리턴 hptr*/
	node* p;
	p = hptr;

	if (p != NULL)
		while (p->link != NULL) { //p가 아닌 p->link가 널이 아닐때까지 반복문을 사용하는 이유는 p의 데이터값이 아니라 p의 링크값이 널이 나오면 더이상 연결된 데이터가 없다는 뜻.
			p = p->link;
		}

	return p;
}

int findPosition(node *hptr, node ** pre, node **targetPtr, int data) {

	*pre = NULL;
	*targetPtr = NULL;

	while (hptr != NULL && hptr->data != data) {
		*pre = hptr;
		hptr = hptr->link;
	}
	//hptr값이 널이 아니고 hptr->data값이 찾는 데이터가 아닐동안
	//	*pre값 = hptr값
	//	hptr은 다음 노드로 이동

	if (hptr->data == data) {
		*targetPtr = hptr;
		return 1;
	}
	//	만약 hptr->data와 data의 값이 같으면
	//	*targetPtr값 = hptr
	//	리턴 1
	else
	{
		return 0;
	}
	//	그렇지 않으면
	//	리턴 0
}

void insertList(node **hptr, node *pptr, int data) {
	node* new;
	new = (node*)malloc(sizeof(node));
	new->link = NULL;
	new->data = data;
	//새로운 노드 생성

	if (*hptr == NULL) {
		*hptr = new;
	}
	//	만약 *hptr 값이 널이면 현재 empty 이므로
	//	*hptr이 new를 가리키게 함

	else if (pptr == NULL) {
		new->link = *hptr;
		*hptr = new;
	}
	//그렇지 않고
	//만약 pptr값이 널이면 처음에 입력해야 함으로
	//새로운 노드의링크, 즉 new->link는 *hptr값으로 함
	//*hptr값은 new의 값으로 함.

	else {
		new->link = pptr->link;
		pptr->link = new;
	}
	//그렇지 않다면, 즉 리스트 중간에 삽입해야 함으로
	//new->link 의 값은 pptr의 링크 값이며
	//pptr->link 는 new의 값으로 함
	//return new->data;
}

void deleteList(node **hptr, node *pre, node *target) {

	if (pre == NULL) {
		*hptr = target->link;
	}
	else {
		pre->link = target->link;
	}
	free(target);
}

void makeList(node **hptr) {
	node *pre = NULL;
	node *new = NULL;
	int data;

	pre = findLast(*hptr); //pre에 초기hptr의 널값을 저장한다.

	printf("입력할 데이터 는 <enter -1 to end>\n");
	scanf("%d", &data);

	while (data != -1) { //사용자가 입력하는 데이터가 -1이 아닌 이상 계속 데이터를 저장한다.

		insertList(hptr, pre, data); //insertList함수에서 데이터를 하나씩 저장하기 시작한다
		//리스트 마지막 노드 포인터 확인
		pre = findLast(*hptr); //findLast를 이용하여 리스트 마지막 노드 포인터값을 pre에 저장

		printf("Enter data again\n");
		scanf("%d", &data);
	}
}

void viewList(node *ptr) {
	while (ptr != NULL) {
		printf("%d ", ptr->data);
		ptr = ptr->link;
	}
	printf("\n");
}