all: main

main: main.c server.o client.o
	gcc -o main main.c server.o client.o

server.o: server.c
	gcc -c server.c

client.o: client.c
	gcc -c client.c

clear:
	rm -f *.o main