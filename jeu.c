#include <stdio.h>
#include "jeu.h"
#include "afficher.h"

int menu() {
    int choix;

    do {
        afficherMenu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                //multijoueur();
                break;
            case 2:
                //campagne();
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 1 && choix != 2);  

    return choix;
}