/*
 * 04_calculo_pi.c - Cálculo de π com MPI_Reduce
 * Exercício 2 do PDF: fórmula de Leibniz distribuída entre processos.
 * π/4 = 1 - 1/3 + 1/5 - 1/7 + ...
 * Cada processo calcula parte dos termos e MPI_Reduce agrega com MPI_SUM.
 *
 * Compilar: mpicc -o 04_calculo_pi 04_calculo_pi.c -lm
 * Executar: mpiexec -np 4 ./04_calculo_pi
 */
#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define NUM_TERMOS 1000000

int main(int argc, char *argv[]) {
    int rank, size;
    double soma_local = 0.0;
    double soma_global = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* Cada processo calcula os termos que lhe correspondem */
    for (long i = rank; i < NUM_TERMOS; i += size) {
        double sinal = (i % 2 == 0) ? 1.0 : -1.0;
        soma_local += sinal / (2.0 * i + 1.0);
    }

    printf("Processo %d: soma local = %.10f\n", rank, soma_local);

    /* Reduz todas as somas parciais para o processo 0 */
    MPI_Reduce(&soma_local, &soma_global, 1, MPI_DOUBLE, MPI_SUM, 0,
               MPI_COMM_WORLD);

    if (rank == 0) {
        double pi_estimado = 4.0 * soma_global;
        printf("\nResultado com %d termos e %d processos:\n", NUM_TERMOS, size);
        printf("  π estimado  = %.15f\n", pi_estimado);
        printf("  π real      = %.15f\n", M_PI);
        printf("  Erro        = %.2e\n", fabs(pi_estimado - M_PI));
    }

    MPI_Finalize();
    return 0;
}
