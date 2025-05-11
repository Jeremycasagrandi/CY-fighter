#ifndef CONSTRUCTEUR_H
#define CONSTRUCTEUR_H
#include <stdio.h>
#define MAX_PERSOS 20
#define MAX_CAPACITES 20
#define MAX_EFFETS 10

typedef struct {
    int id;
    char nom[50];
    char description[200];
    int duree_effet;    
    int cooldown;   
    int cooldown_max;
} Ult;

typedef struct {
    int id;                
    int valeur;            
    int duree_restant;      
} Effet;

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
    int soin;
    Ult capacite;
    int num;
    Effet effets[MAX_EFFETS];
    int nb_effets_actifs;
} Perso;



typedef struct {
    Perso membres[3];
    char nom[50];
    int id;

} Equipe;

typedef struct {
    Equipe equipe1;
    Equipe equipe2;
    Perso* tabE[6];
    
    
} Jeu;


Perso creationperso();
void chargerPersos(Perso persos[], Ult capacites[], const char* nomFichierPersos, const char* nomFichierCapacites, int *nbPersos, int *nbCapacites);
Jeu multijoueur();
void afficherPerso(Perso p);
void afficherCapacite(int n, Ult capacites[], int nbCapacites);
#endif


