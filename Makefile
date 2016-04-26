default: mycat

mycat.o: mycat.c
	gcc -c mycat.c -o mycat.o

mycat: mycat.o
	gcc mycat.o -o mycat

clean:
	-rm -f mycat.o
	-rm -f mycat
