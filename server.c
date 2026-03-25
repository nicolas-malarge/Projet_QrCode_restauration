#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
// for open , O_RDONLY , O_WRONLY
// for printf
// for mkfifo
// for read , write
# define BUFFER_SIZE 512
# define ServerE "ServerE.tube"
# define ClientS "clientS.tube"


int main () {
    char buffer [ BUFFER_SIZE ];

    mkfifo(ServerE, 0666);
    mkfifo(ClientS, 0666);

    printf("Serveur en attente du client...\n");

    
    int fd_read = open(ServerE, O_RDONLY);
    read(fd_read, buffer, sizeof(buffer));

    printf("Commande reçue : %s\n", buffer);

    close(fd_read);

    
    int fd_write = open(ClientS, O_WRONLY);

    char *menu = "Menu:\n1. Pizza\n2. Burger\n3. Salade\n";
    write(fd_write, menu, sizeof(menu) + 1);

    close(fd_write);

    return 0;
}