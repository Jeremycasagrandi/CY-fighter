#ifndef CAPACITE_CLASSIQUE_H
#define CAPACITE_CLASSIQUE_H

#include "constructeur.h"  

Perso* choix_perso_allie(Equipe* equipe);
Perso* choix_perso_ennemi(Equipe* equipe);
void attaque(Jeu* jeu, Perso* perso, int idEquipe, int bonus_ult);
void soin(Jeu* jeu, Perso* soigneur, int idEquipe);
int estSoigneur(Perso* p);
int soinDisponible(Equipe* equipe);
int defense(Perso* cible, int degats);
int esquive(Perso* cible);
#endif