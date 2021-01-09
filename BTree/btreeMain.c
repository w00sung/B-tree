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

// 노드 초기화, 노드 탐색, 값 삽입 - (트리 기준, non-full), 자녀 분리
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
	// 주소를 담고 있는 녀석들을 배열화 할 것이기 때문에 이중포인터
	// ex_ int 배열을 담기 위해서는 int *을 사용한다.
	Node** children = malloc(sizeof(Node*) * min_degree);
	int* key = malloc(sizeof(int) * degree);
	newNode->C = children;
	newNode->Key = key;

}
