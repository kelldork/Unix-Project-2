default: myls

myls.o: myls.c
	gcc -c myls.c -o myls.o

myls: myls.o
	gcc myls.o -o myls

clean:
	-rm -f myls.o
	-rm -f myls
