#include <stdio.h>
#include "capacite_speciale.h"

void ult(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
    printf("\n %d\n", perso_Ult->capacite.id);
    switch (perso_Ult->capacite.id) {
        case 0:  
        capacite0(jeu, perso_Ult, idEquipe); 
        break;
        case 1:  
        capacite1(jeu, perso_Ult, idEquipe); 
        break;
        case 2:  
        capacite2(jeu, perso_Ult, idEquipe); 
        break;
        case 3:  
        capacite3(jeu, perso_Ult, idEquipe); 
        break;
        case 4:  
        capacite4(jeu, perso_Ult, idEquipe); 
        break;
        case 5:  
        capacite5(jeu, perso_Ult, idEquipe); 
        break;
        case 6:  
        capacite6(jeu, perso_Ult, idEquipe); 
        break;
        case 7:  
        capacite7(jeu, perso_Ult, idEquipe); 
        break;
        case 8:  
        capacite8(jeu, perso_Ult, idEquipe); 
        break;
        case 9:  
        capacite9(jeu, perso_Ult, idEquipe); 
        break;
        case 10: 
        capacite10(jeu, perso_Ult, idEquipe); 
        break;
        case 11: 
        capacite11(jeu, perso_Ult, idEquipe); 
        break;
        default:
            printf("Erreur\n");
            break;
    }
}









void capacite0(Jeu* jeu, Perso* perso_Ult, int idEquipe) { //capacité de pasteque
    
    Equipe* equipeEnnemi;
    if (idEquipe == 1) {
        equipeEnnemi = &jeu->equipe2; 
    } else {
        equipeEnnemi = &jeu->equipe1;
    }

    // Choix de la cible qui vera sa vitesse reset
    Perso* cible = choix_perso_ennemi(equipeEnnemi);
    cible->vitesse=0;

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite1(Jeu* jeu, Perso* perso_Ult, int idEquipe) {//capacite de noix de coco
    Equipe* equipeAlliee;
    if (idEquipe == 1) {
        equipeAlliee = &jeu->equipe1;
    } else {
        equipeAlliee = &jeu->equipe2;
    }

    printf("%s renforce la défense de toute son équipe pour %d tours .\n", perso_Ult->nom, perso_Ult->capacite.duree_effet);
    //parcourt tout les persos de l'équipe
    for (int i = 0; i < 3; i++) {
        Perso* allie = &equipeAlliee->membres[i];
        //effet appliqué aux persos vivants
        if (allie->pdv > 0) {
            Effet buffDefense;
            buffDefense.id = 2; //pour le switch case de Appliquer_Effet()
            buffDefense.valeur = 30; 
            buffDefense.duree_restant = perso_Ult->capacite.duree_effet;

            //Ajoute à l'indice suivant de la liste des effets actifs le buff de defense
            allie->effets[allie->nb_effets_actifs++] = buffDefense;
            printf("%s aura 30 en défense pour %d tours.\n", allie->nom, buffDefense.duree_restant);

        }
    }

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}


void capacite2(Jeu* jeu, Perso* perso_Ult, int idEquipe) {//capacité de litchi
    //3 attaques normales /2
    int bonus_ult = 0;
    bonus_ult-=perso_Ult->attaque/2;
    attaque(jeu, perso_Ult, idEquipe, bonus_ult);
    attaque(jeu, perso_Ult, idEquipe, bonus_ult);
    attaque(jeu, perso_Ult, idEquipe, bonus_ult);
    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite3(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
    Equipe* cible;
    if (idEquipe == 1) {
        cible = &jeu->equipe2;
    } else {
        cible = &jeu->equipe1;
    }

    printf("%s utilise une attaque de poison !\n", perso_Ult->nom);

    // Choix de l' ennemi
    Perso* adversaire = choix_perso_ennemi(cible);  


    
    Effet acide;
    acide.id = 0;  
    acide.valeur = 10;  // dégâts par tour 
    acide.duree_restant = perso_Ult->capacite.duree_effet;

    adversaire->effets[adversaire->nb_effets_actifs++] = acide;
    printf("%s est empoisonné pour %d tours !\n", adversaire->nom, acide.duree_restant);

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite4(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
    Equipe* equipeAlliee;
    if (idEquipe == 1) {
        equipeAlliee = &jeu->equipe1;
    } else {
        equipeAlliee = &jeu->equipe2;
    }
    Perso* alliee = choix_perso_ennemi(equipeAlliee);
    alliee->pdv = alliee->pdv_max;
    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite5(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
    Equipe* equipeAlliee;

    if (idEquipe == 1) {
        equipeAlliee = &jeu->equipe1;
    } else {
        equipeAlliee = &jeu->equipe2;
    }

    printf("%s soigne toute son équipe !\n", perso_Ult->nom);
    //Parcourt les 3 membres de l'équipe
    for (int i = 0; i < 3; i++) {
        Perso* allie = &equipeAlliee->membres[i];

        if (allie->pdv > 0) {
            int soin = allie->pdv_max * 0.3;  // soigne 30% des PV max
            allie->pdv += soin;

            if (allie->pdv > allie->pdv_max) {
                allie->pdv = allie->pdv_max;  
            }

            printf("%s récupère %d PV (actuellement %d/%d).\n", allie->nom, soin, allie->pdv, allie->pdv_max);
        }
    }

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite6(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
    Equipe* equipeAlliee;

    if (idEquipe == 1) {
        equipeAlliee = &jeu->equipe1;
    } else {
        equipeAlliee = &jeu->equipe2;
    }

    // Choix du perso à rendre invincible
    Perso* cible = choix_perso_allie(equipeAlliee);



    printf("%s rend %s invincible pour %d tours !\n", perso_Ult->nom, cible->nom, perso_Ult->capacite.duree_effet);

    Effet invincible;
    invincible.id = 4;  
    invincible.valeur = 100;  
    invincible.duree_restant = perso_Ult->capacite.duree_effet;

    cible->effets[cible->nb_effets_actifs++] = invincible;

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite7(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
    Equipe* cible;
    if (idEquipe == 1) {
        cible = &jeu->equipe2;
    } else {
        cible = &jeu->equipe1;
    }

    Perso* adversaire = choix_perso_ennemi(cible);
    printf("%s affaiblit %s pour %d tours !\n", perso_Ult->nom, adversaire->nom, perso_Ult->capacite.duree_effet);

    // affaiblissement
    Effet affaiblissement;
    affaiblissement.id = 1; 
    affaiblissement.valeur = -10;  
    affaiblissement.duree_restant = perso_Ult->capacite.duree_effet;

    adversaire->effets[adversaire->nb_effets_actifs++] = affaiblissement;

    printf("%s ne peut pas recevoir plus d'effets.\n", adversaire->nom);
    

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite8(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite9(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite10(Jeu* jeu, Perso* perso_Ult, int idEquipe) {//capacité du Chou-fleur
    

    Equipe* equipeAlliee;
    if (idEquipe == 1) {
        equipeAlliee = &jeu->equipe1;
    } else {
        equipeAlliee = &jeu->equipe2;
    }

    Perso* allie = choix_perso_allie(equipeAlliee);

    int bonus_ult = allie->attaque;


    attaque(jeu, allie, idEquipe, bonus_ult);
    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite11(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
    Equipe* equipeAlliee;

    if (idEquipe == 1) {
        equipeAlliee = &jeu->equipe1;
    } else {
        equipeAlliee = &jeu->equipe2;
    }

    // Choisir un allié vivant
    Perso* cible = choix_perso_allie(equipeAlliee);

    if ( cible->pdv <= 0) {
        printf("Aucun allié valide pour le soin.\n");
        return;
    }

    printf("%s lance un effet de soin progressif sur %s pour %d tours !\n", perso_Ult->nom, cible->nom, perso_Ult->capacite.duree_effet);

    Effet soin;
    soin.id = 3;  
    soin.valeur = 15;  
    soin.duree_restant = perso_Ult->capacite.duree_effet;

    cible->effets[cible->nb_effets_actifs++] = soin;
    printf("%s recevra %d PV par tour pendant %d tours.\n", cible->nom, soin.valeur, soin.duree_restant);
 
    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}
