#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "insertion.h"


// 차수가 짝수가 들어간다고 가정
#define DEGREE 4

int MIN_DEGREE = (int)((DEGREE + 1) / 2);
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

void deleteTree(Node** root_address, Node* root, int k)
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
		//너 리프야 ?
		//YES
		if (root->isLeaf)
		{
			printf("리프에서 키 땡기기\n");
			// 땡기기
			for (int i = goal_idx; i < (root->N) - 1; i++)
			{
				printf("시작 %d <- %d\n", root->Key[i], root->Key[i + 1]);

				root->Key[i] = root->Key[i + 1];

				printf("종료 %d 가 왼쪽으로 옮겨짐\n", root->Key[i]);

			}
			// 너는 루트 변환 필요없어
			root->N--;
		}
		//NO -> 더 들어가야함
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
				deleteTree(&Left, Left, tmp);
				printf("재귀 delete 끝 LEFT, %d\n", tmp);
				root->Key[goal_idx] = tmp;

			}

			// 후행자
			else if (Right->N >= MIN_DEGREE)
			{
				//int num_right = Right->N;
				int tmp = Right->Key[0];
				printf("재귀 delete 출발 Right, %d\n", tmp);
				deleteTree(&Right, Right, tmp);
				printf("재귀 delete 끝 Right, %d\n", tmp);
				root->Key[goal_idx] = tmp;
			}

			// 자식 합치기
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

				deleteTree(&Left, Left, k);
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
			int num_Target = Target->N;

			// 내려갈 곳이 MIN_DEGREE야 (불안정해 ) -> 안정하게 만들거야
			if (Target->N < MIN_DEGREE)
			{
				int right_idx = goal_idx + 1;
				int left_idx = goal_idx - 1;
				// merge (merge_target , 나)
				// merge (나 , merge_target)

				// 오른쪽형제 먼저 보고 (RIGHT 선언은 이때 조건 검사 후 block 안에서 < bc : idx error)
				if (goal_idx != root->N && root->C[goal_idx + 1]->N >= MIN_DEGREE)
				{
					// 빌려오기
					Node* Target_Right = root->C[goal_idx + 1];

					// 값 내리기
					Target->Key[num_Target] = root->Key[goal_idx];

					//포인터 옮겨오기
					Target->C[num_Target + 1] = Target_Right->C[0];
					Target->N++;

					//노드 키 값 바꾸기
					root->Key[goal_idx] = Target_Right->Key[0];
					
					//형제 키 땡기기,
					//형제 포인터 땡기기

					for (int i = 0; i < (Target_Right->N)-1; i++)
					{
						Target_Right->Key[i] = Target_Right->Key[i + 1];

					}
					for (int i = 0; i < (Target_Right->N); i++)
					{
						Target_Right->C[i] = Target_Right->C[i + 1];
					}
					Target_Right->N--;
				}
				// 왼쪽 형제 볼게
				else if (goal_idx != 0 && root->C[goal_idx - 1]->N >= MIN_DEGREE)
				{
					// 빌려오기

					Node* Target_Left = root->C[goal_idx - 1];
					int num_Left = Target_Left->N;

					// 타겟 밀어놓기
					for (int i = Target->N; i > 0  ; i--)
					{
						Target->Key[i] = Target->Key[i-1];
					}
					// 값 내리기
					Target->Key[0] = root->Key[goal_idx-1];

					// 포인터 밀어놓기
					for (int i = Target->N + 1; i > 0; i--)
					{
						Target->C[i] = Target->C[i - 1];
					}
					Target->C[0] = Target_Left->C[num_Left];
					Target->N++;

					root->Key[goal_idx - 1] = Target_Left->Key[num_Left - 1];
					
					Target_Left->N--;
					

				}

				// 내 형제가 다 작아
				else
				{
					//내가 끝에 서 있어서, 나는 왼쪽하고만 합쳐야돼
					if (goal_idx == root->N)
					{
						// merge_left
						Node* Target_Left = root->C[goal_idx - 1];
						int num_Left = Target_Left->N;
						//mergeNode(Left, Target);
						// Target = Left
						Target_Left->Key[num_Left] = root->Key[goal_idx-1];

						// 왼쪽에 오른쪽 친구들을 붙여줄거야
						for (int i = 0; i < Target->N; i++)
						{
							Target_Left->Key[(num_Left + 1) + i] = Target->Key[i];
						}
						for (int i = 0; i <= Target->N; i++)
						{
							Target_Left->C[(num_Left + 1) + i] = Target->C[i];
						}
						Target_Left->N = MAX_DEGREE;
						root->N--;
						// root 가 빈다면? 
						if (root->N == 0)
						{
							printf("root 가 바뀝니다.\n");
							*root_address = Target_Left;
						}

						free(Target);

						Target = Target_Left;
					}
					else
					{
						// merge_right
						// 오른쪽 형제라 합쳐
						Node* Target_Right = root->C[right_idx];
						// 부모 값 채워 넣기
						

						//mergeNode(Target, Right);
						Target->Key[num_Target] = root->Key[goal_idx];

						for (int i = 0; i < Target_Right->N; i++)
						{
							// 왼쪽자식에 오른쪽 자식 키 넣기
							Target->Key[(num_Target + 1) + i] = Target_Right->Key[i];

						}
						if (!(Target->isLeaf)) 
{
							for (int i = 0; i <= Target_Right->N; i++)
							{
								// 왼쪽 자식의 Child에 오른쪽 자식의 Child 넣기
								Target->C[(num_Target + 1) + i] = Target_Right->C[i];

							}
						}
						Target->N = MAX_DEGREE;

						for (int i = goal_idx; i < (root->N)-1 ; i++)
						{
							root->Key[i] = root->Key[i + 1];
							root->C[i + 1] = root->C[i + 2];
						}
						root->N--;
						if (root->N == 0)
						{
							printf("root 가 바뀝니다.\n");
							*root_address = Target;
						}

						// 오류 가능성 있음.
						// 동적할당을 직접한게 아니라, 동적할당된 주소를 받아서 free를 시켜준것.
						free(Target_Right);
						



					}
				}
			}


			deleteTree(&Target, Target, k);


			// 왼쪽 보고 (LEFT 선언은 이때 조건 검사 후 block 안에서)
		}
	}
}
