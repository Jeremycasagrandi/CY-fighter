#ifndef CONSTRUCTEUR_H
#define CONSTRUCTEUR_H
#include <stdio.h>
#define MAX_PERSOS 20


typedef struct {
    char nom[20];
} Ult;

typedef struct {
    int id;
    char nom [50];

    int pdv;         
    int pdv_max;    
    int attaque; 
    int defense;
    int agilite;
    int vitesse;
    int vitesse_max;
    Ult capacite;
} Perso;



typedef struct {
    Perso membres[3];
    char nom[50];
} Equipe;

typedef struct {
    Equipe equipe1;
    Equipe equipe2;
    
    
} Jeu;


Perso creationperso();
void chargerPersos(Perso persos[], const char* nomFichier, int *nb);

void afficherPerso(Perso p);
#endif


