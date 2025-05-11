#include <stdio.h>
#include "effet.h"
void mettreAJourEffets(Perso* perso) {
    if ( perso == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
    }
    for (int i = 0; i < perso->nb_effets_actifs;) {
        perso->effets[i].duree_restant--;


        if (perso->effets[i].duree_restant <= 0) {
            for (int j = i; j < perso->nb_effets_actifs - 1; j++) {
                perso->effets[j] = perso->effets[j + 1];
            }
            perso->nb_effets_actifs--;
        } else {
            i++;
        }
    }
}
void appliquerEffets(Perso* perso) {
    if ( perso == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
    }
    for (int i = 0; i < perso->nb_effets_actifs; i++) {
        Effet* effet = &perso->effets[i];
        switch (effet->id) {
            case 0:  // Perte de PV par tour
                perso->pdv -= effet->valeur;
                if (perso->pdv < 0){
                    perso->pdv = 0;
                } 
                printf("%s subit %d dégâts de l'effet.  PV restants : %d\n", perso->nom, effet->valeur, perso->pdv);
                break;


            case 1:  // Réduit l'attaque, la defense et l'agilité 
                printf("%s subit un affaiblissement temporaire (-10 atk, def, agi).\n", perso->nom);
                perso->attaque += perso->effets[i].valeur;
                perso->defense += perso->effets[i].valeur;
                perso->agilite += perso->effets[i].valeur;
                break;


            case 2:  // Bonus de défense
                printf("[%s a 50 de défense]\n\n", perso->nom);
                perso->defense = effet->valeur;
                break;

            case 3:  // Soin progressif
                perso->pdv += effet->valeur;
                if (perso->pdv > perso->pdv_max){
                    perso->pdv = perso->pdv_max;
                } 
                printf("%s récupère %d PV grâce à un effet de soin. PV actuels : %d\n", perso->nom, effet->valeur, perso->pdv);
                break;
            case 4:  // Invincibilité 
                perso->defense = effet->valeur;
                printf("%s est invincible ! \n", perso->nom);
                break;
            default:
                printf("%s a un effet inconnu (id: %d)\n", perso->nom, effet->id);
                break;
        }
    }
}