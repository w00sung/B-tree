#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "bptree.h"

#define DEGREE 6

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
	while (idx > 0 && root->Key[idx-1] > k)
	{
		idx--;
	}
	// 너 리프니?
	if (root->isLeaf)
		idx--;

	// 찾았으면? - 리프가 아닐 때만, N에 서있을 수 있다.
	// 리프에서만 찾을 수 있다.
	if ((idx < root->N) && (k == root->Key[idx]))
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

	int isIn = searchNode(*root, k);
	if (isIn == 0)
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
	else
	{
		printf("The key is alredy in the Tree\n");
	}
}


void insertNonfull(Node* root, int k)
{
	int idx = (root->N)-1;
	if (root->isLeaf)
	{
		while ((idx >= 0) && (k < root->Key[idx]))
		{
			root->Key[idx + 1] = root->Key[idx];
			idx--;
		}
		root->Key[idx + 1] = k;
		root->N = (root->N) + 1;
	}
	else
	{
		while ((idx >= 0) && (k < root->Key[idx]))
		{
			idx--;
		}
		// 내가 들어갈 공간 위에 서있어
		idx++;

		// 내가 들어갈 자녀들이 가득 찼으면
		if (root->C[idx]->N == MAX_DEGREE)
		{
			splitChild(root, idx);
			// split 후 root에 값이 추가되니까 내가 어디로 들어갈 지 다시 확인
			if (k > root->Key[idx])
				idx++;
		}
		insertNonfull(root->C[idx], k);
	}
}

void splitChild(Node* parent, int idx)
{

	Node* right = createNode();
	Node* left = parent->C[idx];
	right->isLeaf = left->isLeaf;
	//******************개수 설정해줘야함************************
	//right->N = MIN_DEGREE - 1;

	// 찢을 놈이 리프일때, 부모한테 복사해서 올려줌 (copy up)
	if (left->isLeaf)
	{


		// 오른쪽에 왼쪽의 뒷값들을 넣어주고
		for (int i = 0; i < MIN_DEGREE-1; i++)
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

		left->N = MIN_DEGREE;
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

void printAll(Node* root, int depth)
{
	printf("\n");
	Node* node = root;
	if (node->isLeaf) {
		for (int i = 0; i < depth; i++) {
			printf("\t\t\t||");
		}
		for (int vIdx = 0; vIdx < node->N; vIdx++) {
			printf("%6d", node->Key[vIdx]);
		}
		return;
	}
	if (!node->isLeaf) {
		for (int i = 0; i < depth; i++) {
			printf("\t\t\t||");
		}
		for (int vIdx = 0; vIdx < node->N; vIdx++) {
			printf("%4d", node->Key[vIdx]);
		}
		for (int vIdx = 0; vIdx < node->N + 1; vIdx++) {
			printAll(node->C[vIdx], depth + 1);
		}
	}
}

void deleteTree(Node** root, int k)
{
	int isIn = searchNode(*root, k);
	// 안에 없을 때만 삭제 시작
	if (isIn) 
	{
		int idx = (*root)->N;

		// 나보다 다 크면, 0에 서게 됨
		// 내가 제일 크면 N에 서있음
		while (idx > 0 & (*root)->Key[idx-1] > k)
		{
			idx--;
		}

		const int goal_idx = idx;

		// 들어온 너 리프야?
		if ((*root)->isLeaf)
		{
			// 나는 Key[goal_idx - 1]이다.
			for (int i = goal_idx-1; i < ((*root)->N)-1; i++)
			{
				(*root)->Key[i] = (*root)->Key[i + 1];
			}
			(*root)->N--;
		}
		// 리프아니야 ( == 나 더 들어갈 수 있어 !!)
		else
		{
			Node* Target = (*root)->C[goal_idx];
			if (Target->N < MIN_DEGREE)
			{
				// 자식이 안뚱뚱한데, 리프야
				if (Target->isLeaf)
				{	
					// 오른쪽 끝에 서있으면, 무조건 왼쪽 형제가 형제다.
					if (goal_idx == (*root)->N)
					{
						Node* Sibling = (*root)->C[goal_idx - 1];

					}

					// 그 외에는, 무조건 오른쪽 형제가 형제다.
					else
					{
						Node* Sibling = (*root)->C[goal_idx + 1];
						// 형제 뚱뚱해 ? -> 빌려올거야
						if (Sibling->N >= MIN_DEGREE)
						{
							Target->Key[Target->N] = (*root)->Key[goal_idx];
							Target->N++;
							// 끝 Child 에 Sibling 연결시켜준다.
							Target->C[(Target->N)] = Sibling ;
								
							// 형제의 키 값 당긴다.
							for (int i = 0; i < (Sibling->N)-1; i++)
							{
								Sibling->Key[i] = Sibling->Key[i + 1];
							
							}
							Sibling->N--;
							(*root)->Key[goal_idx] = Sibling->Key[0];
						}
						// 형제도 안뚱뚱해 -> 합칠거야
						else
						{
							for (int i = 0; i < MIN_DEGREE-1; i++)
							{
								Target->Key[(MIN_DEGREE-1) + i] = Sibling->Key[i];
							}
							Target->N = MAX_DEGREE;
							Target->C[Target->N] = Sibling->C[Sibling->N];
							

							for (int i = goal_idx - 1; i < ((*root)->N)-1; i++)
							{
								(*root)->Key[i] = (*root)->Key[i + 1];
								(*root)->C[i + 1] = (*root)->C[i + 2];
							}
							(*root)->N--;
							if ((*root)->N == 0)
							{
								printf("root가 바뀝니다 \n");
								*root = Target;
							}
						}
					}
				}
				// 자식이 안뚱뚱한데, 리프가 아니야
				else
				{

				}
			}
			deleteTree(&Target, k);
		}
	}
	else
	{
		printf("The key is not in the Tree");
	}
}