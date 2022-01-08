#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    int height;
    struct Node* parent;
    struct Node* lChild;
    struct Node* rChild;
}Node;

Node* getNode(){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->parent = NULL;
    newNode->lChild = NULL;
    newNode->rChild = NULL;
    return newNode;
}
int isExternal(Node* w) {
    if (w->lChild == NULL && w->rChild == NULL) return 1;
    else return 0;
}

Node* treeSearch(Node* w, int key) {
    if (isExternal(w)) return w;
    if (w->key == key) return w;
    if (w->key > key) return treeSearch(w->lChild, key);
    else return treeSearch(w->rChild, key);
}
void expandExternal(Node* w) {
    w->lChild = getNode();
    w->rChild = getNode();
    w->lChild->parent = w;
    w->rChild->parent = w;
}
int updateHeight(Node* w) {
    if (isExternal(w)) return 0;
    updateHeight(w->lChild);
    updateHeight(w->rChild);
    if (w->lChild->height > w->rChild->height) w->height = w->lChild->height + 1;
    else w->height = w->rChild->height + 1;
}
int isBalanced(Node* w){
    int gap = w->lChild->height - w->rChild->height;
    if(gap >=-1 && gap <= 1) return 1;
    else return 0;
}
void restructure(Node* x, Node* y, Node* z, Node** root) {
    Node *a;
    Node *b;
    Node *c;
    Node *T0;
    Node *T1;
    Node *T2;
    Node *T3;
    // 1. x, y, z의 중위순회 방문 순서의 나열을 a, b, c라고 한다.
    // 2. x, y, z의 부트리들 가운데 x, y, z를 루트로 하는 부트리를 제외한 4개의 부트리들의 중위순회 방문순서의 나열을 T0, T1, T2, T3라 하자.
    if (x->key < y->key && y->key < z->key) {
        a = x;
        b = y;
        c = z;
        T0 = a->lChild;
        T1 = a->rChild;
        T2 = y->rChild;
        T3 = z->rChild;
    } else if (z->key < y->key && y->key < x->key) {
        a = z;
        b = y;
        c = x;
        T0 = z->lChild;
        T1 = y->lChild;
        T2 = x->lChild;
        T3 = x->rChild;
    } else if (y->key < x->key && x->key < z->key) {
        a = y;
        b = x;
        c = z;
        T0 = y->lChild;
        T1 = x->lChild;
        T2 = x->rChild;
        T3 = z->rChild;
    } else {
        a = z;
        b = x;
        c = y;
        T0 = z->lChild;
        T1 = x->lChild;
        T2 = x->rChild;
        T3 = y->rChild;
    }

    // 3. z를 루트로 하는 부트리를 b를 루트로 하는 부트리로 대체
    if (z == *root) {
        *root = b;
        b->parent = NULL;
    } else if (z->parent->lChild == z) {
        z->parent->lChild = b;
        b->parent = z->parent;
    } else {
        z->parent->rChild = b;
        b->parent = z->parent;
    }

    //4. T0와 T1을 각각 a의 왼쪽 및 오른쪽 부트리로 만든다
    a->lChild = T0;
    a->rChild = T1;
    T0->parent = a;
    T1->parent = a;
    updateHeight(a);

    //5. T2와 T3를 각각 c의 왼쪽 및 오른쪽 부트리로 만든다
    c->lChild = T2;
    c->rChild = T3;
    T2->parent = c;
    T3->parent = c;
    updateHeight(c);

    //6. a와 c를 각각 b의 왼쪽 및 오른쪽 자식으로 만든다
    b->lChild = a;
    b->rChild = c;
    a->parent = b;
    c->parent = b;
    updateHeight(b);

}
void searchAndFixAfterInsertion(Node** root, Node* w) {
    Node *z = w;
    // root면 return
    if (z == *root) return;

    // 1. w에서 루트로 향해 올라가다가 처음 만나는 불균형 노드 설정
    z = z->parent;
    while (updateHeight(z) && isBalanced(z)) {
        if (z == *root) return;
        z = z->parent;
    }
    // 루트에 다다를 때까지 불균형 노드가 없다면 return
    if (isBalanced(z)) return;

    // 2. z의 높은 자식을 y로 설정
    Node *y;
    if (z->lChild->height > z->rChild->height) y = z->lChild;
    else y = z->rChild;

    // 3. y의 높은 자식을 x로 설정
    Node *x;
    if (y->lChild->height > y->rChild->height) x = y->lChild;
    else x = y->rChild;

    // 4. restructure(x, y, z)
    restructure(x, y, z, root);
}
void insertItem(Node** root, int key) {
    Node *w = treeSearch(*root, key);
    if (!isExternal(w)) printf("invalid!\n");
    w->key = key;
    expandExternal(w);
    searchAndFixAfterInsertion(root, w);
}
void printTree(Node* w) {
    if (isExternal(w)) return;
    printf(" %d", w->key);
    printTree(w->lChild);
    printTree(w->rChild);
}
int findElement(Node* root, int key) {
    Node *w = treeSearch(root, key);
    if (isExternal(w)) return -1;
    else return w->key;
}
int main() {
    Node *root = getNode();
    char order;
    int key;
    while (1) {
        scanf("%c", &order);
        if (order == 'i') {
            scanf("%d", &key);
            insertItem(&root, key);
        }
        else if (order == 'd') {

        }
        else if (order == 's') {
            scanf("%d", &key);
            int tmp = findElement(root, key);
            if (tmp == -1) printf("X\n");
            else printf("%d\n", tmp);
        }
        else if (order == 'p') {
            printTree(root);
            printf("\n");
        }
        else if (order == 'q') {
            break;
        }
        getchar();
    }
}