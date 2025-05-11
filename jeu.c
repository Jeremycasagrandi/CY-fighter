#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "jeu.h"
#include "afficher.h"
#include "constructeur.h"
#include "capacite_speciale.h"
#include "capacite_classique.h"

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




int trouverIndexVitesseMax(Perso* tab[]) {
    int maxIndex = -1;
    int maxVitesse = 100;  // seuil minimum pour jouer

    for (int i = 0; i < 6; i++) {
        if (tab[i]->vitesse >= 100 && tab[i]->vitesse > maxVitesse) {
            maxVitesse = tab[i]->vitesse;
            maxIndex = i;
        }
    }

    return maxIndex;
}








//retourne le prochain personnage qui doit jouer a chaque appel
int tour(Jeu* jeu) {
    int index;
    
    
    // 🔹 Affiche les jauges dès l'appel de la fonction
    
  
    afficherPlateau(jeu);

    index = trouverIndexVitesseMax(jeu->tabE);
    

    // 🔹 Si personne ne peut encore jouer, on augmente les vitesses
    while (index == -1) {
        for (int i = 0; i < 6; i++) {
            jeu->tabE[i]->vitesse += jeu->tabE[i]->vitesse_max;
        }
        
        
       
        afficherPlateau(jeu);

        sleep(1);  // pause d’une seconde avant nouveau test
        index = trouverIndexVitesseMax(jeu->tabE);
    }

    // 🔹 Quelqu’un peut jouer
    
    jeu->tabE[index]->vitesse = 0;
    return index;
}






int estVivant(Perso* p) {
    return p->pdv > 0;
}

int Aulti(Perso* perso) {
    return perso->capacite.cooldown == 0;
}

int Aeffet(Perso* perso){
    return perso->nb_effets_actifs > 0;
}


void mettreAJourEffets(Perso* perso) {
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


            case 1:  // Bonus d'attaque 
                printf("%s subit un affaiblissement temporaire (-10 atk, def, agi).\n", perso->nom);
                perso->attaque += perso->effets[i].valeur;
                perso->defense += perso->effets[i].valeur;
                perso->agilite += perso->effets[i].valeur;
                break;


            case 2:  // Bonus de défense
                printf("%s a 50 de défense ", perso->nom);
                perso->defense == effet->valeur;
                break;

            case 3:  // Soin progressif
                perso->pdv += effet->valeur;
                if (perso->pdv > perso->pdv_max){
                    perso->pdv = perso->pdv_max;
                } 
                printf("%s récupère %d PV grâce à un effet de soin. PV actuels : %d\n", perso->nom, effet->valeur, perso->pdv);
                break;
            case 4:  // Invincibilité 
                perso->defense = 100;
                printf("%s est invincible ! \n", perso->nom);
                break;
            default:
                printf("%s a un effet inconnu (id: %d)\n", perso->nom, effet->id);
                break;
        }
    }
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
    if (Aeffet(perso)) {
        appliquerEffets(perso);
        printf("%d",perso->defense);
        if (perso->pdv <= 0) {
            printf("%s est mort à cause de l'acide\n", perso->nom);
            return;
        }
    }
    printf("1. Attaquer\n");
    printf("2. Utiliser capacité ultime : %s\n",perso->capacite.nom);
    
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
        if (choix == 2 && !Aulti(perso)) {
            printf("Capacité ultime indisponible.  %d tours restants.\n", perso->capacite.cooldown);
        }
        if (choix == 3 && !estSoigneur(perso)) {
            printf("Action invalide. Ce personnage n'est pas un soigneur .\n");
        }
    } while ((choix < 1 || choix > 3) || (choix == 2 && !Aulti(perso))||(choix == 3 && (!estSoigneur(perso) || !soinDisponible(equipeJoueur))));
    switch (choix) {
        case 1:  // Attaque
            printf("%s attaque un membre de l'équipe adverse !\n", perso->nom);
            attaque(jeu, perso, idEquipe, 0);
            break;
        
        case 2:  // Utiliser capacité ultime
            printf("%s utilise sa capacité ultime !\n", perso->nom);
            ult(jeu, perso, idEquipe);
            break;
        case 3:
            printf("%s soigne un allié !\n", perso->nom);
            soin(jeu, perso, idEquipe);
            
            break;
        
        default:
            printf("Choix invalide.\n");
            break;
    }
    if (perso->capacite.cooldown > 0) {
        perso->capacite.cooldown--;
    }
    mettreAJourEffets(perso);
}

