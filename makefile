all: exec
constructeur.o: constructeur.c constructeur.h
	gcc -c constructeur.c -o constructeur.o

main.o: main.c constructeur.h afficher.h jeu.h
	gcc -c main.c -o main.o

afficher.o: afficher.c afficher.h constructeur.h
	gcc -c afficher.c -o afficher.o

jeu.o: jeu.c jeu.h afficher.h
	gcc -c jeu.c -o jeu.o

exec: main.o constructeur.o afficher.o jeu.o
	gcc main.o constructeur.o afficher.o jeu.o -o exec
clean:
	rm exec
	rm *.o