all: main

main: main.c server.o
	gcc -o main main.c server.o

server.o: server.c
	gcc -c server.c.

clear:
	rm -f *.o main