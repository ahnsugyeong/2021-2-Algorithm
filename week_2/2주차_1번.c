#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int *x, int N){
    int max, max_index;
    for(int i = N - 1 ; i > 0 ; i--){
        max = x[i];
        max_index = i;
        for(int j = 0 ; j < i ; j++){
            if (max < x[j]){
                max = x[j];
                max_index = j;
            }
        }
        int tmp = x[max_index];
        x[max_index] = x[i];
        x[i] = tmp;
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