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
    char buffer[100];

    
    int fd_write = open(ServerE, O_WRONLY);

    if ( fd_write == -1) {
        printf ( " Ne peut ouvrir ’%s’\n " , ServerE ) ;
        return 0;
    }

    char *message = "Voir le menu";
    write(fd_write, message, sizeof(message) + 1);

    close(fd_write);

    
    int fd_read = open(ClientS, O_RDONLY);
    read(fd_read, buffer, sizeof(buffer));

    printf("Réponse du serveur :\n%s\n", buffer);

    close(fd_read);

    return 0;
}