#include <stdio.h>
#include "constructeur.h"
#include "afficher.h"
#include "jeu.h"

int main() {
    
    Jeu jeu = menu();
    int i=0;

    //fin du jeu vérifie si une equipe est morte (dans jeu.c)
    while(finDuJeu(&jeu)==0){
        int indexJoueur = tour(&jeu);  
        
        
        printf(" Tour %d \n", i+1);
        choisirAction(&jeu, indexJoueur); 
        /*test fin de partie 
        jeu.equipe1.membres[0].pdv=0;
        jeu.equipe1.membres[1].pdv=0;
        jeu.equipe1.membres[2].pdv=0;
        */
        


        

        printf("\nÉquipe 1:\n");
        for (int j = 0; j < 3; j++) {
            printf("Membre %s: %d PV\n", jeu.equipe1.membres[j].nom, jeu.equipe1.membres[j].pdv);
        }
        
        printf("\nÉquipe 2:\n");
        for (int j = 0; j < 3; j++) {
            printf("Membre %s: %d PV\n", jeu.equipe2.membres[j].nom, jeu.equipe2.membres[j].pdv);
        }
        i++;
        
        }
        afficherGagnant(jeu);
    }