#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)

void selectionSort(int* x, int N) {
    int max, max_index;
    for (int i = N - 1; i > 0; i--) {
        max = x[i];
        max_index = i;
        for (int j = 0; j < i; j++) {
            if (max < x[j]) {
                max = x[j];
                max_index = j;
            }
        }
        int tmp = x[max_index];
        x[max_index] = x[i];
        x[i] = tmp;
    }
}

void insertionSort(int* x, int N) {
    for (int i = 1; i < N; i++) {
        int tmp = x[i];
        int j = i - 1;
        while (j >= 0 && x[j] > tmp) {
            x[j + 1] = x[j];
            j--;
        }
        x[j + 1] = tmp;
    }
}
void reverseSort(int* x, int N) {
    int min, min_index;
    for (int i = N - 1; i > 0; i--) {
        min = x[i];
        min_index = i;
        for (int j = 0; j < i; j++) {
            if (min > x[j]) {
                min = x[j];
                min_index = j;
            }
        }
        int tmp = x[min_index];
        x[min_index] = x[i];
        x[i] = tmp;
    }
}
int main() {
    int N;
    scanf("%d", &N);
    int* A = (int*)malloc(sizeof(int) * N);
    int* B = (int*)malloc(sizeof(int) * N);

    srand(time(NULL));

    //난수로 배열 초기화 (1 ~ 100 사이의 수)
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 100 + 1;
        B[i] = A[i];
    }

    /* 미리 정렬 시키기
    selectionSort(A, N);
    selectionSort(B, N);
    */

    /* 미리 역순 정렬 시키기
    reverseSort(A, N);
    reverseSort(B, N);
    */

    LARGE_INTEGER ticksPerSec;
    QueryPerformanceFrequency(&ticksPerSec);

    LARGE_INTEGER start_A, end_A, diff_A;
    QueryPerformanceCounter(&start_A);
    selectionSort(A, N);
    QueryPerformanceCounter(&end_A);
    diff_A.QuadPart = end_A.QuadPart - start_A.QuadPart;
    printf("선택 정렬 수행 시간 : %.12f sec\n", ((double)diff_A.QuadPart / (double)ticksPerSec.QuadPart));

    LARGE_INTEGER start_B, end_B, diff_B;
    QueryPerformanceCounter(&start_B);
    insertionSort(B, N);
    QueryPerformanceCounter(&end_B);
    diff_B.QuadPart = end_B.QuadPart - start_B.QuadPart;
    printf("삽입 정렬 수행 시간 : %.12f sec\n", ((double)diff_B.QuadPart / (double)ticksPerSec.QuadPart));

    return 0;
}