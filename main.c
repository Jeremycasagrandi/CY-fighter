#include <stdio.h>
#include "constructeur.h"
#include "afficher.h"
#include "jeu.h"

int main() {

    
    Jeu jeu = menu();
    printf("%d",tour(&jeu));
    printf("%d",tour(&jeu));
    printf("%d",tour(&jeu));
    printf("%d",tour(&jeu));
}
