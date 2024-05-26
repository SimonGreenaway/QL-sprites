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

#define SECONDS 10
#define RANDS 32768
#define TESTS 9 

void test()
{
	const char *tests[TESTS]={"plot","line","tri","fil tri","box","fill box","circle","fill cir","unplot"};

	unsigned int i,j;
	WINDOWDEF_t w;
	chanid_t cid;
	unsigned int counts[TESTS],pass;
	unsigned char *r=myMalloc(RANDS);
	unsigned int ri=0;
	
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

	puts("Creating random numbers...");
	for(ri=0;ri<RANDS/2;ri++) r[ri]=fastRand()&255;

	cls(SCREEN);

	for(pass=0;pass<TESTS;pass++)
	{
		unsigned int f=getFrames()+SECONDS*50;

		counts[pass]=0;
		ri=0;

		if(pass==0)
		{
			while(getFrames()<f)
			{
				plot(SCREEN,r[ri]   ,r[ri+1], r[ri+2] &7);
				plot(SCREEN,r[ri+3] ,r[ri+4], r[ri+5] &7);
				plot(SCREEN,r[ri+6] ,r[ri+7], r[ri+8] &7);
				plot(SCREEN,r[ri+9] ,r[ri+10],r[ri+11]&7);
				plot(SCREEN,r[ri+12],r[ri+13],r[ri+14]&7);
				plot(SCREEN,r[ri+15],r[ri+16],r[ri+17]&7);
				plot(SCREEN,r[ri+18],r[ri+19],r[ri+20]&7);
				plot(SCREEN,r[ri+21],r[ri+22],r[ri+23]&7);
				plot(SCREEN,r[ri+24],r[ri+25],r[ri+26]&7);
				plot(SCREEN,r[ri+27],r[ri+28],r[ri+29]&7);

				ri+=30;
				if(ri>=RANDS) ri=0;
				counts[0]+=10;
			}
		}
		else while(getFrames()<f)
		{
			unsigned int c;

			switch(pass)
			{
				case 1: line(SCREEN,r[ri++],r[ri++],r[ri++],r[ri++],r[ri++]&7); break;
				case 2: triangle(SCREEN,r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],r[ri++]&7); break;
				case 3:fillTriangle(SCREEN,r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],r[ri++]&7); break;
				case 4:box(SCREEN,r[ri++],r[ri++],r[ri++],r[ri++],r[ri++]&7); break;
				case 5:fillBox(SCREEN,r[ri++],r[ri++],r[ri++],r[ri++],r[ri++]&7); break;
				case 6:circle(SCREEN,128,128,r[ri++]&127,r[ri++]&7); break;
				case 7:fillCircle(SCREEN,128,128,r[ri++]&127,r[ri++]&7); break;
				case 8:unplot(SCREEN,r[ri++],r[ri++]); break;
				case 9:	c=r[ri++]&7;
					triangle(SCREEN,r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],c);
					triangle(SCREEN,r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],c);
					triangle(SCREEN,r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],c);
				        floodFill(SCREEN,r[ri++],r[ri++],c);
					break;
			}

			counts[pass]++;
			if(ri>=RANDS) ri=0;
		}

		if(pass!=7) cls(SCREEN);
	}

	for(i=0;i<TESTS;i++)
		printf("%8s %8.1f p/s\n",tests[i],counts[i]/(double)SECONDS);

	while(1)
	{
		fillTriangle(SCREEN,128+(fastRand()&127),fastRand()&127,128+(fastRand()&127),fastRand()&127,128+(fastRand()&127),fastRand()&127,fastRand()&7);
		line(SCREEN,128+(fastRand()&127),128+(fastRand()&127),128+(fastRand()&127),128+(fastRand()&127),fastRand()&7);
		circle(SCREEN,64,128+64,fastRand()&63,fastRand()&7);
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

	return 0;
}
