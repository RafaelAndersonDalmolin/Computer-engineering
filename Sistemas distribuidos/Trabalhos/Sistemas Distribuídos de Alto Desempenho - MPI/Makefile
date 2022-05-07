mpi:
	mpicc Primo_mpi.c -o Primo_mpi -lm

serial:
	mpicc Primo_serial.c -o Primo_serial -lm

clean:
	@echo "Limpando projeto"
	@rm -f Primo*.o
run_mpi:

	mpirun --oversubscribe -np 16 ./Primo_mpi
.PHONY: clean
