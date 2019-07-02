#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *link;
}node;			//��� Ÿ�� ����

void makeList(node **);	// ����Ʈ ���� �Լ�. ��������: ��� �������� ������
void viewList(node *);	// ����Ʈ ��� �Լ�
node * findLast(node *);	 /* ����Ʈ ������ ��带 ã�� �Լ��� �� ����� ������ ����
							 �������� : ��� ������ �� */

int findPosition(node *, node **, node **, int);
/* �Է� �����Ϳ� ���� �����͸� �����ϴ� ����� ������ �� �� ���� ����� �����͸� ã�� �Լ�.
��������: ���������, ������� ������, Ÿ�� ������, ã�� ���ϴ� ������ */

void insertList(node **, node *, int);
/* ����Ʈ �����Լ�  ��������: ���� �������� ������, Ÿ�� ������, ���Ե����� */

void deleteList(node **, node *, node *);
/* ����Ʈ �����Լ� ��������: ��� �������� ������, ����������, Ÿ�������� */

/* Ÿ�� �����ʹ� findPosition���� ���ϴ� �������� ��ġ �̸� ���� �����ʹ� �� ����� ���� ����� �������� */

void main() {
	node *head = NULL;
	node *pre = NULL;
	node *targetPtr = NULL;
	int newData, target;
	int found;

	// ��� ����
	makeList(&head);

	// ������ ����Ʈ ���
	viewList(head);

	fflush(stdin);

	// ������ ����
	printf("Enter data to insert :\n");
	scanf("%d", &newData);

	printf("��� ������ �����ұ�� : < ó���� �Է��� ���ϸ� -1 �Է�>\n");
	scanf("%d", &target);

	if (target == -1) {  //���� target�� -1�̸� ���ϴ� �����͸� ó���� �Է��Ѵ�
		targetPtr = NULL;
		insertList(&head, targetPtr, newData);
	}
	else { //���ϴ� �����͸� ���ϴ� ��ġ�� �ֱ����� else��
		found = 0;
		found = findPosition(head, &pre, &targetPtr, target);
		if (found == 1) //findPosition���� 1�� ���ϵǸ� ã�� �����Ͱ� �ִٴ� ���̴�. ��, insertList�Լ��� ���� ���ϴ� ��ġ�� �����͸� �����Ѵ�
			insertList(&head, targetPtr, newData);
		else //findPosition���� 1�� �ƴ� �ٸ� ���� ���ϵǸ� ���ϴ� ��ġ�� �����Ͱ� �������� �ʴ´�.
			printf("There is no %d in the list\n", target);
	}

	viewList(head); //���Ե� �����͸� �����ֱ� ���� �Լ�

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
	/*���� ����� ���� �ƴϸ� ������ ������ ������ �̵�
	���� hptr*/
	node* p;
	p = hptr;

	if (p != NULL)
		while (p->link != NULL) { //p�� �ƴ� p->link�� ���� �ƴҶ����� �ݺ����� ����ϴ� ������ p�� �����Ͱ��� �ƴ϶� p�� ��ũ���� ���� ������ ���̻� ����� �����Ͱ� ���ٴ� ��.
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
	//hptr���� ���� �ƴϰ� hptr->data���� ã�� �����Ͱ� �ƴҵ���
	//	*pre�� = hptr��
	//	hptr�� ���� ���� �̵�

	if (hptr->data == data) {
		*targetPtr = hptr;
		return 1;
	}
	//	���� hptr->data�� data�� ���� ������
	//	*targetPtr�� = hptr
	//	���� 1
	else
	{
		return 0;
	}
	//	�׷��� ������
	//	���� 0
}

void insertList(node **hptr, node *pptr, int data) {
	node* new;
	new = (node*)malloc(sizeof(node));
	new->link = NULL;
	new->data = data;
	//���ο� ��� ����

	if (*hptr == NULL) {
		*hptr = new;
	}
	//	���� *hptr ���� ���̸� ���� empty �̹Ƿ�
	//	*hptr�� new�� ����Ű�� ��

	else if (pptr == NULL) {
		new->link = *hptr;
		*hptr = new;
	}
	//�׷��� �ʰ�
	//���� pptr���� ���̸� ó���� �Է��ؾ� ������
	//���ο� ����Ǹ�ũ, �� new->link�� *hptr������ ��
	//*hptr���� new�� ������ ��.

	else {
		new->link = pptr->link;
		pptr->link = new;
	}
	//�׷��� �ʴٸ�, �� ����Ʈ �߰��� �����ؾ� ������
	//new->link �� ���� pptr�� ��ũ ���̸�
	//pptr->link �� new�� ������ ��
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

	pre = findLast(*hptr); //pre�� �ʱ�hptr�� �ΰ��� �����Ѵ�.

	printf("�Է��� ������ �� <enter -1 to end>\n");
	scanf("%d", &data);

	while (data != -1) { //����ڰ� �Է��ϴ� �����Ͱ� -1�� �ƴ� �̻� ��� �����͸� �����Ѵ�.

		insertList(hptr, pre, data); //insertList�Լ����� �����͸� �ϳ��� �����ϱ� �����Ѵ�
		//����Ʈ ������ ��� ������ Ȯ��
		pre = findLast(*hptr); //findLast�� �̿��Ͽ� ����Ʈ ������ ��� �����Ͱ��� pre�� ����

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