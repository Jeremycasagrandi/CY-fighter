#include <stdio.h>
#include "capacite_speciale.h"

void ult(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
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


void capacite0(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
}

void capacite1(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
}

void capacite2(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
}

void capacite3(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
}

void capacite4(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
}

void capacite5(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
}

void capacite6(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
}

void capacite7(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
}

void capacite8(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
}

void capacite9(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
}

void capacite10(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
}

void capacite11(Jeu* jeu, Perso* perso_Ult, int idEquipe) {
}
