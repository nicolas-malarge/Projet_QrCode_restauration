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
# define Client "client.tube"
# define Server "server.tube"

int main () { 

    

    char buffer [ BUFFER_SIZE ];

    // Creation du premier pipe nomme
    int result = mkfifo ( Client , 0777) ;
    printf("%d" , result);
    if ( result != 0) {
        printf ( " Ne peut cree ’%s ’\n " , Client ) ;
        printf("%d", errno);
        return 0;
    }

 // Creation du second pipe nomme
    result = mkfifo ( Server , O_RDONLY) ;
    if ( result != 0) {
        printf ( " Ne peut cree ’%s ’\n " , Server ) ;
        return 0;
    }

// Ouverture en lecture du premier pipe
    int fd_in = open ( Client , O_RDONLY ) ;
    if ( fd_in == -1) {
        printf ( " Ne peut ouvrir ’%s ’\n " , Client ) ;
        return 0;
    }

// Lecture bloquante sur le premier pipe
    result = read ( fd_in , buffer , BUFFER_SIZE ) ;
    if ( result < 0) {
        printf ( " Ne peut lire ’%s ’\n  ", Client ) ;
        return 0;
    }
    printf ( " Recu : ’%s' \n " , buffer ) ;

// Ouverture en ecriture du second pipe
    int fd_out = open ( Server , O_WRONLY ) ;
    if ( fd_out == -1) {
        printf ( " Ne peut ouvrir ’%s’\n " , Server ) ;
        return 0;
    }

// Ecriture sur le second pipe
    result = write ( fd_out , buffer , result ) ;
    if ( result < 0) {
        printf ( " Ne peut ecrire ’%s’\n " , Server ) ;
        return 0;
    }
}