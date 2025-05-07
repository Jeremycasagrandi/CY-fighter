#ifndef CONSTRUCTEUR_H
#define CONSTRUCTEUR_H
#include <stdio.h>
#define MAX_PERSOS 20
#define MAX_CAPACITES 20

typedef struct {
    int id;
    char nom[50];
    char description[200];
    int duree_effet;    
    int cooldown;      
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
    int id;

} Equipe;

typedef struct {
    Equipe equipe1;
    Equipe equipe2;
    
    
} Jeu;


Perso creationperso();
void chargerPersos(Perso persos[], Ult capacites[], const char* nomFichierPersos, const char* nomFichierCapacites, int *nbPersos, int *nbCapacites);

void afficherPerso(Perso p);
void afficherCapacite(int n, Ult capacites[], int nbCapacites);
#endif


