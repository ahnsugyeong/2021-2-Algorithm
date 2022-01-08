#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int findKey(int *x, int k, int l, int r) {
    int min;
    int flag = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (k <= x[mid]) {
            if (flag == 0) {
                min = mid;
                flag = 1;
            } else if (x[min] > x[mid]) {
                min = mid;
            }
            r = mid - 1;
        } else l = mid + 1;
    }
    if (flag == 0) return -1;
    else return min;
}

int main() {
    int N, key;
    scanf("%d %d", &N, &key);
    int *x = (int *) malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", &x[i]);
    int result = findKey(x, key, 0, N - 1);
    if (result == -1) printf(" %d", N);
    else printf(" %d", result);
    return 0;
}
