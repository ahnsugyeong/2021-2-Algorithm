#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    char data[11];
    struct Node *next;
}Node;

typedef struct Stack {
    Node* top;
}Stack;

Node* getNode(){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    return newNode;
}
void Push(Stack* s, char c[]) {
    Node* p = getNode();
    strcpy(p->data, c);
    p->next = s->top;
    s->top = p;
}
char* Pop(Stack* s) {
    char *e = (char*)malloc(sizeof(char)*11);
    strcpy(e, s->top->data);
    Node* p = s->top;
    s->top = s->top->next;
    free(p);
    return e;
}
int main() {
    Stack s;
    s.top = NULL;
    char order[11];
    while (1) {
        scanf("%s", order);
        if (strcmp(order, "*") == 0) break;
        Push(&s, order);
    }
    while(s.top != NULL) {
        printf("%s\n", Pop(&s));
    }
}
