#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "constructeur.h"
#include "jeu.h"
#include "afficher.h"
#include <unistd.h>


Equipe choixPersonnage(int n) {
    Perso persos[MAX_PERSOS]; //tableau de tout les personnages
    Ult capacites[MAX_CAPACITES]; //tableau de toutes les capacités
    int nbPersos, nbCapacites; //nombre de persos et de capacité chargés depuis le fichier
    chargerPersos(persos, capacites, "persos.txt", "capacites.txt", &nbPersos, &nbCapacites);
  
    int debut;
    int fin;
    // Pour choix entre fruit et légume (intervalle de personnages selon fruit ou légume)
    if (n == 1) {
        debut = 0;
        fin = 6;
    } else {
        debut = 6;
        fin = 12;
    }
    clearScreen();
    //affichage du joueur actuel
    if (n == 1) {
        printf("\n--- Joueur 1 (Fruits) ---\n");
    } else {
        printf("\n--- Joueur 2 (Légumes) ---\n");
    }
    //affichage des personnes disponibles pour ce joueur
    for (int i = debut; i < fin; i++) {
        printf("Personnage %d :\n ", i - debut); 
        afficherPerso(persos[i]);
    }
    
    Equipe eq; //equipe en cours de création
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
        }while(pris[choix]==1); //regarde si le perso a déjà été pris 
            
        

        pris[choix] = 1;//eviter doublon de personnage
        eq.membres[i] = persos[debut + choix];
    }
    // l'équipe choisit son nom 

    printf("\n------------------------------------------------->\nChoisissez le nom de l'équipe (max 50 caractères) : ");
    if (scanf(" %50[^\n]", eq.nom) != 1) {
        printf("Erreur : valeurs invalides ou incomplètes.\n");
        exit(1);
    }

   

    return eq;
}



Jeu multijoueur() {
    int choixJ1;
    int choixJ2;
    afficherChoixEq();
  

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
    Jeu jeu;// contient les deux équipes
    jeu.equipe1=equipe1;
    jeu.equipe2=equipe2;
    return jeu;
}

//Charge les persos et capacités
void chargerPersos(Perso persos[], Ult capacites[], const char* nomFichierPersos, const char* nomFichierCapacites, int *nbPersos, int *nbCapacites) {
    //verification
    if ( nbPersos == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
    }
     if ( nbCapacites == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
    }
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
    int idCapacite, duree, cooldown;
    char nomCapacite[50], description[2000];
    int i = 0;
    // Lit les capacités depuis le fichier et les stocke dans le tableau "capacites"
    while (fscanf(fichierCapacites, "%d %s %s %d %d", &idCapacite, nomCapacite, description, &duree, &cooldown) == 5) {
        capacites[i].id = idCapacite;
        strcpy(capacites[i].nom, nomCapacite);
        strcpy(capacites[i].description, description);
        capacites[i].duree_effet = duree;
        capacites[i].cooldown_max = cooldown;
        capacites[i].cooldown =cooldown;
        
        
        
        
        i++;
    }
// Enregistre le nombre total de capacités lues
*nbCapacites = i;
fclose(fichierCapacites);



    int idPerso, pdv_max, attaque, defense, agilite, vitesse, soin;
    char nomPerso[50];
    i = 0;
    // Lit les personnages depuis le fichier et les stocke dans le tableau "persos"
    while (fscanf(fichierPersos, "%d %s %d %d %d %d %d %d", &idPerso, nomPerso, &pdv_max, &attaque, &defense, &agilite, &vitesse,&soin) == 8) {
        persos[i].id = idPerso;
        strcpy(persos[i].nom, nomPerso);
        persos[i].pdv_max = pdv_max;
        persos[i].pdv = pdv_max;  
        persos[i].attaque = attaque;
        persos[i].defense = defense;
        persos[i].agilite = agilite;
        persos[i].vitesse = 0;//vitesse courante
        persos[i].vitesse_max = vitesse;
        persos[i].soin=soin;
        persos[i].nb_effets_actifs=0;
        // Associe la capacité d’indice i au personnage d’indice i
        persos[i].capacite = capacites[i];
        i++;
        

    }
   


    *nbPersos = i;
    fclose(fichierPersos);
}