#include <stdio.h>
#include <stdlib.h>
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

    struct Plat menuBurgerHappy[100];
    struct Plat menuHappySushi[100];
    struct Plat menu3[100];

    ajoutStruct(menuBurgerHappy, 0, "Le Classique..", 14.0);
    ajoutStruct(menuBurgerHappy, 1, "Burger Country", 16.0);
    ajoutStruct(menuBurgerHappy, 2, "Burger Buffalo", 16.0);
    ajoutStruct(menuBurgerHappy, 3, "Le Royal......", 18.0);
    ajoutStruct(menuBurgerHappy, 4, "Le BurKid.....", 8.0);

    // ajoutStruct(menuHappySushi, 0, "Suchi Saumon......", 8);
    // ajoutStruct(menuHappySushi, 1, "Suchi Crevettes...", 6);
    // ajoutStruct(menuHappySushi, 2, "Suchi Thon........", 7);
    // ajoutStruct(menuHappySushi, 3, "Suchi Saumon...", 8);

    char buffer[512];
    char nPlat[200];
    char menu1[1024] = "";
    for(int i = 0; i < 5; i++){
        struct Plat vPlat = menuBurgerHappy[i];
        sprintf(nPlat, "%d : %s %.2f \n", vPlat.idPlat, vPlat.plat, vPlat.prix);
        strcat(menu1, nPlat);
    }

    //char menu2[] = "";
    //for(int i =0; )

    mkfifo(S2D, 0666);
    mkfifo(D2S, 0666);

    printf("En attente de requetes...\n");

    int fd_in = open(S2D, O_RDONLY);
    read(fd_in, buffer, sizeof(buffer));
    printf("[DATA] Reçu du serveur: %s\n", buffer);
    close(fd_in);

    int fd_out = open(D2S, O_WRONLY);
    write(fd_out, menu1, strlen(menu1) + 1);
    close(fd_out);
    return 0;
}