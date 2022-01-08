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

int findElement(Node* root, int key) {
    Node *w = treeSearch(root, key);
    if (isExternal(w)) return -1;
    else return w->key;
}

void expandExternal(Node* w) {
    w->lChild = getNode();
    w->rChild = getNode();
    w->lChild->parent = w;
    w->rChild->parent = w;
}

Node* sibling(Node* z){
    if(z->parent->lChild == z) return z->parent->rChild;
    else return z->parent->lChild;
}

Node* reduceExternal(Node* z, Node** root) {
    Node *w = z->parent;
    Node *zs = sibling(z);
    if (w == *root) {
        zs->parent = NULL;
        *root = zs;
    }
    else {
        Node *g = w->parent;
        zs->parent = g;

        if (g->lChild == w) g->lChild = zs;
        else g->rChild = zs;
    }
    free(z);
    free(w);
    return zs;
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

Node* restructure(Node* x, Node* y, Node* z, Node** root) {
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

    return b;
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

void searchAndFixAfterRemoval(Node* w, Node** root) {
    Node *z = w;
    // 1. w에서 루트로 향해 올라가다가 처음 만나는 불균형 노드 설정
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

    // 3. y의 자식 중 하나를 x라 하자. y의 두 자식 중 어느 한쪽이 높으면 높은 자식을 x라 하고, 두 자식의 높이가 같으면 둘 중 y와 같은 쪽의 자식을 x로 선택.
    Node *x;
    if (y->lChild->height > y->rChild->height) x = y->lChild;
    else if (y->lChild->height < y->rChild->height) x = y->rChild;
    else {
        if (z->lChild == y)x = y->lChild;
        else x = y->rChild;
    }

    // 4. b = restructure(x, y, z)
    // 수행 후, 높이균형 속성은, 방금 전 z를 루트로 했으나 이젠 변수 b를 루트로 하는 부트리에서 '지역적'으로 복구된다.
    // 하지만, 방금의 개조에 의해 b를 루트로 하는 부트리의 높이가 1 줄어들 수 있으며 이때문에 b의 조상이 균형을 잃을 수 있다.
    // 즉, 삭제 후 1회의 개조만으로는 높이균형 속성을 '전역적'으로 복구하지 못할 수도 있다.
    Node *b = restructure(x, y, z, root);
    if (b == *root) return;

    // b의 부모부터 루트까지 올라가면서 균형을 잃은 노드를 찾아 수리하는 것을 계속한다.
    searchAndFixAfterRemoval(b->parent, root);
}

void insertItem(Node** root, int key) {
    Node *w = treeSearch(*root, key);
    if (!isExternal(w)) return;
    w->key = key;
    expandExternal(w);
    searchAndFixAfterInsertion(root, w);
}

Node* inOrderSucc(Node* w) {
    w = w->rChild;
    if (isExternal(w)) printf("invalid\n");
    while (!isExternal(w->lChild)) {
        w = w->lChild;
    }
    return w;
}
int removeElement(Node** root, int key) {
    Node *w = treeSearch(*root, key);
    if (isExternal(w)) return -1;
    Node *z = w->lChild;
    if (!isExternal(z)) z = w->rChild;
    Node *zs;
    if (isExternal(z)) zs = reduceExternal(z, root);
    else {
        Node *y = inOrderSucc(w);
        z = y->lChild;
        w->key = y->key;
        zs = reduceExternal(z, root);
    }
    searchAndFixAfterRemoval(zs->parent, root);
    return key;
}

void printTree(Node* w) {
    if (isExternal(w)) return;
    printf(" %d", w->key);
    printTree(w->lChild);
    printTree(w->rChild);
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
            scanf("%d", &key);
            int tmp = removeElement(&root, key);
            if (tmp == -1) printf("X\n");
            else printf("%d\n", tmp);
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