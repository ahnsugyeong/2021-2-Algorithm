#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    char ID[9];
    char name[21];
    struct Node *next;
}Node;

Node *getNode(){
    Node* newNode=  (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    return newNode;
}

Node* insertData(Node *p, char *ID, char *name){
    Node* q = getNode();

    strcpy(q->ID, ID);
    strcpy(q->name, name);

    p->next = q;
    return q;
}
Node* merge(Node* L1, Node* L2){
    Node* p = L1;
    L1 = L1->next;
    Node* H = p;

    while(L1!=NULL){
        p->next = L1;
        L1 = L1->next;
        p = p->next;
    }
    while(L2!=NULL){
        p->next = L2;
        L2 = L2->next;
        p = p->next;
    }

    return H;
}
Node* mg_partition(Node *L, int k) {
    Node *L2;
    for (int i = 1; i < k; i++)
        L = L->next;
    L2 = L->next;
    L->next = NULL;
    return L2;
}

void findID(Node* L, int N, char *who, Node** res){
    if(N == 1) {
        if(strcmp(who, L->ID)==0) *res = L;
        return;
    }

    Node *L1, *L2;
    int k = N / 2;

    L1 = L;
    L2 = mg_partition(L, k);

    findID(L1, k, who, res);
    findID(L2, N-k, who, res);

    return;
}

int main(){
    int N;
    scanf("%d", &N);
    Node *H = getNode();
    Node*p = H;

    char name[21];
    char ID[9];

    for(int i=0;i<N;i++){
        scanf("%s %s", ID, name);
        p = insertData(p, ID, name);
    }

    char who[9];
    scanf("%s", who);
    p = H->next;

    Node* res = NULL;
    findID(p, N, who, &res);


    if(res == NULL) printf("-1\n");
    else printf("%s %s\n", res->ID, res->name);

    Node *tmp;
    p = H;
    while(p!=NULL){
        tmp = p;
        p = p->next;
        free(tmp);
    }

    return 0;
}