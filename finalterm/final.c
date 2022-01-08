//  222.109.199.24
#include <stdio.h>
#include <stdlib.h>


typedef struct node {

    int data;
    struct node *left;
    struct node *right;
    int height;

} NODE;


NODE *newNode(int data) {

    NODE *node = (NODE *) malloc(sizeof(NODE));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return (node);

}

int isExternal(NODE* w){
    if(w->left == NULL && w->right == NULL) return 1;
    else return 0;
}
NODE* treeSearch(NODE* v, int key){
    if(isExternal(v)|| v->data == key) return v;
    if(v->data > key) return treeSearch(v->left, key);
    else return treeSearch(v->right, key);
}
void updateHeight(NODE* w){
    if(isExternal(w->left) || isExternal(w->right)) return;
    updateHeight(w->left);
    updateHeight(w->right);
    if(w->left->height > w->right->height) w->height = w->left->height+1;
    else w->height = w->right->height+1;

}
int isBalanced(NODE* root, int data){
    NODE* w = treeSearch(root, data);

    updateHeight(w);

    if(!isExternal(w)) {
        int gap = w->left->height - w->right->height;
        if (gap >= -1 && gap <= 1) return 1;
        else {
            return 0;
        }
    }
    else return 1;
}

int main() {

    int n, data;
    NODE *root = NULL;
    scanf("%d %d", &n, &data);    // 트리 번호 , 키값
    if (n == 1) {

// No. 1

        root = newNode(4);
        root->left = newNode(2);
        root->right = newNode(5);
        root->left->left = newNode(1);
        root->left->right = newNode(3);


    } else if (n == 2) {

// No. 2

        root = newNode(5);
        root->left = newNode(2);
        root->left->left = newNode(1);
        root->left->right = newNode(4);

    } else if (n == 3) {

// No. 3

        root = newNode(3);
        root->left = newNode(2);
        root->right = newNode(7);
        root->right->left = newNode(6);
        root->right->left->left = newNode(5);


    }

    printf("%d", isBalanced(root, data));







    return 0;

}

