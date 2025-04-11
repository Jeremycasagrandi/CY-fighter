#include <stdio.h>
#include "personnage.h"

Perso creationperso() {
    int choix;
    Perso perso1;

    printf("choisissez votre perso : ");
    scanf("%d", &choix);
    if (choix == 1) {
        perso1.pdv = 26;
    }
    printf("les pdv du perso sont : %d", perso1.pdv);

    return perso1;
}


