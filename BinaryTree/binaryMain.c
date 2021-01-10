#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    struct _Node *Left;
    int Data;
    struct _Node *Right;

} Node;

// ã�� ���� �θ� ������ pr
Node* pr;

// ��� �ʱ�ȭ (����� �ּҸ� return�Ѵ�.)
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->Data = data;

    // ��,�� �ڽĵ��� ã���鼭 �־��ٰ���
    newNode->Right = NULL;
    newNode->Left = NULL;
    
    return newNode;

}

// ����
// &root : root�� �ּ� (?)
void insertNode(Node** root, int data) {
    Node* newNode = createNode(data);

    // �� Ʈ�����ٸ�?
    if (*root == NULL) {
        // root�� ����
        // root�� �ּҸ� �ִ� ������.
        *root = newNode;


    }

    // ��Ʈ�� �ƴϸ�?
    else {
        //�θ� ������ ũ��?
        if ((*root)->Data > data) {
            // ���� �ڽ� ����ֳ�?
            if ((*root)->Left == NULL) {
                (*root)->Left = newNode;
            }
            // ������ �������� ������
            else {
                // **��������� (recursion) �� ģ���� �θ�� �ؼ� �����Ѵ�.**
                insertNode(&((*root)->Left), data);
            }
        }
        // �θ� ������ ������
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

// �˻��� ����, ���� �ּҸ� �˸�ȴ�. 
// ������ �Ǵ� ������ �ٲ��� �ʾ��൵ �Ǵϱ�!!
Node* Search_Data(Node* root, int data)
{
    // root ���� ��� �޷��� �༮ ����
    Node* horse = root;
    Node* result = NULL;
    
    pr = NULL;
    while (horse != NULL)
    {
        // data�� �� ������?
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
    //ã���� null �ƴϰ�, ��ã���� null ��.
    return result;
}

// Find Successor
// ���� �������� ���� ���� ����
Node* Find_Suc(Node* root, int data)
{
    //���� �ڽ��� ������? -> ���� Successor

    /* �� ���� �༮�� �־��� ���� ���� */
    // ������ ã�� ����� horse
    Node* horse = Search_Data(root, data);
    Node* check;
    Node* pr_cur;
    // ó������ ���������� ��������
    // tmp�� Ȯ�ο�
    check = horse->Right;

    // �θ� ��忡 ���� �ڽ��� ������?
    if (check != NULL)
    {
        //// �����ϰ� ���´�.
        //horse = check;
        //

        // horse�� ���� �ڽ��� ���� ������ ���������� ������
        while (check != NULL)
        {
            /**** ���� �ڷ�� �ٸ��� ****/
            //����� �������� ��� ��
            horse = check;

            // tmp�� �Ѵܰ� �� �������� ��� üũ�� ���ش�.
            check = horse->Left;
        }

    }
    // ������ �ڽ��� ������? (�θ� �߿��� ���� ������ �༮�̴�.) 
    // 1) ���� �θ��� ���� �ڽ��̴�.(�θ𺸴� ũ��?) -> �θ��� �θ� successor
    // 2) ���� �θ��� ���� �ڽ��̴�.(�θ𺸴� �۴�?) -> �θ� successor
    else
    {
        // pr: ���� ã�� ���� �θ�
        // ���� �θ��� ���� �ڽ��� ������?
        if (pr->Left != NULL)
        {
            horse = pr;
        }
        /* ???? */
        // ���� �θ��� ������ �ڽ��� �ִµ�
        if (pr->Right != NULL)
        {
            // ���� �θ� ����
            pr_cur = pr;

            // ���� �θ��� ������ ����?
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

// ������Ű��, �����Ǵ� �������� �ڽ��� ��� ������, successor �� �ٲ۴�.
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
        // !!pr�� �߿��ϴ�!! -- ã�� �༮�� �θ�!
        // �ڽ� ��尡 ����.
        if (cur->Left == NULL && cur->Right == NULL) {
            // ���� �θ� ������ �����ִ�?
            if (pr->Left != NULL) {
                if (pr->Left->Data == cur->Data) {
                    // ���� ������ ����
                    pr->Left = NULL;
                }
                else
                {
                    //������ �����ִµ�, ������ ���� �ƴϸ� ���� ������
                    pr->Right = NULL;
                }
            }
            free(cur); // cur�� �ش��� �޸� �Ҵ� ����
            
        }
        // ���� �ڽ����� ���� á��. -> ������ �༮���� ��ü���ش�.
        else if (cur->Left != NULL && cur->Right == NULL)
        {
            suc = Find_Suc(root, data);

            // ������ �����͸� ���� Ʈ���� �����.
            // tmp�� ������ �ʴ´ٸ�? suc�� free�Ǹ鼭 ���������� �ȴ�.
            tmp = createNode(suc->Data);

            // ���������
            // Ʈ������ �����ش�. -> ������ suc�� �����ϴ°�? NO : free��
            Delete_data(root, suc->Data);
            // �����ڷ� ��ü
            cur->Data = tmp->Data;
            // �ּҴ� �״�� ������
            free(tmp);
        }
        // ���� �ڽ��� �ϳ��ۿ� ����.
        else {
            if (cur->Left == NULL) {
                tmp = cur->Right;
            }
            if (cur->Right == NULL) {
                tmp = cur->Left;

            }
            // why ? cur = tmp ���� ����? -- �������� ����
            cur->Data = tmp->Data;
            cur->Left = tmp->Left;
            cur->Right = tmp->Right;

            free(tmp);
        }

        
    }

}

Node* insertsingleNode(Node* root, int data) {
    Node* newNode = createNode(data);

    // �� Ʈ�����ٸ�?
    if (root == NULL) {
        // root�� ����
        root = newNode;
        return root;
    }

    // ��Ʈ�� �ƴϸ�?
    else {
        //�θ� ������ ũ��?
        if (root->Data > data) {
            // ���� �ڽ� ����ֳ�?
            if (root->Left == NULL) {
                root->Left = newNode;
                return root;
            }
            // ������ �������� ������
            else {
                // **��������� (recursion) �� ģ���� �θ�� �ؼ� �����Ѵ�.**
                root->Left = insertsingleNode(root->Left, data);
                return root;
            }
        }
        // �θ� ������ ������
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
    // ����ü ������
    Node* root;
    root = NULL;
                    //root�� ���°� �߿��Ѱ� �ƴ϶�,
                    // root�� �ּҸ� �����İ� �߿��ϴ�.
                    // NULL�� �ѱ�°Ŵ�.
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
// Node ** child = malloc( k * max(sizeof(Node*)); // �ּ�(������)�� ��� ������