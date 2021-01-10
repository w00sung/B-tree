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

// 노드 초기화, 노드 탐색, 값 삽입 - (트리 기준, non-full), 자녀 분리
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

// 빈 노드 만들기
Node* createNode()
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	//int min_degree = ceil(DEGREE/2);
	// 주소를 담고 있는 녀석들을 배열화 할 것이기 때문에 이중포인터
	// ex_ int 배열을 담기 위해서는 int *을 사용한다.
	Node** children = (Node**)malloc((DEGREE + 1) * sizeof(Node*));
	int* key = (int*)malloc(DEGREE * sizeof(int));

	newNode->C = children;	
	newNode->Key = key;


	return newNode;
}

// **** return 값 변경 필요 *****
Node* searchNode(Node* root, int k)
{
	int i = 0;
	while ((i < (root->N)) && (k > root->Key[i]))
	{
		i += 1;
	}
	// 찾았으면?
	if ((i < root->N) && (k = root->Key[i]))
	{
		return(root, i);
	}
	// 몿찾았고, 리프야
	else if (root->isLeaf)
	{
		// 못찾으면 NULL
		return NULL;
	}
	// 못찾았고, 리프 아니야
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
		// 루트가 될 노드 생성
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
		// 왼쪽이 뚱뚱해짐
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
	// 자식 올라갈 녀석 자리 마련
	for (int i = parent->N; i >= idx+1 ; i--)
	{
		parent->C[i + 1] = parent->C[i];
	}
	parent->C[idx+1] = right;
	// 키 올라갈 녀석 자리 마련
	for (int i = parent->N - 1; i >= idx ; i--)
	{
		parent->Key[i + 1] = parent->Key[i];
	}
	// 부모에 키 삽입
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
		// 내가 들어갈 공간 위에 서있어
		num++;

		// 내가 들어갈 자녀들이 가득 찼으면
		if (root->C[num]->N == max_degree)
		{
			splitChild(root, num);
			// split 후 root에 값이 추가되니까 내가 어디로 들어갈 지 다시 확인
			if (k > root->Key[num])
				num++;
		}
		insertNonfull(root->C[num], k);
	}
}