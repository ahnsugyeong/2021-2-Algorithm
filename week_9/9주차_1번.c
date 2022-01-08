#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node* next;
}Node;

int h(int x, int M){
    return x % M;
}

Node* getNode(int k){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->key = k;
    return newNode;
}

void insertItem(Node* H, int k, int M){
    int i = h(k, M);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = k;
    Node* p = &H[i];
    newNode->next = p->next;
    p->next = newNode;
    return;
}

int searchItem(Node* H, int k, int M){
    int key = 0;
    int i = h(k, M);
    Node* p = H[i].next;
    while(p != NULL) {
        key++;
        if (p->key == k) return key;
        p = p->next;
    }
    return 0;
}

int removeItem(Node* H, int k, int M){
    int i = h(k, M);
    int result = searchItem(H, k, M);
    if(result == 0) return result;

    Node* p = &H[i];
    while(p->next->key != k){
        p = p->next;
    }

    Node* tmp = p->next;
    p->next = p->next->next;
    free(tmp);
    return result;
}

void printItem(Node* H, int M){
    Node* p;
    for(int i=0;i<M;i++){
        p = H[i].next;
        while(p != NULL){
            printf(" %d", p->key);
            p = p->next;
        }
    }
    printf("\n");
    return;
}

int main(){
    int M;
    scanf("%d", &M);
    getchar();
    Node *H = (Node*)malloc(sizeof(Node)*M);
    for(int i=0;i<M;i++)
        H[i].next = NULL;
    char order;
    int k;
    while(1){
        scanf("%c", &order);
        if(order == 'i'){
            scanf("%d", &k);
            insertItem(H, k, M);
        }
        else if(order == 's'){
            scanf("%d", &k);
            printf("%d\n", searchItem(H, k, M));
        }
        else if(order == 'd'){
            scanf("%d", &k);
            printf("%d\n", removeItem(H, k, M));
        }
        else if(order == 'p'){
            printItem(H, M);
        }
        else if(order == 'e') {
            free(H);
            break;
        }
        getchar();
    }

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node* next;
}Node;

Node* getNode(){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    return newNode;
}
int h(int x, int M) {
    return x % M;
}
void insertItem(Node* H, int x, int M){
    Node* newNode = getNode();
    newNode->key = x;
    int v = h(x, M);
    newNode->next = H[v].next;
    H[v].next = newNode;
}

int searchItem(Node* H, int x, int M) {
    int v = h(x, M);
    Node *p = H[v].next;
    int cnt = 0;
    while (p != NULL) {
        cnt++;
        if (p->key == x) return cnt;
        p = p->next;

    }
    return 0;
}

int removeItem(Node* H, int x, int M){
    int v = h(x, M);
    int cnt = searchItem(H, x, M);
    if(cnt == 0) return 0;

    Node *p = &H[v];
    for(int i=0;i<cnt-1;i++){
        p = p->next;
    }
    Node* tmp = p->next;
    p->next = p->next->next;
    free(tmp);

    return cnt;
}
void printTable(Node* H, int M){
    Node* p;
    for(int i=0;i<M;i++){
        p = H[i].next;
        while(p != NULL){
            printf(" %d", p->key);
            p = p->next;
        }
    }
    printf("\n");
}
int main(){
    int M;
    scanf("%d", &M);
    getchar();
    Node* H = (Node *)malloc(sizeof(Node)*M);
    char order;
    int key;
    while(1){
        scanf("%c", &order);
        if(order == 'i'){
            scanf("%d", &key);
            insertItem(H, key, M);
        }
        else if(order == 's'){
            scanf("%d", &key);
            int tmp = searchItem(H, key, M);
            printf("%d\n", tmp);
        }
        else if(order == 'd'){
            scanf("%d", &key);
            int tmp = removeItem(H, key, M);
            printf("%d\n", tmp);
        }
        else if(order == 'p'){
            printTable(H, M);
        }
        else if(order == 'e'){
            break;
        }
        getchar();
    }
    return 0;
}
 */