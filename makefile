all: main.e

main.e: main.o func.o
	gcc -o main.e main.o func.o -lm
main.o: main.c func.h
	gcc -o main.o -c main.c
func.o: func.c func.h
	gcc -o func.o -c func.c

clean:
	rm -f *.o
