#include <stdio.h>
#include "capacite_speciale.h"
#include <unistd.h>
#include <stdlib.h>

void ult(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
    if ( perso_Ult == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}

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

void ajouter_effet(Perso* cible, int idEffet, int valeur, int duree) {
    if ( cible == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}

    Effet effet;
    effet.id = idEffet; //pour le switch case de Appliquer_Effet()
    effet.valeur = valeur; //valeur de l'effet
    effet.duree_restant = duree; // déterminer par la stucture Ult
    cible->effets[cible->nb_effets_actifs++] = effet; // ajoute au tableau des effets actifs l'effet
}


//détermine équipe alliée
Equipe* equipe_alliee(Jeu* jeu, int idEquipe) {
    if (idEquipe == 1) {
        return &jeu->equipe1;
    } else {
        return &jeu->equipe2;
    }
}
//détermine équipe ennemie
Equipe* equipe_ennemie(Jeu* jeu, int idEquipe) {
    if (idEquipe == 1) {
        return &jeu->equipe2;
    } else {
        return &jeu->equipe1;
    }
}








void capacite0(Jeu* jeu, Perso* perso_Ult, int idEquipe) { //capacité de pasteque
    if ( perso_Ult == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}

    afficherPlateau(jeu);
    printf("%s utilise sa capacité ultime !\n", perso_Ult->nom);
    
    Equipe* ennemie = equipe_ennemie(jeu, idEquipe);


    // Choix de la cible qui vera sa vitesse reset
    Perso* choix = choix_perso_ennemi(ennemie);
    choix->vitesse = 0;


    printf("\n\nLa vitesse de %s est remis à 0\n",choix->nom);
    sleep(3);

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite1(Jeu* jeu, Perso* perso_Ult, int idEquipe) { // capacité de noix de coco
    if ( perso_Ult == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}
    afficherPlateau(jeu);  
    printf("%s utilise sa capacité ultime !\n", perso_Ult->nom);

    // Augmente la défense de son équipe
    Equipe* alliee = equipe_alliee(jeu, idEquipe);

    printf("%s renforce la défense de toute son équipe pour %d tours.\n", perso_Ult->nom, perso_Ult->capacite.duree_effet);

    // Parcours tous les persos de l'équipe
    for (int i = 0; i < 3; i++) {
        Perso* allie = &alliee->membres[i];
        
        // Effet appliqué aux persos vivants
        if (allie->pdv > 0) {
            ajouter_effet(allie, 2, 30, perso_Ult->capacite.duree_effet); // Ajoute l'effet buff_Defense
            printf("%s aura 30 en défense pour %d tours.\n", allie->nom, perso_Ult->capacite.duree_effet);
        }
    }

    sleep(3);  

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite2(Jeu* jeu, Perso* perso_Ult, int idEquipe) { // capacité de litchi
    if ( perso_Ult == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}
    afficherPlateau(jeu);  
    printf("%s utilise sa capacité ultime !\n", perso_Ult->nom);

    // 3 attaques normales / 2
    int bonus_ult = 0;
    bonus_ult -= perso_Ult->attaque / 2;
    attaque(jeu, perso_Ult, idEquipe, bonus_ult);
    attaque(jeu, perso_Ult, idEquipe, bonus_ult);
    attaque(jeu, perso_Ult, idEquipe, bonus_ult);

    sleep(3);  

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite3(Jeu* jeu, Perso* perso_Ult, int idEquipe) { // capacité de citron
    if ( perso_Ult == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}
    afficherPlateau(jeu);  
    printf("%s utilise sa capacité ultime !\n", perso_Ult->nom);

    Equipe* ennemie = equipe_ennemie(jeu, idEquipe);
    Perso* choix = choix_perso_ennemi(ennemie);

    printf("%s utilise une attaque d'acide !\n", perso_Ult->nom);
    ajouter_effet(choix, 0, 10, perso_Ult->capacite.duree_effet); //10 dégats par tour effectif lors du tours de la cible
    printf("%s a reçu de l'acide pour %d tours !\n", choix->nom, perso_Ult->capacite.duree_effet);

    sleep(3);  

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite4(Jeu* jeu, Perso* perso_Ult, int idEquipe) { // capacité de prune
    if ( perso_Ult == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}
    afficherPlateau(jeu);  
    printf("%s utilise sa capacité ultime !\n", perso_Ult->nom);
    
    Equipe* alliee = equipe_alliee(jeu, idEquipe);
    Perso* choix = choix_perso_allie(alliee);

    choix->pdv = choix->pdv_max; //restaure entierement la vie 
    printf("Les PV de %s sont restaurés\n", choix->nom);

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
    sleep(3);  
}

void capacite5(Jeu* jeu, Perso* perso_Ult, int idEquipe) { // capacité de raisin
    if ( perso_Ult == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}
    //restaure à hauteur de 30% la vie des persos
    afficherPlateau(jeu); 
    printf("%s utilise sa capacité ultime !\n", perso_Ult->nom);
    
    Equipe* alliee = equipe_alliee(jeu, idEquipe);

    printf("\n%s soigne toute son équipe !\n", perso_Ult->nom);

    
    for (int i = 0; i < 3; i++) {
        Perso* choix = &alliee->membres[i];
        if (choix->pdv > 0) { 
            int soin = choix->pdv_max * 0.3;  // restaure 30% de la vie des persos vivants
            choix->pdv += soin;

            if (choix->pdv > choix->pdv_max) {
                choix->pdv = choix->pdv_max;
            }

            printf("%s récupère %d PV (actuellement %d/%d).\n", choix->nom, soin, choix->pdv, choix->pdv_max);
        }
    }

    sleep(3);  

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite6(Jeu* jeu, Perso* perso_Ult, int idEquipe) { //capacité de salade
    if ( perso_Ult == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}
    // Rends invincible
    afficherPlateau(jeu);  
    printf("%s utilise sa capacité ultime !\n", perso_Ult->nom);
    
    Equipe* alliee = equipe_alliee(jeu, idEquipe);
    Perso* choix = choix_perso_allie(alliee);

    printf("\n%s rend %s invincible pour %d tours (effectif à partir du moment oû le perso va jouer) !\n", perso_Ult->nom, choix->nom, perso_Ult->capacite.duree_effet);
    ajouter_effet(choix, 4, 100, perso_Ult->capacite.duree_effet); // ajoute 100 défense 

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
    sleep(3);  
}

void capacite7(Jeu* jeu, Perso* perso_Ult, int idEquipe) { // capacité de butternut
    if ( perso_Ult == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}
    afficherPlateau(jeu);  
    printf("%s utilise sa capacité ultime !\n", perso_Ult->nom);
    
    Equipe* ennemie = equipe_ennemie(jeu, idEquipe);
    Perso* choix = choix_perso_ennemi(ennemie);

    printf("%s affaiblit %s pour %d tours !\n", perso_Ult->nom, choix->nom, perso_Ult->capacite.duree_effet);

    
    ajouter_effet(choix, 1, -10, perso_Ult->capacite.duree_effet);  // Ajout de l'effet d'affaiblissement -10 Atk, -10 agilité, -10 défense

    printf("%s ne peut pas recevoir plus d'effets.\n", choix->nom);

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
    sleep(3); 
}

void capacite8(Jeu* jeu, Perso* perso_Ult, int idEquipe) { // capacité de oignon
    if ( perso_Ult == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}
    afficherPlateau(jeu);  
    printf("%s utilise sa capacité ultime !\n", perso_Ult->nom);
    
    Equipe* alliee = equipe_alliee(jeu, idEquipe);
    int bonus_ult = 10;  // Par défaut si tous les alliés sont vivants

    // Vérifie s'il y a un allié mort
    for (int i = 0; i < 3; i++) {
        if (alliee->membres[i].pdv <= 0) {
            bonus_ult = 30;  // Bonus en cas d'allié mort
            break;
        }
    }

    attaque(jeu, perso_Ult, idEquipe, bonus_ult);

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite9(Jeu* jeu, Perso* perso_Ult, int idEquipe) {  // capacité de maïs
    if ( perso_Ult == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}
    printf("%s utilise sa capacité ultime !\n", perso_Ult->nom);
    
    Equipe* ennemie = equipe_ennemie(jeu, idEquipe);
    printf("%s déclenche une attaque de zone contre l'ennemie !\n", perso_Ult->nom);
    //attaque tout les ennemis
    for (int i = 0; i < 3; i++) {
        Perso* choix = &ennemie->membres[i];
        if (choix->pdv > 0) {
            int degats = perso_Ult->attaque * 0.7;  // 70% des dégâts de l'attaquant
            choix->pdv -= degats;
            if (choix->pdv < 0){
                choix->pdv = 0;
            }
            

            printf("%s subit %d dégâts (reste %d PV).\n", choix->nom, degats, choix->pdv);
        }
    }

    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
    sleep(3); 
}


void capacite10(Jeu* jeu, Perso* perso_Ult, int idEquipe) { // capacité de chou fleur
    if ( perso_Ult == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}
    afficherPlateau(jeu);
    printf("%s utilise sa capacité ultime !\n", perso_Ult->nom);


    Equipe* equipeAlliee = equipe_alliee(jeu, idEquipe);

    // Choisir un allié
    Perso* allie = choix_perso_allie(equipeAlliee);

    int bonus_ult = allie->attaque; //attaque * 2

    // Utilisation de l'attaque de l'allié sélectionné
    attaque(jeu, allie, idEquipe, bonus_ult);

 
    sleep(3);

 
    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}

void capacite11(Jeu* jeu, Perso* perso_Ult, int idEquipe) { // capacité de poireau
    if ( perso_Ult == NULL) {
        printf("Erreur critique : pointeur NULL Arrêt du programme.\n");
        exit(1); 
}
    afficherPlateau(jeu);
    printf("%s utilise sa capacité ultime !\n", perso_Ult->nom);

    Equipe* equipeAlliee = equipe_alliee(jeu, idEquipe);

    // Choisir un allié vivant
    Perso* cible = choix_perso_allie(equipeAlliee);

    if (cible->pdv <= 0) {
        printf("\nAucun allié valide pour le soin.\n");
        return;
    }

    printf("\n%s lance un effet de soin progressif sur %s pour %d tours !\n", perso_Ult->nom, cible->nom, perso_Ult->capacite.duree_effet);

    // Application de l'effet de soin progressif
    ajouter_effet(cible, 3, 15, perso_Ult->capacite.duree_effet);
    printf("\n%s recevra %d PV par tour pendant %d tours.\n", cible->nom, 15, perso_Ult->capacite.duree_effet);

  
    sleep(3);

  
    perso_Ult->capacite.cooldown = perso_Ult->capacite.cooldown_max;
}