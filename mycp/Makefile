default: mycp

mycp.o: mycp.c
	gcc -c mycp.c -o mycp.o

mycp: mycp.o
	gcc mycp.o -o mycp

clean:
	-rm -f mycp.o
	-rm -f mycp
