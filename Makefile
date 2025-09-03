all: term_chat

term_chat: main.c server.o client.o
	gcc -o term_chat main.c server.o client.o

server.o: server.c
	gcc -c server.c

client.o: client.c
	gcc -c client.c

clear:
	rm -f *.o term_chat