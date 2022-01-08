#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {
    int a, b, N;
    scanf("%d %d %d", &a, &b, &N);
    char *str = (char *) malloc(sizeof(char) * (N + 1));
    scanf("%s", str);
    int i = 0;
    while (a != b) {
        int tmp = (a + b) / 2;
        if (str[i] == 'N') {
            b = tmp;
            i++;
        } else if (str[i] == 'Y') {
            a = tmp + 1;
            i++;
        }
    }
    printf("%d", a);
    return 0;
}
