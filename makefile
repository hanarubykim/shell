all: main.o
	gcc -o shellTest main.o

main.o: main.c headers.h
	gcc -c main.c

run:
		./shellTest
		

clean:
	rm *.o
	rm *~
