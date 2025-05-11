#ifndef AFFICHER_H
#define AFFICHER_H

#include "constructeur.h"

void afficherMenu();
void clearScreen();
void afficherChoixEq();
void afficherPlateau(Jeu* jeu);
Jeu menu();
void afficherPerso(Perso p);
void afficherEquipe(Equipe *equipe, char *titre);
void afficherCapacite(int n, Ult capacites[], int nbCapacites);
void afficherGagnant(Jeu jeu);

void afficherJaugeVitesse2(Perso* perso);
#endif