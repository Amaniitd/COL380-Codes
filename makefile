test: test.c
	mpicc test.c -o test
run: test
	mpirun -np 2 ./test