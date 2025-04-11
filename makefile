all: exec
personnage.o: personnage.c 
	gcc -c personnage.c -o personnage.o

main.o: main.c 
	gcc -c main.c -o main.o

exec: main.o personnage.o
	gcc main.o personnage.o  -o exec
clean:
	rm exec
	rm *.o