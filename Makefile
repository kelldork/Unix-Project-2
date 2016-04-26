TRGTS = MYCAT MYCP MYLS MYSH

all: $(TRGTS)

MYCAT:
	cd ./mycat; make ; cp mycat ../bin/.

MYCP:
	cd ./mycp; make ; cp mycp ../bin/.

MYLS:
	cd ./myls; make ; cp myls ../bin/.
MYSH:
	cd ./mysh; make ; cp mysh ../bin/.

clean:
	rm -f *.o *~
	cd ./mycat; make clean
	cd ./mycp; make clean
	cd ./myls; make clean
	cd ./mysh; make clean
	cd ./bin;  rm mycat; rm mycp; rm myls; rm mysh
