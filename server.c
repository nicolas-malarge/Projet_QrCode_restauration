//serveur.c
#include <pthread.h>
#include <stdlib.h>
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
# define S2C "S2C.tube"
# define C2S "C2S.tube"

# define S2D "S2D.tube"
# define D2S "D2S.tube"



int main () {
    char buffer[4096];

    mkfifo(C2S, 0666);
    mkfifo(S2C, 0666);

    char choix[10];
    //choix[0] = 4;
    int fd_c2s;
    int fd_s2d;
    int fd_d2s;
    int fd_s2c;

    while(1){
        printf("En attente du client...\n");

        fd_c2s = open(C2S, O_RDONLY);
        read(fd_c2s, buffer, sizeof(buffer));
        printf("Le client demande: %s\n", buffer);
        close(fd_c2s);

        if (buffer[0] == '0') {
            printf("Fermeture du serveur.\n");
            break;
        }

        fd_s2d = open(S2D, O_WRONLY);
        write(fd_s2d, buffer, strlen(buffer) + 1);
        close(fd_s2d);

        fd_d2s = open(D2S, O_RDONLY);
        read(fd_d2s, buffer, sizeof(buffer) + 1);
        close(fd_d2s);

        fd_s2c = open(S2C, O_WRONLY);
        write(fd_s2c, buffer, strlen(buffer) + 1);
        close(fd_s2c);

        printf(" Menu transmis au client.\n");
    }
    
    return 0;
}
