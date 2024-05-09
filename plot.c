#include "image.h"

const unsigned short masks[]={0x3F3F,0xCFCF,0xF3F3,0xFCFC};

const unsigned short colours[4][8]={
				{0,1<<6,2<<6,3<<6,512<<6,513<<6,514<<6,515<<6},
				{0,1<<4,2<<4,3<<4,512<<4,513<<4,514<<4,515<<4},
				{0,1<<2,2<<2,3<<2,512<<2,513<<2,514<<2,515<<2},
				{0,1,2,3,512,513,514,515}
				};

// Can't see a way to speed this up. We need to read the screen, mask it with an AND,OR in the new colour and then write back to the screen.

inline void plot(screen screen,unsigned int x,unsigned int y,unsigned char c)
{
	register unsigned short *address=ADDRESS(screen,x,y);

	*address=(*address&masks[x&3])|colours[x&3][c];
}
