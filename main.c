#include <stdio.h>
#include "constructeur.h"
#include "afficher.h"
#include "jeu.h"

#include "campagne.h"
#include <unistd.h>
#include <time.h>
#include <stdlib.h>




#pragma comment(lib, "winmm.lib")

int main() {
    srand(time(NULL)); 

    Jeu jeu;

    int solo=0;  

    jeu = menu(&jeu, &solo);
   
    jeu.tour=1;
 

    //finDuJeu vérifie si une equipe est morte
    while(finDuJeu(&jeu)==0){
        
        int indexJoueur = tour(&jeu);  
        
        if (solo==1){
            if(indexJoueur<3){
                choisirAction(&jeu, indexJoueur);
            }
            else{
                choisirActionRobot(&jeu, indexJoueur);
            }
        }
        else{
            choisirAction(&jeu, indexJoueur);
        }
      
        jeu.tour++;
        
    }
        afficherGagnant(jeu);
}