#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <qdos.h>
#include <math.h>

#include "image.h"

// Initiate a sprite

void spriteSetup(sprite *s,char *name)
{
	bzero(s,sizeof(sprite));

	s->mask=s->draw=1;
	if(name!=NULL) strcpy(s->name,name);

	s->boundsCheck=s->movement=NULL;
	s->images=s->currentImage=0;
}

// Clear sprite's image list

void spriteClearImages(sprite *s)
{
	s->images=s->currentImage=0;
}

// Add an image to the sprite

void spriteAddImage(sprite *s,library *lib,unsigned int i)
{
	if(s->images==10)
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

	// Sanity checks - best to leave in!
	//
	#ifdef MAGIC
	if(image->magic!=MAGIC)
	{
		printf("Invalid sprite '%d' being drawn! (%x)",sprite->name,image->magic);
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
					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*address=  *address&*masks++|*shifts++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 3:	for(y=image->y;y;y--) // x24
				{
					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*address=  *address&*masks++|*shifts++; 
		
					address+=addressDelta;
				}
	
				break;
		
			case 2: for(y=image->y;y;y--) // x16
				{
					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*address=  *address&*masks++|*shifts++; 
		
					address+=addressDelta;
				}
	
				break;
	
			case 1:	if(image->y==8)
				{
					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*address=  *address&*masks++|*shifts++; 
					address+=addressDelta;

					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*address=  *address&*masks++|*shifts++; 
					address+=addressDelta;

					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*address=  *address&*masks++|*shifts++; 
					address+=addressDelta;

					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*address=  *address&*masks++|*shifts++; 
					address+=addressDelta;

					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*address=  *address&*masks++|*shifts++; 
					address+=addressDelta;

					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*address=  *address&*masks++|*shifts++; 
					address+=addressDelta;

					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*address=  *address&*masks++|*shifts++; 
					address+=addressDelta;

					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*address=  *address&*masks++|*shifts; 
				}
				else for(y=image->y;y;y--)
				{
					*L(address)++=*L(address)&*L(masks)++|*L(shifts)++; 
					*address=  *address&*masks++|*shifts++; 
		
					address+=addressDelta;
				}
	
				break;
	
			default:	for(y=image->y;y;y--)
					{
						unsigned int x;
		
						for(x=0;x<image->x>>1;x++)
						{
							*address++=*address&*masks++|*shifts++; 
							*address++=*address&*masks++|*shifts++; 
							*address=*address&*masks++|*shifts++; 
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

	unsigned short *shifter=image->datashifter[sprite->x&3];
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
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;

				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;

				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
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
				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;

				*address++=*address&*maskshifter|(*address2++&~*maskshifter); maskshifter++;
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

void preShift(image *image)
{
        unsigned int pixelShifts;

        for(pixelShifts=0;pixelShifts<4;pixelShifts++)
        {
        	unsigned int y,i,bytes=image->y*image->x/2*6;

                struct shifter shifter1,shifter2,mask,tmp;

                unsigned short *pmask=(unsigned short *)image->mask,*data=(unsigned short *)image->data;
                const unsigned int shifts=2*pixelShifts;

                unsigned short *ss=image->datashifter[pixelShifts]=(unsigned short *)myMalloc(bytes);
                unsigned short *mm=image->maskshifter[pixelShifts]=(unsigned short *)myMalloc(bytes);
		
		unsigned short *ss0=ss,*mm0=mm;

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

					if((ss-ss0>bytes)||(mm-mm0>bytes))
					{
						printf("loadLibrary allocation error: [%d:%d/%d]",bytes,ss-ss0,mm-mm0);

						exit(1);
					}
				}
			}
		}
        }
}
