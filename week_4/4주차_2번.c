#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isRoot(int i){
    if (i == 1) return 1;
    else return 0;
}

void upHeap(int H[], int i){
    if (isRoot(i)) return;
    if (H[i] <= H[i / 2]) return;
    int tmp = H[i];
    H[i] = H[i / 2];
    H[i / 2] = tmp;
    upHeap(H, i / 2);
}
int insertItem(int H[], int *n, int key){
    *n += 1;
    H[*n] = key;
    upHeap(H, *n);
}

void downHeap(int H[], int i, int n){
    if (i * 2 > n) return;
    int bigger = i * 2;
    if (i * 2 + 1 <= n){
        if (H[bigger] < H[i * 2 + 1])
            bigger = i * 2 + 1;
    }
    if (H[bigger] <= H[i]) return;

    int tmp = H[i];
    H[i] = H[bigger];
    H[bigger] = tmp;

    downHeap(H, bigger, n);
}

void printArray(int H[], int n){
    for(int i = 1 ; i <= n ; i++){
        printf(" %d", H[i]);
    }
    printf("\n");
}

void inPlaceHeapSort(int H[], int n){
    if (n == 0) return;
    int tmp = H[n];
    H[n] = H[1];
    H[1] = tmp;
    n--;
    downHeap(H, 1, n);
    inPlaceHeapSort(H, n);
}
int main(){
    int H[100] = {0};
    int N;
    int n=0;
    scanf("%d", &N);
    int key;
    for(int i=0;i<N;i++){
        scanf("%d", &key);
        insertItem(H, &n, key);
    }
    inPlaceHeapSort(H, n);
    printArray(H, n);
    return 0;
}
