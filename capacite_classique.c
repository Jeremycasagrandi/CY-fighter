#include <stdio.h>
#include "capacite_classique.h"
#include "jeu.h"



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

//permet enlever des pv a un membre de l'équipe adverse
void attaque(Jeu* jeu,Perso* perso, int idEquipe){
    
    //choix de l'adversaire
    int choix;
    Perso* cible;
    if (idEquipe==1){
        do {
            printf("tu veux attaquer %s (1),%s(2) ou %s(3)",jeu->equipe2.membres[0].nom,jeu->equipe2.membres[1].nom,jeu->equipe2.membres[2].nom);
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

    //retire pv a l'adversaire
    cible->pdv-=perso->attaque;
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

