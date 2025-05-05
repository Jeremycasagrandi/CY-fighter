#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include "afficher.h"
#include "constructeur.h"

Jeu menu() {
    int choix;
    Jeu jeu;

    do {
        afficherMenu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                jeu=multijoueur();  // Appel de la fonction multijoueur
                break;
            case 2:
                //campagne();
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 1 && choix != 2);
    return jeu;
    
}

Equipe choixPersonnage(int n) {
    Perso persos[MAX_PERSOS];
    int nb;

    chargerPersos(persos, "persos.txt", &nb);

    int debut;
    int fin;
    // Il
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

    Equipe eq;
    int pris[6] ;  // Pour vérifier si un personnage est déjà pris
    for (int i = 0; i < 6; i++) { //Obliger sinon cela bloque certain choix alors qu'il ne doit pas l'être
        pris[i] = 0;
    }
    for (int i = 0; i < 3; i++) {
        int choix;
        do {
            printf("Choix %d (0 à 5) : ", i + 1);
            scanf("%d", &choix);
        } while (choix < 0 || choix > 5 || pris[choix] == 1);

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

    printf("=== Choix de l'équipe %d ===\n", numeroEquipe);
    printf("1. Fruits\n");
    printf("2. Légumes\n");

    do {
        printf("Votre choix (1 ou 2) : ");
        scanf("%d", &choix);
    } while (choix != 1 && choix != 2);

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

    do {
        printf("Choix de l'équipe (1 ou 2) :\n ");
        printf("Attention l'autre équipre prend automatiquement l'autre  \n ");
        scanf("%d", &choixJ1);
    } while (choixJ1 != 1 && choixJ1 != 2); // il y a un bug sur tout les while quand je mets une lettre

    
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



int tour(Jeu* jeu) {
    
    while (1) {
        for (int i = 0; i < 3; i++) {
            // Vérification pour l'équipe 1
            
            jeu->equipe1.membres[i].vitesse--;
            if (jeu->equipe1.membres[i].vitesse <= 0) {
                jeu->equipe1.membres[i].vitesse = jeu->equipe1.membres[i].vitesse_max;
                return i;  // Retourner le joueur de l'équipe 1
            }

            // Vérification pour l'équipe 2
            
            jeu->equipe2.membres[i].vitesse--;
            if (jeu->equipe2.membres[i].vitesse <= 0) {
                jeu->equipe2.membres[i].vitesse = jeu->equipe2.membres[i].vitesse_max;
                return i + 3;  // Retourner le joueur de l'équipe 2
            }
        }
    }
}

