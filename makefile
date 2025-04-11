all: exec
fichier1.o: fichier1.c fichier1.h
	gcc -c fichier1.c -o fichier1.o
main.o: main.c fichier1.h
	gcc -c main.c -o main.o
exec: main.o fichier1.o
	gcc main.o fichier1.o -o exec

clean:
	rm exec
	rm *.o