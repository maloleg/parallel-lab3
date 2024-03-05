#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void add_matrices(double* A, double* B, double* C, int start, long long int end) {
    for (long long int i = start; i < end; ++i) {
        C[i] = A[i] + B[i];
    }
}

void subtract_matrices(double* A, double* B, double* C, int start, long long int end) {
    for (long long int i = start; i < end; ++i) {
        C[i] = A[i] - B[i];
    }
}

int main(int argc, char *argv[]) {
    long long int N = 20000;
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int chunk_size = N*N / size;
    double *A, *B, *C;

    if (rank == 0) {
        A = (double*)malloc(N * N * sizeof(double));
        B = (double*)malloc(N * N * sizeof(double));
        C = (double*)malloc(N * N * sizeof(double));
        for (int i = 0; i < N * N; ++i) {
            A[i] = i;
            B[i] = N * N - i;
        }
    } else {
        A = (double*)malloc(chunk_size * sizeof(double));
        B = (double*)malloc(chunk_size * sizeof(double));
        C = (double*)malloc(chunk_size * sizeof(double));
    }

    MPI_Scatter(A, chunk_size, MPI_DOUBLE, A, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(B, chunk_size, MPI_DOUBLE, B, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double start_time_add = MPI_Wtime();
    add_matrices(A, B, C, 0, chunk_size);
    double end_time_add = MPI_Wtime();
    if (rank == 0) {
        printf("Time for matrix addition with MPI: %f seconds.\n", end_time_add - start_time_add);
    }

    double start_time = MPI_Wtime();
    subtract_matrices(A, B, C, 0, chunk_size);
    double end_time = MPI_Wtime();
    if (rank == 0) {
        printf("Time for matrix subtraction with MPI: %f seconds.\n", end_time - start_time);
    }

    free(A);
    free(B);
    free(C);

    MPI_Finalize();
    return 0;
}
