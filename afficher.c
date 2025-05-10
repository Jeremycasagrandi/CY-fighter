#include <stdio.h>
#include "constructeur.h"
#include "afficher.h"
#include "jeu.h"

void afficherMenu() {
    printf(" _[MENU PRINCIPAL] _________________________________________\n");
    printf("|                                                           |\n");
    printf("|        1. Multijoueur        2. Campagne                  |\n");
    printf("|                                                           |\n");
    printf("|___________________________________________________________|\n\n");
    
    printf("Votre choix : ");
}

Jeu menu() {
    int choix;
    Jeu jeu;
    int verif;
    
    afficherMenu();
        
    choix=scanInt(1,2);
    switch (choix) {
         case 1 :
            jeu=multijoueur();  // Appel de la fonction multijoueur
            break;
        case 2:
            //campagne();
            break;
        default:
            printf("Choix invalide.\n");
    }
    
    return jeu;
    
}


void afficherPerso(Perso p) {
    printf("\n_[Statistiques du personnage______________________________________\n");
    printf("| %17s : %-42s |\n", "Nom", p.nom);
    printf("| %17s : %-3d / %-36d |\n", "Points de vie", p.pdv, p.pdv_max);
    printf("| %17s : %-42d |\n", "Attaque", p.attaque);
    printf("| %17s : %-42d |\n", "Défense", p.defense);
    printf("| %17s : %-42d |\n", "Agilité", p.agilite);
    printf("| %17s : %-42d |\n", "Vitesse", p.vitesse);
    if (estSoigneur(&p)) {
        printf("| %17s : %-42d |\n", "Soin", p.soin);
    }
    printf("|________________________________________________________________|\n");

}



void afficherEquipe(Equipe *equipe, char *n) {
    printf("\n_______________________ %18s : %-8s __________\n", n, equipe->nom);

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

void afficherCapacite(int n, Ult capacites[], int nbCapacites) {
    
    for (int i = 0; i < nbCapacites; i++) {
        if (capacites[i].id == n) {
            printf("|____________________________________________________________|\n");
            printf("| %-18s :  %-13s                       |\n", "NOM" , capacites[i].nom);
            printf("| %-18s :  %-13s                       |\n","DESCRIPTION", capacites[i].description);
            printf("| %-18s :  %-13d tours                 |\n", "DUREE DE L'EFFET", capacites[i].duree_effet);
            printf("| %-18s :  %-13d tours                 |\n", "RECHARGE",capacites[i].cooldown);
            printf("|____________________________________________________________|\n");
            return;  
        }
    }
}

//affiche l'équipe gagnante
void afficherGagnant(Jeu jeu){
    int gagnant=finDuJeu(&jeu);
    if (gagnant==1){
        printf("L'équipe %s a gagné",jeu.equipe1.nom);
    }
    else{
        printf("L'équipe %s a gagné",jeu.equipe2.nom);
    }
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