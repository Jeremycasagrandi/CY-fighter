#include <stdio.h>
#include "constructeur.h"
#include "afficher.h"

void afficherMenu() {
    printf("=== MENU PRINCIPAL ===\n");
    printf("1. Multijoueur\n");
    printf("2. Campagne\n");
    printf("Votre choix : ");
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

void afficherEquipe(Equipe *equipe, char *titre) {
    printf("\n--- %s : %s ---\n", titre, equipe->nom);

    for (int i = 0; i < 3; i++) {
        printf("%s ", equipe->membres[i].nom);
    }
    printf("\n");

    for (int i = 0; i < 3; i++) {
        printf("PDV: %d ", equipe->membres[i].pdv_max);
    }
    printf("\n");

    for (int i = 0; i < 3; i++) {
        printf("ATK: %d ", equipe->membres[i].attaque);
    }
    printf("\n");

    for (int i = 0; i < 3; i++) {
        printf("DEF: %d ", equipe->membres[i].defense);
    }
    printf("\n");

    for (int i = 0; i < 3; i++) {
        printf("VIT: %d ", equipe->membres[i].vitesse);
    }
    printf("\n");

    for (int i = 0; i < 3; i++) {
        printf("AGI: %d ", equipe->membres[i].agilite);
    }
    printf("\n");
}