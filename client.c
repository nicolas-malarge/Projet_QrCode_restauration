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

int main () {
    char buffer[512];

    int fd_out = open(C2S, O_WRONLY);
    char *msg = "Afficher le menu svp";
    write(fd_out, msg, strlen(msg) + 1);
    close(fd_out);

    int fd_in = open(S2C, O_RDONLY);
    read(fd_in, buffer, sizeof(buffer));
    printf("[CLIENT] Menu reçu :\n%s\n", buffer);
    close(fd_in);
    
    // char buffer[512];
    // char myFOOD[30];

    
    // int fd_write = open(S2C, O_WRONLY);

    // if ( fd_write == -1) {
    //     printf ( " Ne peut ouvrir ’%s’\n " , S2C ) ;
    //     return 0;
    // }

    // char * message = "Voir le menu";
    // printf("%ld", sizeof(message) );
    // write(fd_write, message, strlen(message));

    // close(fd_write);

    
    // int fd_read = open(C2S, O_RDONLY);
    // read(fd_read, buffer, sizeof(buffer));

    // printf("Réponse du serveur :\n%s\n", buffer);

    // close(fd_read);
    //int fd_write2 = open(S2C, O_WRONLY);

    //if ( fd_write == -1) {
        //printf ( " Ne peut ouvrir ’%s’\n " , S2C ) ;
        //return 0;
    //}

    //scanf("%ld", &myFOOD);
    //write(fd_write2, myFOOD, strlen(myFOOD));

    //close(fd_write2);

    return 0;
}