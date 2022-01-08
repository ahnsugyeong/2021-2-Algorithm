#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int findKey(int *x, int k, int l, int r, int max) {
    if (l > r) return max;
    int mid = (l + r) / 2;
    if (k >= x[mid]) {
        if (x[max] < x[mid]) max = mid;
        return findKey(x, k, mid + 1, r, max);
    }
    else return findKey(x, k, l, mid - 1, max);
}

int main() {
    int N, key;
    scanf("%d %d", &N, &key);
    int *x = (int *) malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", &x[i]);
    int tmp = findKey(x, key, 0, N - 1, 0);
    if (tmp == 0 && x[0]!=key) printf(" -1");
    else printf(" %d", tmp);

    return 0;
}
