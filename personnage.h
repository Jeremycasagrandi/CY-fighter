#include <stdio.h>

typedef struct {
    int pdv;         
    int pdv_max;    
    int attaque;
    int defense;
    int agilite;
    int vitesse;
} Perso;

Perso creationperso();
void afficherPerso(Perso p);