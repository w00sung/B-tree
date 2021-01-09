#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define degree 4.0f


typedef struct _NODE {
	struct _NODE* C;
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
Node* insertTree(Tree tree);
Node* insertNonfull(Node* root, int k);
void splitChild(Node* parent, int idx);



int main()
{

	return 0;
}

Node* createNode()
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	int min_degree = ceil(degree/2);
	// �ּҸ� ��� �ִ� �༮���� �迭ȭ �� ���̱� ������ ����������
	// ex_ int �迭�� ��� ���ؼ��� int *�� ����Ѵ�.
	Node** children = malloc(sizeof(Node*) * min_degree);
	int* key = malloc(sizeof(int) * degree);
	newNode->C = children;
	newNode->Key = key;

}
