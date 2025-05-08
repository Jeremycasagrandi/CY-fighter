#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "constructeur.h"

void chargerPersos(Perso persos[], Ult capacites[], const char* nomFichierPersos, const char* nomFichierCapacites, int *nbPersos, int *nbCapacites) {
    FILE* fichierPersos = fopen(nomFichierPersos, "r");
    if (fichierPersos == NULL) {
        printf("Erreur ouverture fichier %s\n", nomFichierPersos);
        printf("Code erreur = %d\n", errno);
        printf("Message = %s\n", strerror(errno));
        exit(1);
    }

    FILE* fichierCapacites = fopen(nomFichierCapacites, "r");
    if (fichierCapacites == NULL) {
        printf("Erreur ouverture fichier %s\n", nomFichierCapacites);
        printf("Code erreur = %d\n", errno);
        printf("Message = %s\n", strerror(errno));
        exit(1);
    }

    // Charger les capacités ultimes
    int idCapacite, duree, recharge;
    char nomCapacite[50], description[2000];
    int i = 0;
    while (fscanf(fichierCapacites, "%d %s %s %d %d", &idCapacite, nomCapacite, description, &duree, &recharge) == 5) {
        capacites[i].id = idCapacite;
        strcpy(capacites[i].nom, nomCapacite);
        strcpy(capacites[i].description, description);
        capacites[i].duree_effet = duree;
        capacites[i].cooldown = recharge;
        

        
        i++;
    }

*nbCapacites = i;
fclose(fichierCapacites);



    int idPerso, pdv_max, attaque, defense, agilite, vitesse, soin;
    char nomPerso[50];
    i = 0;
    while (fscanf(fichierPersos, "%d %s %d %d %d %d %d %d", &idPerso, nomPerso, &pdv_max, &attaque, &defense, &agilite, &vitesse,&soin) == 8) {
        persos[i].id = idPerso;
        strcpy(persos[i].nom, nomPerso);
        persos[i].pdv_max = pdv_max;
        persos[i].pdv = pdv_max;  
        persos[i].attaque = attaque;
        persos[i].defense = defense;
        persos[i].agilite = agilite;
        persos[i].vitesse = vitesse;
        persos[i].vitesse_max = vitesse;
        persos[i].soin=soin;

        // Associer la capacité au  personnage avec l'Id
        persos[i].capacite = capacites[i];
        i++;
    }
    printf("Perso %s a capacité : %s\n", persos[i].nom, persos[i].capacite.nom);


    *nbPersos = i;
    fclose(fichierPersos);
}