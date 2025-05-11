#include <stdio.h>
#include "constructeur.h"
#include "afficher.h"
#include "jeu.h"
#include "son.h" 
#include "campagne.h"
#include <unistd.h>

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

int main() {
    
    
    Jeu jeu;
    int solo=0;  
    jeu = menu(&jeu, &solo);
   
    jeu.tour=1;
     //test fin de partie 
        // jeu.equipe1.membres[0].pdv=0;
        // jeu.equipe1.membres[1].pdv=0;
        // jeu.equipe1.membres[2].pdv=0;
     
    

    //fin du jeu vérifie si une equipe est morte (dans jeu.c)
    while(finDuJeu(&jeu)==0){
        printf("la capacité est %s",jeu.equipe1.membres[0].capacite.nom);
        
       
        
       
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
         
      
        
        
        
        

        // printf("\nÉquipe 1:\n");
        // for (int j = 0; j < 3; j++) {
        //     printf("Membre %s: %d PV\n", jeu.equipe1.membres[j].nom, jeu.equipe1.membres[j].pdv);
        // }
        
        // printf("\nÉquipe 2:\n");
        // for (int j = 0; j < 3; j++) {
        //     printf("Membre %s: %d PV\n", jeu.equipe2.membres[j].nom, jeu.equipe2.membres[j].pdv);
        // }
        jeu.tour++;
        
    }
        afficherGagnant(jeu);
}