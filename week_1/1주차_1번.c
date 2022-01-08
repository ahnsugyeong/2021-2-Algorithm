#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void invalid_position(){
    printf("invalid position\n");
}
typedef struct Node{
    char ele;
    struct Node *next;
    struct Node *prev;
}Node;

Node* getNode(){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void add(Node *header, int r, char e){  //삽입
    Node *q = getNode();
    q->ele = e;
    Node *p = header;
    while(r--) p = p->next;
    q->prev = p->prev;
    q->next = p;
    p->prev->next = q;
    p->prev = q;
}
void print(Node *header, Node *trailer){   //출력(순회)
    Node *p = header->next;
    while(p != trailer) {   //헤더노드에서 트레일러노드 만날 떄까지 순회
        printf("%c", p->ele);
        p = p->next;
    }
}
void delete(Node *header, int r){   //삭제
    Node *p = header;
    while(r--) p = p->next;
    Node *tmp = p;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(tmp);  //putNode
}
char get(Node *header, int r){  //순회
    Node *p = header;
    while(r--) p = p->next;
    return p->ele;
}
int main(){
    Node *header; Node *trailer;
    header = getNode();
    trailer = getNode();
    // 헤더노드와 트레일러노드 연결 (초기화)
    header->next = trailer;
    trailer->prev = header;
    int N;
    int size = 0;
    scanf("%d", &N);
    char order;
    int r; char e;
    while(N--){
        getchar();
        scanf("%c", &order);
        if (order == 'A'){  // (삽입)
            scanf("%d %c", &r, &e);
            if (r > size + 1) invalid_position();   // 순위 정보가 유효하지 않을 경우
            else {
                add(header, r, e);
                size++; // 크기 증가
            }
        }
        if (order == 'D'){  // (삭제)
            scanf("%d", &r);
            if (r > size) invalid_position();   // 순위 정보가 유효하지 않을 경우
            else {
                delete(header, r);
                size--; // 크기 감소
            }
        }
        if (order == 'G'){  // (순회)
            scanf("%d", &r);
            if (r > size) invalid_position();   // 순위 정보가 유효하지 않을 경우
            else {
                printf("%c\n", get(header, r));
            }

        }
        else if (order == 'P'){
            print(header, trailer);
            printf("\n");
        }

    }
}
