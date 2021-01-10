#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    struct _Node *Left;
    int Data;
    struct _Node *Right;

} Node;

// 찾은 곳의 부모를 저장할 pr
Node* pr;

// 노드 초기화 (노드의 주소를 return한다.)
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->Data = data;

    // 좌,우 자식들은 찾으면서 넣어줄거임
    newNode->Right = NULL;
    newNode->Left = NULL;
    
    return newNode;

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
    
    pr = NULL;
    while (horse != NULL)
    {
        // data가 더 작으면?
        if (horse->Data > data)
        {  
            pr = horse;
            horse = horse->Left;
        }
        else if (horse->Data < data)
        {
            pr = horse;
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

// Find Successor
// 가장 오른쪽의 가장 밑의 좌측
Node* Find_Suc(Node* root, int data)
{
    //우측 자식이 없으면? -> 내가 Successor

    /* 값 없는 녀석을 넣었을 때도 생각 */
    // 후행자 찾을 출발지 horse
    Node* horse = Search_Data(root, data);
    Node* check;
    Node* pr_cur;
    // 처음으로 오른쪽으로 움직여줌
    // tmp는 확인용
    check = horse->Right;

    // 부모 노드에 우측 자식이 있으면?
    if (check != NULL)
    {
        //// 안전하게 들어온다.
        //horse = check;
        //

        // horse는 왼쪽 자식이 없을 때까지 오른쪽으로 내려감
        while (check != NULL)
        {
            /**** 참조 자료랑 다르다 ****/
            //현재는 왼쪽으로 계속 감
            horse = check;

            // tmp는 한단계 더 내려가서 계속 체크를 해준다.
            check = horse->Left;
        }

    }
    // 오른쪽 자식이 없으면? (부모 중에서 가장 오른쪽 녀석이다.) 
    // 1) 내가 부모의 우측 자식이다.(부모보다 크다?) -> 부모의 부모가 successor
    // 2) 내가 부모의 좌측 자식이다.(부모보다 작다?) -> 부모가 successor
    else
    {
        // pr: 내가 찾은 놈의 부모
        // 내가 부모의 왼쪽 자식이 있으면?
        if (pr->Left != NULL)
        {
            horse = pr;
        }
        /* ???? */
        // 내가 부모의 오른쪽 자식이 있는데
        if (pr->Right != NULL)
        {
            // 현재 부모 저장
            pr_cur = pr;

            // 현재 부모의 우측이 나냐?
            if (pr_cur->Right->Data == horse->Data) {
                Search_Data(root, pr->Data);
                horse = pr;

            }
            if (pr->Right->Data == pr_cur->Data) {
                horse = NULL;
                puts("\n NO SUCCESSOR ");
            }
        }

    }

    return horse;

}

// 삭제시키고, 삭제되는 데이터의 자식이 모두 있으면, successor 와 바꾼다.
void Delete_data(Node* root, int data)
{

    Node* cur;
    Node* suc;
    Node* tmp;

    cur = Search_Data(root, data);

    if (cur == NULL)
    {
        puts("The data is not in Tree \n");
    }
    else {
        // !!pr이 중요하다!! -- 찾은 녀석의 부모!
        // 자식 노드가 없다.
        if (cur->Left == NULL && cur->Right == NULL) {
            // 나의 부모가 왼쪽을 갖고있다?
            if (pr->Left != NULL) {
                if (pr->Left->Data == cur->Data) {
                    // 나와 연결을 끊음
                    pr->Left = NULL;
                }
                else
                {
                    //왼쪽을 갖고있는데, 왼쪽이 내가 아니면 나는 오른쪽
                    pr->Right = NULL;
                }
            }
            free(cur); // cur에 해당한 메모리 할당 해제
            
        }
        // 나는 자식으로 가득 찼다. -> 선행자 녀석으로 대체해준다.
        else if (cur->Left != NULL && cur->Right == NULL)
        {
            suc = Find_Suc(root, data);

            // 선행자 데이터를 가진 트리를 만든다.
            // tmp를 만들지 않는다면? suc이 free되면서 무용지물이 된다.
            tmp = createNode(suc->Data);

            // 재귀적으로
            // 트리에서 지워준다. -> 지워도 suc은 존재하는가? NO : free됨
            Delete_data(root, suc->Data);
            // 선행자로 대체
            cur->Data = tmp->Data;
            // 주소는 그대로 유지됨
            free(tmp);
        }
        // 나는 자식이 하나밖에 없다.
        else {
            if (cur->Left == NULL) {
                tmp = cur->Right;
            }
            if (cur->Right == NULL) {
                tmp = cur->Left;

            }
            // why ? cur = tmp 하지 않지? -- 포인터의 무언가
            cur->Data = tmp->Data;
            cur->Left = tmp->Left;
            cur->Right = tmp->Right;

            free(tmp);
        }

        
    }

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

// Node* child[max]
// Node ** child = malloc( k * max(sizeof(Node*)); // 주소(포인터)를 담는 포인터