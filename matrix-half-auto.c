#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void add_matrices(double *A, double *B, double *C, long long int n) {
    for (long long int i = 0; i < n*n; ++i) {
        C[i] = A[i] + B[i];
    }
}

void subtract_matrices(double *A, double *B, double *C, long long int n) {
    for (long long int i = 0; i < n*n; ++i) {
        C[i] = A[i] - B[i];
    }
}

int main() {
    long long int N = 20000;

    double *A = (double*)aligned_alloc(32, N*N*sizeof(double));
    double *B = (double*)aligned_alloc(32, N*N*sizeof(double));
    double *C = (double*)aligned_alloc(32, N*N*sizeof(double));

    for (long long int i = 0; i < N*N; ++i) {
        A[i] = i;
        B[i] = N*N - i;
    }

        clock_t start_time, end_time;

    start_time = clock();
    add_matrices(A, B, C, N);
    end_time = clock();
    printf("Time for matrix addition: %.2f seconds.\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    start_time = clock();
    subtract_matrices(A, B, C, N);
    end_time = clock();
    printf("Time for matrix subtraction: %.2f seconds.\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    free(A);
    free(B);
    free(C);

    return 0;
}
