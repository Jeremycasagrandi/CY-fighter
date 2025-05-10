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



<<<<<<< HEAD

int trouverIndexVitesseMax(Perso* tab[]) {
    int maxIndex = -1;
    int maxVitesse = 100;  // seuil minimum pour jouer

=======
//parcours les personnage, retourne l'index de celui qui a la plus grande vitesse au dessus de 50, retourne 1 sinon
int trouverIndexVitesseMax(Perso* tab[]) {
    int maxIndex = -1;
    int maxVitesse = 100;  // seuil minimum pour jouer

>>>>>>> 24ea16b3f1bb389da222f845d23840d07c503596
    for (int i = 0; i < 6; i++) {
        if (tab[i]->vitesse >= 100 && tab[i]->vitesse > maxVitesse) {
            maxVitesse = tab[i]->vitesse;
            maxIndex = i;
        }
    }

    return maxIndex;
}
int tour(Jeu* jeu) {
    int index;

    // 🔹 Affiche les jauges dès l'appel de la fonction
    printf("\n=== Jauge de vitesse (début du tour) ===\n");
    for (int i = 0; i < 6; i++) {
        afficherJaugeVitesse(jeu->tabE[i]);
    }

    index = trouverIndexVitesseMax(jeu->tabE);

    // 🔹 Si personne ne peut encore jouer, on augmente les vitesses
    while (index == -1) {
        for (int i = 0; i < 6; i++) {
            jeu->tabE[i]->vitesse += jeu->tabE[i]->vitesse_max;
        }

        printf("\n=== Jauge mise à jour ===\n");
        for (int i = 0; i < 6; i++) {
            afficherJaugeVitesse(jeu->tabE[i]);
        }

        sleep(1);  // pause d’une seconde avant nouveau test
        index = trouverIndexVitesseMax(jeu->tabE);
    }

    // 🔹 Quelqu’un peut jouer
    printf("\n>>> %s joue ! <<<\n", jeu->tabE[index]->nom);
    jeu->tabE[index]->vitesse = 0;
    return index;
}









//retourne le prochain personnage qui doit jouer a chaque appel
int tour(Jeu* jeu) {
    int index;

    // 🔹 Affiche les jauges dès l'appel de la fonction
    printf("\n=== Jauge de vitesse (début du tour) ===\n");
    for (int i = 0; i < 6; i++) {
        afficherJaugeVitesse(jeu->tabE[i]);
    }

    index = trouverIndexVitesseMax(jeu->tabE);

    // 🔹 Si personne ne peut encore jouer, on augmente les vitesses
    while (index == -1) {
        for (int i = 0; i < 6; i++) {
            jeu->tabE[i]->vitesse += jeu->tabE[i]->vitesse_max;
        }

        printf("\n=== Jauge mise à jour ===\n");
        for (int i = 0; i < 6; i++) {
            afficherJaugeVitesse(jeu->tabE[i]);
        }

        sleep(1);  // pause d’une seconde avant nouveau test
        index = trouverIndexVitesseMax(jeu->tabE);
    }

    // 🔹 Quelqu’un peut jouer
    printf("\n>>> %s joue ! <<<\n", jeu->tabE[index]->nom);
    jeu->tabE[index]->vitesse = 0;
    return index;
}







int estVivant(Perso* p) {
    return p->pdv > 0;
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
}

