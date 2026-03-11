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

    s1.idServeur = 1;
    strcpy(s1.nom, "restaurant 1");

    s2.idServeur = 2;
    strcpy(s2.nom, "restaurant 2");

    printf("Nom serveur : %s\n", s1.nom);
    printf("Identifiant serveur : %d\n", s1.idServeur);

    printf("Nom serveur : %s\n", s2.nom);
    printf("Identifiant serveur : %d\n", s2.idServeur);
    return 0;
}