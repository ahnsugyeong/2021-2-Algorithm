#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    char e[11];
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct Que{
    Node *front;
    Node *rear;
}Que;

Node* getNode(){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}
int isEmpty(Que* q){
    if (q->front == NULL) return 1;
    else return 0;
}

void initQue(Que* q){
    q->front = NULL;
    q->rear = NULL;
}
void reverse(char *str) {
    char *p, *q;
    for (p = str, q = str + strlen(str) - 1; p < q; p++, q--) {
        char tmp;
        tmp = *p;
        *p = *q;
        *q = tmp;
    }
}
void enqueue(Que* q, char e[]){
    reverse(e);
    Node* p = getNode();
    strcpy(p->e, e);
    if (isEmpty(q)){
        q->front = p;
        q->rear = p;
    }
    else {
        q->rear->next = p;
        p->prev = q->rear;
        q->rear = p;
    }
}

void dequeue(Que *q, char *str){
    strcpy(str, q->front->e);
    if (q->front->next == NULL) q->rear = NULL;
    else q->front = q->front->next;
    q->front->prev = NULL;
}

int main(){
    Que q;
    initQue(&q);
    char order[11];
    while(1){
        scanf("%s", order);
        if (strcmp(order, "*")==0) break;
        enqueue(&q, order);
    }
    char *str = (char*)malloc(sizeof(char)*11);
    while(q.rear != NULL){
        dequeue(&q, str);
        printf("%s\n", str);
    }
    return 0;
}
