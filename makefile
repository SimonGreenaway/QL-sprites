CC=qgcc qdos-gcc
COPTS=-Wall -O3 -fomit-frame-pointer

OBJS=2d.o system_variables.o frames.o keyboard.o plot.o random.o print.o library.o qdostext.o image.o sprite.o
DEPS=image.h

%.o: %.c $(DEPS)
	$(CC) $(COPTS) -c -o $@ $< $(CFLAGS)

all:	converter test runner

libsprite.a:	$(OBJS) $(DEPS)
		qgcc qdos-ar -rc libsprite.a $(OBJS)

test:	libsprite.a	test.o frames.o
	$(CC) -o test test.o -L/usr/local/share/qdos/lib -lsprite -lm

runner:	libsprite.a	runner.o frames.o
	$(CC) -o runner runner.o frames.o -lsprite

converter:	libsprite.a	converter.o
	$(CC) -o converter converter.o -L/usr/local/share/qdos/lib -lm -lsprite
	cp converter /home/simon/emulators/ql/emulators/sQLux/flp1/

clean:
	rm -f image.o libsprite.a converter.o runner.o test.o  $(OBJS) converter test runner

git:	clean
	git add .
	git commit
	git push

deploy:  runner test
	cp runner test /home/simon/emulators/ql/emulators/sQLux/flp1/
	cp test.lib /home/simon/emulators/ql/emulators/sQLux/flp1/test_lib
	cp BOOT_flp1 /home/simon/emulators/ql/emulators/sQLux/flp1/BOOT

run:    deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0.75 --RAMSIZE=896 --SOUND 8 --WIN_SIZE 2x -b "LRUN flp1_BOOT"

runfast:    deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0 --RAMSIZE=896 --SOUND 8 -b "LRUN flp1_BOOT"

dist:   deploy
	cp BOOT_flp1 BOOT
	cp env.bin env_bin
	qltools sprites.img -fdd sprites -W
	qltools sprites.img -W BOOT test env_bin
	rm -f BOOT env_bin



