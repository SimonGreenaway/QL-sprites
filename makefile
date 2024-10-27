CC=qgcc qdos-gcc
COPTS=-Wall -O3 -fomit-frame-pointer 

OBJS=2d.o system_variables.o frames.o keyboard.o random.o print.o library.o qdostext.o image.o sprite.o malloc.o lsbrk.o font.o
DEPS=image.h font_4x6.h

%.o: %.c $(DEPS)
	$(CC) $(COPTS) -c -o $@ $< $(CFLAGS)

all:	converter test runner font

libsprite.a:	$(OBJS) $(DEPS)
		qgcc qdos-ar -rc libsprite.a $(OBJS)

library.o:	library.c
	$(CC) -c -o library.o library.c

test:	libsprite.a	test.o frames.o
	$(CC) -o test test.o -L/usr/local/share/qdos/lib -lsprite -lm

runner:	libsprite.a	runner.o frames.o
	$(CC) -o runner runner.o frames.o -lsprite

converter:	libsprite.a	converter.o
	$(CC) -o converter converter.o -L/usr/local/share/qdos/lib -lm -lsprite
	cp converter flp1

#font:	libsprite.a	font.o
#	$(CC) -o font font.o -L/usr/local/share/qdos/lib -lsprite -lm

clean:
	rm -f image.o libsprite.a converter.o runner.o test.o  $(OBJS) converter test runner

git:	clean
	git add .
	git commit
	git push

deploy:  runner test font
	rm -fR flp1
	mkdir flp1
	cp runner test font flp1
	cp test.lib flp1/test_lib
	cp BOOT_flp1 flp1/BOOT
	cp env.bin flp1/env_bin

runfont:    deploy
	cp BOOT_font_flp1 flp1/BOOT
	/home/simon/emulators/ql/emulators/sQLux/sqlux ./sqlux --romdir=/home/simon/emulators/ql/emulators/sQLux/roms --speed=0.75 --ramsize=896 --sound 8 --win_size 2x --device flp1,./flp1,/home/simon/code/ql/QL-sprites/flp1,qdos-like --romport=TK236.rom --fixaspect=2 --filter=1  -b "LRUN flp1_BOOT"

run:    deploy
	/home/simon/emulators/ql/emulators/sQLux/sqlux ./sqlux --romdir=/home/simon/emulators/ql/emulators/sQLux/roms --speed=0.75 --ramsize=896 --sound 8 --win_size 2x --device flp1,./flp1,/home/simon/code/ql/QL-sprites/flp1,qdos-like --romport=TK236.rom --fixaspect=2 --filter=1  -b "LRUN flp1_BOOT"

runfast:    deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --speed=0 --ramsize=896 --sound 8 -b "LRUN flp1_BOOT"

dist:   deploy
	cp BOOT_flp1 BOOT
	cp env.bin env_bin
	qltools sprites.img -fdd sprites -W
	qltools sprites.img -W BOOT test env_bin
	rm -f BOOT env_bin



