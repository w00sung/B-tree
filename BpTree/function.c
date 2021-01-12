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
	// ���԰������� �ʿ��Ͽ�, �ϳ��� �� �߰�
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
	// �� ������?
	if (root->isLeaf)
		idx--;

	// ã������? - ������ �ƴ� ����, N�� ������ �� �ִ�.
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
	Node* tmp = *root;
	if (((*root)->N == MAX_DEGREE))
	{
		// ��Ʈ�� �� ��� ����
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
		// ���� �� ���� ���� ���־�
		num++;

		// ���� �� �ڳ���� ���� á����
		if (root->C[num]->N == MAX_DEGREE)
		{
			splitChild(root, num,k);
			// split �� root�� ���� �߰��Ǵϱ� ���� ���� �� �� �ٽ� Ȯ��
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
	//******************���� �����������************************
	//right->N = MIN_DEGREE - 1;

	// �����϶�, �θ����� �����ؼ� �÷��� (copy up)
	if (parent->isLeaf)
	{

		//k�� ���� ������ Ȯ���ϰ�, (left)�а�, �����ϰ�, split
		int k_insert_idx = (left->N) ;
		while (k_insert_idx >= 0 && left->Key[k_insert_idx] > k)
		{
			k_insert_idx--;
		}
		for (int i = (left->N)-1; i >= k_insert_idx; i--)
		{
			// k�� �־��� �� �ְ�, �� �о��ֱ�
			left->Key[i + 1] = left->Key[i];
			left->C[i + 2] = left->C[i+1];
		}

		/// ���� �Ϸ�
		left->Key[k_insert_idx] = k;
		int up_idx = (left->N + 1) / 2;

		// �����ʿ� ������ �ް����� �־��ְ�
		for (int i = 0; i < MIN_DEGREE; i++)
		{
			// ������ �׶�����
			right->Key[i] = left->Key[i + MIN_DEGREE];
			// ������, ���� ��� ��� C(�ڳ�)���� ���´�.
		}
		//for (int i = 0; i <= MIN_DEGREE; i++)
		//{
		//	right->C[i] = left->C[i + MIN_DEGREE];
		//}

		// ���� ��带 ����Ű�� ����
		right->N = MIN_DEGREE - 1;
		right->C[right->N] = left->C[left->N];

		left->N = MIN_DEGREE - 1;
		left->C[left->N] = right;
		


		//(�θ�) �а�, �߰��ڸ� �ø���, �ڽ� �����Ű��
		// �ڽ� �ö� �༮ �ڸ� ����
		// idx N �̸�, parent-> N : N-1, idx : N �̶� for���� ���� ����!
		for (int i = parent->N; i >= idx; i--)
		{
			parent->C[i + 1] = parent->C[i];
		}
		// idx�� N�̾, ���� �߰��Ǵϱ�
		parent->C[idx + 1] = right;
		// Ű �ö� �༮ �ڸ� ����
		for (int i = parent->N - 1; i >= idx; i--)
		{
			parent->Key[i + 1] = parent->Key[i];
		}
		// �θ� Ű ����
		parent->Key[idx] = right->Key[0];
		parent->N++;
		
	}

	//������ �ƴϸ�, (B TREE �� ���� )
	else 
	{
		// �����ʿ� ������ �ް����� �־��ְ�
		for (int i = 0; i < MIN_DEGREE - 1; i++)
		{
			// ������ �׶�����
			right->Key[i] = left->Key[i + MIN_DEGREE];
		}
		// ������, ���� ��� ��� C(�ڳ�)���� ���´�.
		for (int i = 0; i < MIN_DEGREE; i++)
		{
			right->C[i] = left->C[i + MIN_DEGREE];
		}

		left->N = MIN_DEGREE - 1;
		right->N = MIN_DEGREE - 1;

		// �ڽ� �ö� �༮ �ڸ� ����
		// idx N �̸�, parent-> N : N-1, idx : N �̶� for���� ���� ����!
		for (int i = parent->N; i >= idx; i--)
		{
			parent->C[i + 1] = parent->C[i];
		}
		// idx�� N�̾, ���� �߰��Ǵϱ�
		parent->C[idx + 1] = right;
		// Ű �ö� �༮ �ڸ� ����
		for (int i = parent->N - 1; i >= idx; i--)
		{
			parent->Key[i + 1] = parent->Key[i];
		}
		// �θ� Ű ����
		parent->Key[idx] = left->Key[MIN_DEGREE - 1];
		parent->N++;
	}

}

