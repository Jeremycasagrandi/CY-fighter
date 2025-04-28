#include <stdio.h>

typedef struct {
    char nom[20];
} Ult;

typedef struct {
    char nom [50];

    int pdv;         
    int pdv_max;    
    int attaque; 
    int defense;
    int agilite;
    int vitesse;
    Ult capacité;
} Perso;



typedef struct {
    Perso membres[3];
    char nom[50];
} Equipe;

typedef struct {
    Equipe equipe1;
    Equipe equipe2;
    
    
} Jeu;



void afficherPerso(Perso p);


