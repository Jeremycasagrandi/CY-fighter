#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "constructeur.h"
#include "jeu.h"
#include "afficher.h"
#include "campagne.h"
#include <unistd.h>

Perso* choix_perso_ennemi_robot(Equipe* equipe) {
    if ( equipe == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
    }
    int choix;
    do {
        choix=rand()%3;

    } while (choix < 1 || choix > 3 || !estVivant(&equipe->membres[choix - 1]));

    return &equipe->membres[choix - 1];
}

void attaqueRobot(Jeu* jeu,Perso* perso, int idEquipe, int bonus_ult){
    if ( perso == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
    }
    
    //choix de l'adversaire
    int choix;
    Perso* cible;
    if (idEquipe == 1) {
        cible = choix_perso_ennemi_robot(&jeu->equipe2);
    } else {
        cible = choix_perso_ennemi_robot(&jeu->equipe1);
    }

    // vérifie si l'attaque est esquivée
    if (esquive(cible)) {
        printf("%s a esquivé l'attaque !\n", cible->nom);
        
        return;
    }

    // calcule les dégats réels 
    int degats = defense(cible, perso->attaque)+bonus_ult;
    cible->pdv -= degats;
    if (bonus_ult!=0){
        printf("%s subit %d dégâts (%d (attaque de base) %d(ult)).\n", cible->nom, degats, perso->attaque,bonus_ult);
    }
    else{
        printf("%s subit %d dégâts .\n", cible->nom, degats);
    }

    if (cible->pdv < 0) {
        cible->pdv = 0;  // Pour éviter d'afficher des pdv négatifs
    }
}

int choisirActionRobot(Jeu* jeu, int indexEquipe){
    int choix;
    Equipe* equipeJoueur;
    int idEquipe;
    
    
    
    if (indexEquipe < 3) { 
        equipeJoueur = &jeu->equipe1;
        idEquipe=1;
    } else {
        equipeJoueur = &jeu->equipe2;
        indexEquipe -= 3;  
        idEquipe=2;
    }

    printf("\n------------------------------>\n");
    printf("C'est au tour de %s !\n\n",equipeJoueur->membres[indexEquipe].nom );

    
    Perso* perso = &equipeJoueur->membres[indexEquipe];
    attaqueRobot(jeu, perso, idEquipe, 0);
    mettreAJourEffets(perso);
    sleep(3);
}


Equipe choixPersonnageRobot(int n) {
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
    clearScreen();
    if (n == 1) {
        printf("\n--- Joueur 1 (Fruits) ---\n");
    } else {
        printf("\n--- Joueur 2 (Légumes) ---\n");
    }
    
 
    char c;
 

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
            choix = rand() % 6;
        }while(pris[choix]==1);
            
        

        pris[choix] = 1;//eviter doublon personnage
        eq.membres[i] = persos[debut + choix];
    }
   


    strcpy(eq.nom, "IA");
   

    return eq;
}

Jeu campagne() {
    int choixJ1;
    int choixJ2;
    afficherChoixEq();
  

    choixJ1=scanInt(1,2);

    
    //robot prends automatiquement l'autre équipe 
    if (choixJ1 == 1) {
        choixJ2 = 2;
    } else {
        choixJ2 = 1;
    }

    // création des équipes
    Equipe equipe1 = choixPersonnage(choixJ1);
    Equipe equipe2 = choixPersonnageRobot(choixJ2);
    Jeu jeu;
    jeu.equipe1=equipe1;
    jeu.equipe2=equipe2;

     
   
    // Affichage des équipes sélectionnées

    afficherEquipe(&equipe1, "Équipe Joueur 1");
  
    afficherEquipe(&equipe2, "Équipe Joueur 2");
    return jeu;
} 