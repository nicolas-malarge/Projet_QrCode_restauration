#include <stdio.h>
#include <string.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

# define BUFFER_SIZE 512
# define D2S "D2S.tube"
# define S2D "S2D.tube"

struct Serveur {
    int idServeur;
    char nom[30];
};

struct Client {
    int idClient;
    char nom[20];
    char prenom[20];
};

struct Plat {
    int idPlat;
    char plat[30];
    double prix;
};

void afficherMenu(struct Plat pPlat){
    //printf("Menu %s \n", );
    printf("%s......... Prix : %f euros\n", pPlat.plat, pPlat.prix);
}

void ajoutStruct(struct Plat pPlat[], int pId, char* pNomPlat, double pPrix){
    struct Plat vPlat;
    vPlat.idPlat = pId;
    strcpy(vPlat.plat, pNomPlat); 
    vPlat.prix = pPrix;
    pPlat[pId] = vPlat;
}

int main() {
    char buffer[512];
    char *menu = " 1. Classique (14 euros)\n 2. Country (16 euros)\n 3. Buffalo (16 euros)\n ";

    mkfifo(S2D, 0666);
    mkfifo(D2S, 0666);

    printf("En attente de requetes...\n");

    int fd_in = open(S2D, O_RDONLY);
    read(fd_in, buffer, sizeof(buffer));
    printf("[DATA] Reçu du serveur: %s\n", buffer);
    close(fd_in);

    int fd_out = open(D2S, O_WRONLY);
    write(fd_out, menu, strlen(menu) + 1);
    close(fd_out);
    return 0;
}