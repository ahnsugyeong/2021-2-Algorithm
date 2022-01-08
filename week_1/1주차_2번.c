#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
}Node;

Node* getNode(){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}
Node* findData(Node *p, int data){  //특정 data값을 가진 노드 탐색하기
    if (p != NULL) {
        if (p->data == data) return p;
        Node *q = NULL;
        q = findData(p->left, data);
        if (q != NULL) return q;
        q = findData(p->right, data);
        if (q != NULL) return q;
    }
    return NULL;
}

int main(){
    int N;
    scanf("%d", &N);
    int data, l, r;
    // 트리 만들기
    Node *root = getNode();
    for(int i = 0 ; i < N ; i++){
        scanf("%d %d %d", &data, &l, &r);
        if (i == 0){    // 초기 root노드 설정
            root->data = data;  // findData 할 필요 없이 root노드에 바로 값 대입
            if (l != 0) {  // 값이 존재하면 공간을 할당한 후 data 넣기
                root->left = getNode();
                root->left->data = l;
            }
            if (r != 0) {
                root->right = getNode();
                root->right->data = r;
            }
        }
        else{
            Node *p = findData(root, data); //data값을 가진 노드 탐색하여 p와 연
            p->data = data;
            if (l != 0) {
                p->left = getNode();
                p->left->data = l;
            }
            if (r != 0) {
                p->right = getNode();
                p->right->data = r;
            }
        }
    }
    // 탐색
    int S;
    scanf("%d", &S);
    char str[101];
    while(S--){
        Node *p = root;
        scanf("%s", str);
        for(int i = 0 ; i < strlen(str); i++){
            printf(" %d", p->data);
            if (str[i] == 'L') p = p->left;
            else if (str[i] == 'R') p = p->right;
        }
        printf(" %d\n", p->data);
    }
    return 0;
}