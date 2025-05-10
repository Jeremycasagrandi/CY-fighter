#include <stdio.h>
#include "capacite_classique.h"
#include "jeu.h"
#include <stdlib.h>


// Capacité de soin
int estSoigneur(Perso* p) {
    return p->soin > 0;
}
//Eviter boucle infini dans soin()
int soinDisponible(Equipe* equipe) {
    for (int i = 0; i < 3; i++) {
        if (estVivant(&equipe->membres[i]) && (equipe->membres[i].pdv < equipe->membres[i].pdv_max)) {
            return 1; // Soin possible pour des persos encore vivant
        }
    }
    return 0; // aucun soin possible
}

int defense(Perso* cible, int degats) {
    int reduction=0;
    //peut etre pour les capacités spéciales
    if (cible->defense < 0){
        cible->defense = 0;
    } 
    if (cible->defense > 100){
        cible->defense = 100;
    } 

    reduction = (degats * cible->defense) / 100;
    return degats - reduction;
}

int esquive(Perso* cible) {
    int chance=0;
    //peut etre pour les capacités spéciales
    if (cible->agilite < 0){
        cible->agilite = 0;
    } 
    if (cible->agilite > 100){
        cible->agilite = 100;
    } 

    chance = rand() % 100;  
    return chance < cible->agilite;
}
//permet enlever des pv a un membre de l'équipe adverse
void attaque(Jeu* jeu,Perso* perso, int idEquipe){
    
    //choix de l'adversaire
    int choix;
    Perso* cible;
    if (idEquipe==1){
        do {
            printf("tu veux attaquer %s (1),%s(2) ou %s(3) ",jeu->equipe2.membres[0].nom,jeu->equipe2.membres[1].nom,jeu->equipe2.membres[2].nom);
            choix = scanInt(1,3);
            if (!estVivant(&jeu->equipe2.membres[choix - 1])){
                printf("Il est déjà mort. Vous ne pouvez plus l'attaquer. ");
            }
        } while (choix < 1 || choix > 3 || !estVivant(&jeu->equipe2.membres[choix - 1])); 
        cible=&jeu->equipe2.membres[choix-1];
        
    }
    else {
        do {
            printf("tu veux attaquer %s (1),%s(2) ou %s(3)",jeu->equipe1.membres[0].nom,jeu->equipe1.membres[1].nom,jeu->equipe1.membres[2].nom);
            choix = scanInt(1,3);
            if (!estVivant(&jeu->equipe2.membres[choix - 1])){
                printf("Il est déjà mort. Vous ne pouvez plus l'attaquer. ");
            }
        } while (choix < 1 || choix > 3 || !estVivant(&jeu->equipe1.membres[choix - 1])); 
        cible=&jeu->equipe1.membres[choix-1];
       
    }

    // vérifie si l'attaque est esquivée
    if (esquive(cible)) {
        printf("%s a esquivé l'attaque !\n", cible->nom);
        return;
    }

    // calcule les dégats réels 
    int degats = defense(cible, perso->attaque);
    cible->pdv -= degats;

    printf("%s subit %d dégâts.\n", cible->nom, degats);
    if (cible->pdv < 0) {
        cible->pdv = 0;  // Pour éviter d'afficher des pdv négatifs
    }
}

void soin(Jeu* jeu, Perso* perso, int idEquipe) {
    // Choix de l'allié à soigner
    int choix;
    Perso* cible;

    if (idEquipe == 1) {
        do {
            printf("Tu veux soigner %s (1), %s (2) ou %s (3) : ", jeu->equipe1.membres[0].nom, jeu->equipe1.membres[1].nom, jeu->equipe1.membres[2].nom);
            choix = scanInt(1,3);
            if (!estVivant(&jeu->equipe1.membres[choix - 1])) {
                printf("Il est déjà mort. Vous ne pouvez plus le soigner.\n");
            }
             else if (jeu->equipe1.membres[choix - 1].pdv == jeu->equipe1.membres[choix - 1].pdv_max) {
                printf("Ce personnage a déjà tous ses points de vie.\n");
            }
        } while (choix < 1 || choix > 3 || !estVivant(&jeu->equipe1.membres[choix - 1]));

        cible = &jeu->equipe1.membres[choix - 1];
    } 
    else {
        do {
            printf("Tu veux soigner %s (1), %s (2) ou %s (3) : ", jeu->equipe2.membres[0].nom, jeu->equipe2.membres[1].nom, jeu->equipe2.membres[2].nom);
            choix = scanInt(1,3);
            if (!estVivant(&jeu->equipe2.membres[choix - 1])) {
                printf("Il est déjà mort. Vous ne pouvez plus le soigner.\n");
            } 
            else if (jeu->equipe2.membres[choix - 1].pdv == jeu->equipe2.membres[choix - 1].pdv_max) {
                printf("Ce personnage a déjà tous ses points de vie.\n");
            }
        } while (choix < 1 || choix > 3 || !estVivant(&jeu->equipe2.membres[choix - 1])||jeu->equipe1.membres[choix - 1].pdv == jeu->equipe1.membres[choix - 1].pdv_max);

        cible = &jeu->equipe2.membres[choix - 1];
    }

    // Applique le soin
    cible->pdv += perso->soin;

    
    if (cible->pdv > cible->pdv_max) {
        cible->pdv = cible->pdv_max;
    }
}

