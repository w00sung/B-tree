#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "insertion.h"


// ������ ¦���� ���ٰ� ����
#define DEGREE 4

int MIN_DEGREE = (int)((DEGREE + 1) / 2);
int MAX_DEGREE = DEGREE - 1;

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

// return 0 or 1
int searchNode(Node* root, int k)
{
	int idx = (root->N) - 1;
	while (idx >= 0 && root->Key[idx] > k)
	{
		idx--;
	}
	// �� ����? : NO !!
	// �ε��� ���� �߻� ���ɼ� �ſ� ������ ����
	if (idx < 0 || root->Key[idx] != k)
		idx++;

	// ã������?
	if ((idx < root->N) && (k = root->Key[idx]))
	{
		return 1;
	}
	// ��ã�Ұ�, ������
	else if (root->isLeaf)
	{
		// ��ã���� NULL
		return 0;
	}
	// ��ã�Ұ�, ���� �ƴϾ�
	else
	{
		return searchNode(root->C[idx], k);
	}
}


void insertTree(Node** root, int k)
{
	int max_degree = (int)2 * ceil(DEGREE / 2) - 1;
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
	right->N = min_degree - 1;
	for (int i = 0; i < min_degree - 1; i++)
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
	left->N = min_degree - 1;
	// �ڽ� �ö� �༮ �ڸ� ����
	for (int i = parent->N; i >= idx + 1; i--)
	{
		parent->C[i + 1] = parent->C[i];
	}
	parent->C[idx + 1] = right;
	// Ű �ö� �༮ �ڸ� ����
	for (int i = parent->N - 1; i >= idx; i--)
	{
		parent->Key[i + 1] = parent->Key[i];
	}
	// �θ� Ű ����
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

void deleteTree(Node** root_address, Node* root, int k)
{
	int isIn = searchNode(root, k);
	if (isIn) {
		int idx = (root->N) - 1;

		// ������ ó������ ���� ���ְ�, ������ ū���� ��Ÿ�� �� ����
		while (idx >= 0 && root->Key[idx] > k)
		{
			idx--;
		}

		// �� ����? : NO !!
		// �ε��� ���� �߻� ���ɼ� �ſ� ������ ����
		if (idx < 0 || root->Key[idx] != k)
			idx++;

		// �� ������ (= ���� ���� ������ idx)
		const int goal_idx = idx;

		// �� ����?
		if (root->Key[goal_idx] == k)
		{
			//�� ������ ?
			//YES
			if (root->isLeaf)
			{
				printf("�������� Ű �����\n");
				// �����
				for (int i = goal_idx; i < (root->N) - 1; i++)
				{
					printf("���� %d <- %d\n", root->Key[i], root->Key[i + 1]);

					root->Key[i] = root->Key[i + 1];

					printf("���� %d �� �������� �Ű���\n", root->Key[i]);

				}
				// �ʴ� ��Ʈ ��ȯ �ʿ����
				root->N--;
			}
			//NO -> �� ������
			else
			{
				Node* Left = root->C[goal_idx];
				Node* Right = root->C[goal_idx + 1];
				int num_left = Left->N;
				int num_right = Right->N;

				// ������
				if (Left->N >= MIN_DEGREE)
				{
					int tmp = Left->Key[num_left - 1];
					printf("��� delete ��� LEFT, %d\n", tmp);
					deleteTree(&Left, Left, tmp);
					printf("��� delete �� LEFT, %d\n", tmp);
					root->Key[goal_idx] = tmp;

				}

				// ������
				else if (Right->N >= MIN_DEGREE)
				{
					//int num_right = Right->N;
					int tmp = Right->Key[0];
					printf("��� delete ��� Right, %d\n", tmp);
					deleteTree(&Right, Right, tmp);
					printf("��� delete �� Right, %d\n", tmp);
					root->Key[goal_idx] = tmp;
				}

				// �ڽ� ��ġ��
				else
				{


					// ���� �ڽĿ� ���� ������ �ڽ� ��ġ��
					Left->Key[num_left] = k;
					printf("�Ѵ� t-1�̾, ���ʿ� %d�� �־����\n", Left->Key[num_left]);
					for (int i = 0; i < num_right; i++)
					{
						Left->Key[(num_left + 1) + i] = Right->Key[i];
					}

					// ��������
					if (!(Left->isLeaf))
					{
						for (int i = 0; i <= num_right; i++)
						{
							Left->C[(num_left + 1) + i] = Right->C[i];
						}
					}

					Left->N = MAX_DEGREE;
					free(Right);

					// �θ� Ű & �ڽ� �����
					for (int i = goal_idx; i < (root->N) - 1; i++)
					{
						root->Key[i] = root->Key[i + 1];
						root->C[i + 1] = root->C[i + 2];
					}
					root->N--;

					if (root->N == 0)
					{
						printf("root �� �ٲ�ϴ�.\n");
						*root_address = Left;
					}

					// ����� + ��ġ�� �Ϸ� //

					// ��� ����
					printf("�Ѵ� t-1, ���ʿ� k(==%d) �ְ� ��� ���� ����!\n", Left->Key[num_left]);

					deleteTree(&Left, Left, k);
					printf("�Ѵ� t-1, ���ʿ� k �ְ� ��� ���� �Ϸ��ؼ� �� �ڸ��� %d�� ��ü��\n", Left->Key[num_left]);

				}

			}
		}
		// �� ���� ��忡 ����.
		else
		{

			Node* Target = root->C[goal_idx];
			int num_Target = Target->N;

			// ������ ���� MIN_DEGREE�� (�Ҿ����� ) -> �����ϰ� ����ž�
			if (Target->N < MIN_DEGREE)
			{
				int right_idx = goal_idx + 1;
				int left_idx = goal_idx - 1;
				// merge (merge_target , ��)
				// merge (�� , merge_target)

				// ���������� ���� ���� (RIGHT ������ �̶� ���� �˻� �� block �ȿ��� < bc : idx error)
				if (goal_idx != root->N && root->C[goal_idx + 1]->N >= MIN_DEGREE)
				{
					// ��������
					Node* Target_Right = root->C[goal_idx + 1];

					// �� ������
					Target->Key[num_Target] = root->Key[goal_idx];

					//������ �Űܿ���
					Target->C[num_Target + 1] = Target_Right->C[0];
					Target->N++;

					//��� Ű �� �ٲٱ�
					root->Key[goal_idx] = Target_Right->Key[0];

					//���� Ű �����,
					//���� ������ �����

					for (int i = 0; i < (Target_Right->N) - 1; i++)
					{
						Target_Right->Key[i] = Target_Right->Key[i + 1];

					}
					for (int i = 0; i < (Target_Right->N); i++)
					{
						Target_Right->C[i] = Target_Right->C[i + 1];
					}
					Target_Right->N--;
				}
				// ���� ���� ����
				else if (goal_idx != 0 && root->C[goal_idx - 1]->N >= MIN_DEGREE)
				{
					// ��������

					Node* Target_Left = root->C[goal_idx - 1];
					int num_Left = Target_Left->N;

					// Ÿ�� �о����
					for (int i = Target->N; i > 0; i--)
					{
						Target->Key[i] = Target->Key[i - 1];
					}
					// �� ������
					Target->Key[0] = root->Key[goal_idx - 1];

					// ������ �о����
					for (int i = Target->N + 1; i > 0; i--)
					{
						Target->C[i] = Target->C[i - 1];
					}
					Target->C[0] = Target_Left->C[num_Left];
					Target->N++;

					root->Key[goal_idx - 1] = Target_Left->Key[num_Left - 1];

					Target_Left->N--;


				}

				// �� ������ �� �۾�
				else
				{
					//���� ���� �� �־, ���� �����ϰ� ���ľߵ�
					if (goal_idx == root->N)
					{
						// merge_left
						Node* Target_Left = root->C[goal_idx - 1];
						int num_Left = Target_Left->N;
						//mergeNode(Left, Target);
						// Target = Left
						Target_Left->Key[num_Left] = root->Key[goal_idx - 1];

						// ���ʿ� ������ ģ������ �ٿ��ٰž�
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
						// root �� ��ٸ�? 
						if (root->N == 0)
						{
							printf("root �� �ٲ�ϴ�.\n");
							*root_address = Target_Left;
						}

						free(Target);

						Target = Target_Left;
					}
					else
					{
						// merge_right
						// ������ ������ ����
						Node* Target_Right = root->C[right_idx];
						// �θ� �� ä�� �ֱ�


						//mergeNode(Target, Right);
						Target->Key[num_Target] = root->Key[goal_idx];

						for (int i = 0; i < Target_Right->N; i++)
						{
							// �����ڽĿ� ������ �ڽ� Ű �ֱ�
							Target->Key[(num_Target + 1) + i] = Target_Right->Key[i];

						}
						if (!(Target->isLeaf))
						{
							for (int i = 0; i <= Target_Right->N; i++)
							{
								// ���� �ڽ��� Child�� ������ �ڽ��� Child �ֱ�
								Target->C[(num_Target + 1) + i] = Target_Right->C[i];

							}
						}
						Target->N = MAX_DEGREE;

						for (int i = goal_idx; i < (root->N) - 1; i++)
						{
							root->Key[i] = root->Key[i + 1];
							root->C[i + 1] = root->C[i + 2];
						}
						root->N--;
						if (root->N == 0)
						{
							printf("root �� �ٲ�ϴ�.\n");
							*root_address = Target;
						}

						// ���� ���ɼ� ����.
						// �����Ҵ��� �����Ѱ� �ƴ϶�, �����Ҵ�� �ּҸ� �޾Ƽ� free�� �����ذ�.
						free(Target_Right);




					}
				}
			}


			deleteTree(&Target, Target, k);


			// ���� ���� (LEFT ������ �̶� ���� �˻� �� block �ȿ���)

		}
	}
	else
	{
		printf("The key is not in the Tree");
	}
}
