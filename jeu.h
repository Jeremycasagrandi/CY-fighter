#ifndef JEU_H
#define JEU_H

#include "constructeur.h"  
Jeu menu();
Jeu multijoueur();
int tour();
void debut();
void choisirAction(Jeu* jeu, int indexEquipe);
int finDuJeu(Jeu* jeu);


#endif