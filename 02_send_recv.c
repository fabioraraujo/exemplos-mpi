/*
 * 02_send_recv.c - Comunicação Ponto a Ponto
 * Processo 0 envia um valor inteiro para Processo 1 usando MPI_Send/MPI_Recv.
 *
 * Compilar: mpicc -o 02_send_recv 02_send_recv.c
 * Executar: mpiexec -np 2 ./02_send_recv
 */
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int valor = 42;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0)
            printf("Este programa requer pelo menos 2 processos.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        printf("Processo 0: enviando valor %d para Processo 1...\n", valor);
        MPI_Send(&valor, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Processo 0: valor enviado com sucesso.\n");
    } else if (rank == 1) {
        int recebido;
        MPI_Recv(&recebido, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Processo 1: recebi o valor %d do Processo %d (tag=%d).\n",
               recebido, status.MPI_SOURCE, status.MPI_TAG);
    }

    MPI_Finalize();
    return 0;
}
