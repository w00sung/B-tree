#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "insertion.h"


// 차수가 짝수가 들어간다고 가정
#define DEGREE 4

int MIN_DEGREE = (int)((DEGREE+1) / 2);
int MAX_DEGREE = DEGREE - 1;

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

//// **** return 값 변경 필요 *****
//Node* searchNode(Node* root, int k)
//{
//	int i = 0;
//	while ((i < (root->N)) && (k > root->Key[i]))
//	{
//		i += 1;
//	}
//	// 찾았으면?
//	if ((i < root->N) && (k = root->Key[i]))
//	{
//		return(root, i);
//	}
//	// 몿찾았고, 리프야
//	else if (root->isLeaf)
//	{
//		// 못찾으면 NULL
//		return NULL;
//	}
//	// 못찾았고, 리프 아니야
//	else
//	{
//		return searchNode(root->C[i], k);
//	}
//}


void insertTree(Node** root, int k)
{
	int max_degree = (int)2 * ceil(DEGREE / 2) - 1;
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
	right->N = min_degree - 1;
	for (int i = 0; i < min_degree - 1; i++)
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
	left->N = min_degree - 1;
	// 자식 올라갈 녀석 자리 마련
	for (int i = parent->N; i >= idx + 1; i--)
	{
		parent->C[i + 1] = parent->C[i];
	}
	parent->C[idx + 1] = right;
	// 키 올라갈 녀석 자리 마련
	for (int i = parent->N - 1; i >= idx; i--)
	{
		parent->Key[i + 1] = parent->Key[i];
	}
	// 부모에 키 삽입
	parent->Key[idx] = left->Key[min_degree - 1];
	parent->N++;
}

void insertNonfull(Node* root, int k)
{
	int max_degree = (int)2 * ceil(DEGREE / 2) - 1;
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

void deleteTree(Node** root_address,Node* root, int k)
{
	int idx = (root->N) - 1;

	// 끝부터 처음까지 위에 서있고, 나보다 큰놈이 나타날 때 까지
	while (idx >= 0 && root->Key[idx] > k)
	{
		idx--;
	}

	// 너 나니? : NO !!
	// 인덱스 에러 발생 가능성 매우 적지만 있음
	if (idx < 0 || root->Key[idx] != k)
		idx++;

	// 내 목적지 (= 내가 들어가기 적절한 idx)
	const int goal_idx = idx;

	// 너 나냐?
	if (root->Key[goal_idx] == k)
	{
		//YES
		if (root->isLeaf)
		{
			printf("리프에서 키 땡기기\n");
			// 땡기기
			for (int i = goal_idx; i < (root->N) - 1; i++)
			{
				printf("시작 %d <- %d\n", root->Key[i], root->Key[i+1]);

				root->Key[i] = root->Key[i + 1];

				printf("종료 %d 가 왼쪽으로 옮겨짐\n", root->Key[i]);

			}
			root->N--;
		}
		else
		{
			Node* Left = root->C[goal_idx];
			Node* Right = root->C[goal_idx + 1];
			int num_left = Left->N;
			int num_right = Right->N;

			// 선행자
			if (Left->N >= MIN_DEGREE)
			{
				int tmp = Left->Key[num_left - 1];
				printf("재귀 delete 출발 LEFT, %d\n", tmp);
				deleteTree(&Left,Left, tmp);
				printf("재귀 delete 끝 LEFT, %d\n", tmp);
				root->Key[goal_idx] = tmp;

			}

			// 후행자
			else if (Right->N >= MIN_DEGREE)
			{
				//int num_right = Right->N;
				int tmp = Right->Key[0];
				printf("재귀 delete 출발 Right, %d\n", tmp);
				deleteTree(&Right,Right, tmp);
				printf("재귀 delete 끝 Right, %d\n", tmp);
				root->Key[goal_idx] = tmp;
			}

			else
			{


				// 왼쪽 자식에 나와 오른쪽 자식 합치기
				Left->Key[num_left] = k;
				printf("둘다 t-1이어서, 왼쪽에 %d값 넣었어요\n", Left->Key[num_left]);
				for (int i = 0; i < num_right; i++)
				{
					Left->Key[(num_left + 1) + i] = Right->Key[i];
				}

				// 주의하자
				if (!(Left->isLeaf))
				{
					for (int i = 0; i <= num_right; i++)
					{
						Left->C[(num_left + 1) + i] = Right->C[i];
					}
				}

				Left->N = MAX_DEGREE;
				free(Right);

				// 부모 키 & 자식 땡기기
				for (int i = goal_idx; i < (root->N) - 1; i++)
				{
					root->Key[i] = root->Key[i + 1];
					root->C[i + 1] = root->C[i + 2];
				}
				root->N--;

				if (root->N == 0)
				{
					printf("root 가 바뀝니다.\n");
					*root_address = Left;
				}

				// 땡기기 + 합치기 완료 //

				// 재귀 삭제
				printf("둘다 t-1, 왼쪽에 k(==%d) 넣고 재귀 삭제 시작!\n", Left->Key[num_left]);

				deleteTree(&Left,Left, k);
				printf("둘다 t-1, 왼쪽에 k 넣고 재귀 삭제 완료해서 그 자리에 %d로 대체됨\n", Left->Key[num_left]);

			}

		}
	}
	// 나 여기 노드에 없어.
	else
	{
		//값이 없다.
		if (root->isLeaf)
		{
			printf("The key is not in Tree");
		}
		//나 리프아니야. == 더 내려갈 수 있어.
		else
		{
			Node* Target = root->C[goal_idx];
			int num_Target= Target->N;

			// 내가 내려갈 곳을 본다.
			if (Target->N >= MIN_DEGREE)
			{
				//문제 없이, 
				deleteTree(&Target, Target, k);
			}
			else
			{
				// 오른쪽 형
			}
		}
	}
}