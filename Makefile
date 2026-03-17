CC = mpicc
CFLAGS = -Wall -O2

PROGRAMS = 01_hello_mpi 02_send_recv 03_soma_cadeia 04_calculo_pi 05_broadcast 06_scatter_gather

all: $(PROGRAMS)

01_hello_mpi: 01_hello_mpi.c
	$(CC) $(CFLAGS) -o $@ $<

02_send_recv: 02_send_recv.c
	$(CC) $(CFLAGS) -o $@ $<

03_soma_cadeia: 03_soma_cadeia.c
	$(CC) $(CFLAGS) -o $@ $<

04_calculo_pi: 04_calculo_pi.c
	$(CC) $(CFLAGS) -o $@ $< -lm

05_broadcast: 05_broadcast.c
	$(CC) $(CFLAGS) -o $@ $<

06_scatter_gather: 06_scatter_gather.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(PROGRAMS)

.PHONY: all clean
