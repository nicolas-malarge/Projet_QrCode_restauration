CC=gcc
# On ajoute -pthread pour la compilation
CFLAGS=-W -Wall -pthread 

all: ExecutableServer ExecutableData ExecutableClient

ExecutableServer: server.o
	$(CC) -o ExecutableServer server.o -pthread

ExecutableData: data.o
	$(CC) -o ExecutableData data.o -pthread

ExecutableClient: client.o
	$(CC) -o ExecutableClient client.o -pthread

server.o :
	$(CC) -o server.o -c server.c $(CFLAGS)

data.o :
	$(CC) -o data.o -c data.c $(CFLAGS)

client.o :
	$(CC) -o client.o -c client.c $(CFLAGS)
clean:
	rm -f *.o ExecutableServer ExecutableData ExecutableClient
