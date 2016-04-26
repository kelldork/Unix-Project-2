default: mysh

mysh.o: mysh.c
	gcc -c mysh.c -o mysh.o

mysh: mysh.o
	gcc mysh.o -o mysh

clean:
	-rm -f mysh.o
	-rm -f mysh
