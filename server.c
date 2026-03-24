# include <netinet/in.h> // for sockaddr_in , htons , INADDR_ANY , IPPROTO_TCP
# include <stdio.h>
// for printf
# include <sys/socket.h> // for accept , bind , listen , socket , AF_INET , SOCK_ ...
# define NB_CLIENTS 2
# define IP INADDR_ANY
# define PORT 8080
# define BACKLOG 3

int main () {
    int clients [ NB_CLIENTS ];
    // Initialise adresse
    struct sockaddr_in adresse ;
    adresse.sin_family = AF_INET ;
    // IPv4
    adresse.sin_addr.s_addr = IP ;
    // L adresse eccoute
    adresse.sin_port = htons ( PORT ) ; // Le port ecoute
    // Creation de la socket
    int fdsocket = socket( AF_INET , SOCK_STREAM ,  IPPROTO_TCP ) ; // TCP
    if ( fdsocket == -1) {
        return 0;
    }
    // Attache la socket au port
    int result = bind (fdsocket , (struct sockaddr*) &adresse , sizeof(adresse ));
    if ( result != 0) {
        return 0;
    }
    // Ecoute sur la socket
    result = listen ( fdsocket , BACKLOG ) ;
    if ( result != 0) {
        return 0;
    }
    struct sockaddr_in client_adresse ;
    int taille = sizeof ( client_adresse ) ;
    // Attend une connexion
    int client = accept( fdsocket , ( struct sockaddr *) &client_adresse , ( socklen_t *) &taille );
    if ( client == -1) {
        return 0;
}
    printf (" Connexion \n") ;
    close ( client ) ;
    close ( fdsocket ) ;
}