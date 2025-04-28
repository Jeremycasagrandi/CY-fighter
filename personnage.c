#include <stdio.h>
#include "personnage.h"

Perso creationperso() {
    int choix;
    Perso perso1;

    printf("choisissez votre perso : ");
    scanf("%d", &choix);
    if (choix == 1) {
        perso1.pdv = 26;
        perso1.pdv_max = 26;
        perso1.attaque = 7;
        perso1.defense = 8;
        perso1.agilite = 4;
        perso1.vitesse = 5;
        
    }
    printf("les pdv du perso sont : %d", perso1.pdv);

    return perso1;
}


