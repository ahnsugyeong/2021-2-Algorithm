#include <stdio.h>
#include <stdlib.h>

int h(int x, int M){
    return x % M;
}
int h2(int x, int q){
    return q - (x % q);
}

int getNextBucket(int i, int x, int M, int q){
    return (h(x, M) + i*h2(x, q)) % M;
}
void insertItem(int* H, int k, int M, int q){
    int index;
    for(int i=0;i<M;i++) {
        index = getNextBucket(i, k, M, q);
        if(H[index]==0){
            H[index] = k;
            printf("%d\n", index);
            return;
        }
        else{
            printf("C");
        }
    }
}

int searchItem(int* H, int k, int M, int q){
    int index;
    for(int i=0;i<M;i++) {
        index = getNextBucket(i, k, M, q);
        if(H[index]==k){
            return index;
        }
    }
    return -1;
}

void printItem(int* H, int M){
    for(int i=0;i<M;i++){
        printf(" %d", H[i]);
    }
    printf("\n");
}

int main(){
    int M, n, q;
    scanf("%d %d %d", &M, &n, &q);
    getchar();
    int* H = (int*)malloc(sizeof(int)*M);
    for(int i=0;i<M;i++){
        H[i] = 0;
    }

    char order;
    int k;
    while(1){
        scanf("%c", &order);
        if(order == 'i'){
            scanf("%d", &k);
            insertItem(H, k, M, q);

        }
        else if(order == 's'){
            scanf("%d", &k);
            int tmp = searchItem(H, k, M, q);
            if(tmp == -1) printf("-1\n");
            else{
                printf("%d %d\n", tmp, k);
            }
        }
        else if(order == 'p'){
            printItem(H, M);
        }
        else if(order == 'e'){
            printItem(H, M);
            free(H);
            break;
        }
        getchar();
    }
    return 0;
}

/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int h(int x, int M) {
    return x % M;
}
int h2(int x, int q) {
    return q - (x % q);
}
int getNextBucket(int v, int i, int M, int x, int q){
    return (v+i*h2(x, q))%M;
}
void insertItem(int *H, int M, int x, int q){
    int v = h(x, M);
    int i=0;
    while(i<M){
        int b = getNextBucket(v, i, M, x, q);
        if(H[b]==0) {
            H[b] = x;
            printf("%d\n", b);
            return;
        }
        else {
            printf("C");
            i++;
        }
    }
}

int searchItem(int *H, int M, int x, int q) {
    int v = h(x, M);
    int i=0;
    while(i<M){
        int b = getNextBucket(v, i, M, x, q);
        if(H[b]==0) return -1;
        else if(H[b]==x) return b;
        else i++;
    }
    return -1;
}
void printTable(int *H, int M){
    for(int i=0;i<M;i++)
        printf(" %d", H[i]);
    printf("\n");
}
int main() {
    int M;
    int n;
    int q;
    scanf("%d %d %d", &M, &n, &q);
    getchar();
    int *H = (int *) malloc(sizeof(int) * M);
    for (int i = 0; i < M; i++)
        H[i] = 0;
    char order;
    int key;
    while (1) {
        scanf("%c", &order);
        if (order == 'i') {
            scanf("%d", &key);
            insertItem(H, M, key, q);
        }
        else if (order == 's') {
            scanf("%d", &key);
            int tmp = searchItem(H, M, key, q);
            if(tmp == -1) printf("-1\n");
            else printf("%d %d\n", tmp, key);
        }
        else if(order == 'p'){
            printTable(H, M);
        }
        else if (order == 'e') {
            printTable(H, M);
            free(H);
            break;
        }
        getchar();
    }
    return 0;
}
 */