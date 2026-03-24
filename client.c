# include <arpa/inet.h> // for inet_addr
# include <netinet/in.h> // for sockaddr_in , htons , IPPROTO_TCP , in_addr
# include <stdio.h>
// for printf
# include <sys/socket.h> // for connect , socket , AF_INET , SOCK_STREAM
# include <unistd.h>// for close
# define NB_CLIENTS 2
# define IP "127.0.0.3"
# define PORT 8080

int main () {
    struct sockaddr_in adresse ;
        adresse.sin_family = AF_INET ;
        // IPv4
        adresse.sin_addr.s_addr = inet_addr ( IP ) ; // L adresse du serveur
        adresse.sin_port = htons ( PORT ) ;
    // Le port sur le serveur
    int fdsocket = socket ( AF_INET , SOCK_STREAM , IPPROTO_TCP ) ; // TCP
    if ( fdsocket == -1) {
        return 0;
    }

    int result = connect ( fdsocket , ( struct sockaddr *) & adresse , sizeof( adresse ) ) ;
    if ( result != 0) {
        return 0;
    }
    printf (" Connecte \n") ;
    close ( fdsocket ) ;
}