#ifndef CAMPEGNE_H
#define CAMPEGNE_H

#include "jeu.h"
#include "constructeur.h"
Perso* choix_perso_ennemi_robot(Equipe* equipe);
Perso* choix_perso_ennemi(Equipe* equipe);
Equipe choixPersonnage(int n);
void attaqueRobot(Jeu* jeu, Perso* perso, int idEquipe, int bonus_ult);
int choisirActionRobot(Jeu* jeu, int indexEquipe);
Equipe choixPersonnageRobot(int n);
Jeu campagne();
void mettreAJourEffets(Perso* perso);
#endif
