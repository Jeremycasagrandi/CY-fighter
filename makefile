all: exec
constructeur.o: constructeur.c 
	gcc -c constructeur.c -o constructeur.o

main.o: main.c 
	gcc -c main.c -o main.o

exec: main.o constructeur.o
	gcc main.o constructeur.o  -o exec
clean:
	rm exec
	rm *.o