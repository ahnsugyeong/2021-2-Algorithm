#include <stdio.h>
#include <stdlib.h>

int h(int x, int M){
    return x % M;
}

int getNextBucket(int v, int i, int M){
    return (v + i) % M;
}
void insertItem(int* H, int k, int M){
    int index;
    for(int i=0;i<M;i++) {
        index = getNextBucket(h(k, M), i, M);
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

int searchItem(int* H, int k, int M){
    int index;
    for(int i=0;i<M;i++) {
        index = getNextBucket(h(k, M), i, M);
        if(H[index]==k){
            return index;
        }
    }
    return -1;
}

int main(){
    int M, n;
    scanf("%d %d", &M, &n);
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
            insertItem(H, k, M);

        }
        else if(order == 's'){
            scanf("%d", &k);
            int tmp = searchItem(H, k, M);
            if(tmp == -1) printf("-1\n");
            else{
                printf("%d %d\n", tmp, k);
            }
        }
        else if(order == 'e'){
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

int getNextBucket(int v, int i, int M){
    return (v+i)%M;
}
void insertItem(int *H, int M, int x){
    int v = h(x, M);
    int i=0;
    while(i<M){
        int b = getNextBucket(v, i, M);
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

int searchItem(int *H, int M, int x) {
    int v = h(x, M);
    int i=0;
    while(i<M){
        int b = getNextBucket(v, i, M);
        if(H[b]==0) return -1;
        else if(H[b]==x) return b;
        else i++;
    }
    return -1;
}

int main() {
    int M;
    int n;
    int q;
    scanf("%d %d", &M, &n);
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
            insertItem(H, M, key);
        }
        else if (order == 's') {
            scanf("%d", &key);
            int tmp = searchItem(H, M, key);
            if(tmp == -1) printf("-1\n");
            else printf("%d %d\n", tmp, key);
        }
        else if (order == 'e') {
            free(H);
            break;
        }
        getchar();
    }
    return 0;
}*/