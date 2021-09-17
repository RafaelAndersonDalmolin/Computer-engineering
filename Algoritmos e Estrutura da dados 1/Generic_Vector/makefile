# Makefile
all: Main

Main: vector.o Main.o
	gcc -o Main vector.o Main.o

vector.o: vector.c
	gcc -c vector.c

Main.o: Main.c
	gcc -c Main.c

clean:
	rm -rf *.o
    
run: Main
	./Main