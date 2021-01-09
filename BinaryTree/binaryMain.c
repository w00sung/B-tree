#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    struct _Node *Left;
    int Data;
    struct _Node *Right;

} Node;

// 노드 초기화 (노드의 주소를 return한다.)
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->Data = data;

    // 좌,우 자식들은 찾으면서 넣어줄거임
    newNode->Right = NULL;
    newNode->Left = NULL;
}

// 삽입
// &root : root의 주소 (?)
void insertNode(Node** root, int data) {
    Node* newNode = createNode(data);

    // 빈 트리였다면?
    if (*root == NULL) {
        // root는 나다
        // root에 주소를 넣는 행위다.
        *root = newNode;
    }

    // 빈트리 아니면?
    else {
        //부모가 나보다 크면?
        if ((*root)->Data > data) {
            // 왼쪽 자식 비어있냐?
            if ((*root)->Left == NULL) {
                (*root)->Left = newNode;
            }
            // 무조건 왼쪽으로 들어가야함
            else {
                // **재귀적으로 (recursion) 그 친구를 부모로 해서 실행한다.**
                insertNode(&((*root)->Left), data);
            }
        }
        // 부모가 나보다 작으면
        else if ((*root)->Data < data) {
            if ((*root)->Right == NULL) {
                (*root)->Right = newNode;
            }
            else {
                insertNode(&((*root)->Right), data);
            }
        }
        else {
            printf("This input is already in Tree");
        }


        
    }
}

// 검색할 때는, 시작 주소만 알면된다. 
// 시작이 되는 지점을 바꾸지 않아줘도 되니까!!
Node* Search_Data(Node* root, int data)
{
    // root 부터 계속 달려갈 녀석 선언
    Node* horse = root;
    Node* result = NULL;

    while (horse != NULL)
    {
        // data가 더 작으면?
        if (horse->Data > data)
        {
            horse = horse->Left;
        }
        else if (horse->Data < data)
        {
            horse = horse->Right;
        }
        else {
            result = horse;
            break;
        }
        
    }
    //찾으면 null 아니고, 못찾으면 null 임.
    return result;
}


Node* insertsingleNode(Node* root, int data) {
    Node* newNode = createNode(data);

    // 빈 트리였다면?
    if (root == NULL) {
        // root는 나다
        root = newNode;
        return root;
    }

    // 빈트리 아니면?
    else {
        //부모가 나보다 크면?
        if (root->Data > data) {
            // 왼쪽 자식 비어있냐?
            if (root->Left == NULL) {
                root->Left = newNode;
                return root;
            }
            // 무조건 왼쪽으로 들어가야함
            else {
                // **재귀적으로 (recursion) 그 친구를 부모로 해서 실행한다.**
                root->Left = insertsingleNode(root->Left, data);
                return root;
            }
        }
        // 부모가 나보다 작으면
        else if (root->Data < data) {
            if (root->Right == NULL) {
                root->Right = newNode;
                return root;
            }
            else {
                root->Right = insertsingleNode(root->Right, data);
                return root;
            }
        }
        else {
            printf("This input is already in Tree");
            return root;
        }

    }
}

int main() {
    // 구조체 포인터
    Node* root;
    root = NULL;
                    //root의 형태가 중요한게 아니라,
                    // root가 주소를 가졌냐가 중요하다.
                    // NULL을 넘기는거다.
    root = insertsingleNode(root, 4);
    insertsingleNode(root, 2);
    insertsingleNode(root, 3);
    printf("root : %d\n root->Left : %d\n root->Left->Right:%d", root->Data, root->Left->Data, root->Left->Right->Data);

    //printf("insert single - root : %d\n", root->Data);
    //insertNode(&root, 4);
    //printf("Insert Double - root : %d", root->Data);

    return 0;
}
