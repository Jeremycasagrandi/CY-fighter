#ifndef JEU_H
#define JEU_H

#include "constructeur.h"  
Jeu menu();
Jeu multijoueur();
int tour();
void debut();
void choisirAction(Jeu* jeu, int indexEquipe);
int finDuJeu(Jeu* jeu);
int estVivant(Perso* p);
void attaque(Jeu* jeu, Perso* perso, int idEquipe);
void soin(Jeu* jeu, Perso* perso, int idEquipe);
int estSoigneur(Perso* p);
int soinDisponible(Equipe* equipe);
#endif