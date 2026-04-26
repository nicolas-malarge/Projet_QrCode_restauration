//data.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <bits/pthreadtypes.h>

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

typedef struct{
    char filepath[256];
    int write;
}lecture;

void* lire_fichier(void* arg){
    lecture* args = (lecture*)arg;
    FILE* file = fopen(args-> filepath, "r");

    if (file == NULL){
        char* erreur = "Erreur : Impossible d'ouvrir le menu du restaurant.\n";
        write(args->write, erreur, strlen(erreur));
        close(args->write);
        pthread_exit(NULL);
    }

    char buffer[512];
    size_t bytes;

    while((bytes = fread(buffer, 1, sizeof(buffer), file)) > 0){
            write(args->write , buffer, bytes);
    }

    fclose(file);
    close(args->write);
    pthread_exit(NULL);
}


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
    struct Plat menuPizzHappy[100];

    ajoutStruct(menuBurgerHappy, 0, "Le Classique.....", 14.0);
    ajoutStruct(menuBurgerHappy, 1, "Burger Country...", 16.0);
    ajoutStruct(menuBurgerHappy, 2, "Burger Buffalo...", 16.0);
    ajoutStruct(menuBurgerHappy, 3, "Le Royal.........", 18.0);
    ajoutStruct(menuBurgerHappy, 4, "Le BurKid........", 8.0);

    ajoutStruct(menuHappySushi, 0, "Suchi Saumon......", 8);
    ajoutStruct(menuHappySushi, 1, "Suchi Crevettes...", 6);
    ajoutStruct(menuHappySushi, 2, "Suchi Thon........", 7);
    ajoutStruct(menuHappySushi, 3, "Suchi Magicarpe...", 8);
    ajoutStruct(menuHappySushi, 4, "Suchi Brochet.....", 8);

    ajoutStruct(menuPizzHappy, 0, "Margharita.........", 8);
    ajoutStruct(menuPizzHappy, 1, "Americaine.........", 13);
    ajoutStruct(menuPizzHappy, 2, "Orientale..........", 13);
    ajoutStruct(menuPizzHappy, 3, "Burattina..........", 13);
    ajoutStruct(menuPizzHappy, 4, "Chèvre miel........", 14);
    

    char buffer[512];
    char nPlat[200];
    char menu1[1024] = "";
    char nom_fichier[50];

    char menu_a_envoyer[4096] = "";
    char read_buffer[1024];
    ssize_t nbytes;

    mkfifo(S2D, 0666);
    mkfifo(D2S, 0666);

    printf("En attente de requetes...\n");

    int fd_in = open(S2D, O_RDONLY);
    read(fd_in, buffer, sizeof(buffer));
    printf("Reçu du serveur: %s\n", buffer);
    close(fd_in);

    if (buffer[0] == '1') {
        strcpy(nom_fichier, "menuBurgerHappy.txt");
    } else if (buffer[0] == '2') {
        strcpy(nom_fichier, "menuHappySushi.txt");
    } else if (buffer[0] == '3') {
        strcpy(nom_fichier, "menuPizzHappy.txt");
    } else {
        strcpy(nom_fichier, "erreur_introuvable.txt"); 
    }

    int pipe_ano[2];
    if (pipe(pipe_ano) == -1) {
        perror("Erreur création pipe");
        return 1;
    }

    lecture args;
    strcpy(args.filepath, nom_fichier);
    args.write = pipe_ano[1];

    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, lire_fichier, &args) != 0) {
        perror("Erreur création thread");
        return 1;
    }

    close(pipe_ano[1]);

    while ((nbytes = read(pipe_ano[0], read_buffer, sizeof(read_buffer) - 1)) > 0) {
        read_buffer[nbytes] = '\0';
        strcat(menu_a_envoyer, read_buffer);
    }
    close(pipe_ano[0]);

    pthread_join(thread_id, NULL);

    int fd_out = open(D2S, O_WRONLY);
    if (fd_out != -1) {
        write(fd_out, menu_a_envoyer, strlen(menu_a_envoyer) + 1);
        close(fd_out);
        printf("Menu envoyé au serveur avec succès.\n");
    } else {
        perror("Erreur d'ouverture de D2S");
    }

    //int pipeD2S[2];

    // while ((nbytes = read(S2D, read_buffer, sizeof(read_buffer) - 1)) > 0) {
    //     read_buffer[nbytes] = '\0';
    //     strcat(menu_a_envoyer, read_buffer);
    // }
    // close(S2D); 

    // for(int i = 0; i < 5; i++){
    //     struct Plat vPlat = menuBurgerHappy[i];
    //     sprintf(nPlat, "%d : %s %.2f \n", vPlat.idPlat, vPlat.plat, vPlat.prix);
    //     strcat(menu1, nPlat);
    // }

    // char menu2[1024] = ""; 
    // for(int i = 0; i < 5; i++){
    //     struct Plat vPlat = menuHappySushi[i];
    //     sprintf(nPlat, "%d : %s %.2f \n", vPlat.idPlat, vPlat.plat, vPlat.prix);
    //     strcat(menu2, nPlat);
    // }

    // char menu3[1024] = ""; 
    // for(int i = 0; i < 5; i++){
    //     struct Plat vPlat = menuPizzHappy[i];
    //     sprintf(nPlat, "%d : %s %.2f \n", vPlat.idPlat, vPlat.plat, vPlat.prix);
    //     strcat(menu3, nPlat);
    // }

    // if(buffer[0] == '1'){ 
    //     int fd_out = open(D2S, O_WRONLY);
    //     write(fd_out, menu1, strlen(menu1) + 1);
    //     close(fd_out);
    // }
    // if(buffer[0] == '2'){
    //     int fd_out = open(D2S, O_WRONLY);
    //     write(fd_out, menu2, strlen(menu2) + 1);
    //     close(fd_out);
    // }
    // if(buffer[0] == '3'){
    //     int fd_out = open(D2S, O_WRONLY);
    //     write(fd_out, menu3, strlen(menu3) + 1);
    //     close(fd_out);
    // }
    return 0;
}
