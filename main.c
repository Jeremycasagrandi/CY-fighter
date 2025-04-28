#include<stdio.h>
#include"constructeur.h"





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
                printf("Choix invalide. \n");
        }
    } while (choix == 1 && choix ==2);

    return 0;
}


void afficherPerso(Perso p) {
    printf("\n--- Statistiques du personnage ---\n");
    printf("Points de vie  : %d / %d\n", p.pdv, p.pdv_max);
    printf("Attaque        : %d\n", p.attaque);
    printf("Défense        : %d\n", p.defense);
    printf("Agilité        : %d\n", p.agilite);
    printf("Vitesse        : %d\n", p.vitesse);
    printf("----------------------------------\n");
}

int main (){
    Perso perso1;
    perso1=creationperso();
    afficherPerso(perso1);
    menu();
}