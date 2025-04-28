#include <stdio.h>

typedef struct {
    char nom [50];

    int pdv;         
    int pdv_max;    
    int attaque;
    int defense;
    int agilite;
    int vitesse;
} Perso;

typedef struct{
    
}Equipe;
Perso creationperso();
void afficherPerso(Perso p);

typedef struct {
    char nom[20];
    Perso membres[3]; 
} Equipe;

typedef struct {
    char nom[20];
}Ult;

