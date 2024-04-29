#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <qdos.h>

#include "image.h"

void benchmark()
{
	unsigned int s;
	screen scratch,background=createScreen();
	library lib;

	scratch=background;

	init();

	loadLibrary(&lib,"test_lib",1);
	//copyAllScreen(background,SCREEN);

	for(s=0;s<4;s++)
	{
		const int n=10;

		unsigned long t,c=0,pass;
		unsigned int x=0,y=0;
		sprite sprite[8];

		for(c=0;c<8;c++)
		{
			sprite[c].image[0]=&lib.images[s];
			sprite[c].currentImage=0;
			sprite[c].x=x++;

			sprite[c].y=y;
			sprite[c].draw=1;

			y+=sprite[c].image[0]->y;
			if(y+sprite[c].image[0]->y>255) y=0;
		}

		for(pass=0;pass<2;pass++)
		{
			for(c=0;c<8;c++) sprite[c].mask=pass;

			t=getFrames()+n*50;
	
			while(t>getFrames())
			{
				unsigned int i,y=0,x=0;

				copyAllScreen(scratch,background);

				for(i=0;i<8;i++)
				{
					spritePlot(scratch,&sprite[i]);
				}

				c+=8;

				#ifdef DOUBLEBUFFER
				showAll(scratch);
				#endif
			}

			#ifdef DOUBLEBUFFER
			showAll(scratch);
			#endif

			printf("%c %d x %d -> %d\n",pass==1?'M':' ',lib.images[s].x<<4,lib.images[s].y,c);
			copyAllScreen(background,SCREEN);
		}
	}

	exit(0);
}

void test()
{
	library l;
	sprite s;
	unsigned int i,j,k,m;

	init();

	loadLibrary(&l,"test_lib",1); 

	for(i=0;i<4;i++) s.image[i]=&l.images[i];

	for(m=1;m<4;m++)
	{
		s.draw=m&1; 
		s.mask=(m&2)>1;

		for(j=0;j<4;j++)
		{
			for(i=0;i<32768;i++)
				*((unsigned char *)(0x20000+i))=*((unsigned char*)i);

			printf("M=%d D=%d\n",s.mask,s.draw);
	
	
			s.x=s.y=0;
			s.currentImage=j;
		
			for(i=0;1;i++)
			{
				s.x=i; s.y=i*s.image[s.currentImage]->y;
				if(s.y+s.image[s.currentImage]->y>=255) break;	
				spritePlot(SCREEN,&s);
			}
		
			while(!keyrow(1));
			while(keyrow(1));

			if(m==3)
			{
				s.draw=0;
				for(i=0;1;i++)
				{
					s.x=i; s.y=i*s.image[s.currentImage]->y;
					if(s.y+s.image[s.currentImage]->y>=255) break;	
					spritePlot(SCREEN,&s);
				}
				s.draw=1;
				while(!keyrow(1));
				while(keyrow(1));

				s.y=0;

				for(i=0;i<255-s.image[s.currentImage]->y;i++)
				{
					unsigned int f;

					s.x=i;
								
					spritePlot(SCREEN,&s);

					s.draw=0;
					f=getFrames();		
					while(f>=getFrames()) ;
					spritePlot(SCREEN,&s);
					s.draw=1;
				}
			}
		}
	}

	exit(0);
}

//////////
// main //
//////////

int main(int argc, char *argv[])
{
	unsigned int s;

	// Parse the args

	setSysBase((unsigned char *)0x28000);

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
