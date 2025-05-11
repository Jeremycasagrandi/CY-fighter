#include <stdio.h>
#include "effet.h"
#include <stdlib.h>
//met a jour la durée des effets actifs sur un personnage
void mettreAJourEffets(Perso* perso) {
    if ( perso == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
    }
    //Parcourt tous les effets actifs
    for (int i = 0; i < perso->nb_effets_actifs;) {
        //réduit la durée restante de l'effet
        perso->effets[i].duree_restant--;

        //Si l'effet est terminé
        if (perso->effets[i].duree_restant <= 0) {
            //supprime l'effet et décale les suivants vers la gauche 
            for (int j = i; j < perso->nb_effets_actifs - 1; j++) {
                perso->effets[j] = perso->effets[j + 1];
            }
            //décrémente le nombre d'effets actifs
            perso->nb_effets_actifs--;
            //pas besoin de i++ car décaler vers la gauche donc le nouvel effet est copié à l'indice i
        } else { //Passe à l'effet suivant
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
                printf("[%s a %d de défense]\n\n", perso->nom, effet->valeur);
                perso->defense = effet->valeur;
                break;

            case 3:  // Soin progressif
                if (perso->pdv > 0) {  // Ne soigne que si le personnage est vivant
                    perso->pdv += effet->valeur;
                    if (perso->pdv > perso->pdv_max) {
                        perso->pdv = perso->pdv_max;
                    } 
                printf("%s récupère %d PV grâce à un effet de soin. PV actuels : %d\n", perso->nom, effet->valeur, perso->pdv);
                }
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