#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include <qdos.h>
#include <math.h>

#include "image.h"

screen SCREEN;

void* myMalloc(unsigned int i)
{
	void *p=malloc(i);

	if(p==NULL)
	{
		printf("Memory allocation error of %d bytes\n",i);
		exit(3);
	}

	bzero(p,i);

	return p;
}

void *makeHigh(void *p,unsigned int size)
{
	char *p2=myMalloc(size);

	memcpy(p2,p,size);

	return p2;
}

// Initialise the sprite system
//     Set the screen mode and other stuff used by this library

void init(unsigned int c)
{
	short colours=c,mode=0;

	mt_dmode(&colours,&mode);	// Set the mode (4 or 8)

	SCREEN=(screen)0x20000; // Set default screen location
}

////////////////////////////////
// Buffer creation and moving //
////////////////////////////////

unsigned short *screenAddress(screen screen,unsigned int y,unsigned int x)
{
	unsigned short *address=(unsigned short *)screen;

	address+=y*64+(x>>2);

	return address;
}

// Screen 

screen createScreen()
{
	return (screen)myMalloc(32768);
}

void closeScreen(screen s)
{
	free((void *)s);
}

void copyScreen(screen to,screen from,unsigned int rowStart,unsigned int rowEnd)
{
	memcpy((char *)to+(rowStart<<7),(char *)from+(rowStart<<7),(rowEnd-rowStart)<<7);
}

void copyAllScreen(screen to,screen from)
{
	copyScreen(to,from,0,256);
}

void showAll(screen screen)
{
	copyAllScreen(SCREEN,screen);
}

void show(screen screen,unsigned int lowy,unsigned int highy)
{
	copyScreen(SCREEN,screen,lowy,highy);
}

int loadScreen(unsigned char *scr,char *dir,char *file)
{
	char file2[128];
        FILE *in;

	//puts("loadScreen: creating filename"); sleep(1);

	sprintf(file2,"%s%s",dir,file);

	//printf("loadScreen: opening '%s'\n",file2); sleep(1);

        in=fopen(file2,"r");

        if(in!=NULL)
        {
		//printf("loadScreen: Loading file into memory %X\n",(unsigned int)scr); sleep(1);

                fread(scr,1,32768,in);


	//puts("loadScreen: closing file"); sleep(1);
                fclose(in);

	
	//puts("loadScreen: returning 1 (=success)"); sleep(1);

                return 1;
        }

	//puts("loadScreen: returning 0 (=failure)"); sleep(1);
        return 0;
}
