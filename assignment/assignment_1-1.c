#include <stdio.h>

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
int lastInternal(int H[], int N){
    return H[N/2];
}
int main() {
    int H[100] = {0};
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &H[i]);
    if (isMinHeap(H, N)) printf("Yes\n");
    else printf("No\n");
    printf("%d\n", lastInternal(H, N));
    return 0;
}