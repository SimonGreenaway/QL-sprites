#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <qdos.h>

#include "image.h"

void binPrint2(short i)
{
	int z;

	for(z=15;z>=0;z--)
		putchar(i&(1<<z)?'1':'0');
}

void benchmark()
{
	unsigned int s;
	screen background=createScreen();
	library lib;

	init(8);

	loadLibrary(&lib,"test_lib",1);
	copyAllScreen(background,SCREEN);

	for(s=0;s<4;s++)
	{
		const int n=10;

		unsigned long t,c=0,pass;
		unsigned int x=0,y=0;
		sprite sprite[8];

		for(c=0;c<8;c++)
		{
			spriteSetup(&sprite[c],"");
			spriteAddImage(&sprite[c],&lib,s);
			sprite[c].currentImage=0;
			sprite[c].x=x++;

			sprite[c].y=y;
			sprite[c].draw=1;

			y+=sprite[c].image[0]->y;
			if(y+sprite[c].image[0]->y>255)
			{
				y=0;
				x+=sprite[c].image[0]->x<<2;
			}
		}

		for(pass=0;pass<2;pass++)
		{
			for(c=0;c<8;c++) sprite[c].mask=pass;

			t=getFrames()+n*50;
	
			while(t>getFrames())
			{
				unsigned int i;

				for(i=0;i<8;i++) spritePlot(SCREEN,&sprite[i]);

				c+=8;
			}

			copyAllScreen(SCREEN,background);

			if(pass==0)
				printf("%d x %d\t-> %ld",lib.images[s].x<<2,lib.images[s].y,c);
			else printf("\tMasked %ld\n",c);

			copyAllScreen(background,SCREEN);
		}
	}

	exit(0);
}

static unsigned int g_seed;

// Used to seed the generator.           

void fastSrand(int seed)
{
        g_seed = seed;
}

// Compute a pseudorandom integer.
// Output value in range [0, 32767]

inline unsigned int fastRand(void)
{
        g_seed = (214013*g_seed+2531011);
        return (g_seed>>16);
}

void test()
{
	unsigned int i;
	WINDOWDEF_t w;
	chanid_t cid;
	unsigned int counts[7],pass,count=0;

	init(8);
	framesInit();

	//loadLibrary(&l,"test_lib",1); 
	
	w.width=w.height=512;
	w.x_origin=w.y_origin=0;
	w.paper=0; w.ink=7;

	cid=ut_con(&w);

	cls(SCREEN); fastSrand(0);

	for(i=0;i<120;i++)
	{
		box(SCREEN,i+4-1,i*2+4-1,200-i+1,i*2+4+1,7);
		line(SCREEN,i+4,i*2+4,200-i,i*2+4,(i/4)&7);
	}

	sleep(5);
	cls(SCREEN); fastSrand(0);


	for(pass=0;pass<7;pass++)
	{
		unsigned int f=getFrames()+10*50;

		count=0;

		while(getFrames()<f)
		{
			switch(pass)
			{
				case 0: plot(SCREEN,fastRand()&255,fastRand()&255,fastRand()&7); break;
				case 1: line(SCREEN,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&7); break;
				case 2: triangle(SCREEN,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&7); break;
				case 3:fillTriangle(SCREEN,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&7); break;
				case 4:box(SCREEN,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&7); break;
				case 5:fillBox(SCREEN,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&255,fastRand()&7); break;
				case 6:unplot(SCREEN,fastRand()&255,fastRand()&255); break;
			}

			count++;
		}

		cls(SCREEN); fastSrand(0);

		counts[pass]=count;

		for(i=0;i<=pass;i++) printf("%d\n",counts[i]);
	}
}

void testMode4()
{
	unsigned int i;

	init(4);

	while(1)
	{
		for(i=0;i<8;i++)
		{
			plot4(SCREEN,i,0,3);
			plot4(SCREEN,i,i,3); sleep(1);
		}

		while(1);
	}
}

void testKey()
{
	while(1)
	{
		unsigned char c=scanKey();

		if(c==8) printf("DEL");
		else if(c!=0) putchar(c);
	}
}

//////////
// main //
//////////

char *drive="MDV1_";

int main(int argc, char *argv[],char *argp[])
{
	unsigned int s;

	if(getenv("DRIVE")!=NULL) strcpy(drive,getenv("DRIVE"));

	printf("Default drive is '%s'\n",drive);

	// Parse the args

	setSysBase((unsigned char *)0x28000);

	//testMode4();
	//testKey();
	//testVars();

	for(s=1;s<argc;s++)
	{
		if(strcmp(argv[s],"-bm")==0) benchmark();
		else if(strcmp(argv[s],"-t")==0) test();
		else
		{
			printf("Unknown command line argument: %s\n",argv[s]);
			exit(4);	
		}
	}
}
