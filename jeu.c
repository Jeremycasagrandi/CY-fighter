#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#include "jeu.h"
#include "afficher.h"
#include "constructeur.h"
#include "capacite_speciale.h"
#include "capacite_classique.h"
#include "effet.h"


// Vide le tampon d'entrée
void vide_buffer(){
    while (getchar() != '\n') {}
}


// permet de récupérer un entier entre min et max de manière sécurisé
int scanInt(int min, int max){
    int verif;
    int n;
    do {
       
        verif = scanf("%d", &n);


       
        while (getchar() != '\n') {}


        if (verif != 1 || n < min || n > max) {
            printf("Erreur : veuillez entrer un entier valide entre %d et %d.\n", min, max);
        }
    } while (verif != 1 || n < min || n > max);


    return n;
}






//regarde si une equipe est éléminé, retourne 1 si equipe 1 gagne, 2 si equipe 2 gagne
int finDuJeu(Jeu* jeu){
    Equipe eq1=jeu->equipe1;
    Equipe eq2=jeu->equipe2;
    if (eq1.membres[0].pdv<=0&&eq1.membres[1].pdv<=0&&eq1.membres[2].pdv<=0){
        return 2;
    }
    else if (eq2.membres[0].pdv<=0&&eq2.membres[1].pdv<=0&&eq2.membres[2].pdv<=0){
        return 1;
    }
    else{
        return 0;
    }
}






// trouve le perso qui a la vitesse maximal au dessus du seuil
int trouverIndexVitesseMax(Perso* tab[]) {
   
    int maxIndex = -1;
    int maxVitesse = 100;  


    for (int i = 0; i < 6; i++) {
        if (tab[i]->vitesse >= 100 && tab[i]->vitesse > maxVitesse) {
            maxVitesse = tab[i]->vitesse;
            maxIndex = i;
        }
    }


    return maxIndex;
}
















//retourne le prochain personnage qui doit jouer a chaque appel, affiche la progression de la vitesse
int tour(Jeu* jeu) {
    int index;
   
    afficherPlateau(jeu);


    index = trouverIndexVitesseMax(jeu->tabE);
   
    // Si personne ne peut encore jouer, on augmente les vitesses
    while (index == -1) {
        for (int i = 0; i < 6; i++) {
            jeu->tabE[i]->vitesse += jeu->tabE[i]->vitesse_max;
        }
       
        afficherPlateau(jeu);


        sleep(1);  
        index = trouverIndexVitesseMax(jeu->tabE);
    }


    jeu->tabE[index]->vitesse = 0;
    return index;
}




// regarde si un perso est vivant
int estVivant(Perso* p) {
    if ( p == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1);
    }
    return p->pdv > 0;
}


// regarde si l'ulti est disponible
int Aulti(Perso* perso) {
    if ( perso == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1);
    }
    return perso->capacite.cooldown == 0;
}


// regarde si un perso a un effet
int Aeffet(Perso* perso){
    if ( perso == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1);
    }
    return perso->nb_effets_actifs > 0;
}




// Permet choisir action
void choisirAction(Jeu* jeu, int indexEquipe) {
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


   
    Perso* perso = &equipeJoueur->membres[indexEquipe];


    printf("\n------------------------------>\n");
    printf("C'est au tour de %s !\n\n", perso->nom);




// applique les effet au perso qui joue
    if (Aeffet(perso)) {
        appliquerEffets(perso);
       
        if (perso->pdv <= 0) {
            printf("%s est mort à cause de l'acide\n", perso->nom);
            return;
        }
    }
   
    printf("1. Attaquer\n");
    printf("2. Utiliser capacité ultime : %s (%s)       [disponible dans %d tour(s)]\n",perso->capacite.nom,perso->capacite.description,perso->capacite.cooldown);
   
    if (estSoigneur(perso)){
        if (soinDisponible(equipeJoueur)){
            printf("3. Soin\n");
        }
        else{
            printf("3. Soin [indisponible (PV max pour les persos)]\n");
        }
    }
   
   
    do {
        printf("\nChoisissez une action : ");
        choix = scanInt(1,3);
        if (choix == 2 && !Aulti(perso)) {
            printf("\n[Capacité ultime indisponible.  %d tours restants.]\n", perso->capacite.cooldown);
        }
    } while ((choix == 2 && !Aulti(perso))||(choix == 3 && (!estSoigneur(perso) || !soinDisponible(equipeJoueur))));




    switch (choix) {
        case 1:  // Attaque
            attaque(jeu, perso, idEquipe, 0);
            break;
        case 2:  // Utiliser capacité ultime
            ult(jeu, perso, idEquipe);
            break;
        case 3:
            soin(jeu, perso, idEquipe);
            break;
        default:
            printf("Choix invalide.\n");
            break;
    }
    if (perso->capacite.cooldown > 0) {
        perso->capacite.cooldown--;
    }
    mettreAJourEffets(perso);
}
