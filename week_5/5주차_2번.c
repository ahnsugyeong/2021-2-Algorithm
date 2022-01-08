#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int findPivotIndex(int *L, int l, int r){
    srand(time(NULL));
    int a = rand() % (r - l + 1) + l;
    int b = rand() % (r - l + 1) + l;
    int c = rand() % (r - l + 1) + l;
    if ((L[b] >= L[a] && L[a] >= L[c]) || (L[c] >= L[a] && L[a] >= L[b])) return a;
    else if ((L[a] >= L[b] && L[b] >= L[c]) || (L[c] >= L[b] && L[b] >= L[a])) return b;
    else if ((L[a] >= L[c] && L[c] >= L[b]) || (L[b] >= L[c] && L[c] >= L[a])) return c;
}
int inPlacePartition(int *L, int l, int r, int k) {
    int pivot = L[k];
    int tmp;
    tmp = L[k];
    L[k] = L[r];
    L[r] = tmp;
    int i = l, j = r - 1;
    while (i <= j) {
        while (i <= j && L[i] <= pivot)
            i++;
        while (j >= i && L[j] >= pivot)
            j--;
        if (i < j) {
            tmp = L[i];
            L[i] = L[j];
            L[j] = tmp;
        }
    }
    tmp = L[i];
    L[i] = L[r];
    L[r] = tmp;
    return i;
}
void inPlaceQuickSort(int *L, int l, int r) {
    if (l >= r) return;
    int k = findPivotIndex(L, l, r);
    int pivot = inPlacePartition(L, l, r, k);
    inPlaceQuickSort(L, l, pivot - 1);
    inPlaceQuickSort(L, pivot + 1, r);
}
int main() {
    int N;
    scanf("%d", &N);
    int *L = (int *) malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &L[i]);
    }
    inPlaceQuickSort(L, 0, N - 1);
    for (int i = 0; i < N; i++) {
        printf(" %d", L[i]);
    }

    return 0;
}
