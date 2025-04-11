all: exec
test.o: test.c 
	gcc -c test.c -o test.o
main.o: main.c test.h
	gcc -c main.c -o main.o
exec: main.o test.o
	gcc main.o test.o -o exec
clean:
	rm exec
	rm *.o