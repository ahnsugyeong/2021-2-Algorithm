#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void downHeap(int H[], int i, int n){
    if (i * 2 > n) return;
    int smaller = i * 2;
    if (i * 2 + 1 <= n){
        if (H[smaller] > H[i * 2 + 1])
            smaller = i * 2 + 1;
    }
    if (H[smaller] >= H[i]) return;

    int tmp = H[i];
    H[i] = H[smaller];
    H[smaller] = tmp;

    downHeap(H, smaller, n);
}

void rBuildHeap(int H[], int i, int  n){
    if (i > n) return;
    rBuildHeap(H, i * 2, n);
    rBuildHeap(H, i * 2 + 1, n);
    downHeap(H, i, n);
}
void buildHeap(int H[], int n){
    for(int i = n / 2 ; i > 0 ; i--) downHeap(H, i, n);
}
void insertionSort(int *x, int N){
    for(int i = 2 ; i <= N ; i++){
        int tmp = x[i];
        int j = i - 1;
        while(j >= 1 && x[j] > tmp){
            x[j + 1] = x[j];
            j--;
        }
        x[j + 1] = tmp;
    }
}
int isMinHeap(int H[], int N) {
    for (int i = 1; i <= N / 2; i++) {
        if (H[i * 2 + 1] != 0) {
            if (H[i] > H[i * 2] || H[i] > H[i * 2 + 1]) return 0;
        } else {
            if (H[i] > H[i * 2]) return 0;
        }
    }
    return 1;
}
int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    int *H = (int *)malloc(sizeof(int)*(K+1));
    for(int i=1;i<=K;i++)
        scanf("%d", &H[i]);
    int tmp;
    for(int i = K+1;i<=N;i++) {


        scanf("%d", &tmp);
        if(!isMinHeap(H, i))buildHeap(H, K);
        if (H[1] < tmp) {
            H[1] = tmp;
        }
    }

    insertionSort(H, K);

    for(int i=1;i<=K;i++)
        printf(" %d", H[i]);
    free(H);
    return 0;
}
