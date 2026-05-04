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
} ThreadArg;

void* traiter_requete(void* arg) {
    ThreadArg* data = (ThreadArg*)arg;
    char buffer_reponse[1024] = "";
    FILE *fichier;

    printf("Traitement de la requête : %s\n", data->requete);

    if (strcmp(data->requete, "1234 1234 0001") == 0) { 
        fichier = fopen("menu_burger.txt", "r");
    } else if (strcmp(data->requete, "1234 1234 0002") == 0) {
        fichier = fopen("menu_sushi.txt", "r");
    } else if (strcmp(data->requete, "1234 1234 0003") == 0) {
        fichier = fopen("menu_pizza.txt", "r");
    } else {
        fichier = fopen("codes_erreur.txt", "r");
    }

    if (fichier != NULL) {
        char ligne[256];
        while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
            strcat(buffer_reponse, ligne);
        }
        fclose(fichier);
    } else {
        strcpy(buffer_reponse, "Erreur : Fichier introuvable sur le serveur.\n");
    }

    int fd_out = open(D2S, O_WRONLY);
    write(fd_out, buffer_reponse, strlen(buffer_reponse) + 1);
    close(fd_out);

    free(data); 
    pthread_exit(NULL);
}

int main() {
    char buffer[512];

    mkfifo(S2D, 0666);
    mkfifo(D2S, 0666);

    printf("Serveur DATA en attente de requetes...\n");

    while(1) {
        int fd_in = open(S2D, O_RDONLY);
        if (read(fd_in, buffer, sizeof(buffer)) > 0) {
            
            ThreadArg* arg = malloc(sizeof(ThreadArg));
            strcpy(arg->requete, buffer);

            pthread_t thread_id;
            pthread_create(&thread_id, NULL, traiter_requete, arg);
            
            pthread_detach(thread_id); 
        }
        close(fd_in);
    }
    return 0;
}
