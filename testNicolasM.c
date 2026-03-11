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

    printf("Nom serveur : %s\n", s1.nom);
    printf("Identifiant serveur : %d\n", s1.idServeur);

    return 0;
}