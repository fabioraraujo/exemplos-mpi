# Exemplos MPI - Programação Distribuída e Paralela

Códigos de exemplo em C para a disciplina **Programação Distribuída e Paralela** do CESUPA, baseados no material "Programação Paralela com Memória Distribuída: Desvendando o MPI".

## Pré-requisitos

- Compilador C (gcc)
- Implementação MPI instalada (Open MPI ou MPICH)

### Instalação do MPI

**macOS (Homebrew):**
```bash
brew install open-mpi
```

**Ubuntu/Debian:**
```bash
sudo apt install openmpi-bin libopenmpi-dev
```

**Fedora/RHEL:**
```bash
sudo dnf install openmpi openmpi-devel
```

## Exemplos

| # | Arquivo | Conceito | Funções MPI |
|---|---------|----------|-------------|
| 1 | `01_hello_mpi.c` | Hello World MPI | `MPI_Init`, `MPI_Finalize`, `MPI_Comm_rank`, `MPI_Comm_size` |
| 2 | `02_send_recv.c` | Comunicação ponto a ponto | `MPI_Send`, `MPI_Recv`, `MPI_Status` |
| 3 | `03_soma_cadeia.c` | Soma distribuída em cadeia | `MPI_Send`, `MPI_Recv` (padrão pipeline) |
| 4 | `04_calculo_pi.c` | Cálculo de π com redução | `MPI_Reduce`, `MPI_SUM` |
| 5 | `05_broadcast.c` | Broadcast de configuração | `MPI_Bcast` |
| 6 | `06_scatter_gather.c` | Distribuição e coleta de dados | `MPI_Scatter`, `MPI_Gather` |

## Compilação

Compilar todos os exemplos de uma vez:
```bash
make
```

Compilar um exemplo individual:
```bash
mpicc -Wall -O2 -o 01_hello_mpi 01_hello_mpi.c
```

Limpar binários:
```bash
make clean
```

## Execução

Executar com N processos usando `mpiexec`:
```bash
mpiexec -np 4 ./01_hello_mpi
mpiexec -np 2 ./02_send_recv
mpiexec -np 4 ./03_soma_cadeia
mpiexec -np 4 ./04_calculo_pi
mpiexec -np 4 ./05_broadcast
mpiexec -np 4 ./06_scatter_gather
```

> **Nota:** O exemplo `02_send_recv.c` requer no mínimo 2 processos.

## Descrição dos Exemplos

### 01 - Hello World MPI
Introdução ao MPI. Cada processo identifica seu rank (ID) e o número total de processos no comunicador `MPI_COMM_WORLD`.

### 02 - Comunicação Ponto a Ponto
O Processo 0 envia o valor `42` para o Processo 1 usando `MPI_Send`/`MPI_Recv`. Demonstra o uso de tags, tipos de dados MPI e `MPI_Status`.

### 03 - Soma Distribuída em Cadeia
Implementação do Exercício 1 do PDF. Os processos formam uma cadeia: o processo *i* recebe a soma parcial do processo *i-1*, adiciona seu rank e envia para *i+1*. O último processo imprime a soma final, que deve ser `N*(N-1)/2`.

### 04 - Cálculo de π
Implementação do Exercício 2 do PDF. Usa a fórmula de Leibniz (`π/4 = 1 - 1/3 + 1/5 - ...`) com os termos distribuídos entre processos. `MPI_Reduce` com `MPI_SUM` agrega as somas parciais no processo raiz.

### 05 - Broadcast de Configuração
Implementação do Exercício 3 do PDF. O processo 0 define parâmetros de configuração (iterações, tolerância, modo verbose) e `MPI_Bcast` distribui para todos os processos.

### 06 - Scatter e Gather
Demonstra operações coletivas de distribuição e coleta. `MPI_Scatter` divide um array igualmente entre os processos, cada um dobra seus valores, e `MPI_Gather` reúne os resultados no processo 0.

## Estrutura do Projeto

```
scripts/
├── 01_hello_mpi.c
├── 02_send_recv.c
├── 03_soma_cadeia.c
├── 04_calculo_pi.c
├── 05_broadcast.c
├── 06_scatter_gather.c
├── Makefile
└── README.md
```

## Referência

- Material: *Programação Paralela com Memória Distribuída: Desvendando o MPI*
- [Open MPI Documentation](https://www.open-mpi.org/doc/)
- [MPI Standard](https://www.mpi-forum.org/docs/)

## Licença

Material educacional para uso na disciplina de Programação Distribuída e Paralela - CESUPA.

---
Prof. Fábio Araújo - CESUPA
