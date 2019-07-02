#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct book { //å�� ����� ���, ������ ������ �ڱ���������ü ����
	char title[50];
	char qty[5];
	char price[10];
	struct book* next;
}book;

typedef struct author { //�۰��� �̸��� �����ϰ� å�� ������ ����Ű�� ����ü ����
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
	greeting(); //���α׷� ����� �ݰ����ϴ� �Լ�

	int flag, choice; //flag�� while���������� �ֱ� ���Ͽ�, choice�� ����ڰ� ���ϴ� �޴� ��ȣ�� ���������� �� ���� �����Ͽ� ���ϴ� �Լ��� ���� ���� �����̴�

	author* theInventory; //readDatabase�Լ����� ���� theInventory�� �����ϱ� ���� ���� ����
	author a[] = { 0, }; // theInventory�� ����ü�� ���ҷ��� ������ �迭�� --> ������ ���� �ʿ��ؼ� a�� ����

	theInventory = readDatabase(&a); //readDatabase�Լ��� a��� �迭�� �ּҸ� ������ ��, �Լ��ȿ��� theInventory�� �۰��� å ���� ������ �����ؼ� ������ ���´� �׸��� theInventory�� ����

	flag = 1; //�޴������� �ݺ����� �����ϱ� ���� ��

	while (flag) { //����ڰ� ���Ḧ ���Ҷ����� �޴��� �ݺ������Ѵ�.

		choice = printMenu(); //����ڰ� ���ϴ� �޴� ��ȣ�� �����ϱ� ���� �Լ�

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

		else if (choice == 8) { //����ڰ� ���Ḧ ���Ҷ� ���α׷��� �����Ѵ�
			printf("Thank you for using this program\n");
			flag = 0; //����ڰ� ���Ḧ ���Ҷ� �޴� ���� �ݺ����� Ż���ϱ� ���� �� ����
		}

		else
			printf("Invalid choice\n");
	}

	free(theInventory);
	return 0;
}

void greeting(void) { //����ڸ� �ݱ�� �Լ�
	printf("Welcome to bookstore program!\n");
}

author* readDatabase(author* theInventory) { //����ü�� ���ҷ��� theInventory�� ������ ���´�. �� �Լ����� theInventory�� ä���� ������
	
	int z = 0; //title[z] å ������ �� ���ھ� �����ϱ� ���� ����
	int k = 0; //stock[k] å ��� �� ���ھ� �����ϱ� ���� ����
	int l = 0; //price[l] å ������ �� ���ھ� �����ϱ� ���� ����
	int r = 0; //authorName[r] �۰� �̸��� �� ���� �����ϱ� ���� ����
	int cnt = 0; // , �� ������ �����ϱ� ���� ���� ����
	int num = 0; // theInventory ���� ���� ��
	char fileName[20]; //����ڰ� ���ϴ� ������ �̸��� �Է¹ޱ� ���� ����
	char title[30] = { 0, }; //å ������ �����ϱ� ���� ����
	char stock[30] = { 0, }; //å�� ��� �����ϱ� ���� ����
	char authorName[30] = { 0, }; //�۰��� �̸��� �����ϱ� ���� ����
	char price[10] = { 0, }; //å�� ������ �����ϱ� ���� ����
	FILE* stream; //������ �ҷ����� ���� ����
	book* bk; //readDatabase�Լ����� theInventory�� �����ϱ� �� �ӽ÷� �����ϱ� ���� ����
	int a = 0; //���� ������ �޾ƿ� line�� �� ���ھ� ������ ���� ����
	char firstName[20] = { 0, }; //�۰��� firstName
	char lastName[20] = { 0, }; //�۰��� lastName
	int c = 0; //����ڰ� �Է��� �۰��� �̹� �����ϴ��� �����ϱ� ���� ����

	while (1) { //����ڰ� ������ �Է��� �߸����� �� �ٽ� �Է��ϰ� �ϱ� ���� �ݺ����̴�
		printf("Enter the name of the file : ");
		scanf(" %s", &fileName);

		stream = fopen(fileName, "r"); //������ �б� �������� �ҷ��´�

		if (stream != NULL) //����ڰ� ���� �̸��� ��Ȯ�ϰ� �Է������� �� �ݺ����� Ż���ϰ� ���� �ܰ�� �Ѿ��
			break;

		else if (stream == NULL) //����ڰ� ���� �̸��� �߸� �Է������� �߸���ٴ� �޽����� ���̰� �ٽ� �Է��ϰ� �Ѵ�
			printf("Error reading database\n");
	}

	theInventory = (author*)malloc(sizeof(author) * 100); //theInventory�� �����Ҵ� �ޱ� ���� ����
	char * line = (char*)malloc(sizeof(char) * 100); //������ å ������ ���� ������ �޾ƿ��� ���� �����Ҵ�

	while (!feof(stream)) {//������ �� �޾ƿö����� �ݺ��Ѵ�

		fgets(line, 100, stream); //line�� å ������ ���� ������ �޾ƿ´�

		k = 0, l = 0, z = 0, a = 0, r = 0, cnt = 0;   //�ݺ��� ���� �ʱ�ȭ

		memset(authorName, 0, strlen(authorName)); // �۰��� �̸��� ���� �ޱ� ���� �ʱ�ȭ
		memset(title, 0, strlen(title)); //å ������ ���� �ޱ� ���� �ʱ�ȭ
		memset(price, 0, strlen(price)); //å ������ ���� �ޱ� ���� �ʱ�ȭ
		memset(stock, 0, strlen(stock)); //å ��� ���� �ޱ� ���� �ʱ�ȭ

		while (1) { // ,�� 0�� �Ǵ� 1�� ���� ��� 

			if (cnt == 2) { //�ι�° �޸��� ���������� å ������ �Ѿ��
				a++; // , �� �����ϰ� å ������ �����ϱ� ���� �ϳ� �Ѿ��
				break;
			}

			authorName[r++] = line[a++]; // ���� �̸��� ���ļ� authorName�� ����

			if (line[a] == ',') { // , �� �������� cnt������ �ϳ� ���ؼ� ����
				cnt++;
			}
		}

		while (1) { // å ������ �����ϰ� ����° , �� ������ ���� �Ѿ��

			if (cnt == 3)
				break;

			title[z++] = line[a++];

			if (line[a] == ',') { // , �� �������� cnt������ �ϳ� ���ؼ� ����
				cnt++;
				a++;
			}
		}

		while (1) { // å ��� �����ϰ� �׹�° , �� ������ �������� �Ѿ��

			stock[k++] = line[a++];

			if (line[a] == ',') { // , �� �������� cnt������ �ϳ� ���ؼ� ����
				cnt++;
				a++;
			}

			if (cnt == 4)
				break;
		}

		while (1) { //������ �����ϰ� �ٹٲ��϶��� �ݺ��� Ż��

			price[l++] = line[a++];

			if (line[a] == 10)
				break;
		}

		bk = (book *)malloc(sizeof(book) * 100); // �ӽ÷� å ���� ������ �����ϱ� ���ؼ� readDatabase�Լ����� ������ ����ü ������ �����Ҵ� �޴´�
		strcpy(bk->title, title); //bk->title�� å ������ �����Ѵ�
		strcpy(bk->qty, stock); //bk->qty�� å ��� �����Ѵ�
		strcpy(bk->price, price); //bk->price�� å ������ �����Ѵ�
		bk->next = NULL; //bk->next�� ����Ű�� ��ũ�� ���̴�
		c = 0; //�ٹٲ��� �� ������ �۰��� �̸��� ������ Ȯ���ϱ� ���� ����

		for (int b = 0; b < num; b++) { //b�� 0����, ����� �۰��� ������ �۰��� �̸��� ������ ���ϱ� ���� for��
			if (strcmp(theInventory[b].name, authorName) == 0) {
				c = 1; //���࿡ �۰��̸��� ���ٸ� c=1�� �����Ͽ� �۰� �̸��� ���ٴ°� ǥ��
				bk->next = theInventory[b].link; //bk����ü�� ���� ��忡 ���� �۰� �迭 ��ũ�� ����
				theInventory[b].link = bk; //���� �۰� �迭 ��ũ�� å ������ �ִ´�
				break; //�۰��̸��� ���� ��� ����Ʈ�� �����߱� ������ ���� �����ִ� �񱳸� �� �ʿ䰡 ��� for�� Ż��
			}
		}

		if (c == 0) { //���� �۰��� �̸��� �ٸ��ٸ� ���ο� �迭�� �۰��� �̸��� ������ �����Ѵ�.
			theInventory[num].link = NULL; //�۰� �迭 ó�� ��ũ�� NULL���� �־��ش�. �ֳ��ϸ� ���� ��ǰ ������ �������� ���� �� ���̱� �����̴�
			strcpy(theInventory[num].name, authorName); //�迭�� �۰� �̸��� �־��ش�
			theInventory[num++].link = bk; //�۰� �迭�� ����Ű�� ��ũ�� å ������ ����Ű�� �ϰ� ���� �۰��� ������ �ְ� num���� �ϳ� �÷��ش�
		}
	}

	theInventory[num].link = NULL; //������ theInventory���� �ΰ�

	return theInventory; //readDatabase�Լ����� ���� ����ü�� main�Լ��� ������ ������
}

int printMenu(void) { //����ڰ� ���ϴ� �޴� ��ȣ�� �����ϱ� ���� �Լ��̴�

	int a; //��ȣ�� ���� ���� ����

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

		while (getchar() != '\n'); //���ڿ� ���� ����

		printf("Enter your choice : ");
		scanf("%d", &a);

		if (a == 1 || a == 2 || a == 3 || a == 4 || a == 5 || a == 6 || a == 7 || a == 8) { //�޴���ȣ ������ ����ó��
			break;
		}

		else {
			printf("���ϴ� �޴� ��ȣ�� �ٽ� �Է��ϼ���\n");
		}
	}

	return a; //����ڰ� �� �޴� ��ȣ�� ������ ������
}

void displayInventory(author* a) { //å�� ������ ����ڿ��� �����ֱ� ���� �Լ�

	int i = 0; //�۰��� ����� �迭�� ǥ���ϱ� ���� ����

	book * tmp = NULL; //����� ��ũ�� ������ ���� �ٲٴ°� �ƴ϶� �ӽ÷� ����ü�� �����ؼ� ��ũ�� ���� �ȴ�� ����ϱ� ���� ����

	while (1) { //�۰��� ������ �����ֱ� ���� while��

		printf("--------------------------------\n");
		printf("The author is : %s\n", a[i].name); //�۰��� �̸��� ���

		tmp = a[i].link; //�۰��� �̸��� ����� ��ũ�� tmp�� ����Ű�� �Ѵ�

		printf("--------------------------------\n");

		while (tmp != NULL) { //�ش� �۰��� �������� ���
			printf("\tThe title is : %s\n\tThe qty is : %s\n\tThe price is : %s\n", tmp->title, tmp->qty, tmp->price);
			printf("--------------------------------\n");
			tmp = tmp->next;
		}
		i++; //���� �۰��� �Ѿ

		if (a[i].link == NULL) //���� �۰��迭�� NULL�̸� while�� Ż��
			break;
	}
}

void displayAuthorsWork(author* theInventory) {

	int a = 0; //�۰��� ��
	int num = 0; // �۰��� ����� �迭��ȣ�� ��Ÿ���� ���� ���� ����
	char firstName[20] = { 0, }; //����ڰ� �Է��ϴ� firstName
	char lastName[20] = { 0, };  //����ڰ� �Է��ϴ� lastName
	char buf[100] = { 0, };   //����ڰ� ������ �Է��� firstName�� lastName�� ��ġ�� ���� ����
	book * tmp = NULL; //å �������� ����Ҷ� �ӽ÷� ����ü�� �����ؼ� ����� ��ũ��� ����Ѵ�
	int count = 0; //����� ����Ʈ�� ����
	book * temp; //������ �ϱ����� ����ü ����
	int i, j; //������ �ϱ����� ����

	while (1) { //�۰��� �� ������ �������� �ݺ���
		while (theInventory[a].link != NULL) {
			a++;
		}
		break;
	}
	a--; //�۰��� ���� ��Ȯ�ϰ� �����ֱ� ���� �������� �ϳ� ����

	while (1) { //�۰��� �̸��� �߸� �Է��������� ����ó��

		memset(buf, 0, strlen(buf)); // �۰��� �̸��� �߸� �Է����� �� �ʱ�ȭ�ϰ� ���� �޴´�
		memset(lastName, 0, strlen(lastName)); // �۰��� �̸��� �߸� �Է����� �� �ʱ�ȭ�ϰ� ���� �޴´�
		memset(firstName, 0, strlen(firstName)); // �۰��� �̸��� �߸� �Է����� �� �ʱ�ȭ�ϰ� ���� �޴´�
		num = 0; // �۰��� �̸��� �߸� �Է����� �� �ʱ�ȭ�ϰ� ���� �޴´�

		printf("Enter the author's firstname : ");
		scanf("%s", &firstName);

		printf("Enter the author's lastname : ");
		scanf("%s", &lastName);

		sprintf(buf, "%s,%s", lastName, firstName); //����ڰ� �Է��� �۰��� �̸��� �ϳ��� �����ش�

		while (1) { //����ڰ� ã�� �۰��� ������ �� �ݺ����� ��ü �ݺ����� Ż���Ѵ�
			if (_stricmp(buf, theInventory[num].name) == 0) //����ڰ� �Է��� �۰��� �̸��� ������ �� �ݺ����� Ż���Ѵ�
				break;
			else { //�迭�� �ִ� ����� �۰��� ��� ���ϱ� ���� �迭���� �ϳ� �÷��ش�
				num++;
			}

			if (num > a) { //����ڰ� �Է��� �۰��� �̸��� ���� ��
				printf("�۰��� ������ �������� �ʽ��ϴ�\n");
				break;
			}
		}

		if (_stricmp(buf, theInventory[num].name) == 0)
			break; //�۰� �̸� �Է¹޴� ��ü �ݺ��� Ż��
	}

	tmp = theInventory[num].link; //�ش� �۰��� ����� å �������� ���� �ٲٴ°� �ƴ϶� �ӽ÷� ��� ���ֱ� ���� ����
								  //num�� ���� �ݺ������� ����ڰ� �Է��� �ش� �۰��̹Ƿ� �迭��ȣ�� �����´�
	while (tmp != NULL) { //����� ����Ʈ�� ������ �ľ��Ѵ�
		count++;
		tmp = tmp->next;
	}

	book ** tmpbook = (book **)malloc(sizeof(book*) * count); //������ �ϱ� ���� �����Ҵ�

	tmp = theInventory[num].link;

	for (a = 0; a < count; a++) { //����� ����Ʈ�� ����ŭ tmp�� ����
		tmpbook[a] = tmp;
		tmp = tmp->next;
	}

	for (i = 0; i<count - 1; i++)//��Ƚ���� �����Ͱ���-1, �ڱ� �ڽŰ��� �� ���� ���� 
	{
		for (j = 0; j<count - 1; j++)
		{
			if (strcmp(tmpbook[j]->title, tmpbook[j + 1]->title) > 0)
			{
				temp = tmpbook[j];//���ڸ��� ���� �� ũ�� ��ü 
				tmpbook[j] = tmpbook[j + 1];
				tmpbook[j + 1] = temp;
			}
		}
	}

	for (i = 0; i<count; i++) { //�ش� �۰��� �������� ���
		printf("--------------------------------\n");
		printf("\tThe title is : %s\n\tThe qty is : %s\n\tThe price is : %s\n", tmpbook[i]->title, tmpbook[i]->qty, tmpbook[i]->price);
		printf("--------------------------------\n");
	}

	return;
}

author* addBook(author* theInventory) {

	char firstName[20] = { 0, }; //�۰��� firstName�� �޴´�
	char lastName[20] = { 0, };  //�۰��� lastName�� �޴´�
	char buf[100] = { 0, }; //����ڰ� �Է��� �۰��� �̸��� ��ġ�� ���� ����
	int num = 0; //�۰��� �����ϴ� �迭�� ��ȣ
	char title[200] = { 0, }; //å ������ �Է� �޴� ����
	char qty[10]; //å ��� �Է� �޴� ����
	char price[100]; //å ������ �Է¹޴� ����
	char buf2[100] = { 0, }; //å�� qty�� price�� �Է¹޴� ����
	int state = 0; //����ڰ� �Է��� �۰��� ���� ����
	book * tmp = NULL; //����ڰ� �Է��� å ������ ���Ҷ� ������ �ٲ��� �ʱ� ���ؼ�
	char* ex; // .�� �����ϱ� ���� ����
	char* ex2; // .�� �����ϱ� ���� ����

	book* bk; //å�� ������ ��ũ�� �����Ű�� ���� ����ü ����
	bk = (book *)malloc(sizeof(book) * 100); //å�� ������ �����ϱ� ���� ����ü�� �����Ҵ��� �Ѵ�

	while (1) { //�۰��� �̸��� �߸� �Է��������� ����ó��

		printf("Enter the author's firstname : ");
		scanf("%s", &firstName);

		printf("Enter the author's lastname : ");
		scanf("%s", &lastName);

		sprintf(buf, "%s,%s", lastName, firstName); //�۰��� �̸��� ��ģ��

		while (theInventory[num].link != NULL) { //����ڰ� ã�� �۰��� ���������� �ݺ��Ѵ�
			if (_stricmp(buf, theInventory[num].name) == 0) { //����ڰ� �Է��� �۰��� �̸��� ������ �� �ݺ����� Ż���Ѵ�
				state = 1; // �۰��� �����ϴ� ��� state = 1
				break;
			}

			num++; //���� �۰��� �Ѿ
		}

		break; //�۰� �̸� �Է¹޴� ��ü �ݺ��� Ż��
	}

	while (getchar() != '\n');

	while (1) { //å�� ������ �����ϱ� ���� �ݺ���

		memset(title, 0, strlen(title)); //����ڰ� å ������ �߸� �Է����� �� �ٽ� �޾ƾߵȴ�
		tmp = NULL; //����ڰ� å ������ �߸� �Է����� �� �ٽ� �޾ƾߵȴ�

		printf("Enter the title : ");
		fgets(title, 200, stdin); //�ι�° ������ �� ������
		title[strlen(title) - 1] = 0;

		if (state == 1) { //����ڰ� �Է��� �۰��� ������ ��

			tmp = theInventory[num].link;
			while (1) { //���� ����ڰ� �Է��� å�� �̹� ������ �ٽ� �Է��ϰ� �Ѵ�
				if (tmp != NULL && _stricmp(tmp->title, title) == 0) {
					printf("This book is already in the Inventory and cannot be added again\n");
					break;
				}
				else {
					tmp = tmp->next; //å�� ���� ����Ʈ�� �Ѿ��
					if (tmp == NULL)
						break; //����ڰ� �Է��� å ������ ��ġ�� �����Ƿ� �ݺ��� Ż��
				}
			}
			if (tmp->title == NULL) //��ü �ݺ��� Ż��
				break;
		}

		else if (state == 0) { //�۰� �̸��� ������ å�� ���ο� ������� ����̹Ƿ� å ������ �Է¹ް� �ٷ� ��ü while�� Ż��
			break;
		}
	}

	strcpy(bk->title, title); //�Է¹��� å ������ bk->title�� å ������ �����Ѵ�

	while (1) { //��� ������ ����ó���� ���� �ݺ���

		printf("Enter the qty : ");
		scanf("%s", qty);

		ex2 = strchr(qty, '.'); //���ڿ��� �ް� �Ǽ��� �����ϱ� ���� .�� ã�´�

		if (atoi(qty) > 0 && ex2 == NULL) { //������ �ٲ����� ����̰ų� .�� ���� ��, �Ǽ��� �ƴҶ� Ż���Ѵ�
			break;
		}
		else {
			continue;
		}
	}

	sprintf(buf2, "%s", qty);
	strcpy(bk->qty, buf2); //bk->qty�� qty�� ����

	while (1) {

		printf("Enter the price : ");
		scanf("%s", price);

		ex = strchr(price, '.'); //���ڿ��� �ް� �Ǽ��� �����ϱ� ���� .�� ã�´�

		if (atof(price) <= 0 || ex == NULL || strlen(ex) != 3) { //�Ǽ��� �ٲ����� �����̰ų� �����̰ų� �Ҽ�����°�ڸ��� �ƴϸ� �ݺ��Ѵ�
			continue;
		}
		else
			break;
	}

	sprintf(buf2, "%s", price);
	strcpy(bk->price, buf2); //bk->price�� å ������ ����

	bk->next = NULL; //bk->next�� ����Ű�� ��ũ�� ���̴�

	if (state == 1) {
		bk->next = theInventory[num].link; //bk����ü�� ���� ��忡 ���� �۰� �迭 ��ũ�� ����
		theInventory[num].link = bk; //���� �۰� �迭 ��ũ�� å ������ �ִ´�
	}

	else
	{
		strcpy(theInventory[num].name, buf); //�迭�� �۰� �̸��� �־��ش�
		theInventory[num++].link = bk; //�۰� �迭�� ����Ű�� ��ũ�� å ������ ����Ű�� �ϰ� ���� �۰��� ������ �ְ� num���� �ϳ� �÷��ش�
		theInventory[num].link = NULL; //������ �۰� �迭 ��ũ�� ���� �־��ش�
	}

	return theInventory;
}

void changePrice(author* theInventory) {

	int a = 0; //�۰��� ��
	char firstName[20] = { 0, }; //�۰��� firstName�� �޴´�
	char lastName[20] = { 0, };  //�۰��� lastName�� �޴´�
	char buf[100] = { 0, }; //����ڰ� �Է��� �۰��� �̸��� ��ġ�� ���� ����
	int num = 0; //�۰��� �����ϴ� �迭�� ��ȣ
	char title[200] = { 0, }; //å ������ �Է� �޴� ����
	char tmpprice[100]; //������ �ӽ������ϱ� ���� ����
	char price[100]; //å ������ �Է¹޴� ����
	book * tmp = NULL; //����ڰ� �Է��� å ������ ���Ҷ� ������ �ٲ��� �ʱ� ���ؼ�
	char* ex; // . �����ϱ� ���� ����

	while (1) { //�۰��� �� ������ �������� �ݺ���
		while (theInventory[a].link != NULL) {
			a++;
		}
		break;
	}
	a--; //�۰��� ���� ��Ȯ�ϰ� �����ֱ� ���� �������� �ϳ� ����

	while (1) { //�۰��� �̸��� �߸� �Է��������� ����ó��

		memset(buf, 0, strlen(buf)); // �۰��� �̸��� �߸� �Է����� �� �ʱ�ȭ�ϰ� ���� �޴´�
		memset(lastName, 0, strlen(lastName)); // �۰��� �̸��� �߸� �Է����� �� �ʱ�ȭ�ϰ� ���� �޴´�
		memset(firstName, 0, strlen(firstName)); // �۰��� �̸��� �߸� �Է����� �� �ʱ�ȭ�ϰ� ���� �޴´�
		num = 0; // �۰��� �̸��� �߸� �Է����� �� �ʱ�ȭ�ϰ� ���� �޴´�

		printf("Enter the author's firstname : ");
		scanf("%s", &firstName);

		printf("Enter the author's lastname : ");
		scanf("%s", &lastName);

		sprintf(buf, "%s,%s", lastName, firstName); //����ڰ� �Է��� �۰��� �̸��� �ϳ��� �����ش�

		while (1) { //����ڰ� ã�� �۰��� ������ �� �ݺ����� ��ü �ݺ����� Ż���Ѵ�
			if (_stricmp(buf, theInventory[num].name) == 0) //����ڰ� �Է��� �۰��� �̸��� ������ �� �ݺ����� Ż���Ѵ�
				break;
			else { //�迭�� �ִ� ����� �۰��� ��� ���ϱ� ���� �迭���� �ϳ� �÷��ش�
				num++;
			}

			if (num > a) { //����ڰ� �Է��� �۰��� �̸��� ���� ��
				printf("�۰��� ������ �������� �ʽ��ϴ�\n");
				break;
			}
		}

		if (_stricmp(buf, theInventory[num].name) == 0)
			break; //�۰� �̸� �Է¹޴� ��ü �ݺ��� Ż��
		else
			continue;
	}

	while (getchar() != '\n'); //���ڿ� ���� ����

	while (1) { //å�� ������ �����ϱ� ���� �ݺ���

		memset(title, 0, strlen(title)); //����ڰ� å ������ �߸� �Է����� �� �ٽ� �޾ƾߵȴ�
		tmp = NULL; //����ڰ� å ������ �߸� �Է����� �� �ٽ� �޾ƾߵȴ�

		printf("Enter the title : ");
		fgets(title, 200, stdin);  //å�� ������ ���⵵ �ޱ����� fgets���
		title[strlen(title) - 1] = 0; //å ���� �迭�� ����� �����ش�

		tmp = theInventory[num].link;

		while (1) { //����ڰ� �Է��� å ������ �����ϸ� ������ �ٲٱ� ���� �ݺ��� Ż��
			if (tmp != NULL && _stricmp(tmp->title, title) == 0) {
				break;
			}
			else {
				tmp = tmp->next;
				if (tmp == NULL) {
					printf("å ������ �������� �ʽ��ϴ�\n");
					break; //����ڰ� �Է��� å ������ �����Ƿ� å ������ �ٽ� �Է���
				}
			}
		}

		if (tmp != NULL && _stricmp(tmp->title, title) == 0) //����ڰ� �Է��� å ������ ���� �� ��ü �ݺ��� Ż��
			break;
		else
			continue;
	}

	while (1) {

		printf("Enter the price : ");
		scanf("%s", price);

		ex = strchr(price, '.'); //���ڿ��� �ް� �Ǽ��� �����ϱ� ���� .�� ã�´�

		if (atof(price) <= 0 || ex == NULL || strlen(ex) != 3) { //�Ǽ��� �ٲ����� �����̰ų� �����̰ų� �Ҽ�����°�ڸ��� �ƴϸ� �ݺ��Ѵ�
			continue;
		}
		else
			break;
	}
	

	printf("Price will be updated from %s to %s\n", theInventory[num].link->price, price);

	sprintf(tmpprice, "%s", price); //������ ������ ����
	strcpy(tmp->price, tmpprice);

	return;
}

void changeQty(author* theInventory) {

	char* ex; // . �����ϱ� ���� ����
	int a = 0; //�۰��� ��
	char firstName[20] = { 0, }; //�۰��� firstName�� �޴´�
	char lastName[20] = { 0, };  //�۰��� lastName�� �޴´�
	char buf[100] = { 0, }; //����ڰ� �Է��� �۰��� �̸��� ��ġ�� ���� ����
	int num = 0; //�۰��� �����ϴ� �迭�� ��ȣ
	char title[200] = { 0, }; //å ������ �Է� �޴� ����
	char tmpqty[100]; //��� �ӽ� ���� ����
	char qty[10]; //å ���
	book * tmp = NULL; //����ڰ� �Է��� å ������ ���Ҷ� ������ �ٲ��� �ʱ� ���ؼ�

	while (1) { //�۰��� �� ������ �������� �ݺ���
		while (theInventory[a].link != NULL) {
			a++;
		}
		break;
	}
	a--; //�۰��� ���� ��Ȯ�ϰ� �����ֱ� ���� �������� �ϳ� ����

	while (1) { //�۰��� �̸��� �߸� �Է��������� ����ó��

		memset(buf, 0, strlen(buf)); // �۰��� �̸��� �߸� �Է����� �� �ʱ�ȭ�ϰ� ���� �޴´�
		memset(lastName, 0, strlen(lastName)); // �۰��� �̸��� �߸� �Է����� �� �ʱ�ȭ�ϰ� ���� �޴´�
		memset(firstName, 0, strlen(firstName)); // �۰��� �̸��� �߸� �Է����� �� �ʱ�ȭ�ϰ� ���� �޴´�
		num = 0; // �۰��� �̸��� �߸� �Է����� �� �ʱ�ȭ�ϰ� ���� �޴´�

		printf("Enter the author's firstname : ");
		scanf("%s", &firstName);

		printf("Enter the author's lastname : ");
		scanf("%s", &lastName);

		sprintf(buf, "%s,%s", lastName, firstName); //����ڰ� �Է��� �۰��� �̸��� �ϳ��� �����ش�

		while (1) { //����ڰ� ã�� �۰��� ������ �� �ݺ����� ��ü �ݺ����� Ż���Ѵ�
			if (_stricmp(buf, theInventory[num].name) == 0) //����ڰ� �Է��� �۰��� �̸��� ������ �� �ݺ����� Ż���Ѵ�
				break;
			else { //�迭�� �ִ� ����� �۰��� ��� ���ϱ� ���� �迭���� �ϳ� �÷��ش�
				num++;
			}

			if (num > a) { //����ڰ� �Է��� �۰��� �̸��� ���� ��
				printf("�۰��� ������ �������� �ʽ��ϴ�\n");
				break;
			}
		}

		if (_stricmp(buf, theInventory[num].name) == 0)
			break; //�۰� �̸� �Է¹޴� ��ü �ݺ��� Ż��
		else
			continue;
	}

	while (getchar() != '\n'); //���ڿ� ���� ����

	while (1) { //å�� ������ �����ϱ� ���� �ݺ���

		memset(title, 0, strlen(title)); //����ڰ� å ������ �߸� �Է����� �� �ٽ� �޾ƾߵȴ�
		tmp = NULL; //����ڰ� å ������ �߸� �Է����� �� �ٽ� �޾ƾߵȴ�

		printf("Enter the title : ");
		fgets(title, 200, stdin); //å�� ������ ���⵵ �ޱ����� fgets���
		title[strlen(title) - 1] = 0; //å ������ �迭 ����� �����ش�

		tmp = theInventory[num].link; //���� ����Ű�� ������ �ű�� �ǹǷ� tmp���

		while (1) { //����ڰ� �Է��� å ������ �����ϸ� ������ �ٲٱ� ���� �ݺ��� Ż��
			if (tmp != NULL && _stricmp(tmp->title, title) == 0) {
				break;
			}
			else {
				tmp = tmp->next;
				if (tmp == NULL) {
					printf("å ������ �������� �ʽ��ϴ�\n");
					break; //����ڰ� �Է��� å ������ �����Ƿ� å ������ �ٽ� �Է���
				}
			}
		}

		if (tmp != NULL && _stricmp(tmp->title, title) == 0) //����ڰ� �Է��� å ������ ���� �� ��ü �ݺ��� Ż��
			break;
		else
			continue;
	}

	while (1) { //��� ������ ����ó���� ���� �ݺ���
		
		printf("Enter the qty : ");
		scanf("%s", qty);

		ex = strchr(qty, '.'); //���ڿ��� �ް� �Ǽ��� �����ϱ� ���� .�� ã�´�

		if (atoi(qty) > 0 && ex == NULL) { //������ �ٲ����� ����̰ų� .�� ���� ��, �Ǽ��� �ƴҶ� Ż���Ѵ�
			break;
		}
		else {
			continue;
		}
	}

	printf("Price will be updated from %s to %s\n", theInventory[num].link->qty, qty);

	sprintf(tmpqty, "%s", qty); //������ ��� ����
	strcpy(tmp->qty, tmpqty);

	return;
}

void totalQty(author* theInventory) {

	int a = 0; //�۰��� ��
	int total = 0; //����� �� ��
	book* tmp; //��� ����Ű�� ���� ������

	while (1) { //�۰��� �� ������ �������� �ݺ���
		while (theInventory[a].link != NULL) {
			a++;
		}
		break;
	}

	for (int i = 0; i <= a; i++) { //�۰��� ����ŭ �ݺ��Ѵ�
		tmp = theInventory[i].link;
		while (tmp != NULL) {
			total = total + atoi(tmp->qty); //��� �����ش�
			tmp = tmp->next; //���� ��ũ�� ����Ų��
		}
	}

	printf("The total number of book is %d\n", total);

	return;
}

void calculateTotalAmount(author* theInventory) {

	int a = 0; //�۰��� ��
	double total = 0; //������ ����
	book* tmp; //������ ����Ű�� ���� ������

	while (1) { //�۰��� �� ������ �������� �ݺ���
		while (theInventory[a].link != NULL) {
			a++;
		}
		break;
	}

	for (int i = 0; i <= a; i++) { //�۰��� �� ��ŭ �ݺ��Ѵ�
		tmp = theInventory[i].link;
		while (tmp != NULL) {
			total = total + (atof(tmp->price)); //������ ���Ѵ�
			tmp = tmp->next; //���� ��ũ�� ����Ų��
		}
	}

	printf("The total value of the inventory is $%.2lf\n", total);

	return;
}