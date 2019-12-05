all: main.o
	gcc -o shellTest main.o

main.o: main.c
	gcc -c main.c

run:
		./shellTest

clean:
	rm *.o
	rm *~
