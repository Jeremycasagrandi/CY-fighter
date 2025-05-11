#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "constructeur.h"
#include "afficher.h"
#include "jeu.h"
#include "string.h"
#include "campagne.h"
// vide le terminal et remonte le curseur en haut
void videTer() {
    #ifdef _WIN32
        system("cls");
       
    #else
        printf("\033[2J\033[H");
        fflush(stdout);
    #endif
}

// Affiche le menu du début
void afficherMenu() {
    videTer();
    printf(" Bienvenue dans SALADE DE FRUITS LEGUMES COMBAT : LA REVANCHE DES VEGETAUX\n\n");
    printf(" _[MENU PRINCIPAL] _________________________________________\n");
    printf("|                                                           |\n");
    printf("|        1. Multijoueur        2. Campagne                  |\n");
    printf("|                                                           |\n");
    printf("|___________________________________________________________|\n\n");
    printf("Votre choix : ");
}

// Affiche le menu de choix équipe
void afficherChoixEq(){
    videTer();
    printf(" _[CHOIX DE L'EQUIPE DU JOUEUR 1 ] _____________\n");
    printf("|                                               |\n");
    printf("|        1. Fruits        2. Légumes            |\n");
    printf("|                                               |\n");
    printf("|_______________________________________________|\n\n");
    printf("Votre choix : ");
}



// Initialise la création du jeu, solo sert a créer le jeu en fonction de si on est en mode multijoueur ou campagne, retourne l'adresse du jeu ()
Jeu menu(Jeu* jeu, int* solo) {
    if ( jeu == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
    }
    if ( solo == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
    }

    int choix;
    int verif;

    afficherMenu();
       
    choix=scanInt(1,2);
    switch (choix) {
         case 1 :
            *jeu=multijoueur(); 
            *solo=0;
            break;
        case 2:
            *jeu = campagne();
            *solo=1;
            break;
        default:
            printf("Choix invalide.\n");
    }
//  rempli le raccouci vers les perso dans tabE
    for (int i = 0; i < 3; i++) {
            jeu->tabE[i] =  &(jeu->equipe1.membres[i]);
            jeu->tabE[i + 3] = &(jeu->equipe2.membres[i]);
        }
        for (int i = 0; i < 6; i++) {
            jeu->tabE[i]->num=i;
    }


    for (int i = 0; i < 6; i++) {
    if (jeu->tabE[i] == NULL) {
        printf("Erreur : tabE[%d] est NULL. Arrêt du programme.\n", i);
        exit(1);
    }
}
        return *jeu;
   
}



// Affiche les perso pendant la séléction de perso
void afficherPerso(Perso p) {
    printf("\n [Statistiques du personnage]________________________________________________________________________________________________\n");
    printf("| %17s : %-20s %s                                                                        |\n", "Nom", p.nom,"CAPACITE :");
    printf("| %17s : %-3d / %-78d                   |\n", "Points de vie", p.pdv, p.pdv_max);
    printf("| %17s : %-30d %-18s :  %-50s|\n", "Attaque", p.attaque, "NOM" , p.capacite.nom);
    printf("| %17s : %-30d %-18s :  %-50s|\n", "Défense", p.defense,"DESCRIPTION", p.capacite.description);
    printf("| %17s : %-30d %-18s :  %d tours                                           |\n", "Agilité", p.agilite,"DUREE DE L'EFFET", p.capacite.duree_effet);
    printf("| %17s : %-30d %-18s :  %d tours                                           |\n", "Vitesse", p.vitesse_max,"RECHARGE",p.capacite.cooldown);
    if (estSoigneur(&p)) {
        printf("| %17s : %-88d               |\n", "Soin", p.soin);
    }
    printf("|____________________________________________________________________________________________________________________________|\n");
}




// Affiche la jauge de vie
void afficherJaugeVie(Perso* perso) {
    if ( perso == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
    }
   
    int nbBarres = (perso->pdv * 20) / perso->pdv_max;
   
    if (nbBarres > 20){
        nbBarres = 20;
    }

    printf("[");  // alignement du nom
    if( perso->pdv==0){
        printf("  dans le composte  ");
    }

    else{

        for (int i = 0; i < nbBarres; i++) {
            printf("O");
        }
        
        for (int i = nbBarres; i < 20; i++) {
            printf(".");
        }

    }
   
    printf("] %3d/%d", perso->pdv, perso->pdv_max);

}



// Affiche le plateau de jeu
void afficherPlateau(Jeu* jeu) {
    if ( jeu == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
    }
    videTer();
    printf(" _____________\n");
    printf("|   TOUR %3d  |\n",jeu->tour);
    printf("|_____________|\n\n");
    printf("%20s %43s",jeu->equipe1.nom,jeu->equipe2.nom);
    printf("\n");
    printf(" ______________________________________________________________________________________\n");
    printf("|                                                                                      |\n");
    for(int i=0;i<3;i++){
        printf("|%20s %43s                      |\n",jeu->tabE[i]->nom,jeu->tabE[i+3]->nom);
        printf("|      ");
        afficherJaugeVie(jeu->tabE[i]);
        printf("              ");
        afficherJaugeVie(jeu->tabE[i+3]);
        printf("        |\n");
        printf("|      ");
        afficherJaugeVitesse2(jeu->tabE[i]);
        printf("             ");
        afficherJaugeVitesse2(jeu->tabE[i+3]);
        printf("       |\n");
        printf("|                                                                                      |\n");
    }
    printf("|______________________________________________________________________________________|\n");
   
}


//affiche l'équipe gagnante
void afficherGagnant(Jeu jeu){
    int gagnant=finDuJeu(&jeu);
    afficherPlateau(&jeu);
    printf("\n\n");

    char tab[50];
if (gagnant == 1) {
    strcpy(tab, jeu.equipe1.nom);
} else {
    strcpy(tab, jeu.equipe2.nom);
}
    int len = strlen("L'équipe ") + strlen(tab) + strlen(" est le maître du potager !");


    // Ligne du haut
    printf("+");
    for (int i = 0; i < len + 2; i++){
        printf("-");
    }
    printf("+\n");


    // Ligne du texte
    printf("| L'équipe %s est la maître du potager ! |\n", tab);


    // Ligne du bas
    printf("+");
    for (int i = 0; i < len + 2; i++){
        printf("-");
    }
   
    printf("+\n\n\n");
}








// Affiche la jauge de vitesse (s'apelle Vitesse2 car ça a remplacé Vitesse1)
void afficherJaugeVitesse2(Perso* perso) {
    if ( perso == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
    }
    int max = 100;
    int nbBarres = (perso->vitesse * 20) / max;
    if (nbBarres > 20){
        nbBarres = 20;
    }

    printf("[");  
    for (int i = 0; i < nbBarres; i++) {
        printf(">");
    }
    for (int i = nbBarres; i < 20; i++) {
        printf(".");
    }
    printf("] %3d/100", perso->vitesse);
}
