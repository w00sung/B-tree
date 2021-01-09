#include <stdio.h>
#include <stdlib.h>

typedef struct listNode {
  int Data;
  struct listNode* Next;
  struct listNode* Prev
} Node;

Node* createNode(int data) {
  // 새로 생길 노드
  Node* newNode = (Node*)malloc(sizeof(Node));

  // variable initialization
  newNode->Data = data;
  newNode->Next = NULL;
  newNode->Prev = NULL;

  return newNode;
}

// 노드삭제 : 메모리 상에서만 없앤다.
void deleteNode(Node* Node) { free(Node); }

//해당 인덱스에 서 노드를 갖고와라.
//(시작점 필요)
Node* getNodeAt(Node* head, int idx) {
  // head부터 idx까지 달릴 hores
  Node* horse = head;

  // 달리는 횟수
  int cnt = 0;

  while (horse != NULL) {
    // idx 까지 달릴거다.
    if (cnt == idx) return horse;
    horse = horse->Next;
    cnt += 1;
  }
  // 아무것도 못찾고
  // 중간에 NULL을 만나서 나왔을 경우
  return NULL;
}

//리스트의 개수가 몇개냐?
//출발할 head를 받는다.
int countNode(Node* head) {
  int cnt = 0;
  Node* horse = head;
  while (horse != NULL) {
    horse = horse->Next;
    cnt++;
  }
  return cnt;
}
// 노드 맨 뒤에 append 해주기
// (why 이중포인터?!) --> 리스트의 head를 바꿀 수 있다.
void addNode(Node** head, Node* newNode) {
  // no list exists
  if ((*head) == NULL) {
    *head = newNode;
  }
  // list exists
  else {
    Node* horse = (*head);
    // 다음이 NULL일 때까지 달려
    // == 다음이 NULL일 때 멈춰!
    while (horse->Next != NULL) {
      horse = horse->Next;
    }
    horse->Next = newNode;
    newNode->Prev = horse;
  }
}

// 지금 위치 다음에 삽입
void inserAfterNode(Node* current, Node* newNode) {
  // head
  // 받는 것의 prev, next 모두 NULL
  if ((current->Next == NULL) && (current->Prev == NULL)) {
    current->Next = newNode;
    newNode->Prev = current;
  }

  // not head
  // tail("??) 
  else if (current->Next == NULL) {
    current->Next = newNode;
    newNode->Prev = current;
  }

  else {
    // current의 Next -> Prev : 현재의 다음의 Prev
    current->Next->Prev = newNode;
    newNode->Prev = current;
    // 순서를 주의하자! (유용한 데이터 뒤집어 쓸 수 있음)
    newNode->Next = current->Next;
    current->Next = newNode;
  }

  // in the middle of 2 nodes
  newNode->Prev = current;
  newNode->Next = current->Next;
}
// head에 변화를 주기 때문에 더블 포인터
                // head의 주소는 &List 와 같이 넘겨준다.
void removeNode(Node** head, Node* remove) {
  
  // remove 하려는게 head일때?
    // head를 뒤로 밀어줘야한다 !! -> !!이중포인터!!
  if (*head == remove) {
    // head를 remove하려는 다음으로 밀어준다.
    *head = remove->Next;
  }

  // else 붙일 필요없다.
  if (remove->Next != NULL) {
      //지우려는 놈의 다음 놈은 내가 지워지면 앞에 녀석 정보를 바꿔줘야한다.
    remove->Next->Prev = remove->Prev;
    }
  
  if (remove->Prev != NULL) {
    remove->Prev->Next = remove->Next;
  }

  //여기 까지오면, remove를 가리키는 애가 아무도 없다.
  deleteNode(remove);
  //
}

int main() { 
    
    return 0; 

}
