VERSION=\"v0.0.1\"
CC = gcc
NNLS_CFLAGS = -O3 -s -mtune=native -Wall -lm -lz -DVERSION=$(VERSION)

all: nnls_solver

nnls_solver:
	$(CC) nnls_solver.c nnls.c -o nnls_solver $(NNLS_CFLAGS)
clean:
	rm -vf nnls_solver 
