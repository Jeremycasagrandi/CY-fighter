#ifndef JEU_H
#define JEU_H

#include "constructeur.h" 
#include "afficher.h"
#include "capacite_speciale.h"
#include "capacite_classique.h"
void vide_buffer();
int scanInt(int min, int max);
int finDuJeu(Jeu* jeu);
int trouverIndexVitesseMax(Perso* tab[]);
int tour(Jeu* jeu);
int estVivant(Perso* p);
int Aulti(Perso* perso);
void choisirAction(Jeu* jeu, int indexEquipe);

#endif