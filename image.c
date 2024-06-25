#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include <qdos.h>
#include <math.h>

#include "image.h"

void binPrint(unsigned int i,unsigned char d);

screen SCREEN;

// Print a number in binary to a set number of places...

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

char *readLine(FILE *in,char *buffer)
{
        do
        {
                if(feof(in))
                {
                        puts("Error reading library!\n");
                        exit(1);
                }

                fgets(buffer,80,in);
        }
        while(buffer[0]=='#');

        return buffer;
}

void preShift(image *image);

int bLoadLibrary(library *library,char *filename,int shift)
{
	unsigned int i,n,b;
	char buffer[80];
	unsigned short *d,*m;
	FILE *in;

	in=fopen(filename,"rb");

	if(in==NULL)
	{
		printf("Error: Cannot open '%s' to read\n",filename);
		return 0;
	}

	fread(&library->n,sizeof(unsigned int),1,in);

        library->images=(image *)(myMalloc(sizeof(image)*library->n));

	for(i=0;i<library->n;i++)
	{
		#ifdef MAGIC
		library->images[i].magic=MAGIC;
		#endif
	
        	readLine(in,buffer);
                buffer[strcspn(buffer, "\r\n")] = 0;

                library->images[i].name=(char *)myMalloc(strlen(buffer)+1);
                strcpy(library->images[i].name,buffer);

		fread(&library->images[i].x,sizeof(unsigned int),1,in);
		fread(&library->images[i].y,sizeof(unsigned int),1,in);

                n=2*sizeof(unsigned short)*library->images[i].x*library->images[i].y;

                if(n==0) continue;

                d=library->images[i].data=(unsigned short *)(myMalloc(n));
                m=library->images[i].mask=(unsigned short *)(myMalloc(n));

                for(b=0;b<library->images[i].y;b++)
                {
			fread(d,sizeof(unsigned short),library->images[i].x,in);
			fread(m,sizeof(unsigned short),library->images[i].x,in);

			d+=library->images[i].x;
			m+=library->images[i].x;
                }

                if(shift)
                {
                        preShift(&library->images[i]);

                        free(library->images[i].data);
                        free(library->images[i].mask);
                }
	}

	return 1;
}

void bSaveLibrary(library *library,char *filename)
{
	FILE *out;
	unsigned int i,b;
        unsigned short *d,*m;

	out=fopen(filename,"wb");

	if(out==NULL)
	{
		printf("Error: Cannot open '%s' to write\n",filename);
		exit(2);
	}

	fwrite(&library->n,sizeof(unsigned int),1,out); // n

	for(i=0;i<library->n;i++)
	{
		fprintf(out,"%s\n",library->images[i].name);

                fwrite(&library->images[i].x,sizeof(unsigned int),1,out);
                fwrite(&library->images[i].y,sizeof(unsigned int),1,out);

                d=library->images[i].data;
                m=library->images[i].mask;

                for(b=0;b<library->images[i].y;b++)
                {
                        fwrite(d,sizeof(unsigned short),library->images[i].x,out);
                        fwrite(m,sizeof(unsigned short),library->images[i].x,out);

                        d+=library->images[i].x;
                        m+=library->images[i].x;
                }
	}

	fclose(out);
}

void loadLibrary(library *library,char *filename,int shift,int verbose)
{
	int i,a,b;
	unsigned short *d,*m;

	FILE *in;
	char buffer[80];

	if(verbose) puts("Loading library...");

	in=fopen(filename,"r");

	if(in==NULL)
	{
		printf("ERROR: Cannot read %s\n",filename);
		exit(1);
	}

	readLine(in,buffer); library->n=atoi(buffer);

	if(verbose) printf(" images: %d\n",library->n);
	
	library->images=(image *)(myMalloc(sizeof(image)*library->n));

	for(i=0;i<library->n;i++)
	{
		int n;

		//printf("%d\n",n);

		#ifdef MAGIC
		library->images[i].magic=MAGIC;
		#endif

		readLine(in,buffer);
		if(verbose)  printf("  %d %s",i,buffer);
		buffer[strcspn(buffer, "\r\n")] = 0;

		library->images[i].name=(char *)myMalloc(strlen(buffer)+1);
		strcpy(library->images[i].name,buffer);

		readLine(in,buffer); library->images[i].x=atoi(buffer); 
		readLine(in,buffer); library->images[i].y=atoi(buffer); 

		n=2*sizeof(unsigned short)*library->images[i].x*library->images[i].y;

		if(n==0)
		{
			printf("N is zero! %d x %d - skipping!\n",library->images[i].x,library->images[i].y);
			continue;
		}

		d=library->images[i].data=(unsigned short *)(myMalloc(n));
		m=library->images[i].mask=(unsigned short *)(myMalloc(n));

		for(b=0;b<library->images[i].y;b++)
		{
			for(a=0;a<library->images[i].x;a++)
			{
				readLine(in,buffer); *d++=(unsigned short)atoi(buffer);
				readLine(in,buffer); *m++=(unsigned short)atoi(buffer);
			}
		}

		for(a=0;a<2*library->images[i].x*library->images[i].y;a+=2)
		{
			unsigned short hi,lo;

			hi=(library->images[i].data[a+1]&255)
                          |(library->images[i].data[a]<<8);

			lo=(library->images[i].data[a]&0xff00)
			  |(library->images[i].data[a+1]>>8);

			library->images[i].data[a]=hi;
			library->images[i].data[a+1]=lo;

			hi=(library->images[i].mask[a+1]&255)
                          |(library->images[i].mask[a]<<8);

			lo=(library->images[i].mask[a]&0xff00)
			  |(library->images[i].mask[a+1]>>8);

			library->images[i].mask[a]=hi;
			library->images[i].mask[a+1]=lo;
		}

                if(shift)
		{
			preShift(&library->images[i]);

			//free(library->images[i].data);
			//free(library->images[i].mask);
		}
	}

	fclose(in);

	if(verbose) printf("Loaded %d sprites.\n",library->n);
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
