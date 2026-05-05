#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define S2C "S2C.tube"
#define C2S "C2S.tube"
#define S2D "S2D.tube"
#define D2S "D2S.tube"

int main () {
    char buffer[512]; 

    //créer les tubes pour communiquer avec data et client
    mkfifo(C2S, 0666);
    mkfifo(S2C, 0666);
    mkfifo(S2D, 0666);
    mkfifo(D2S, 0666);

    int fd_c2s;
    int fd_s2d;
    int fd_d2s;
    int fd_s2c;

    //permet de laisser tourner data même après la gestion des clients.
    while(1) {
        printf("\n En attente du client...\n");

        //ouvre et lit la sortie du tube venant de client
        fd_c2s = open(C2S, O_RDONLY);
        read(fd_c2s, buffer, sizeof(buffer));
        printf("Le client demande: %s\n", buffer);

        //fait passer la requête à data pour la traiter
        fd_s2d = open(S2D, O_WRONLY);
        write(fd_s2d, buffer, strlen(buffer) + 1);

        //lit ce que data renvoie (la requête traitée)
        fd_d2s = open(D2S, O_RDONLY);
        read(fd_d2s, buffer, sizeof(buffer));

        //envoie au client le menu correspondant à sa requête.
        fd_s2c = open(S2C, O_WRONLY);
        write(fd_s2c, buffer, strlen(buffer) + 1);

        printf("Menu transmis au client.\n");

        //on ferme les tubes nommés
        close(fd_c2s);
        close(fd_s2d);
        close(fd_d2s);
        close(fd_s2c);
    }
    
    return 0;
}
