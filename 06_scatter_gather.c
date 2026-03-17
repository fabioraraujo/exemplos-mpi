/*
 * 06_scatter_gather.c - Scatter e Gather
 * Distribui um array com MPI_Scatter, cada processo dobra seus valores,
 * e MPI_Gather coleta os resultados.
 *
 * Compilar: mpicc -o 06_scatter_gather 06_scatter_gather.c
 * Executar: mpiexec -np 4 ./06_scatter_gather
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ELEMENTOS_POR_PROC 4

int main(int argc, char *argv[]) {
    int rank, size;
    int *dados = NULL;
    int *resultado = NULL;
    int local[ELEMENTOS_POR_PROC];
    int local_resultado[ELEMENTOS_POR_PROC];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int total = size * ELEMENTOS_POR_PROC;

    if (rank == 0) {
        dados = malloc(total * sizeof(int));
        resultado = malloc(total * sizeof(int));

        printf("Array original: ");
        for (int i = 0; i < total; i++) {
            dados[i] = i + 1;
            printf("%d ", dados[i]);
        }
        printf("\n\n");
    }

    /* Distribui partes iguais do array para cada processo */
    MPI_Scatter(dados, ELEMENTOS_POR_PROC, MPI_INT,
                local, ELEMENTOS_POR_PROC, MPI_INT,
                0, MPI_COMM_WORLD);

    /* Cada processo dobra seus valores */
    printf("Processo %d recebeu: ", rank);
    for (int i = 0; i < ELEMENTOS_POR_PROC; i++) {
        printf("%d ", local[i]);
        local_resultado[i] = local[i] * 2;
    }
    printf("-> dobrando -> ");
    for (int i = 0; i < ELEMENTOS_POR_PROC; i++)
        printf("%d ", local_resultado[i]);
    printf("\n");

    /* Coleta os resultados de volta no processo 0 */
    MPI_Gather(local_resultado, ELEMENTOS_POR_PROC, MPI_INT,
               resultado, ELEMENTOS_POR_PROC, MPI_INT,
               0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nArray resultado (dobrado): ");
        for (int i = 0; i < total; i++)
            printf("%d ", resultado[i]);
        printf("\n");

        free(dados);
        free(resultado);
    }

    MPI_Finalize();
    return 0;
}
