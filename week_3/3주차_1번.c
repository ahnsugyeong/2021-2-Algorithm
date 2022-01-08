#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void downHeap(int H[], int i, int n){
    if (i * 2 > n) return;
    int bigger;
    if (H[i * 2] > H[i * 2 + 1]) bigger = i * 2;
    else bigger = i * 2 + 1;
    if (H[i] >= H[bigger]) return;
    int tmp = H[i];
    H[i] = H[bigger];
    H[bigger] = tmp;
    downHeap(H, bigger, n);
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
void printHeap(int H[], int n){
    for(int i = 1 ;i <= n ;i++)
        printf(" %d", H[i]);
    printf("\n");
}
int main(){
    int n, H[100] = {0};
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++){
        scanf("%d", &H[i]);
    }
    buildHeap(H, n);
    printHeap(H, n);
    return 0;
}