#include <stdio.h>
#include "constructeur.h"
#include "afficher.h"

void afficherMenu() {
    printf("=== MENU PRINCIPAL ===\n");
    printf("1. Multijoueur\n");
    printf("2. Campagne\n");
    printf("Votre choix : ");
}

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

void afficherPerso(Perso p) {
    printf("\n--- Statistiques du personnage ---\n");
    printf("Nom           : %s\n", p.nom);
    printf("Points de vie : %d / %d\n", p.pdv, p.pdv_max);
    printf("Attaque       : %d\n", p.attaque);
    printf("Défense       : %d\n", p.defense);
    printf("Agilité       : %d\n", p.agilite);
    printf("Vitesse       : %d\n", p.vitesse);
    printf("----------------------------------\n");
}