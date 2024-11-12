#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <qdos.h>

#include "image.h"

char *drive="MDV1_"; // Default drive to load files from

// Print i as binary
void binPrint2(short i)
{
	int z;

	for(z=15;z>=0;z--)
		putchar(i&(1<<z)?'1':'0');
}

// Sprite benchmark
//
void benchmark()
{
	unsigned int s;
	screen background=createScreen(); // Create a 32k screen for storing the background data
	library lib;

	init(8);	// Initiate the graphics with colour mode 8

	puts("Loading font...");

	loadLibrary(&lib,"test_lib",1,0);

	cls(SCREEN);

	puts("Sprites drawn per second:\n");

	while(1)
	{
		copyAllScreen(background,SCREEN); // Copy what is on the display to the background buffer so we can draw sprites masked onto background

		for(s=0;s<4;s++) // 4 sprite sizes 8,16,24 and 32 bits square
		{
			const int n=10;

			unsigned long t,c=0,pass;
			unsigned int x=0,y=0;
			sprite sprite[8];

			for(c=0;c<8;c++)
			{
				spriteSetup(&sprite[c],""); // Initiate the sprite
				spriteAddImageFromLibrary(&sprite[c],&lib,s); // Add an image to the sprite
				sprite[c].currentImage=0; // Set the default image
				sprite[c].x=x++;	// Set the xposition
	
				sprite[c].y=y;		// Set the y position
				sprite[c].draw=1;	// draw=1 to display data

				// Work out the next sprite's position
				y+=sprite[c].image[0]->y;
				if(y+sprite[c].image[0]->y>255)
				{
					y=0;
					x+=sprite[c].image[0]->x<<2;
				}
			}

			for(pass=0;pass<2;pass++) // Draw sprites with unmasked then masked
			{
				unsigned long t0;

				for(c=0;c<8;c++) sprite[c].mask=pass; // Set the mask mode

				// Wait for frame to end (50hz interrupt counter)
				t0=getFrames();	
				while(getFrames()<=t0);
				t=(t0+1)+n*50;
	
				while(t>getFrames())
				{
					// Draw each of the 8 sprites repeatedly
					spritePlot(SCREEN,&sprite[0]); 
					spritePlot(SCREEN,&sprite[1]);
					spritePlot(SCREEN,&sprite[2]);
					spritePlot(SCREEN,&sprite[3]);
					spritePlot(SCREEN,&sprite[4]);
					spritePlot(SCREEN,&sprite[5]);
					spritePlot(SCREEN,&sprite[6]);
					spritePlot(SCREEN,&sprite[7]);
	
					c++;
				}

				c*=8;
	
				copyAllScreen(SCREEN,background); // Copy the saved bg back to the screen
	
				if(pass==0)
					printf("%d x %d\t-> %6.1f",lib.images[s].x<<2,lib.images[s].y,c/(float)n);
				else printf("\tMasked %6.1f\n",c/(float)n);
	
				copyAllScreen(background,SCREEN); // And save, with the newly printed stuff above
			}
		}

		puts("");
	}

	exit(0);
}

// Run the 2d tests
// Doesn't quite work at the moment!

#define SECONDS 10
#define RANDS 32768
#define TESTS 10

void test()
{
	const char *tests[TESTS]={"plot","line","tri","fil tri","box","fill box","circle","fill cir","unplot","flood"};

	unsigned int i;
	WINDOWDEF_t w;
	chanid_t cid;
	unsigned int counts[TESTS],pass;
	unsigned char *r=myMalloc(RANDS);
	unsigned int ri=0;

	
	init(8);
	//framesInit();


	//loadLibrary(&l,"test_lib",1); 
	
	w.width=w.height=512;
	w.x_origin=w.y_origin=0;
	w.paper=0; w.ink=7;

	cid=ut_con(&w);

	cls(SCREEN); fastSrand(0);

	for(i=0;i<120;i++)
	{
		//box(SCREEN,i+4-1,i*2+4-1,200-i+1,i*2+4+1,7);
		//line(SCREEN,i+4,i*2+4,200-i,i*2+4,(i/4)&7);
	}

	//puts("Hello!"); while(1);

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

					counts[pass]=getFrames()-f-1;
					break;
			}

			counts[pass]++;
			if(ri>=RANDS) ri=0;
		}

		if(pass!=7) cls(SCREEN);
	}

	for(i=0;i<TESTS;i++)
	{
		if(i==9)
			printf("%8s %8.1f p/s\n",tests[i],counts[i]/(double)50);
		else printf("%8s %8.1f p/s\n",tests[i],counts[i]/(double)SECONDS);
	}

	while(1)
	{
		fillTriangle(SCREEN,128+(fastRand()&127),fastRand()&127,128+(fastRand()&127),fastRand()&127,128+(fastRand()&127),fastRand()&127,fastRand()&7);
		line(SCREEN,128+(fastRand()&127),128+(fastRand()&127),128+(fastRand()&127),128+(fastRand()&127),fastRand()&7);
		circle(SCREEN,64,128+64,fastRand()&63,fastRand()&7);
	}
}

void testKey()
{
	puts("ESC to quit...\n");

	while(1)
	{
		unsigned char c=scanKey();

		if(c==8) printf("DEL");
		else if(c==27) return;
		else if(c!=0) putchar(c);
	}

	putchar('\n');
	putchar('\n');
}

void osText()
{
	unsigned int f=getFrames()+250;
	chanid_t chan;

	chan=wopen(50,50,256,100);

	if(chan<0)
	{
		printf("Error opening window: %d\n",(int)chan);
		exit(1);
	}

	while(f>getFrames())
	{
		wfputs(chan,"Hello world! ");
		wborder(chan,fastRand()&7,2);
	}

	wclose(chan);
}

void test4Text()
{
	int x,y;
	char z[2];
	unsigned int t;
	
	z[1]='\0';

	init(8);
        cls(SCREEN);

	fastSrand(0);

	t=getFrames()+50*10;

	while(getFrames()<=t) for(y=0;y<256-8;y+=6)
	{
		for(x=0;x<256-4;x+=4)
		{
			z[0]=32+fastRandInt(96);

			print4(x,y,z,7,0);
		}
	}

	cls(SCREEN);
}
	
void testText()
{
	unsigned int x,y,t,t2;
	unsigned char c;
	library font;
	char s[1],z[64];

	init(8);

	puts("Loading font...");

	sprintf(z,"%sATARI_LIB",drive);
	
	if(loadLibrary(&font,z,1,0)==0)
	{
		printf("Could not load font %s\n",z);
		exit(1);
	}

	//loadLibrary(&font,z,1,1);
	//
	
	for(c=0;c<font.n;c++)
	{
		for(t=1;t<4;t++)
		{
			free(font.images[c].datashifter[1]);
			free(font.images[c].maskshifter[1]);
		}
	}

	setFontMasking(2);

	t=getFrames();

	for(c=32;c<128;c++)
	{
		s[0]=(char)c;

		for(y=0;y<32;y++)
			for(x=0;x<32;x++)
				printStringAtBlock(SCREEN,&font,8,x,y,s);
	}

	t=getFrames()-t;

	t2=getFrames();

	for(c=32;c<128;c++)
	{
		for(y=0;y<32;y++)
			for(x=0;x<32;x++)
				printCharAtBlock(SCREEN,&font,x,y,c);
	}

	t2=getFrames()-t2;

	printf("%d\n",t);
	printf("%d\n",t2);

	sleep(5);
}

//////////
// main //
//////////

int main(int argc, char *argv[],char *argp[])
{
	unsigned int s;

	if(getenv("DRIVE")!=NULL) strcpy(drive,getenv("DRIVE"));

	printf("Default drive is '%s'\n",drive);

	framesInit();
	setSysBase((unsigned char *)0x28000);

	if(argc<2)
	{
		char line[16];

		while(1)
		{
			puts("\nTest menu\n1) OS text\n2) Direct text\n3) Small text\n4) Keys\n5) Sprite drawing benchmark\n6) 2d graphics benchmark\n\n?");

			fgets(line,80,stdin);

			s=atoi(line);
	
			switch(s)
			{
				case 1: osText(); break;
				case 2: testText(); break;
				case 3: test4Text(); break;
				case 4: testKey(); break; 
				case 5: benchmark(); break;
				case 6: test(); break;
				default: puts("?");
			}

		}
	}
	else
	{
		// Parse the args
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

	return 0;
}
