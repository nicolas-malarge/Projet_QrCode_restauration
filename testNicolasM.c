#include <stdio.h>
#include <string.h> 

struct Serveur {
    int idServeur;
    char nom[30];
};

struct Client {
    int idClient;
    char nom[20];
    char prenom[20];
};

int main() {
    struct Serveur s1;
    struct Serveur s2;
    struct Client c1;

    s1.idServeur = 1;
    strcpy(s1.nom, "restaurant 1");

    s2.idServeur = 2;
    strcpy(s2.nom, "restaurant 2");

    c1.idClient = 1;
    strcpy(c1.nom, "MALARGE");
    strcpy(c1.prenom, "Nicolas");

    printf("Nom serveur : %s\n", s1.nom);
    printf("Identifiant serveur : %d\n", s1.idServeur);

    printf("Nom serveur : %s\n", s2.nom);
    printf("Identifiant serveur : %d\n", s2.idServeur);

    printf("Nom client : %s\n", c1.nom);
    printf("Prenom client : %s\n", c1.prenom);
    return 0;
}