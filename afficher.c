#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "constructeur.h"
#include "afficher.h"
#include "jeu.h"
#include "string.h"
#include "campagne.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
       
    #else
        printf("\033[2J\033[H");
        fflush(stdout);
    #endif
}


void afficherMenu() {
    clearScreen();
    printf(" _[MENU PRINCIPAL] _________________________________________\n");
    printf("|                                                           |\n");
    printf("|        1. Multijoueur        2. Campagne                  |\n");
    printf("|                                                           |\n");
    printf("|___________________________________________________________|\n\n");
   
    printf("Votre choix : ");
   
}
void afficherChoixEq(){
    clearScreen();
    printf(" _[CHOIX DE L'EQUIPE DU JOUEUR 1 ] _____________\n");
    printf("|                                               |\n");
    printf("|        1. Fruits        2. Légumes            |\n");
    printf("|                                               |\n");
    printf("|_______________________________________________|\n\n");
   
    printf("Votre choix : ");
   




}








Jeu menu(Jeu* jeu, int* solo) {
    int choix;
   
    int verif;
   
    afficherMenu();
       
    choix=scanInt(1,2);
    switch (choix) {
         case 1 :
            *jeu=multijoueur(); 
            *solo=0;
             // Appel de la fonction multijoueur
            break;
        case 2:
            *jeu = campagne();
            *solo=1;
            break;
        default:
            printf("Choix invalide.\n");
    }
 
    for (int i = 0; i < 3; i++) {
            jeu->tabE[i] =  &(jeu->equipe1.membres[i]);
            jeu->tabE[i + 3] = &(jeu->equipe2.membres[i]);
        }
        for (int i = 0; i < 6; i++) {
            jeu->tabE[i]->num=i;
    }
        return *jeu;
   
}




void afficherPerso(Perso p) {
   
    printf("\n [Statistiques du personnage]________________________________________________________________________________________________\n");
    printf("| %17s : %-20s %s                                                                        |\n", "Nom", p.nom,"CAPACITE :");
    printf("| %17s : %-3d / %-78d                   |\n", "Points de vie", p.pdv, p.pdv_max);
    printf("| %17s : %-30d %-18s :  %-50s|\n", "Attaque", p.attaque, "NOM" , p.capacite.nom);
    printf("| %17s : %-30d %-18s :  %-50s|\n", "Défense", p.defense,"DESCRIPTION", p.capacite.description);
    printf("| %17s : %-30d %-18s :  %d tours                                           |\n", "Agilité", p.agilite,"DUREE DE L'EFFET", p.capacite.duree_effet);
    printf("| %17s : %-30d %-18s :  %d tours                                           |\n", "Vitesse", p.vitesse,"RECHARGE",p.capacite.cooldown);
    if (estSoigneur(&p)) {
        printf("| %17s : %-88d               |\n", "Soin", p.soin);
    }
    printf("|____________________________________________________________________________________________________________________________|\n");
}




// void afficherCapacite(int n, Ult capacites[], int nbCapacites) {
   
//     for (int i = 0; i < nbCapacites; i++) {
//         if (capacites[i].id == n) {
//             printf("|____________________________________________________________|\n");
//             printf("| %-18s :  %-13s                       |\n", "NOM" , capacites[i].nom);
//             printf("| %-18s :  %-13s                       |\n","DESCRIPTION", capacites[i].description);
//             printf("| %-18s :  %-13d tours                 |\n", "DUREE DE L'EFFET", capacites[i].duree_effet);
//             printf("| %-18s :  %-13d tours                 |\n", "RECHARGE",capacites[i].cooldown);
//             printf("|____________________________________________________________|\n");
//             return;  
//         }
//     }
// }






void afficherEquipe(Equipe *equipe, char *n) {


    printf("\n_______________________ %18s : %-8s                   \n", n, equipe->nom);


    // Affichage des noms avec une largeur fixe
    printf("| %-13s | %-13s | %-13s | %-13s |\n", " ",equipe->membres[0].nom, equipe->membres[1].nom, equipe->membres[2].nom);


    // Lignes de stats
    printf("| %-13s | %-13d | %-13d | %-13d |\n", "PDV max",equipe->membres[0].pdv_max, equipe->membres[1].pdv_max, equipe->membres[2].pdv_max);


    printf("| %-13s | %-13d | %-13d | %-13d |\n", "Attaque",equipe->membres[0].attaque, equipe->membres[1].attaque, equipe->membres[2].attaque);


    printf("| %-13s | %-13d | %-13d | %-13d |\n", "Défense",equipe->membres[0].defense, equipe->membres[1].defense, equipe->membres[2].defense);


    printf("| %-13s | %-13d | %-13d | %-13d |\n", "Vitesse",equipe->membres[0].vitesse, equipe->membres[1].vitesse, equipe->membres[2].vitesse);


    printf("| %-13s | %-13d | %-13d | %-13d |\n", "Agilité",equipe->membres[0].agilite, equipe->membres[1].agilite, equipe->membres[2].agilite);
   
    printf("| %-13s | %-13d | %-13d | %-13d |\n", "Soin",equipe->membres[0].soin, equipe->membres[1].soin, equipe->membres[2].soin);
   
    printf("|_______________________________________________________________|\n");
}
void afficherJaugeVie(Perso* perso) {
   
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




void afficherPlateau(Jeu* jeu) {
    clearScreen();
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
        printf("      |\n");
        printf("|      ");
        afficherJaugeVitesse2(jeu->tabE[i]);
        printf("              ");
        afficherJaugeVitesse2(jeu->tabE[i+3]);
        printf("      |\n");
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


void afficherJaugeVitesse(Perso* perso) {
    int max = 100;
    int nbBarres = (perso->vitesse * 20) / max;
    if (nbBarres > 20) nbBarres = 20;


    printf("%-12s [", perso->nom);  // alignement du nom
    for (int i = 0; i < nbBarres; i++) {
        printf("#");
    }
    for (int i = nbBarres; i < 20; i++) {
        printf("-");
    }
    printf("] %3d/100\n", perso->vitesse);
}








void afficherJaugeVitesse2(Perso* perso) {
    int max = 100;
    int nbBarres = (perso->vitesse * 20) / max;
    if (nbBarres > 20) nbBarres = 20;




    printf("[");  // alignement du nom
    for (int i = 0; i < nbBarres; i++) {
        printf(">");
    }
    for (int i = nbBarres; i < 20; i++) {
        printf(".");
    }
    printf("] %3d/100", perso->vitesse);
}
