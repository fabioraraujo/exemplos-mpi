/*
 * 01_hello_mpi.c - Hello World MPI
 * Demonstra inicialização/finalização do MPI, MPI_Comm_rank e MPI_Comm_size.
 *
 * Compilar: mpicc -o 01_hello_mpi 01_hello_mpi.c
 * Executar: mpiexec -np 4 ./01_hello_mpi
 */
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Olá! Eu sou o processo %d de %d processos.\n", rank, size);

    MPI_Finalize();
    return 0;
}
