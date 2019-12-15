all: main.o functions.o
	gcc -o shellTest main.o functions.o

main.o: main.c
	gcc -c main.c

functions.o: functions.c headers.h
	gcc -c functions.c

run:
		./shellTest


clean:
	rm *.o
	rm *~
