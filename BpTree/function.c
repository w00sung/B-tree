#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "bptree.h"

#define DEGREE 4

int MIN_DEGREE = (int)((DEGREE + 1) / 2);
int MAX_DEGREE = DEGREE - 1;

Node* createNode()
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	// 삽입과정에서 필요하여, 하나씩 더 추가
	Node** children = (Node**)malloc((DEGREE + 2) * sizeof(Node*));
	int* key = (int*)malloc((DEGREE+1) * sizeof(int));

	newNode->C = children;
	newNode->Key = key;


	return newNode;
}

int searchNode(Node* root, int k)
{
	int idx = (root->N);
	while (idx >= 0 && root->Key[idx] > k)
	{
		idx--;
	}
	// 너 리프니?
	if (root->isLeaf)
		idx--;

	// 찾았으면? - 리프가 아닐 때만, N에 서있을 수 있다.
	if ((idx < root->N) && (k = root->Key[idx]))
	{
		return 1;
	}
	// 몿찾았고, 리프야
	else if (root->isLeaf)
	{
		// 못찾으면 NULL
		return 0;
	}
	// 못찾았고, 리프 아니야
	else
	{
		return searchNode(root->C[idx], k);
	}
}


void insertTree(Node** root, int k)
{
	Node* tmp = *root;
	if (((*root)->N == MAX_DEGREE))
	{
		// 루트가 될 노드 생성
		Node* to_be_root = createNode();
		*root = to_be_root;
		to_be_root->isLeaf = false;
		to_be_root->N = 0;
		to_be_root->C[0] = tmp;
		splitChild(to_be_root, 0, k);
		insertNonfull(to_be_root, k);
	}
	else
	{
		insertNonfull(*root, k);
	}
}


void insertNonfull(Node* root, int k)
{
	int num = (root->N) - 1;
	if (root->isLeaf)
	{
		while ((num >= 0) && (k < root->Key[num]))
		{
			root->Key[num + 1] = root->Key[num];
			num--;
		}
		root->Key[num + 1] = k;
		root->N = (root->N) + 1;
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
		if (root->C[num]->N == MAX_DEGREE)
		{
			splitChild(root, num,k);
			// split 후 root에 값이 추가되니까 내가 어디로 들어갈 지 다시 확인
			if (k > root->Key[num])
				num++;
		}
		insertNonfull(root->C[num], k);
	}
}

void splitChild(Node* parent, int idx, int k)
{

	Node* right = createNode();
	Node* left = parent->C[idx];
	right->isLeaf = left->isLeaf;
	//******************개수 설정해줘야함************************
	//right->N = MIN_DEGREE - 1;

	// 리프일때, 부모한테 복사해서 올려줌 (copy up)
	if (parent->isLeaf)
	{

		//k를 어디다 놓을지 확인하고, (left)밀고, 삽입하고, split
		int k_insert_idx = (left->N) ;
		while (k_insert_idx >= 0 && left->Key[k_insert_idx] > k)
		{
			k_insert_idx--;
		}
		for (int i = (left->N)-1; i >= k_insert_idx; i--)
		{
			// k를 넣어줄 수 있게, 값 밀어주기
			left->Key[i + 1] = left->Key[i];
			left->C[i + 2] = left->C[i+1];
		}

		/// 삽입 완료
		left->Key[k_insert_idx] = k;
		int up_idx = (left->N + 1) / 2;

		// 오른쪽에 왼쪽의 뒷값들을 넣어주고
		for (int i = 0; i < MIN_DEGREE; i++)
		{
			// 왼쪽이 뚱뚱해짐
			right->Key[i] = left->Key[i + MIN_DEGREE];
			// 리프와, 내부 노드 모드 C(자녀)들을 갖는다.
		}
		//for (int i = 0; i <= MIN_DEGREE; i++)
		//{
		//	right->C[i] = left->C[i + MIN_DEGREE];
		//}

		// 다음 노드를 가리키게 연결
		right->N = MIN_DEGREE - 1;
		right->C[right->N] = left->C[left->N];

		left->N = MIN_DEGREE - 1;
		left->C[left->N] = right;
		


		//(부모) 밀고, 중간자를 올리고, 자식 연결시키고
		// 자식 올라갈 녀석 자리 마련
		// idx N 이면, parent-> N : N-1, idx : N 이라서 for문이 돌지 않음!
		for (int i = parent->N; i >= idx; i--)
		{
			parent->C[i + 1] = parent->C[i];
		}
		// idx가 N이어도, 값이 추가되니까
		parent->C[idx + 1] = right;
		// 키 올라갈 녀석 자리 마련
		for (int i = parent->N - 1; i >= idx; i--)
		{
			parent->Key[i + 1] = parent->Key[i];
		}
		// 부모에 키 삽입
		parent->Key[idx] = right->Key[0];
		parent->N++;
		
	}

	//리프가 아니면, (B TREE 와 동일 )
	else 
	{
		// 오른쪽에 왼쪽의 뒷값들을 넣어주고
		for (int i = 0; i < MIN_DEGREE - 1; i++)
		{
			// 왼쪽이 뚱뚱해짐
			right->Key[i] = left->Key[i + MIN_DEGREE];
		}
		// 리프와, 내부 노드 모드 C(자녀)들을 갖는다.
		for (int i = 0; i < MIN_DEGREE; i++)
		{
			right->C[i] = left->C[i + MIN_DEGREE];
		}

		left->N = MIN_DEGREE - 1;
		right->N = MIN_DEGREE - 1;

		// 자식 올라갈 녀석 자리 마련
		// idx N 이면, parent-> N : N-1, idx : N 이라서 for문이 돌지 않음!
		for (int i = parent->N; i >= idx; i--)
		{
			parent->C[i + 1] = parent->C[i];
		}
		// idx가 N이어도, 값이 추가되니까
		parent->C[idx + 1] = right;
		// 키 올라갈 녀석 자리 마련
		for (int i = parent->N - 1; i >= idx; i--)
		{
			parent->Key[i + 1] = parent->Key[i];
		}
		// 부모에 키 삽입
		parent->Key[idx] = left->Key[MIN_DEGREE - 1];
		parent->N++;
	}

}

