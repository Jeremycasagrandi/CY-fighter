#ifndef CAPACITE_SPECIALE_H
#define CAPACITE_SPECIALE_H

#include "jeu.h" 
#include "constructeur.h"
#include "capacite_classique.h"
void ult(Jeu* jeu, Perso* perso_Ult, int idEquipe);
void ajouter_effet(Perso* cible, int idEffet, int valeur, int duree);
Equipe* equipe_alliee(Jeu* jeu, int idEquipe);
Equipe* equipe_ennemie(Jeu* jeu, int idEquipe);

void capacite0(Jeu* jeu, Perso* perso_Ult, int idEquipe);
void capacite1(Jeu* jeu, Perso* perso_Ult, int idEquipe);
void capacite2(Jeu* jeu, Perso* perso_Ult, int idEquipe);
void capacite3(Jeu* jeu, Perso* perso_Ult, int idEquipe);
void capacite4(Jeu* jeu, Perso* perso_Ult, int idEquipe);
void capacite5(Jeu* jeu, Perso* perso_Ult, int idEquipe);
void capacite6(Jeu* jeu, Perso* perso_Ult, int idEquipe);
void capacite7(Jeu* jeu, Perso* perso_Ult, int idEquipe);
void capacite8(Jeu* jeu, Perso* perso_Ult, int idEquipe);
void capacite9(Jeu* jeu, Perso* perso_Ult, int idEquipe);
void capacite10(Jeu* jeu, Perso* perso_Ult, int idEquipe);
void capacite11(Jeu* jeu, Perso* perso_Ult, int idEquipe);

#endif
