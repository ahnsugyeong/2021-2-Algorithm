#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int *x, int N){
    for(int i = 1 ; i < N ; i++){
        int tmp = x[i];
        int j = i - 1;
        while(j >= 0 && x[j] > tmp){
            x[j + 1] = x[j];
            j--;
        }
        x[j + 1] = tmp;
    }
}

int main(){
    int N;
    scanf("%d", &N);
    int *x = (int *)malloc(sizeof(int)*N);
    for(int i = 0 ; i < N ; i++)
        scanf("%d", &x[i]);
    insertionSort(x, N);
    for(int i = 0 ; i < N ; i++)
        printf(" %d", x[i]);
    return 0;
}