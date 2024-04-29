COPTS=-O3 -fomit-frame-pointer -std=gnu9x

#test:	libsprite.a	test.o frames.o
#	qdos-gcc -o test test.o frames.o -lsprite

libsprite.a:	image.o system_variables.o frames.o makefile
		qdos-ar -rc libsprite.a image.o system_variables.o frames.o

image.o:	image.c image.h makefile
		qdos-gcc $(COPTS) -o image.o -c image.c

frames.o:	frames.c image.h makefile
		qdos-gcc $(COPTS) -o frames.o -c frames.c

test.o:	test.c image.h makefile
		qdos-gcc $(COPTS) -o test.o -c test.c

system_variables.o:	system_variables.c system_variables.h makefile
		qdos-gcc $(COPTS) -o system_variables.o -c system_variables.c

clean:
	rm -f image.o libsprite.a  system_variables.o libsprite.o test.o test frames.o

git:	clean
	git add .
	git commit

deploy:  test
	cp test /home/simon/emulators/ql/emulators/sQLux/flp1
	cp BOOT_flp1 /home/simon/emulators/ql/emulators/sQLux/flp1/BOOT

run:    deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0.70 --RAMSIZE=896 --SOUND 8 -b "LRUN flp1_BOOT"

