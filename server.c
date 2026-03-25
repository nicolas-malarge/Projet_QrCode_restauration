#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
// for open , O_RDONLY , O_WRONLY
// for printf
// for mkfifo
// for read , write
# define BUFFER_SIZE 512
# define S2C "S2C.tube"
# define C2S "C2S.tube"

# define S2D "S2D.tube"
# define D2S "D2S.tube"


int main () {
    char buffer [ BUFFER_SIZE ];

    mkfifo(S2C, 0666);
    mkfifo(C2S, 0666);
    mkfifo(S2D, 0666);
    mkfifo(D2S, 0666);

    printf("Serveur en attente du client...\n");

    
    int fd_read = open(S2C, O_RDONLY);
    if ( fd_read == -1) {
        printf ( " Ne peut ouvrir ’%s ’\n " , S2C ) ;
        return 0;
    }
    read(fd_read, buffer, sizeof(&buffer));

    printf("Commande reçue : %s\n", buffer);

    close(fd_read);

    
    int fd_write = open(C2S, O_WRONLY);

    char *menu = "Menu:\n1. Le classique\n2. Burger country\n3. Buffalo\n4. Le Royal \n5. Le Burkid\n";
    write(fd_write, menu, strlen(menu));

    close(fd_write);

    return 0;
}