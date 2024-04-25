libsprite.a:	image.o spritePlot.o
		qdos-ar -rc libsprite.a image.o spriteplot.o

spritePlot.o:	spritePlot.c image.h 
		qcc -O -o spritePlot.o -c spritePlot.c

image.o:	image.c image.h
		qcc -O -o image.o -c image.c
		#qcc -O -S image.c

system_variables.o:	system_variables.c system_variables.h
		@echo $(PATH)
		qcc -O -o system_variables.o -c system_variables.c

clean:
	rm -f image.o libpsprite.a spritePlot.o 

cleaner:	clean
	rm -f libsprite.o

git:	cleaner
	git add .
	git commit
