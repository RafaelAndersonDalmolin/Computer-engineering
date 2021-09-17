# Makefile
all: Main

Main: vector.o stack.o Main.o
	gcc -o Main vector.o stack.o Main.o

vector.o: vector.c
	gcc -c vector.c

stack.o: stack.c
	gcc -c stack.c

Main.o: Main.c
	gcc -c Main.c

clean:
	rm -rf *.o
    
run: Main
	./Main
