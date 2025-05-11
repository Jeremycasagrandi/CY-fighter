#include <stdio.h>
#include "capacite_classique.h"
#include "jeu.h"
#include <stdlib.h>
#include <unistd.h>


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

Perso* choix_perso_allie(Equipe* equipe) {
    int choix;
    do {
        printf("Choisis un allié : %s (1), %s (2), %s (3) : ",
            equipe->membres[0].nom, equipe->membres[1].nom, equipe->membres[2].nom);
        choix = scanInt(1, 3);
        if (!estVivant(&equipe->membres[choix - 1])) {
            printf("Il est déjà mort. Vous ne pouvez plus le cibler.\n");
        }
    } while (choix < 1 || choix > 3 || !estVivant(&equipe->membres[choix - 1]));

    return &equipe->membres[choix - 1];
}

Perso* choix_perso_ennemi(Equipe* equipe) {
    int choix;
    do {
        printf("\nChoisis un ennemi : %s (1), %s (2), %s (3) : ",
            equipe->membres[0].nom, equipe->membres[1].nom, equipe->membres[2].nom);
        choix = scanInt(1, 3);
        if (!estVivant(&equipe->membres[choix - 1])) {
            printf("\n[Il est déjà mort. Vous ne pouvez plus l'attaquer.]\n");
        }
    } while (choix < 1 || choix > 3 || !estVivant(&equipe->membres[choix - 1]));

    return &equipe->membres[choix - 1];
}

//permet enlever des pv a un membre de l'équipe adverse
void attaque(Jeu* jeu,Perso* perso, int idEquipe, int bonus_ult){
    afficherPlateau(jeu);
    printf("\n%s attaque un membre de l'équipe adverse !\n", perso->nom);
    
    //choix de l'adversaire
    int choix;
    Perso* cible;
    if (idEquipe == 1) {
        cible = choix_perso_ennemi(&jeu->equipe2);
    } else {
        cible = choix_perso_ennemi(&jeu->equipe1);
    }

    // vérifie si l'attaque est esquivée
    if (esquive(cible)) {
        printf("\n%s a esquivé l'attaque !\n", cible->nom);
        return;
    }

    // calcule les dégats réels 
    int degats = defense(cible, perso->attaque)+bonus_ult;
    cible->pdv -= degats;
    if (bonus_ult!=0){
        printf("\n%s subit %d dégâts\n", cible->nom, degats);
        //printf("\n%s subit %d dégâts (%d (attaque de base) %d(ult)).\n", cible->nom, degats, perso->attaque,bonus_ult);
    }
    else{
        printf("\n%s subit %d dégâts .\n", cible->nom, degats);
    }

    if (cible->pdv < 0) {
        cible->pdv = 0;  // Pour éviter d'afficher des pdv négatifs
    }
    
    sleep(3);
}

void soin(Jeu* jeu, Perso* perso, int idEquipe) {
    // Choix de l'allié à soigner
    Perso* cible;
    Equipe* equipe;
    afficherPlateau(jeu);
    printf("\n%s soigne un allié !\n\n", perso->nom);

    if (idEquipe == 1) {
        equipe = &jeu->equipe1;
    } else {
        equipe = &jeu->equipe2;
    }

    do {
        cible = choix_perso_allie(equipe);
        if (cible->pdv == cible->pdv_max) {
            printf("\n[Ce personnage a déjà tous ses points de vie.]\n");
        }
    } while (cible->pdv == cible->pdv_max);

    // Applique le soin
    cible->pdv += perso->soin;
    printf("\n%s est soigné de %d Pv\n\n", cible->nom,perso->soin);

    sleep(3);
    
    if (cible->pdv > cible->pdv_max) {
        cible->pdv = cible->pdv_max;
    }
}

