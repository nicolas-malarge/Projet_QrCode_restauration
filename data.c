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

struct Plat {
    int idPlat;
    char plat[30];
    double prix;
};

void afficherMenu(struct Plat pPlat){
    printf("Plat : %s ........ Prix : %f euros\n", pPlat.plat, pPlat.prix);

    //int j;
    //    while (pPlat.plat[j]!='\0'){
    //        printf("%c", pPlat.plat[j]);
    //        j++;
    //    }
    //printf("%s\n", pPlat.plat);
}

void ajoutStruct(struct Plat pPlat[], int pId, char pNomPlat, double pPrix){
    struct Plat vPlat;
    vPlat.idPlat = pId;
    vPlat.plat[30] = pNomPlat;
    vPlat.prix = pPrix;
    pPlat[pId] = vPlat;
}

int main() {
    struct Serveur s1;
    struct Serveur s2;
    struct Client c1;
    struct Plat menu1[100];

    char char1[30] = {'L','e',' ','C', 'l', 'a', 's', 's', 'i', 'q', 'u', 'e'};
    printf("%s", char1);
    ajoutStruct(menu1, 1, char1, 14.0);
    ajoutStruct(menu1, 2, "Burger Country", 16.0);
    ajoutStruct(menu1, 3, "Burger Buffalo", 16.0);
    ajoutStruct(menu1, 4, "Le Royal", 18.0);
    ajoutStruct(menu1, 5, "Le BurKid", 8.0);

    s1.idServeur = 1;
    strcpy(s1.nom, "Burger Happy");

    s2.idServeur = 2;
    strcpy(s2.nom, "Happy Sushi");

    c1.idClient = 1;
    strcpy(c1.nom, "MALARGE");
    strcpy(c1.prenom, "Nicolas");

    printf("Nom serveur : %s\n", s1.nom);
    printf("Identifiant serveur : %d\n", s1.idServeur);

    printf("Nom serveur : %s\n", s2.nom);
    printf("Identifiant serveur : %d\n", s2.idServeur);

    printf("Nom client : %s\n", c1.nom);
    printf("Prenom client : %s\n", c1.prenom);

    for(int i = 1; i < 6; i++){

        afficherMenu(menu1[i]);
    }
    return 0;
}