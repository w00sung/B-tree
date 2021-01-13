#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "bptree.h"


int main()
{
	Node* root = createNode();
	root->N = 0;
	root->isLeaf = true;

	//printf("������ �Է��ϼ��� : ");
	//scanf("%d", DEGREE);
	//MAX_DEGREE = (int)((DEGREE + 1) / 2);
	//MIN_DEGREE = DEGREE - 1;


	//while (1)
	//{
	//	int input=0;
	//	int val = 0;
	//	int flag = 0;
	//	int isSearch = 0;
	//	printf("\n1.��ȸ\t2/����\t3.����\t4.���\t5.���� :");
	//	scanf("%d", &input);

	//	switch (input) {
	//	case 1:
	//		printf("���� �Է��ϼ��� : ");
	//		scanf("%d", &val);
	//		isSearch = searchNode(root, val);
	//		if (isSearch)
	//			printf("���� �����մϴ� !! ����");
	//		else
	//			printf("���� �������� �ʽ��ϴ�. �Ф�");
	//		break;
	//	case 2:
	//		printf("���� �Է��ϼ��� : ");
	//		scanf("%d", &val);
	//		insertTree(&root, val);
	//		break;
	//	case 3:
	//		printf("���� �Է��ϼ��� : ");
	//		
	//		/*deleteTree(&root, val);*/
	//		scanf("%d", &val);
	//		break;
	//	case 4:
	//		printAll(root, 0);
	//		break;
	//	case 5:
	//		flag = 1;
	//		break;
	//	default:
	//		printf("�ν��� �� ���� ���Դϴ�.");
	//		break;
	//	}
	//	if (flag)
	//		break;
	//}

	/* Samsung Note ���� */
	//insertTree(&root, 10);
	//insertTree(&root, 20);
	//insertTree(&root, 30);
	//insertTree(&root, 40);
	//insertTree(&root, 50);
	//insertTree(&root, 60);
	//insertTree(&root, 70);
	//insertTree(&root, 80);
	//insertTree(&root, 0);
	//insertTree(&root, 15);
	//insertTree(&root, 5);
	//insertTree(&root, 7);
	//insertTree(&root, 45);
	//insertTree(&root, 35);
	//insertTree(&root, 32);
	//insertTree(&root, 31);
	//insertTree(&root, 100);
	//insertTree(&root, 110);
	//insertTree(&root, 120);
	//insertTree(&root, 130);
	//insertTree(&root, 140);
	//insertTree(&root, 150);
	//insertTree(&root, 160);
	//insertTree(&root, 170);
	//deleteTree(&root, 140);

	int val = 0;
	int flag = 0;
	for (int i = 0; i < 1000; i++)
	{
		val = rand();
		val %= 1000;
		flag = searchNode(root, val);
		if (flag)
			continue;
		insertTree(&root, val);
		//printf("%d %d\n", i,val);
	}

	for (int i = 0; i < 500; i++)
	{
		val = rand();
		val %= 1000;
		flag = searchNode(root, val);
		if (flag == 0)
			continue;

		
		printAll(root, 0);
		deleteTree(&root, val);
		//printf("%d %d\n", i, val);

	}


	//printAll(root, 0);

	/* ���� ���� */

	/* root ����� */
	//insertTree(&root, 10);
	//insertTree(&root, 20);
	//insertTree(&root, 30);
	//insertTree(&root, 50);
	//insertTree(&root, 60);
	//insertTree(&root, 70);
	//deleteTree(&root, 70);
	//deleteTree(&root, 60);

	//deleteTree(&root, 20);








	return 0;
}
