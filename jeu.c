#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "jeu.h"
#include "afficher.h"
#include "constructeur.h"

void vide_buffer(){
    while (getchar() != '\n') {}
    
}

int scanInt(int min, int max){
    int verif;
    int n;
    do {
        
        verif = scanf("%d", &n);

        
        while (getchar() != '\n') {}

        if (verif != 1 || n < min || n > max) {
            printf("Erreur : veuillez entrer un entier valide entre %d et %d.\n", min, max);
        }
    } while (verif != 1 || n < min || n > max);

    return n;
}



//regarde si une equipe est éléminé, retourne 1 si equipe 1 gagne, 2 si equipe 2 gagne
int finDuJeu(Jeu* jeu){
    Equipe eq1=jeu->equipe1;
    Equipe eq2=jeu->equipe2;
    if (eq1.membres[0].pdv<=0&&eq1.membres[1].pdv<=0&&eq1.membres[2].pdv<=0){
        return 2;
    }
    else if (eq2.membres[0].pdv<=0&&eq2.membres[1].pdv<=0&&eq2.membres[2].pdv<=0){
        return 1;
    }
    else{
        return 0;
    }
}



int tour(Jeu* jeu) {
    
    while (1) {
        for (int i = 0; i < 3; i++) {
            // Vérification pour l'équipe 1
            if (estVivant(&jeu->equipe1.membres[i])) {
                jeu->equipe1.membres[i].vitesse--;
                if (jeu->equipe1.membres[i].vitesse <= 0) {
                    jeu->equipe1.membres[i].vitesse = jeu->equipe1.membres[i].vitesse_max;
                    return i;  // Retourner le joueur de l'équipe 1
                }
            }

            // Vérification pour l'équipe 2
            if (estVivant(&jeu->equipe2.membres[i])) {
                jeu->equipe2.membres[i].vitesse--;
                if (jeu->equipe2.membres[i].vitesse <= 0) {
                    jeu->equipe2.membres[i].vitesse = jeu->equipe2.membres[i].vitesse_max;
                    return i + 3;  // Retourner le joueur de l'équipe 2
                }
            }
        }
    }
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

int estVivant(Perso* p) {
    return p->pdv > 0;
}

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


void choisirAction(Jeu* jeu, int indexEquipe) {
    int choix;
    Equipe* equipeJoueur;
    int idEquipe;
    
    
    if (indexEquipe < 3) { 
        equipeJoueur = &jeu->equipe1;
        idEquipe=1;
    } else {
        equipeJoueur = &jeu->equipe2;
        indexEquipe -= 3;  
        idEquipe=2;
    }

    
    Perso* perso = &equipeJoueur->membres[indexEquipe];

    printf("\nC'est au tour de %s !\n", perso->nom);
    //effet_special()
    printf("1. Attaquer\n");
    printf("2. Utiliser capacité ultime\n");
    if (estSoigneur(perso)){
        if (soinDisponible(equipeJoueur)){
            printf("3. Soin\n");
        }
        else{
            printf("3.Soin indisponible (PV max pour les persos)\n");
        }
    }
    
    
    do {
        printf("Choisissez une action (1, 2 ou 3) : ");
        choix = scanInt(1,3);
        if (choix == 3 && !estSoigneur(perso)) {
            printf("Action invalide. Ce personnage n'est pas un soigneur .\n");
        }
    } while ((choix < 1 || choix > 3) || (choix == 3 && (!estSoigneur(perso) || !soinDisponible(equipeJoueur))));
    switch (choix) {
        case 1:  // Attaque
            printf("%s attaque un membre de l'équipe adverse !\n", perso->nom);
            attaque(jeu, perso, idEquipe);
            break;
        
        case 2:  // Utiliser capacité ultime
            printf("%s utilise sa capacité ultime !\n", perso->nom);
            // ult(jeu, )
            break;
        case 3:
            printf("%s soigne un allié !\n", perso->nom);
            soin(jeu, perso, idEquipe);
            
            break;
        
        default:
            printf("Choix invalide.\n");
            break;
    }
}

