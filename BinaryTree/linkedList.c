#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
	struct NODE* next;
	int data;
}Node;

// Node의 주소(curr or NULL)를 return으로 하는 함수
Node *findNode(struct NODE *target, int data)
{
	if (target == NULL)
		return NULL;

	// 다음 녀석의 주소를 가진 놈을 선언
	Node*curr = target->next;
	while (curr != NULL)
	{
		// 찾을때 까지 진행한다.
		if (curr->data == data)
			return curr;

		curr = curr->next;
	}
	// 끝에 도달하면 NULL이다. 
	return NULL;
}

void addFirst(Node* target, int data);
void removeFirst(Node* target);

int main()
{
	// 다음이 없던 녀석이 head
	Node* head;
	
	head = malloc(sizeof(Node));
	// 아무도 안가리키고 있다.
	head->next = NULL;

	// 헤드 위치 노드 다음에 10을 넣는다.
	addFirst(head, 10);
	addFirst(head, 20);
	addFirst(head, 30);

	// horse : 노드가 있는 곳까지 달릴 말이다.
	Node* horse = head->next;
	while (horse != NULL) {
		printf("%d\n", horse->data);
		//지금 주소를 가진 녀석의 다음 녀석을 가리킨다.
		horse = horse->next;
	}
	/* WOW!! -- 함수로 생성하면 자동 free 
		-> 중간으로 접근이 불가능하다 ? */
//	free(node2);
//	free(node1);
	free(head);
	return 0;
}

// target node 뒤의 노드를 추가한다.
void addFirst(Node* target, int data) 
{
	/* newNode는 함수 끝나면 자동 삭제 */
	Node* newNode = malloc(sizeof(Node)); // 새노드생성
	
	// 중간에 끼어들꺼니까 기존 target의 다음이 나의 다음
	newNode->next = target->next; 
	// 입력받은 data 넣기
	newNode->data = data;

	//기존에 있던 것은 나를 가리킨다.
	target->next = newNode;
}

// target node 뒤의 노드를 삭제한다.
void removeFirst(Node* target)
{
	// 다음 녀석 위치에 가 있는다
	Node* removeNode = target->next;

	// target기준 다 다음 녀석을 가리킨다.
	target->next = removeNode->next;

	// 다음녀석의 메모리 할당 끊어준다.
	free(removeNode);
}