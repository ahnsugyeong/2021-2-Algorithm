#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    char c_ID[11];
    char c_name[21];
    char ID[9];
    struct Node *next;
}Node;

Node *getNode(){
    Node* newNode=  (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    return newNode;
}

Node* mg_partition(Node *L1, int k) {
    Node *L2;
    for (int i = 1; i < k; i++)
        L1 = L1->next;
    L2 = L1->next;
    L1->next = NULL;
    return L2;
}

Node *merge(Node* L1, Node* L2) {
    /*
    * (초기) 과목 ID 비교해서 사전순으로 더 앞선 노드를 p가 가리키게 하기
    * 안정성을 위하여 첫 번째 if문에 등호를 넣어줌
    */
    Node *p;
    if (strcmp(L1->c_ID, L2->c_ID) <= 0) {
        p = L1;
        L1 = L1->next;
    }
    else {
        p = L2;
        L2 = L2->next;
    }

    /*
    * 과목 ID 비교해서 사전순으로 더 앞선 노드를 p가 가리키게 하기
    * 안정성을 위하여 첫 번째 if문에 등호를 넣어줌
    */
    Node *H = p;
    while (L1 != NULL && L2 != NULL) {
        if (strcmp(L1->c_ID, L2->c_ID) <= 0) {
            p->next = L1;
            L1 = L1->next;
        }
        else {
            p->next = L2;
            L2 = L2->next;
        }
        p = p->next;
    }

    // 남은 노드까지 다 붙여주기
    if (L1 != NULL) p->next = L1;
    else p->next = L2;

    return H;
}

Node* mergeSort(Node* L, int N){
    // base case
    if(N == 1) return L;


    //L을 L1과 L2로 나누기
    Node *L1, *L2;
    int k = N / 2;

    L1 = L;
    L2 = mg_partition(L, k);

    // 재귀적 합병정렬 구현
    L1 = mergeSort(L1, k);
    L2 = mergeSort(L2, N-k);

    // 합치기
    return merge(L1, L2);
}

Node* insertData(Node *p, char *c_ID, char *c_name, char *ID){
    // 새로운 노드에 메모리 할당 후 데이터 삽입하기
    Node* q = getNode();
    strcpy(q->c_ID,c_ID);
    strcpy(q->c_name,c_name);
    strcpy(q->ID, ID);

    // 전 노드에 새로운 노드 이어 붙이기
    p->next = q;
    return q;
}

int main(){
    int N;
    scanf("%d", &N);
    Node *H = getNode();
    Node*p = H;

    char c_ID[11];
    char c_name[21];
    char ID[9];

    // 데이터 삽입
    for(int i=0;i<N;i++){
        scanf("%s %s %s", c_ID, c_name, ID);
        p = insertData(p, c_ID, c_name, ID);
    }

    // 합병 정렬
    p = H->next;
    p = mergeSort(p, N);
    for(int i=0;i<N;i++){
        printf("%s %s %s\n", p->c_ID, p->c_name, p->ID);
        p = p->next;
    }

    // 메모리 해제
    Node *tmp;
    p = H;
    while(p!=NULL){
        tmp = p;
        p = p->next;
        free(tmp);
    }

    return 0;
}
