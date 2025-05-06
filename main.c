#include <stdio.h>
#include "constructeur.h"
#include "afficher.h"
#include "jeu.h"

int main() {
    
    Jeu jeu = menu();

    
    for (int i = 0; i < 6; i++) {  // test
        int indexJoueur = tour(&jeu);  
        
        
        printf(" Tour %d \n", i+1);
        choisirAction(&jeu, indexJoueur); 
        
        
        printf("\nÉquipe 1:\n");
        for (int j = 0; j < 3; j++) {
            printf("Membre %s: %d PV\n", jeu.equipe1.membres[j].nom, jeu.equipe1.membres[j].pdv);
        }
        
        printf("\nÉquipe 2:\n");
        for (int j = 0; j < 3; j++) {
            printf("Membre %s: %d PV\n", jeu.equipe2.membres[j].nom, jeu.equipe2.membres[j].pdv);
        }
    }

    return 0;
}
