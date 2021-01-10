#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define DEGREE 4


typedef struct _NODE {
	struct _NODE** C;
	int* Key;
	int N;
	bool isLeaf;
}Node;

typedef struct _TREE {
	struct _NODE* root;

}Tree;

// ��� �ʱ�ȭ, ��� Ž��, �� ���� - (Ʈ�� ����, non-full), �ڳ� �и�
Node* createNode();

Node* searchNode(Node* root, int k);
void insertTree(Node** root, int k);
void insertNonfull(Node* root, int k);
void splitChild(Node* parent, int idx);



int main()
{
	Node* root = createNode();
	root->N = 0;
	root->isLeaf = true;

	insertTree(&root, 10);
	insertTree(&root, 200);
	insertTree(&root, 300);
	insertTree(&root, 400);
	insertTree(&root, 500);
	insertTree(&root, 0);
	insertTree(&root, 450);
	printf("450 : %d\n", root->C[2]->Key[0]);
	insertTree(&root, 600);
	printf("600 : %d\n", (root->C[2]->Key[2]));
	insertTree(&root, 700);
	printf("300 : %d\n", root->C[1]->Key[0]);
	printf("400 : %d\n", root->Key[1]);
	printf("450 : %d\n", root->C[2]->Key[0]);
	printf("500 : %d\n", (root->Key[2]));
	printf("600 : %d\n", (root->C[3]->Key[0]));
	printf("700 : %d\n", (root->C[3]->Key[1]));
	insertTree(&root, 800);
	printf("800 : %d\n", (root->C[1]->C[1]->Key[2]));
	insertTree(&root, 900);
	printf("400 : %d\n", root->Key[0]);
	printf("900 : %d\n", root->C[1]->C[2]->Key[1]);





	return 0;
}

// �� ��� �����
Node* createNode()
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	//int min_degree = ceil(DEGREE/2);
	// �ּҸ� ��� �ִ� �༮���� �迭ȭ �� ���̱� ������ ����������
	// ex_ int �迭�� ��� ���ؼ��� int *�� ����Ѵ�.
	Node** children = (Node**)malloc((DEGREE + 1) * sizeof(Node*));
	int* key = (int*)malloc(DEGREE * sizeof(int));

	newNode->C = children;	
	newNode->Key = key;


	return newNode;
}

// **** return �� ���� �ʿ� *****
Node* searchNode(Node* root, int k)
{
	int i = 0;
	while ((i < (root->N)) && (k > root->Key[i]))
	{
		i += 1;
	}
	// ã������?
	if ((i < root->N) && (k = root->Key[i]))
	{
		return(root, i);
	}
	// ��ã�Ұ�, ������
	else if (root->isLeaf)
	{
		// ��ã���� NULL
		return NULL;
	}
	// ��ã�Ұ�, ���� �ƴϾ�
	else 
	{
		return searchNode(root->C[i], k);
	}
}


void insertTree(Node** root, int k)
{
	int max_degree = (int)2*ceil(DEGREE/2) - 1;
	Node* tmp = *root;
	if (((*root)->N == max_degree))
	{
		// ��Ʈ�� �� ��� ����
		Node* to_be_root = createNode();
		*root = to_be_root;
		to_be_root->isLeaf = false;
		to_be_root->N = 0;
		to_be_root->C[0] = tmp;
		splitChild(to_be_root, 0);
		insertNonfull(to_be_root, k);
	}
	else
	{
		insertNonfull(*root, k);
	}
}

void splitChild(Node* parent, int idx)
{
	int min_degree = (int)ceil(DEGREE / 2);
	Node* right = createNode();
	Node* left = parent->C[idx];
	right->isLeaf = left->isLeaf;
	right->N = min_degree-1;
	for (int i = 0; i < min_degree-1; i++)
	{
		// ������ �׶�����
		right->Key[i] = left->Key[i + min_degree];
	}
	if (!left->isLeaf)
	{
		for (int i = 0; i < min_degree; i++)
		{
			right->C[i] = left->C[i + min_degree];
		}
	}
	left->N = min_degree-1;
	// �ڽ� �ö� �༮ �ڸ� ����
	for (int i = parent->N; i >= idx+1 ; i--)
	{
		parent->C[i + 1] = parent->C[i];
	}
	parent->C[idx+1] = right;
	// Ű �ö� �༮ �ڸ� ����
	for (int i = parent->N - 1; i >= idx ; i--)
	{
		parent->Key[i + 1] = parent->Key[i];
	}
	// �θ� Ű ����
	parent->Key[idx] = left->Key[min_degree-1];
	parent->N++;
}

void insertNonfull(Node* root, int k)
{
	int max_degree = (int)2*ceil(DEGREE/2)-1;
	int num = (root->N) - 1;
	if (root->isLeaf)
	{
		while ((num >= 0) && (k < root->Key[num]))
		{
			root->Key[num + 1] = root->Key[num];
			num--;
		}
		root->Key[num + 1] = k;
		root->N = (root->N)+1;
	}
	else
	{
		while ((num >= 0) && (k < root->Key[num]))
		{
			num--;
		}
		// ���� �� ���� ���� ���־�
		num++;

		// ���� �� �ڳ���� ���� á����
		if (root->C[num]->N == max_degree)
		{
			splitChild(root, num);
			// split �� root�� ���� �߰��Ǵϱ� ���� ���� �� �� �ٽ� Ȯ��
			if (k > root->Key[num])
				num++;
		}
		insertNonfull(root->C[num], k);
	}
}