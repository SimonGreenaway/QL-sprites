#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include <qdos.h>
#include <math.h>

#include "image.h"

// Initiate a sprite

void spriteSetup(sprite *s,char *name)
{
	spriteSetupFull(s,name,1,1,1);
}

void spriteSetupFull(sprite *s,char *name,unsigned int active,unsigned int mask,unsigned int draw)
{
	bzero((unsigned char *)s,sizeof(sprite));

	s->mask=mask;
	s->draw=draw;
	if(name!=NULL) strcpy(s->name,name);

	s->boundsCheck=s->movement=NULL;
	s->images=s->currentImage=0;
	s->active=active;
}

// Clear sprite's image list

void spriteClearImages(sprite *s)
{
	s->images=s->currentImage=0;
}

// Add an image to the sprite

void spriteAddImage(sprite *s,image *i)
{
	if(s->images==MAXIMAGES)
	{
		printf("Too many images added to sprite '%s'\n",s->name);
		exit(1);
	}

        s->image[s->images++]=i;
}

void spriteAddImageFromLibrary(sprite *s,library *lib,unsigned int i)
{
	if(s->images==MAXIMAGES)
	{
		printf("Too many images (%d) added to sprite '%s'\n",s->images,s->name);
		exit(1);
	}
	else if(i>=lib->n)
	{
		printf("Adding invalid image %d to sprite '%s' when lib only has %d\n",i,s->name,lib->n);
		exit(1);
	}
	#ifdef MAGIC
	else if(lib->images[i].magic!=MAGIC)
	{
		printf("Adding invalid image to sprites '%s' invalid MAGIC\n",s->name);
		exit(1);
	}
	#endif

	spriteAddImage(s,&lib->images[i]);
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

// Macro to convert a pointer to an unsigned long pointer...
#define L(a) ((unsigned long *)(a))

// Draw an sprite's current image, erasing old one if needed.
//
// Can be in 3 modes: mask+data - maskout screen data and write pixels
//                    data - just write the pixels (if we know the screen is empty)
//                    mask - blank out the sprite (also see spriteClear)

void spritePlot(screen screen,sprite *sprite)
{
	image *image=sprite->image[sprite->currentImage];	// Short cut to the image being drawn

	register unsigned short *address=ADDRESS(screen,sprite->x,sprite->y); // Screen address containing first pixel
	unsigned int addressDelta=64-image->x;		// Delta to add to get to next screen row

	unsigned short *shifts=image->datashifter[sprite->x&3];	// Pre-shifted sprite pixels
	unsigned short *masks=image->maskshifter[sprite->x&3];	// Pre-shifted sprite mask 

	unsigned short *shiftmasks=image->datamaskshifter[sprite->x&3];

	// Sanity checks - best to leave in!
	//
	#ifdef MAGIC
	if(image->magic!=MAGIC)
	{
		printf("Invalid sprite '%s' being drawn! (%x)",sprite->name,image->magic);
		exit(1);
	}

	if(sprite->y<0)
	{
		printf("image %s <y sprite '%s'\n",image->name,sprite->name);
		exit(1);
	}
	else if(sprite->y+image->y>255)
	{
		printf("image %s %d-%d>y sprite '%s'\n",image->name,sprite->y,sprite->y+image->y,sprite->name);
		exit(1);
	}
	
	if(sprite->y<0)
	{
		printf("ERROR: Sprite plot '%s' with y<0 sprite '%s'",sprite->image[sprite->currentImage]->name,sprite->name);
		exit(4);
	}

	#endif

	if(sprite->mask&&sprite->draw) // Draw sprite masking background out
	{
		register unsigned int y;

		switch(image->x>>1) // Welcome to loop unroll City....
		{
			case 4:	for(y=image->y;y;y--) // x32
				{
					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*address=  (*address&*masks++)|*shifts++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 3:	for(y=image->y;y;y--) // x24
				{
					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*address=  (*address&*masks++)|*shifts++; 
		
					address+=addressDelta;
				}
	
				break;
		
			case 2: for(y=image->y;y;y--) // x16
				{
					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*address=  (*address&*masks++)|*shifts++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 1:	if(image->y==8)
				{
					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*address=  (*address&*masks++)|*shifts++; 
					address+=addressDelta;

					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*address=  (*address&*masks++)|*shifts++; 
					address+=addressDelta;

					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*address=  (*address&*masks++)|*shifts++; 
					address+=addressDelta;

					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*address=  (*address&*masks++)|*shifts++; 
					address+=addressDelta;

					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*address=  (*address&*masks++)|*shifts++; 
					address+=addressDelta;

					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*address=  (*address&*masks++)|*shifts++; 
					address+=addressDelta;

					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*address=  (*address&*masks++)|*shifts++; 
					address+=addressDelta;

					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*address=  (*address&*masks++)|*shifts; 
				}
				else for(y=image->y;y;y--)
				{
					*L(address)++=(*L(address)&*L(masks)++)|*L(shifts)++; 
					*address=  (*address&*masks++)|*shifts++; 
		
					address+=addressDelta;
				}
	
				break;
	
			default:	for(y=image->y;y;y--)
					{
						unsigned int x;
		
						for(x=0;x<image->x>>1;x++)
						{
							*address++=(*address&*masks++)|*shifts++; 
							*address++=(*address&*masks++)|*shifts++; 
							*address=(*address&*masks++)|*shifts++; 
						}
		
						address+=addressDelta;
					}
		}
	}
	else if(sprite->draw) // Draw with no mask
	{
		register unsigned int y;

		switch(image->x>>1) // Welcome to loop unroll City....
		{
			case 4:	for(y=image->y;y;y--) // x=32 pixels
				{
					*L(address)++|=*L(shifts)++;
					*L(address)++|=*L(shifts)++;
					*L(address)++|=*L(shifts)++;
					*L(address)++|=*L(shifts)++;
					*address  |=*shifts++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 3:	for(y=image->y;y;y--) // x=24 pixels
				{
					*L(address)++|=*L(shifts)++;
					*L(address)++|=*L(shifts)++;
					*L(address)++|=*L(shifts)++;
					*address  |=*shifts++; 
		
					address+=addressDelta;
				}
	
				break;
		
			case 2:	for(y=image->y;y;y--) // x=16 pixels
				{
					*L(address)++|=*L(shifts)++;
					*L(address)++|=*L(shifts)++;
					*address  |=*shifts++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 1:	if(image->y==8) // x=8 pixels
				{
					*L(address)++|=*L(shifts)++;
					*address  |=*shifts++; 
					address+=addressDelta;

					*L(address)++|=*L(shifts)++;
					*address  |=*shifts++; 
					address+=addressDelta;

					*L(address)++|=*L(shifts)++;
					*address  |=*shifts++; 
					address+=addressDelta;

					*L(address)++|=*L(shifts)++;
					*address  |=*shifts++; 
					address+=addressDelta;

					*L(address)++|=*L(shifts)++;
					*address  |=*shifts++; 
					address+=addressDelta;

					*L(address)++|=*L(shifts)++;
					*address  |=*shifts++; 
					address+=addressDelta;

					*L(address)++|=*L(shifts)++;
					*address  |=*shifts++; 
					address+=addressDelta;

					*L(address)++|=*L(shifts)++;
					*address  |=*shifts; 
				}
				else for(y=image->y;y;y--)
				{
					*L(address)++|=*L(shifts)++;
					*address  |=*shifts++; 
		
					address+=addressDelta;
				}

				break;
	
			default:
				for(y=image->y;y;y--)
				{
					unsigned int x;
		
					for(x=image->x>>1;x;x--)
					{
						*address++|=*shifts++; 
						*address++|=*shifts++; 
						*address  |=*shifts++; 
					}
		
					address+=addressDelta;
				}
		}
	}
	else //if(sprite->mask)
	{
		register unsigned int y;

		switch(image->x>>1) // Welcome to loop unroll City....
		{
			case 4:	for(y=image->y;y;y--)
				{
					*L(address)++&=*L(masks)++;
					*L(address)++&=*L(masks)++;
					*L(address)++&=*L(masks)++;
					*L(address)++&=*L(masks)++;
					*address=  *address&*masks++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 3:	for(y=image->y;y;y--)
				{
					*L(address)++&=*L(masks)++;
					*L(address)++&=*L(masks)++;
					*L(address)++&=*L(masks)++;
					*address=  *address&*masks++; 
		
					address+=addressDelta;
				}
	
				break;
		
			case 2:	for(y=image->y;y;y--)
				{
					*L(address)++&=*L(masks)++;
					*L(address)++&=*L(masks)++;
					*address=  *address&*masks++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 1:	for(y=image->y;y;y--)
				{
					*L(address)++&=*L(masks)++;
					*address=  *address&*masks++; 
		
					address+=addressDelta;
				}

				break;
	
			default:	for(y=image->y;y;y--)
					{
						unsigned int x;
		
						for(x=image->x>>1;x;x--)
						{
							*address++=*address&*masks++; 
							*address++=*address&*masks++; 
							*address=*address&*masks++; 
						}
		
						address+=addressDelta;
					}
		}
	}
}

// Erase image, using the background given

void spriteClear(screen scr,screen background,sprite *sprite)
{
	register int a;

	image *image=sprite->image[sprite->currentImage];

	unsigned short *address=(unsigned short *)scr;
	unsigned short *address2=(unsigned short *)background;

	unsigned int addressDelta=64-image->x;

	unsigned short *maskshifter=image->maskshifter[sprite->x&3];

	unsigned xlim=image->x>>1;

	address+=sprite->y*64+(sprite->x>>2);
	address2+=sprite->y*64+(sprite->x>>2);

	if(sprite->currentImage>=sprite->images)
	{
		printf("Error: Sprite clear - current sprite image out of range (%d) for '%s'\n",sprite->currentImage,sprite->name);

		exit(1);
	}
	#ifdef MAGIC
	if(image->magic!=MAGIC)
	{
		printf("Invalid sprite '%s' image %d being cleared! Magic is %x\n",sprite->name,sprite->currentImage,image->magic);
		exit(1);
	}

	if(sprite->y<0)
	{
		printf("image %s <y\n",image->name);
		exit(1);
	}
	else if(sprite->y+image->y>255)
	{
		printf("image %s %d>y\n",image->name,sprite->y+image->y);
		exit(1);
	}
	
	#endif

	if(sprite->y<0)
	{
		printf("ERROR: Sprite plot '%s' with y<0\n",sprite->image[sprite->currentImage]->name);
		exit(4);
	}

	switch(xlim) // Welcome to loop unroll City....
	{
		case 4:	for(a=0;a<image->y;a++) // x32
			{
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;

				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;

				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;

				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address=  (*address&*maskshifter)|(*address2&~*maskshifter); maskshifter++;
	
				address+=addressDelta;
				address2+=addressDelta;
			}

			break;

		case 3:	for(a=0;a<image->y;a++) // x24
			{
	
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;

				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;

				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address=  (*address&*maskshifter)|(*address2&~*maskshifter); maskshifter++;
				address+=addressDelta;
				address2+=addressDelta;
			}

			break;
	
		case 2:	for(a=0;a<image->y;a++) // x16
			{
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address++=  (*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address=  (*address&*maskshifter)|(*address2&~*maskshifter); maskshifter++;

				address+=addressDelta;
				address2+=addressDelta;
			}

			break;

		case 1:	for(a=0;a<image->y;a++) // x8
			{
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter); maskshifter++;
				*address++=(*address&*maskshifter)|(*address2++&~*maskshifter);  maskshifter++;
				*address=  (*address&*maskshifter)|(*address2&~*maskshifter); maskshifter++;


				address+=addressDelta;
				address2+=addressDelta;
			}

			break;

		default:	for(a=0;a<image->y;a++)
				{
					unsigned int b;
	
					for(b=0;b<xlim;b++)
					{
						*address++=(*address&*maskshifter)|(*address2++&~*maskshifter);  maskshifter++;
						*address++=(*address&*maskshifter)|(*address2++&~*maskshifter);  maskshifter++;
					}
	
					address+=addressDelta;
					address2+=addressDelta;
				}
	}
}

void preShift(image *image)
{
        unsigned int pixelShifts;

	if(image->magic!=MAGIC)
	{
		printf("preshift error: invalid sprite!\n");
		exit(3);
	}

	if((image->x==0)||(image->y==0))
	{
		printf("preshift error in '%s': image->y=%d image->x=%d\n",image->name,image->x,image->y);
		exit(3);
	}

        for(pixelShifts=0;pixelShifts<4;pixelShifts++)
        {
        	unsigned int y,i,bytes=image->y*(6+((image->x-2)/2*4));

                struct shifter shifter1,shifter2,mask,tmp;

                unsigned short *pmask=(unsigned short *)image->mask,*data=(unsigned short *)image->data;
                const unsigned int shifts=2*pixelShifts;

                unsigned short *ss,*mm,*ss0,*mm0;

                ss=image->datashifter[pixelShifts]=(unsigned short *)myMalloc(bytes);
                mm=image->maskshifter[pixelShifts]=(unsigned short *)myMalloc(bytes);
		
		ss0=ss,mm0=mm;

		if(bytes==0)
		{
			printf("Image size odd: %d x %d\n",image->y,image->x);
			exit(3);
		}

                for(y=0;y<image->y;y++)
                {
			unsigned int x;

                        for(x=0;x<image->x;x+=2)
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
				
					if((x>0)&&(i==0))
					{
						ss--;
						*ss++|=tmp.z.w[0];
					}
					else *ss++=tmp.z.w[0];

					tmp.z.b[0]=mask.z.b[i];
					tmp.z.b[1]=mask.z.b[i];

					if((x>0)&&(i==0))
					{
						mm--;
						*mm++&=tmp.z.w[0];
					}
					else *mm++=tmp.z.w[0];
				}
			}
		}

		if(((unsigned int)ss-(unsigned int)ss0!=bytes)||((unsigned int)mm-(unsigned int)mm0!=bytes))
		{
			printf("loadLibrary preshift allocation error on (%dx%d):\nalloc=%d\nused s=%d\nused m=%d\n",image->x,image->y,bytes,(unsigned int)ss-(unsigned int)ss0,(unsigned int)mm-(unsigned int)mm0);

			exit(1);
		}
        }
}

void grabImage(screen screen,image *image,unsigned int x0,unsigned int y0,unsigned int w,unsigned int h)
{
	unsigned int x,y;
	unsigned short *d;
        unsigned int n=2*sizeof(unsigned short)*(x0/4)*y0;

	#ifdef MAGIC
	image->magic=MAGIC;
	#endif

	image->x=w/4; image->y=h;

	image->mask=myMalloc(n);
	image->data=myMalloc(n);

	d=image->data;

	for(x=0;x<n;x++) image->mask[x]=255;

	for(y=0;y<y0;y++)
	{
		unsigned short *a=ADDRESS(screen,x0,y0+y);

		for(x=0;x<x0;x+=4)
		{
			*d++=*a++;
		}
	}

	preShift(image);
}

void colorShift(image *image,unsigned int shift)
{
	unsigned int x,y,bit,c;
	unsigned short new,*data=(unsigned short *)image->data;

	for(y=0;y<image->y;y++)
	{
		printf("y=%d\n",y);

		for(x=0;x<image->x;x++)
		{
			printf(" x=%d\n",x);
			new=0;

			for(bit=0;bit<4;bit++)
			{
				printf("  bit=%d\n",bit);
				printf("   data=%d\n",*data);

				// Extract the colour for the given bit
				c=(((*data)>>(2*bit))&3)
				  +((((*data)>>(8+2*bit))&2)<<1);

				printf("   c1=%d\n",c);
				c=(c+shift)&7; // Shift and rotate colour
				printf("   c2=%d\n",c);

				new|=(c&3)<<(2*bit);
				if(c&4) new|=4<<(8+2*bit);

				printf("   new=%d\n",new);
			}

			*data++=new;	// Write the shifted colours back
		}
	}

	preShift(image);
}

inline unsigned int pointHit(unsigned int x,unsigned int y,unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1)
{
        return (x>=x0)&&(x<=x1)&&(y>=y0)&&(y<=y1);
}

inline unsigned hitBox(unsigned int px0,unsigned int py0,unsigned int px1,unsigned int py1,
                    unsigned int ax0,unsigned int ay0,unsigned int ax1,unsigned int ay1)
{
        if(     pointHit(px0,py0,ax0,ay0,ax1,ay1)) return 1;
        else if(pointHit(px0,py1,ax0,ay0,ax1,ay1)) return 1;
        else if(pointHit(px1,py1,ax0,ay0,ax1,ay1)) return 1;
        else if(pointHit(px1,py0,ax0,ay0,ax1,ay1)) return 1;
        else return 0;
}
