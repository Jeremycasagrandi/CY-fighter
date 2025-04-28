#include<stdio.h>
#include"personnage.h"



int main (){
    Perso perso1;
    perso1=creationperso();
    afficherPerso(perso1);
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
