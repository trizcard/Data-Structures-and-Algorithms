all: main.o binaryTree.o
	gcc -O3 -march=native -lm -o prog.exe main.o binaryTree.o binaryTree.h

run:
	./prog.exe

main.o: main.c
	gcc -O3 -march=native -lm -o main.o -c main.c

binaryTree.o: binaryTree.c binaryTree.h
	gcc -lm -o binaryTree.o -c binaryTree.c 

clean:
	rm -f *.exe *.o
