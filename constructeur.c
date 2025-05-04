#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "constructeur.h"

void chargerPersos(Perso persos[], const char* nomFichier, int *nb) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur ouverture fichier %s\n", nomFichier);
        printf("Code erreur = %d\n", errno);
        printf("Message = %s\n", strerror(errno));
        exit(1);
    }

    int id, pdv_max, attaque, defense, agilite, vitesse;
    char nom[50];
    int i = 0;

    while (fscanf(fichier, "%d %s %d %d %d %d %d",
                  &id, nom, &pdv_max, &attaque, &defense, &agilite, &vitesse) == 7) {
        persos[i].id = id;
        strcpy(persos[i].nom, nom);
        persos[i].pdv_max = pdv_max;
        persos[i].pdv = pdv_max;  
        persos[i].attaque = attaque;
        persos[i].defense = defense;
        persos[i].agilite = agilite;
        persos[i].vitesse = vitesse;
        i++;
    }

    *nb = i;  
    fclose(fichier);
}



