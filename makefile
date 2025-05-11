all: exec

constructeur.o: constructeur.c constructeur.h
	gcc -c constructeur.c -o constructeur.o

main.o: main.c constructeur.h afficher.h jeu.h capacite_speciale.h son.h
	gcc -c main.c -o main.o

afficher.o: afficher.c afficher.h constructeur.h
	gcc -c afficher.c -o afficher.o

jeu.o: jeu.c jeu.h afficher.h constructeur.h capacite_speciale.h
	gcc -c jeu.c -o jeu.o

capacite_speciale.o: capacite_speciale.c capacite_speciale.h constructeur.h jeu.h
	gcc -c capacite_speciale.c -o capacite_speciale.o

capacite_classique.o: capacite_classique.c capacite_classique.h constructeur.h
	gcc -c capacite_classique.c -o capacite_classique.o

effet.o: effet.c effet.h
	gcc -c effet.c -o effet.o

son.o: son.c son.h
	gcc -c son.c -o son.o

exec: main.o constructeur.o afficher.o jeu.o capacite_speciale.o capacite_classique.o effet.o son.o
	gcc main.o constructeur.o afficher.o jeu.o capacite_speciale.o capacite_classique.o effet.o son.o -o exec -lwinmm


clean:
	rm exec
	rm *.o
