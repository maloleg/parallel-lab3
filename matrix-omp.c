#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h> //OpenMP

void add_matrices(double *A, double *B, double *C, long long int n) {
    #pragma omp parallel for // Директива для распараллеливания цикла
    for (long long int i = 0; i < n*n; ++i) {
        C[i] = A[i] + B[i];
    }
}

void subtract_matrices(double *A, double *B, double *C, long long int n) {
    #pragma omp parallel for // Директива для распараллеливания цикла
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

    double start_time, end_time;

    start_time = omp_get_wtime();
    add_matrices(A, B, C, N);
    end_time = omp_get_wtime();
    printf("Time for matrix addition with OpenMP: %.2f seconds.\n", end_time - start_time);

    start_time = omp_get_wtime();
    subtract_matrices(A, B, C, N);
    end_time = omp_get_wtime();
    printf("Time for matrix subtraction with OpenMP: %.2f seconds.\n", end_time - start_time);

    free(A);
    free(B);
    free(C);

    return 0;
}
