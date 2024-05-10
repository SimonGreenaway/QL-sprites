#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <qdos.h>
#include <math.h>

#include "image.h"

void binPrint(unsigned int i,unsigned char d);

unsigned char *addresses[256];
unsigned int secondAddress;
unsigned short bits[8];

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

        if(c-33>=font->n)
        {
                printf("Font error: %d>=%d\n",c-33,font->n);
                exit(1);
        }

        s.x=x; s.y=y;
        s.image[0]=&font->images[c-33];
        s.currentImage=0;
        s.draw=1;
        s.mask=fontMasking;

        spritePlot(screen,&s);
}

void printAt(screen screen,library *font,unsigned int x,unsigned y,char *s)
{
        while(*s!=0)
        {
                if(*s!=32) printCharAt(screen,font,x,y,*s);

                s++;
                x+=6;
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

	memset(p,i,0);

	return p;
}

// Initialise the sprite system

//long _stack = 4L*1024L; /* size of stack */
 //long _mneed = 4L*1024L; /* minimum requirement */
//long _mneed = 256L*1024L; /* minimum requirement */
 //long _memmax = 9999L * 1024L; /* maximum allowed */
 //long _memincr = 1L * 1024L; /* increment size */
 //long _memqdos = 20L * 1024L; /* minimum for QDOS */

//long _stack = 500*1024L; /* size of stack */

void init(unsigned int c)
{
	int i;
	short colours=c,mode=0;

	//background=(unsigned char *)createBuffer(256);
	//scratch=createBuffer(256);
	//secondAddress=(int)(background)-0x20000;

	mt_dmode(&colours,&mode);

	for(i=0;i<256;i++) addresses[i]=(unsigned char *)(i<<7);

	for(i=0;i<8;i++) bits[i]=(i&3)+(i&4)<<7;

	SCREEN=(screen)0x20000;
}

void spriteSetup(sprite *s,char *name)
{
	bzero(s,sizeof(sprite));

	s->mask=s->draw=1;
	strcpy(s->name,name);

	s->boundsCheck=s->movement=NULL;
	s->images=0;
}

void spriteClearImages(sprite *s)
{
	s->images=s->currentImage=0;
}

void spriteAddImage(sprite *s,library *lib,unsigned int i)
{
	if(s->images==8)
	{
		printf("Too many images added to sprite '%s'\n",s->name);
		exit(1);
	}
	else if(i>=lib->n)
	{
		printf("Adding invalid image %d to sprite '%s'\n",i,s->name);
		exit(1);
	}
	#ifdef MAGIC
	else if(lib->images[i].magic!=MAGIC)
	{
		printf("Adding invalid image to sprites '%s'\n",s->name);
		exit(1);
	}
	#endif

	s->image[s->images++]=&lib->images[i];
}

void spriteSetImage(sprite *s,unsigned int ci)
{
	if(ci>=s->images)
	{
		printf("Error: Trying to use image %d/%d on sprite '%s'\n",ci,s->images,s->name);
		exit(1);
	}

	s->currentImage=ci;
}

void fill(screen screen,unsigned int rowStart,unsigned int rowEnd,unsigned char c)
{
	memset((char *)screen+(rowStart<<7),c,(rowEnd-rowStart)<<7);
}

// Draw an image, erasing old one if needed

void spritePlot(screen screen,sprite *sprite)
{
	image *image=sprite->image[sprite->currentImage];

	unsigned short *address=(unsigned short *)screen;
	unsigned int addressDelta=64-image->x;

	unsigned short *shifter=image->datashifter[sprite->x&3];
	unsigned short *maskshifter=image->maskshifter[sprite->x&3];

	unsigned xlim=image->x>>1;

	address+=sprite->y*64+(sprite->x>>2);

	#ifdef MAGIC
	if(image->magic!=MAGIC)
	{
		puts("Invalid sprite being drawn)!");
		printf("'%s' ?\n",sprite->name);
		exit(1);
	}

	if(sprite->y<0)
	{
		printf("image %s <y sprite '%s'\n",image->name,sprite->name);
		exit(1);
	}
	else if(sprite->y+image->y>255)
	{
		printf("image %s %d>y sprite '%s'\n",image->name,sprite->y+image->y,sprite->name);
		exit(1);
	}
	
	#endif

	if(sprite->y<0)
	{
		printf("ERROR: Sprite plot '%s' with y<0 sprite '%s'",sprite->image[sprite->currentImage]->name,sprite->name);
		exit(4);
	}

	if(sprite->mask&&sprite->draw)
	{
		register unsigned int a;

		switch(xlim) // Welcome to loop unroll City....
		{
			case 4:	for(a=0;a<image->y;a++)
				{
					*address++=*address&*maskshifter++|*shifter++; 
					*address++=*address&*maskshifter++|*shifter++; 
					*address++=(*address&*maskshifter++|*shifter++);
					*address++=*address&*maskshifter++|*shifter++; 
					*address++=(*address&*maskshifter++|*shifter++);
						
					*address++=*address&*maskshifter++|*shifter++; 
					*address++=(*address&*maskshifter++|*shifter++);
					*address++=*address&*maskshifter++|*shifter++; 
					*address=  *address&*maskshifter++|*shifter++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 3:	for(a=0;a<image->y;a++)
				{
					*address++=*address&*maskshifter++|*shifter++; 
					*address++=*address&*maskshifter++|*shifter++; 
					*address++=(*address&*maskshifter++|*shifter++);
					*address++=*address&*maskshifter++|*shifter++; 
					*address++=(*address&*maskshifter++|*shifter++);
					*address++=*address&*maskshifter++|*shifter++; 
					*address=  *address&*maskshifter++|*shifter++; 
		
					address+=addressDelta;
				}
	
				break;
		
			case 2:	for(a=0;a<image->y;a++)
				{
					*address++=*address&*maskshifter++|*shifter++; 
					*address++=*address&*maskshifter++|*shifter++; 
					*address++=(*address&*maskshifter++|*shifter++);

					*address++=*address&*maskshifter++|*shifter++; 
					*address=  *address&*maskshifter++|*shifter++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 1:	for(a=0;a<image->y;a++) // 8x8
				{
					*address++=*address&*maskshifter++|*shifter++; 
					*address++=*address&*maskshifter++|*shifter++; 
					*address=  *address&*maskshifter++|*shifter++; 
		
					address+=addressDelta;
				}
	
				break;
	
			default:	for(a=0;a<image->y;a++)
					{
						unsigned int b;
		
						for(b=0;b<xlim;b++)
						{
							*address++=*address&*maskshifter++|*shifter++; 
							*address++=*address&*maskshifter++|*shifter++; 
							*address=*address&*maskshifter++|*shifter++; 
						}
		
						address+=addressDelta;
					}
		}
	}
	else if(sprite->draw)
	{
		register unsigned int a;

		switch(xlim) // Welcome to loop unroll City....
		{
			case 4:	for(a=0;a<image->y;a++)
				{
					*address++|=*shifter++; 
					*address++|=*shifter++; 
					//*address|=*shifter++; 
					*address++|=*shifter++; 
					*address++|=*shifter++; 
					//*address|=*shifter++; 
					*address++|=*shifter++; 
					*address++|=*shifter++; 
					//*address|=*shifter++; 
					*address++|=*shifter++; 
					*address++|=*shifter++; 
					*address  |=*shifter++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 3:	for(a=0;a<image->y;a++)
				{
					*address++|=*shifter++; 
					*address++|=*shifter++; 
					//*address|=*shifter++; 
					*address++|=*shifter++; 
					*address++|=*shifter++; 
					//*address|=*shifter++; 
					*address++|=*shifter++; 
					*address++|=*shifter++; 
					*address  |=*shifter++; 
		
					address+=addressDelta;
				}
	
				break;
		
			case 2:	for(a=0;a<image->y;a++)
				{
					*address++|=*shifter++; 
					*address++|=*shifter++; 
					//*address|=*shifter++; 
					*address++|=*shifter++; 
					*address++|=*shifter++; 
					*address  |=*shifter++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 1:	for(a=0;a<image->y;a++)
				{
					*address++|=*shifter++; 
					*address++|=*shifter++; 
					*address  |=*shifter++; 
		
					address+=addressDelta;
				}

				break;
	
			default:	for(a=0;a<image->y;a++)
					{
						unsigned int b;
		
						for(b=0;b<xlim;b++)
						{
							*address++|=*shifter++; 
							*address++|=*shifter++; 
							*address  |=*shifter++; 
						}
		
						address+=addressDelta;
					}
		}
	}
	else //if(sprite->mask)
	{
		register unsigned int a;

		switch(xlim) // Welcome to loop unroll City....
		{
			case 4:	for(a=0;a<image->y;a++)
				{
					*address++=*address&*maskshifter++; 
					*address++=*address&*maskshifter++; 
					//*address=*address&*maskshifter++;
					*address++=*address&*maskshifter++;
					*address++=*address&*maskshifter++; 
					//*address=*address&*maskshifter++;
					*address++=*address&*maskshifter++;
					*address++=*address&*maskshifter++; 
					//*address=*address&*maskshifter++;
					*address++=*address&*maskshifter++;
					*address++=*address&*maskshifter++; 
					*address=  *address&*maskshifter++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 3:	for(a=0;a<image->y;a++)
				{
					*address++=*address&*maskshifter++; 
					*address++=*address&*maskshifter++; 
					//*address=*address&*maskshifter++;
					*address++=*address&*maskshifter++;
					*address++=*address&*maskshifter++; 
					//*address=*address&*maskshifter++;
					*address++=*address&*maskshifter++;
					*address++=*address&*maskshifter++; 
					*address=  *address&*maskshifter++; 
		
					address+=addressDelta;
				}
	
				break;
		
			case 2:	for(a=0;a<image->y;a++)
				{
					*address++=*address&*maskshifter++; 
					*address++=*address&*maskshifter++; 
					//*address=*address&*maskshifter++;
					*address++=*address&*maskshifter++;
					*address++=*address&*maskshifter++; 
					*address=  *address&*maskshifter++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 1:	for(a=0;a<image->y;a++)
				{
					*address++=*address&*maskshifter++; 
					*address++=*address&*maskshifter++; 
					*address=  *address&*maskshifter++; 
		
					address+=addressDelta;
				}

				break;
	
			default:	for(a=0;a<image->y;a++)
					{
						unsigned int b;
		
						for(b=0;b<xlim;b++)
						{
							*address++=*address&*maskshifter++; 
							*address++=*address&*maskshifter++; 
							*address=*address&*maskshifter++; 
						}
		
						address+=addressDelta;
					}
		}
	}
}

// Erase image, using the background given

void spriteClear(screen scr,screen background,sprite *sprite,char m)
{
	register int a;

	image *image=sprite->image[sprite->currentImage];

	unsigned short *address=(unsigned short *)scr;
	unsigned short *address2=(unsigned short *)background;

	unsigned int addressDelta=64-image->x;

	unsigned short *shifter=image->datashifter[sprite->x&3];
	unsigned short *maskshifter=image->maskshifter[sprite->x&3];

	unsigned xlim=image->x>>1;

	address+=sprite->y*64+(sprite->x>>2);
	address2+=sprite->y*64+(sprite->x>>2);

	if(sprite->currentImage>=sprite->images)
	{
		printf("Error: Sprite clear - current sprite image out of range (%d) for '%s'\nAt %c",sprite->currentImage,sprite->name,m);

		exit(1);
	}
	#ifdef MAGIC
	if(image->magic!=MAGIC)
	{
		printf("Invalid sprite '%s' image %d being cleared! Magic is %x\nAt %c\n",sprite->name,sprite->currentImage,image->magic,m);
		exit(1);
	}

	if(sprite->y<0)
	{
		printf("image %s <y\nAt %c\n",image->name,m);
		exit(1);
	}
	else if(sprite->y+image->y>255)
	{
		printf("image %s %d>y\nAt %c\n",image->name,sprite->y+image->y,m);
		exit(1);
	}
	
	#endif

	if(sprite->y<0)
	{
		printf("ERROR: Sprite plot '%s' with y<0\nAt %c",sprite->image[sprite->currentImage]->name,m);
		exit(4);
	}

	switch(xlim) // Welcome to loop unroll City....
	{
		case 4:	for(a=0;a<image->y;a++) // x32
			{
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				//*address=  *address&*maskshifter|(*address2&~*maskshifter); maskshifter++;
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;

				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				//*address=  *address&*maskshifter|(*address2&~*maskshifter); maskshifter++;
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;

				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				//*address=  *address&*maskshifter|(*address2&~*maskshifter); maskshifter++;
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;

				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				*address=  *address&*maskshifter|(*address2&~*maskshifter); maskshifter++;
	
				address+=addressDelta;
				address2+=addressDelta;
			}

			break;

		case 3:	for(a=0;a<image->y;a++) // x24
			{
	
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				//*address=  *address&*maskshifter|(*address2&~*maskshifter); maskshifter++;
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;

				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				//*address=  *address&*maskshifter|(*address2&~*maskshifter); maskshifter++;
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;

				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				*address=  *address&*maskshifter|(*address2&~*maskshifter); maskshifter++;
				address+=addressDelta;
				address2+=addressDelta;
			}

			break;
	
		case 2:	for(a=0;a<image->y;a++) // x16
			{
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				//*address=*address&*maskshifter|(*address2&~*maskshifter); maskshifter++;
				*address++=  *address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				*address=  *address&*maskshifter|(*address2&~*maskshifter); maskshifter++;

				address+=addressDelta;
				address2+=addressDelta;
			}

			break;

		case 1:	for(a=0;a<image->y;a++) // x8
			{
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				*address++=*address&*maskshifter|(*address2++&~*maskshifter);  maskshifter++;
				*address=  *address&*maskshifter|(*address2&~*maskshifter); maskshifter++;


				address+=addressDelta;
				address2+=addressDelta;
			}

			break;

		default:	for(a=0;a<image->y;a++)
				{
					unsigned int b;
	
					for(b=0;b<xlim;b++)
					{
						*address++=*address&*maskshifter|(*address2++&~*maskshifter);  maskshifter++;
						*address++=*address&*maskshifter|(*address2++&~*maskshifter);  maskshifter++;
					}
	
					address+=addressDelta;
					address2+=addressDelta;
				}
	}
}

// Draw an image, erasing old one if needed

void imagePlot(unsigned int x,unsigned int y,image *image)
{
	unsigned short *pmask=image->mask,*data=image->data;
	const int shifts=2*(x&3);
	unsigned char *address=addresses[y]+2*(x>>2);
	unsigned int addressRow=128-2*image->x;

	unsigned int yloop;

	for(yloop=0;yloop<image->y;yloop++)
	{
		int xloop;

		for(xloop=0;xloop<image->x;xloop+=2)
		{
			struct shifter shifterHigh,shifterLow,mask;

			shifterHigh.z.l=shifterLow.z.l=mask.z.l=0;

			shifterHigh.z.w[0]=*data++;
			shifterLow.z.w[0]=*data++;
			mask.z.w[0]=*pmask;

			shifterHigh.z.l>>=shifts;
			shifterLow.z.l>>=shifts;
			mask.z.l>>=shifts;

			mask.z.l=~mask.z.l;

			*address++=((*address)&mask.z.b[0])|shifterLow.z.b[0]; 
			*address++=((*address)&mask.z.b[0])|shifterHigh.z.b[0]; 
			*address++=((*address)&mask.z.b[1])|shifterLow.z.b[1];
			*address++=((*address)&mask.z.b[1])|shifterHigh.z.b[1];
			*address++=((*address)&mask.z.b[2])|shifterLow.z.b[2];
			*address--=((*address)&mask.z.b[2])|shifterHigh.z.b[2];
		}

		address+=addressRow;
	}
}

void tilePlot(unsigned short x,unsigned short y,image *image)
{
	unsigned short *mask=(unsigned short *)image->mask;
	unsigned short *data=(unsigned short *)image->data;
	int a;

	for(a=0;a<image->y;a++)
	{
		int b;

		for(b=0;b<image->x;b++)
		{
			unsigned char *address=addresses[a+y]+(x>>2)+b;

			//(*address)=((*address)&*mask)|(*data);
			*address=*data;

			mask++;
			data++;
		}
	}
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

void preShift(image *image)
{
        int a,b,x,i,n=image->y*image->x/2*8;

	if(n==0)
	{
		printf("Image size odd: %d x %d\n",image->y,image->x);
		exit(3);
	}

        for(x=0;x<4;x++)
        {
                struct shifter shifter1,shifter2,mask,tmp;

                unsigned short *pmask=(unsigned short *)image->mask,*data=(unsigned short *)image->data;
                const unsigned int shifts=2*x;

                unsigned short *ss=image->datashifter[x]=(unsigned short *)myMalloc(n);
                unsigned short *mm=image->maskshifter[x]=(unsigned short *)myMalloc(n);
		
		unsigned short *ss0=ss,*mm0=mm;

                for(a=0;a<image->y;a++)
                {
                        for(b=0;b<image->x;b+=2)
                        {
                                shifter1.z.l=shifter2.z.l=mask.z.l=0;

                                shifter1.z.w[0]=*data++;
                                shifter2.z.w[0]=*data++;
                                mask.z.w[0]=*pmask++; pmask++;

                                shifter1.z.l>>=shifts;
                                shifter2.z.l>>=shifts;
                                mask.z.l>>=shifts;

                                mask.z.l=~mask.z.l;

				for(i=0;i<3;i++)
				{
					tmp.z.b[1]=shifter1.z.b[i];
					tmp.z.b[0]=shifter2.z.b[i];

				
					if((b>0)&&(i==0))
					{
						ss--;
						*ss++|=tmp.z.w[0];
					}
					else *ss++=tmp.z.w[0];

					tmp.z.b[0]=mask.z.b[i];
					tmp.z.b[1]=mask.z.b[i];

					if((b>0)&&(i==0))
					{
						mm--;
						*mm++&=tmp.z.w[0];
					}
					else *mm++=tmp.z.w[0];
				}
                        }
                }

		if((ss-ss0>n)||(mm-mm0>n))
		{
			printf("loadLibrary error: [%d:%d/%d]",n,ss-ss0,mm-mm0);

			exit(1);
		}
        }
}

void bLoadLibrary(library *library,char *filename,int shift)
{
	unsigned int i,n,b,a;
	char buffer[80];
	unsigned short *d,*m;
	FILE *in;

	in=fopen(filename,"rb");

	if(in==NULL)
	{
		printf("Error: Cannot open '%s' to read\n",filename);
		exit(2);
	}

	fread(&library->n,sizeof(unsigned int),1,in);

        library->images=(image *)(myMalloc(sizeof(image)*library->n));

	for(i=0;i<library->n;i++)
	{
		library->images[i].magic=MAGIC;
	
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

void loadLibrary(library *library,char *filename,int shift)
{
	int i,a,b;
	unsigned short *d,*m;

	FILE *in;
	char buffer[80];

	puts("Loading library...");

	in=fopen(filename,"r");

	if(in==NULL)
	{
		printf("ERROR: Cannot read %s\n",filename);
		exit(1);
	}

	readLine(in,buffer); library->n=atoi(buffer);

	printf(" images: %d\n",library->n);
	
	library->images=(image *)(myMalloc(sizeof(image)*library->n));

	for(i=0;i<library->n;i++)
	{
		int n;

		//printf("%d\n",n);

		library->images[i].magic=MAGIC;
		readLine(in,buffer); printf("  %d %s",i,buffer);
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

	printf("Loaded %d sprites.\n",library->n);
}

////////////////////////////////
// Buffer creation and moving //
////////////////////////////////

unsigned short *screenAddress(screen screen,unsigned int y,unsigned int x)
{
	unsigned short *address=(unsigned short *)screen;
	unsigned short data;
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

	sprintf(file2,"%s%s",dir,file);

        in=fopen(file2,"rb");

        if(in!=NULL)
        {
                fread(scr,1,32768,in);

                fclose(in);

                return 1;
        }

        return 0;
}

/*
typedef struct
{
	unsigned int active:1;

	int images;
	image *image[8];

	int x,y,dx,dy,currentImage;
	unsigned int mask,draw;
	timer timer,timer2;

	int xmin,xmax,ymin,ymax;
	int (*bounce)(sprite *);
} sprite2;

typedef struct
{
	sprite2 *sprite;
	sprite_list *previous,*next;
}
sprite_list;

void run(screen screen,screen background,sprite_list *list,int n)
{
	unsigned int i;
	unsigned int frames=0; //getFrames();

	while(list!=NULL)
	{
		sprite *sprite=sprite_list->sprite;

		if((sprite!=NULL)&&sprite->active&&(sprite->timer.value<=frames))
		{
			if((sprite->dx!=0)||(sprite->dy!=0)) // Only move if we have a delta
			{
				// Erase the sprite, using the background
				sprite->draw=0;spritePlot2(screen,background,sprite);

				// Move the sprite
				sprite->x+=sprite->dx;
				sprite->y+=sprite->dy;

				// Draw the moved sprite
				sprite->draw=1;spritePlot2(screen,background,sprite);

				// Check for a bounce
				if((sprite->x<=sprite->xmin)||(sprite->y<=sprite->ymin)
				 ||(sprite->x>=sprite->xmax)||(sprite->y>=sprite->ymax))
				{
					if(sprite->bounce==NULL)
					{
						// If no bounce call-back just stop the sprite
						sprite->dx=sprite->dy=0;
					}
					else sprite->bounce(sprite); // Run the bounce call-back 
				}
			}
	
			sprite->timer.value+=sprite->timer.delta; // Set the time for the next movement
		}

		sprite_list=sprite_list->next; // Move to next sprite in the list (or NULL)
	}
}
*/
