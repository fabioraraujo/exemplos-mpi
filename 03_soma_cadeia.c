/*
 * 03_soma_cadeia.c - Soma Distribuída em Cadeia
 * Exercício 1 do PDF: processo i recebe de i-1, soma seu rank e envia para i+1.
 * O último processo imprime a soma final = N*(N-1)/2.
 *
 * Compilar: mpicc -o 03_soma_cadeia 03_soma_cadeia.c
 * Executar: mpiexec -np 4 ./03_soma_cadeia
 */
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int soma = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        /* Processo 0 inicia a cadeia com seu próprio rank (0) */
        soma = rank;
        printf("Processo %d: iniciando cadeia com soma = %d\n", rank, soma);
        MPI_Send(&soma, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    } else {
        /* Recebe a soma parcial do processo anterior */
        MPI_Recv(&soma, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        soma += rank;
        printf("Processo %d: soma parcial = %d\n", rank, soma);

        if (rank < size - 1) {
            /* Envia para o próximo processo */
            MPI_Send(&soma, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        } else {
            /* Último processo imprime o resultado final */
            int esperado = size * (size - 1) / 2;
            printf("\nProcesso %d (último): soma final = %d\n", rank, soma);
            printf("Valor esperado N*(N-1)/2 = %d*(%d-1)/2 = %d\n",
                   size, size, esperado);
        }
    }

    MPI_Finalize();
    return 0;
}
