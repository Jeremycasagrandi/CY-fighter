#ifndef CAPACITE_CLASSIQUE_H
#define CAPACITE_CLASSIQUE_H

#include "constructeur.h"  

// Fonctions exportées
void attaque(Jeu* jeu, Perso* attaquant, int idEquipe);
void soin(Jeu* jeu, Perso* soigneur, int idEquipe);
int estSoigneur(Perso* p);
int soinDisponible(Equipe* equipe);

#endif