#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    int key;
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

int isExternal(Node* w){
    if(w->lChild == NULL && w->rChild == NULL) return 1;
    else return 0;
}

Node* treeSearch(Node* v, int key){
    if(isExternal(v)) return v;
    if(v->key == key) return v;
    if(v->key > key) return treeSearch(v->lChild, key);
    else return treeSearch(v->rChild, key);
}
int findElement(Node* root, int key){
    Node* w = treeSearch(root, key);
    if(isExternal(w)) return -1;
    else return w->key;
}
void expandExternal(Node* w){
    w->lChild = getNode();
    w->rChild = getNode();
    w->lChild->parent = w;
    w->rChild->parent = w;
}
void insertItem(Node* root, int key){
    Node* w = treeSearch(root, key);
    if(!isExternal(w)) return;
    else {
        w->key = key;
        expandExternal(w);
        return;
    }
}
int isRoot(Node* p){
    if(p->parent == NULL) return 1;
    else return 0;
}
/*Node* sibling(Node* w){
    if(isRoot(w)) printf("invalid!\n");
    if(w->parent->lChild == w) return w->parent->rChild;
    else return w->parent->lChild;
}
Node* reduceExternal(Node* z, Node** root){
    Node* w = z->parent;
    Node* zs = sibling(z);
    if(isRoot(w)){
        *root = zs;
        zs->parent = NULL;
    }
    else{
        Node* g = w->parent;
        zs->parent = g;
        if(w == g->lChild) g->lChild = zs;
        else g->rChild = zs;
    }
    free(z);
    free(w);
    return zs;
}
Node* inOrderSucc(Node* w){
    w = w->rChild;
    if(isExternal(w)) printf("invalid\n");
    while(!isExternal(w->lChild)) w = w->lChild;
    return w;

}
int removeElement(Node** root, int key){
    Node* w = treeSearch(*root, key);
    if(isExternal(w)) return -1;
    int k = key;

    //Case 1: 자식 둘 중 하나라도 외부노드이면
    Node* z = w->lChild;
    if(!isExternal(z)) z = w->rChild;

    //해당 노드(w)와 외부노드인 자식(z)까지 전부 reduceExternal
    if(isExternal(z)) reduceExternal(z, root);

    //Case 2: 자식들이 전부 내부노드라면?
    else{
        // 중위순회 계승자 y(w의 오른쪽 부트리 내 노드 중 가장 왼쪽으로 돌출된 내부노드)와 그의 왼쪽 자식인 z
        Node* y = inOrderSucc(w);
        z = y->lChild;
        w->key = y->key;
        //y와 z를 삭제
        redceExternal(z, root);
    }
    return k;
}
 */
Node* sibling(Node* z){
    if(z->parent->lChild == z) return z->parent->rChild;
    else return z->parent->lChild;
}
void reduceExternal(Node* z, Node** root){
    Node* w = z->parent;
    Node* zs = sibling(z);
    if(w==*root){
        zs->parent = NULL;
        *root = zs;
    }
    else{
        Node* g = w->parent;
        zs->parent = g;
        if(g->lChild == w) g->lChild = zs;
        else g->rChild = zs;
    }
    free(z);
    free(w);
}

Node* inOrderSucc(Node* w){
    w = w->rChild;
    if(isExternal(w)) printf("invalid!\n");
    else{
        while(!isExternal(w->lChild)) w = w->lChild;
    }
    return w;
}

int removeElement(Node** root, int key){
    Node* w = treeSearch(*root, key);
    if(isExternal(w)) return -1;
    int k = w->key;
    //Case 1: 둘 중에 하나가 외부노드라면
    Node* z = w->lChild;
    if(!isExternal(z)) z = w->rChild;
    if(isExternal(z))reduceExternal(z, root);
    //Case 2: 둘 다 내부노드라면
    else{
        Node* y = inOrderSucc(w);
        w->key = y->key;
        Node* z = y->lChild;
        reduceExternal(z, root);
    }

    return k;
}

void printTree(Node* w){
    if(isExternal(w)) return;
    printf(" %d", w->key);
    printTree(w->lChild);
    printTree(w->rChild);
}
int main(){
    char order;
    int key;
    Node *root = getNode();
    while(1){
        scanf("%c", &order);
        if(order == 'i'){
            scanf("%d", &key);
            insertItem(root, key);
        }
        else if(order == 'd'){
            scanf("%d", &key);
            int tmp = removeElement(&root, key);
            if(tmp == -1) printf("X\n");
            else printf("%d\n", tmp);
        }
        else if(order == 's'){
            scanf("%d", &key);
            int tmp = findElement(root, key);
            if(tmp == -1) printf("X\n");
            else printf("%d\n", tmp);
        }
        else if(order == 'p'){
            printTree(root);
            printf("\n");
        }
        else if(order == 'q'){
            break;
        }


        getchar();
    }
    return 0;
}