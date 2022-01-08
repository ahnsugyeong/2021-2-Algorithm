#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* getNode(){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    return newNode;
}
Node* mg_partition(Node* L1, int k){
    Node* L2;
    for(int i = 0 ; i < k - 1 ; i++){
        L1 = L1->next;
    }
    L2 = L1->next;
    L1->next = NULL;
    return L2;
}
Node* merge(Node* L1, Node* L2){
    Node* p;
    if (L1->data <= L2->data){
        p = L1;
        L1 = L1->next;
    }
    else{
        p = L2;
        L2 = L2->next;
    }
    Node* H = p;
    while(L1!=NULL&&L2!=NULL){
        if (L1->data < L2->data){
            p->next = L1;
            L1 = L1->next;
        }
        else{
            p->next = L2;
            L2 = L2->next;
        }
        p = p->next;
    }

    if (L1 != NULL) p->next = L1;
    else p->next = L2;

    return H;
}

Node* mergeSort(Node* L, int N){
    if (N == 1) return L;
    Node* L1, *L2;
    int k = N / 2;
    L1 = L;
    L2 = mg_partition(L, k);
    L1 = mergeSort(L1, k);
    L2 = mergeSort(L2, N - k);
    return merge(L1, L2);
}

Node* insertData(Node* p, int data){
    Node* q = getNode();
    q->data = data;
    p->next = q;
    return q;
}

int main() {
    int N;
    scanf("%d", &N);
    Node *H = getNode();
    Node *p = H;
    for (int i = 0; i < N; i++) {
        int data;
        scanf("%d", &data);
        p = insertData(p, data);
    }
    p = H->next;
    p = mergeSort(p, N);

    for (int i = 0; i < N; i++) {
        printf("%d ", p->data);
        p = p->next;
    }
    p = H;
    while (H != NULL) {
        p = H;
        H = H->next;
        free(p);
        p = NULL;
    }
    free(p);
    free(H);
    return 0;
}