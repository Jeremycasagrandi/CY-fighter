
#include <stdio.h>
#include "constructeur.h"
#include "afficher.h"

int main() {
    Perso perso1 = creationperso();  
    afficherPerso(perso1);
    int choix = menu();

    
    return 0;
}
