CC=gcc
CFLAGS=-W -Wall

all: ExecutableServer ExecutableData ExecutableClient

ExecutableServer: server.o
	$(CC) -o ExecutableServer server.o

ExecutableData: data.o
	$(CC) -o ExecutableData data.o

ExecutableClient: client.o
	$(CC) -o ExecutableClient client.o

server.o :
	$(CC) -o server.o -c server.c $(CFLAGS)

data.o :
	$(CC) -o data.o -c data.c $(CFLAGS)

client.o :
  $(CC) -o client.o -c client.c $(CFLAGS)

clean:
	rm -f *.o ExecutableServer ExecutableData ExecutableClient
