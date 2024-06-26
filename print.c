#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include <qdos.h>
#include <math.h>

#include "image.h"

void binPrint(unsigned int i,unsigned char d)
{
	int z,b=32768;

	for(z=15;z>=0;z--)
	{
		if(z<=d-1) putchar(i&b?'1':'0');

		b>>=1;
	}
}

unsigned int fontMasking=0;

void setFontMasking(unsigned int m)
{
	fontMasking=m;
}

void printCharAt(screen screen,library *font,unsigned int x,unsigned int y,char c)
{
        sprite s;
	char start=font->images[0].name[0];

        if((c-start<0)||(c-start>=font->n))
        {
                printf("Font error: start=%d (%c), c=%d (%c). %d>=%d\n",
			start,start,c,c,c-start,font->n);
                exit(1);
        }

        s.x=x; s.y=y;
        s.image[0]=&font->images[c-start];
        s.currentImage=0;
        s.draw=1;
        s.mask=fontMasking;

	if(fontMasking==2)
		fillBox(screen,s.x,s.y,s.x+8,s.y+8,0);

        spritePlot(screen,&s);
}

void printAt(screen screen,library *font,unsigned int width,unsigned int x,unsigned y,char *s)
{
        while(*s!=0)
        {
                if(*s!=32) printCharAt(screen,font,x,y,*s);

                s++;
                x+=width;
        }
}

void printCharAtBlock(screen screen,library *font,unsigned int x,unsigned y,char c)
{
        char start=font->images[0].name[0];
        unsigned long *address=(unsigned long *)ADDRESS(SCREEN,x*8,y*8);

	if(c==' ')
 	{
                *address    =0;
                address[32] =0;
                address[64] =0;
                address[96] =0;
                address[128]=0;
                address[160]=0;
                address[192]=0;
                address[224]=0;
        }
        else
        {
                unsigned short *d=(unsigned short *)font->images[c-start].datashifter[0];

                address[0]  =*((unsigned long *)&d[0]);
                address[32] =*((unsigned long *)&d[3]);
                address[64] =*((unsigned long *)&d[6]);
                address[96] =*((unsigned long *)&d[9]);
                address[128]=*((unsigned long *)&d[12]);
                address[160]=*((unsigned long *)&d[15]);
                address[192]=*((unsigned long *)&d[18]);
                address[224]=*((unsigned long *)&d[21]);
        }
}

void printStringAtBlock(screen screen,library *font,unsigned int width,unsigned int x,unsigned y,char *s)
{
	char start=font->images[0].name[0];
	unsigned long *address=(unsigned long *)ADDRESS(SCREEN,x*8,y*8);

        while(*s!=0)
        {
                if(*s==32)
		{
			*address    =0;
			address[32] =0;
			address[64] =0;
			address[96] =0;
			address[128]=0;
			address[160]=0;
			address[192]=0;
			address[224]=0;
		}
		else
		{
			unsigned short *d=font->images[*s-start].datashifter[0];

			*address    =*((unsigned long *)d);
			address[32] =*((unsigned long *)&d[3]);
			address[64] =*((unsigned long *)&d[6]);
			address[96] =*((unsigned long *)&d[9]);
			address[128]=*((unsigned long *)&d[12]);
			address[160]=*((unsigned long *)&d[15]);
			address[192]=*((unsigned long *)&d[18]);
			address[224]=*((unsigned long *)&d[21]);
		}

                s++;
		address++;
        }
}
