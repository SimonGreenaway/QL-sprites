SQLUX=/home/simon/emulators/ql/emulators/sQLux
SQLUXFLP1=$(SQLUX)/flp1/

COPTS=-Wall -O3 -fomit-frame-pointer

hello_world:	hello_world.o
	qgcc qdos-gcc -o hello_world hello_world.o  -L/usr/local/share/qdos/lib -lm

hello_world.o:	hello_world.c makefile
		qgcc qdos-gcc -O -o hello_world.o -c hello_world.c

clean:
	rm -f hello_world.o hello_world

deploy:  hello_world
	cp hello_world $(SQLUXFLP1)
	cp BOOT_flp1 $(SQLUXFLP1)/BOOT

run:    deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0.75 --RAMSIZE=896 --SOUND 8 --WIN_SIZE 2x -b "LRUN flp1_BOOT"

runfast:    deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0 --RAMSIZE=896 --SOUND 8 -b "LRUN flp1_BOOT"
