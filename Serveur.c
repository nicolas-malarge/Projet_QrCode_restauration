#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TAILLE_CHAINE   256

int main()
{   char * tube_serveur="/tmp/myfifo";
    int sortieTube;
    int entree_tube;
    char chaineALire[TAILLE_CHAINE];
    char *tube_client;/*un pointeur pour la fonction strtok (chaineALire, ";") qui permet de segmenter chaineALire */
    char *mot;/* mot que le client veut tester si c'est un palindrome ou non */

    /***************** création tube serveur **********************/
    
    int fd = open(mkfifo(tube_serveur, 0666), O_RDONLY);
    if(fd == -1)
    {   fprintf(stderr, "Impossible de créer le tube nommé.\n");
        exit(EXIT_FAILURE);
    }
     
    /**************** Attente d'un appel client ******************/
    if((sortieTube = open (tube_serveur, O_RDONLY)) == -1)
    {
        fprintf(stderr, "Impossible d'ouvrir la sortie du tube nommé.\n");
        exit(EXIT_FAILURE);
    }
    read(sortieTube, chaineALire, TAILLE_CHAINE);
    printf("%s", chaineALire);
    tube_client = strtok (chaineALire, ";");
    mot = strtok (NULL, ";");
    printf ("client : %s\n", tube_client);
    printf ("message : %s\n", mot);
/* Tant que le client n'a pas dit "FIN" le serveur attend des requêtes */
    while(strcmp(mot,"FIN")!=0)
    {   printf("\ndebut de la boucle\n");
        /************* Ecriture dans le tube client ********/
        if((entree_tube = open(tube_client, O_WRONLY)) == -1)
        {   fprintf(stderr, "Impossible d'ouvrir l'entrée du tube nommé.\n");
            exit(EXIT_FAILURE);
        }
        write(entree_tube,"tube_client.fifo;riri", strlen("tube_client.fifo;riri"));
        /* Vider les chaines de caractere avant de les revaloriser */
        memset(chaineALire,0,TAILLE_CHAINE);
        memset(tube_client,0,sizeof(tube_client));
        memset(mot,0,sizeof(mot));
        read(sortieTube, chaineALire, TAILLE_CHAINE);
        printf("%s", chaineALire);
        tube_client = strtok (chaineALire, ";");
        mot = strtok (NULL, ";");
        printf ("client : %s\n", tube_client);
        printf ("message : %s\n", mot);
    }
    /************** Programme terminé *****************************/
    unlink(tube_serveur);
    return EXIT_SUCCESS;
}