//client.c
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 
// for open , O_RDONLY , O_WRONLY
// for printf
// for mkfifo
// for read , write
#define S2C "S2C.tube"
#define C2S "C2S.tube"

/// Création d'un mutex pour que les clients ne soient pas confondus
pthread_mutex_t mutex_tubes = PTHREAD_MUTEX_INITIALIZER;

void* demanderMenu(void* pChoix) {
    char* choix = (char*)pChoix;
    char buffer[512];
    
    // Le thread prend la place, si un autre l'a déjà, il attend son tour
    pthread_mutex_lock(&mutex_tubes); 
    printf("\n(nouveau client) Envoi de la commande : %s\n", choix);

    //Envoi de la requête au serveur
    int fd_out = open(C2S, O_WRONLY);
    if(fd_out != -1) {
        write(fd_out, choix, strlen(choix) + 1);
        close(fd_out);
    }else{
        perror("Erreur d'écriture dans C2S");
    }
    int fichier = open(S2C, O_RDONLY);

    if(fichier == -1) {
        perror("impossible d'ouvrir le tuyau S2C");
    }else{
        int nb_lettres = read(fichier, buffer, sizeof(buffer) - 1);
        if(nb_lettres > 0) {
            printf("\n Le serveur a répondu : %s\n", buffer);
        }
        close(fichier);
    }
    // Le thread a fini, il rend la place pour le prochain client
    pthread_mutex_unlock(&mutex_tubes);
    // On libère la mémoire allouée pour ce choix
    free(choix); 
    pthread_exit(NULL);
}

int main() {
    FILE *fichier = fopen("choix_client.txt", "r");
    if(fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir 'choix_client.txt'\n");
        return 1;
    }

    char lecture[128];
    pthread_t threads[100];
    int nb_clients = 0;
    printf("Simulation plusieurs clients\n");
    
    // On boucle pour lire chaque ligne du fichier
    while (fgets(lecture, sizeof(lecture), fichier) != NULL && nb_clients < 100) {
        lecture[strcspn(lecture, "\n")] = 0; // =0 pour couper la chaine de caractère
        if(strlen(lecture) == 0) continue; // Saute les lignes vides

        // On copie le choix en mémoire pour le donner au thread afin d'éviter que les menus soient perdus à cause d'une autre demande
        char* choix_pour_thread = strdup(lecture);
        
        // Création et Vérification de la création du thread
        if(pthread_create(&threads[nb_clients], NULL, demanderMenu, choix_pour_thread) != 0) {
            perror("Erreur lors de la création du thread");
        }else{
            nb_clients++;
        }
    }
    
    fclose(fichier);
    printf("%d clients ont été lancés.\n", nb_clients);

    // On attend que tous les clients aient terminé de commander avant de quitter le programme
    for (int i = 0; i < nb_clients; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\n Tous les clients ont été servis. Fin du programme.\n");
    return 0;
}
    return 0;
}
