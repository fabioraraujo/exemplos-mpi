/*
 * 05_broadcast.c - Broadcast de Configuração
 * Exercício 3 do PDF: processo 0 define parâmetros e MPI_Bcast distribui.
 *
 * Compilar: mpicc -o 05_broadcast 05_broadcast.c
 * Executar: mpiexec -np 4 ./05_broadcast
 */
#include <stdio.h>
#include <mpi.h>

typedef struct {
    int num_iteracoes;
    double tolerancia;
    int modo_verbose;
} Configuracao;

int main(int argc, char *argv[]) {
    int rank, size;
    Configuracao config;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        /* Processo 0 define os parâmetros de configuração */
        config.num_iteracoes = 1000;
        config.tolerancia = 0.001;
        config.modo_verbose = 1;
        printf("Processo 0: configuração definida.\n");
        printf("  - Iterações: %d\n", config.num_iteracoes);
        printf("  - Tolerância: %f\n", config.tolerancia);
        printf("  - Verbose: %d\n\n", config.modo_verbose);
    }

    /* Broadcast de cada campo para todos os processos */
    MPI_Bcast(&config.num_iteracoes, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&config.tolerancia, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&config.modo_verbose, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Processo %d: recebeu iterações=%d, tolerância=%f, verbose=%d\n",
           rank, config.num_iteracoes, config.tolerancia, config.modo_verbose);

    MPI_Finalize();
    return 0;
}
