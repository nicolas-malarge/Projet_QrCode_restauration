// data.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#define D2S "D2S.tube"
#define S2D "S2D.tube"

//on créé ce struct pour y mettre l'information que l'on va envoyer au client
typedef struct {
    char requete[512];
} Information;

void* traiterRequete(void* pRequete) { //traite la requète envoyée par le client.
    Information* data = (Information*)pRequete;
    char buffer_reponse[512] = "";
    FILE *fichier;

    printf("Traitement de la requête : %s\n", data->requete);

    if(strcmp(data->requete, "1234 1234 0001") == 0) { //on envoie le menu du restaurant correspondant.
        fichier = fopen("menu_burger.txt", "r");
    }else if(strcmp(data->requete, "1234 1234 0002") == 0) {
        fichier = fopen("menu_sushi.txt", "r");
    }else if(strcmp(data->requete, "1234 1234 0003") == 0) {
        fichier = fopen("menu_pizza.txt", "r");
    }else {
        fichier = fopen("codes_erreur.txt", "r");
    }

    if(fichier != NULL) { //le bon fichier récupéré, on vérifie s'il n'est pas vide.
        char ligne[256];
        //on récupère et lie les lignes contenues dans le fichier .txt.
        while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
            strcat(buffer_reponse, ligne);
        }
        fclose(fichier); //on ferme le fichier
    }else{ //si le fichier est vide, on renvoie un message d'erreur
        strcpy(buffer_reponse, "Erreur : Fichier introuvable sur le serveur.\n");
    }

    //on envoie le contenu du fichier à travers le tube vers le serveur puis on le ferme.
    int fd_out = open(D2S, O_WRONLY);
    write(fd_out, buffer_reponse, strlen(buffer_reponse) + 1);
    close(fd_out);

    free(data); 
    pthread_exit(NULL);
}

int main() {
    char buffer[512];

    //création des tubes
    mkfifo(S2D, 0666);
    mkfifo(D2S, 0666);

    printf("Serveur data en attente de requetes...\n");

    //permet de laisser tourner data même après la gestion des clients.
    while(1) {
        int fd_in = open(S2D, O_RDONLY);
        //lit la sortie du pipe venant de server et alloue la mémoire necessaire.
        if(read(fd_in, buffer, sizeof(buffer)) > 0) {
            
            Information* vReponse = malloc(sizeof(Information));
            strcpy(vReponse->requete, buffer);

            pthread_t vThread;
            pthread_create(&vThread, NULL, traiterRequete, vReponse);
            pthread_detach(vThread); 
        }
        close(fd_in);
    }
    return 0;
}

