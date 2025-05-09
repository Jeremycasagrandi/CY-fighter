#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "constructeur.h"
#include "jeu.h"
#include "afficher.h"

Equipe choixPersonnage(int n) {
    Perso persos[MAX_PERSOS];
    Ult capacites[MAX_CAPACITES]; 
    int nbPersos, nbCapacites;
    int verif;
    chargerPersos(persos, capacites, "persos.txt", "capacites.txt", &nbPersos, &nbCapacites);

    int debut;
    int fin;
    // Pour choix entre fruit et légume
    if (n == 1) {
        debut = 0;
        fin = 6;
    } else {
        debut = 6;
        fin = 12;
    }

    if (n == 1) {
        printf("\n--- Joueur 1 (Fruits) ---\n");
    } else {
        printf("\n--- Joueur 2 (Légumes) ---\n");
    }

    for (int i = debut; i < fin; i++) {
        printf("%d. ", i - debut); 
        afficherPerso(persos[i]);
    }
    char c;
    do {
        printf("Voulez vous voir les capacités? oui = o / non = n   ");
        
        verif=scanf(" %c", &c);
        vide_buffer();
        if (c=='o'||verif!=1){
            for (int i = debut; i < fin; i++) {
                afficherCapacite(persos[i].capacite.id, capacites, nbCapacites);
            }
        }
    } while ((c != 'n' && c != 'o') || verif != 1);

    Equipe eq;
    verif=0;
    eq.id=n;

    int pris[6] ;  // Pour vérifier si un personnage est déjà pris
    for (int i = 0; i < 6; i++) { //Obliger sinon cela bloque certain choix alors qu'il ne doit pas l'être
        pris[i] = 0;
    }
    for (int i = 0; i < 3; i++) {
        int choix;
        
       
        do{
            printf("Choix %d (0 à 5) : ", i + 1);
            choix = scanInt(0,5);
        }while(pris[choix]==1);
            
        

        pris[choix] = 1;//eviter doublo personnage
        eq.membres[i] = persos[debut + choix];
    }
    // temporaire l'équipe doit pouvoir choisir son nom (consigne)
    if (n == 1) {
        strcpy(eq.nom, "Fruits");
    } else {
        strcpy(eq.nom, "Légumes");
    }

    return eq;
}

void choixEquipe(Equipe *equipe, int numeroEquipe) {
    int choix;
    int verif;
    printf("=== Choix de l'équipe %d ===\n", numeroEquipe);
    printf("1. Fruits\n");
    printf("2. Légumes\n");

    choix=scanInt(1,2);
    

    if (choix == 1) {
        *equipe = choixPersonnage(1);  // Joueur 1 choisit Fruits
    } else {
        *equipe = choixPersonnage(2);  // Joueur 2 choisit Légumes
    }
}

Jeu multijoueur() {
    int choixJ1;
    int choixJ2;

    printf("=== Joueur 1 ===\n");
    printf("1. Fruits\n");
    printf("2. Légumes\n");

    choixJ1=scanInt(1,2);

    
    //joueur 2 prends automatiquement l'autre équipe 
    if (choixJ1 == 1) {
        choixJ2 = 2;
    } else {
        choixJ2 = 1;
    }

    // création des équipes
    Equipe equipe1 = choixPersonnage(choixJ1);
    Equipe equipe2 = choixPersonnage(choixJ2);
    Jeu jeu;
    jeu.equipe1=equipe1;
    jeu.equipe2=equipe2;
   
    // Affichage des équipes sélectionnées

    afficherEquipe(&equipe1, "Équipe Joueur 1");
  
    afficherEquipe(&equipe2, "Équipe Joueur 2");
    return jeu;
}

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