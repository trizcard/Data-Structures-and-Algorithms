all: main.o AVL.o
	gcc -O3 -march=native -lm -o prog.exe main.o AVL.o AVL.h

run:
	./prog.exe

main.o: main.c
	gcc -O3 -march=native -lm -o main.o -c main.c

AVL.o: AVL.c AVL.h
	gcc -lm -o AVL.o -c AVL.c 

clean:
	rm -f *.exe *.o
