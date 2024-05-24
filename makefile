COPTS=-Wall -O3 -fomit-frame-pointer -std=gnu9x -ansi

libsprite.a:	image.o 2d.o system_variables.o frames.o keyboard.o sprite.o makefile
		qgcc qdos-ar -rc libsprite.a image.o 2d.o sprite.o system_variables.o frames.o keyboard.o sprite.o 

test:	libsprite.a	test.o frames.o
	qgcc qdos-gcc -o test test.o frames.o -L/usr/local/share/qdos/lib -lsprite -lm

runner:	libsprite.a	runner.o frames.o
	qgcc qdos-gcc -o runner runner.o frames.o -lsprite

sprite.o:	sprite.c image.h makefile
		qgcc qdos-gcc $(COPTS) -o sprite.o -c sprite.c

runner.o:	runner.c image.h makefile
		qgcc qdos-gcc $(COPTS) -o runner.o -c runner.c

keyboard.o:	keyboard.c image.h makefile
		qgcc qdos-gcc $(COPTS) -o keyboard.o -c keyboard.c

image.o:	image.c image.h makefile
		qgcc qdos-gcc $(COPTS) -o image.o -c image.c

2d.o:	2d.c image.h makefile
		qgcc qdos-gcc $(COPTS) -o 2d.o -c 2d.c
		#qgcc qdos-gcc $(COPTS) -S 2d.c

frames.o:	frames.c image.h makefile
		qgcc qdos-gcc $(COPTS) -o frames.o -c frames.c

test.o:	test.c image.h makefile
		qgcc qdos-gcc $(COPTS) -o test.o -c test.c

system_variables.o:	system_variables.c system_variables.h makefile
		qgcc qdos-gcc $(COPTS) -o system_variables.o -c system_variables.c

clean:
	rm -f image.o libsprite.a  system_variables.o libsprite.o test.o test frames.o runner.o 2d.s runner.s sprite.o  2d.o keyboard.o

git:	clean
	git add .
	git commit
	git push

deploy:  runner test
	cp runner test /home/simon/emulators/ql/emulators/sQLux/flp1/
	cp test.lib /home/simon/emulators/ql/emulators/sQLux/flp1/test_lib
	cp BOOT_flp1 /home/simon/emulators/ql/emulators/sQLux/flp1/BOOT

run:    deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0.75 --RAMSIZE=896 --SOUND 8 -b "LRUN flp1_BOOT"

runfast:    deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0 --RAMSIZE=896 --SOUND 8 -b "LRUN flp1_BOOT"


dist:   deploy
	cp BOOT_flp1 BOOT
	qltools sprites.img -fdd sprites -W
	qltools sprites.img -W BOOT test
	rm -f BOOT

