#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <qdos.h>

#include "image.h"

const unsigned short lineColourw[]={0x0000,0x0055,0x00AA,0x00FF,0xAA00,0xAA55,0xAAAA,0xAAFF};
const unsigned long lineColourl[]={0x00000000,0x00550055,0x00AA00AA,0x00FF00FF,0xAA00AA00,0xAA55AA55,0xAAAAAAAA,0xAAFFAAFF};

// Clear the screen to black
                
void cls(screen screen)
{
        bzero((unsigned char *)screen,32768);
}

// Clear screen to a colour

void clsColour(screen screen,unsigned int colour)
{
	unsigned int short *s;

	if(colour==0) cls(screen);
	else for(s=screen;s<(unsigned short *)(screen+16384);s++)
			*s++=lineColourw[colour];
}

void fill(screen screen,unsigned int rowStart,unsigned int rowEnd,unsigned char c)
{
        memset((char *)screen+(rowStart<<7),c,(rowEnd-rowStart)<<7);
}

// Return the 16 bit pixel data for the 4 bits containing this pixel

unsigned short peek(screen screen,unsigned int y,unsigned int x)
{
        unsigned short *address=(unsigned short *)screen;
        unsigned short data;
        address+=y*64+(x>>2);

        data=*address;

        switch(x&3)
        {
                case 3: return data&0x0203;
                case 2: return data&0x080C;
                case 1: return data&0x2030;
                case 0: return data&0x80C0;
        }

	return 0; // IMPOSSIBLE!
}

const unsigned short masks[]={0x3F3F,0xCFCF,0xF3F3,0xFCFC};

const unsigned short colours[4][9]=
		{
			{0,1<<6,2<<6,3<<6,512<<6,513<<6,514<<6,515<<6,0x3F3F},
			{0,1<<4,2<<4,3<<4,512<<4,513<<4,514<<4,515<<4,0xCFCF},
			{0,1<<2,2<<2,3<<2,512<<2,513<<2,514<<2,515<<2,0xF3F3},
			{0,1,   2,   3,   512,   513,   514,   515,0xFCFC}
		};

const unsigned char shifts[]={6,4,2,0};

// Plot a point in the given colour
//
// (1) Find address of the 16bit area containing the require colour data
// (2) Mask out the bit with zeros
// (3) Set the colour via a pre-shifted 16bit value for each colour
//
// Can't see a way to speed this up. We need to read the screen, mask it with an AND,OR in the new colour and then write back to the screen.

inline void plot(screen screen,unsigned int x,unsigned int y,unsigned char c)
{
        register unsigned short *address=ADDRESS(screen,x,y);

        *address=(*address&masks[x&3])|colours[x&3][c];
}

void plot4(screen screen,unsigned int x,unsigned int y,unsigned char c)
{
	const unsigned short masks[]={0x7F7F,0xBFBF,0xDFDF,0xEFEF,0xF7F7,0xFBFB,0xFDFD,0xFEFE};
	const unsigned short colours[8][4]={
                                        {0,0x80,0x8000,0x8080},
                                        {0,0x40,0x4000,0x4040},
                                        {0,0x20,0x2000,0x2020},
                                        {0,0x10,0x1000,0x1010},
                                        {0,0x8,0x800,0x808},
                                        {0,0x4,0x400,0x404},
                                        {0,0x2,0x200,0x202},
                                        {0,0x1,0x100,0x101}
        	                           };


	unsigned short *address=ADDRESS4(screen,x,y);

	*address=(*address&masks[x&7])|colours[x&7][c];
}

// Return colour at the given screen location

unsigned int unplot(screen screen,unsigned short x,unsigned short y)
{
	unsigned short d=(*ADDRESS(screen,x,y)&~masks[x&3])>>shifts[x&3];

	return (d&3)+(d>256?4:0);
}

// Draw a box

void box(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c)
{
	line(SCREEN,x1,y1,x2,y1,c);
	line(SCREEN,x2,y1,x2,y2,c);
	line(SCREEN,x2,y2,x1,y2,c);
	line(SCREEN,x1,y2,x1,y1,c);
}

// Fill a box with colour. Could be optimised by writing all the y pixels at once....

void fillBox(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c)
{
        for(;y1<=y2;y1++) line(screen,x1,y1,x2,y1,c);
}

void copyBox(screen screen,unsigned char **m,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c)
{
        unsigned int x,y;

        for(x=x1;x<=x2;x++)
                for(y=y1;y<=y2;y++)
                        m[x][y]=unplot(screen,x,y);
}

void drawBox(screen screen,unsigned char **m,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c)
{
        unsigned int x,y;

        for(x=0;x<=x2;x++)
                for(y=0;y<=y2;y++)
                        plot(screen,x+x1,y+y1,m[x][y]);
}

void hline(screen screen,unsigned int x,unsigned int x2,unsigned int y,unsigned int c)
{
	unsigned long *a;

	// Make sure x2>x
	if(x>x2) SWAP(x,x2);

	switch(x&3) // 0-3 bits before word break
	{
		case 1: plot(screen,x++,y,c);
		case 2: plot(screen,x++,y,c);
		case 3: plot(screen,x++,y,c);
	}

	switch(x2&3) // 0-3 bits after work break
	{
		case 2: plot(screen,x2--,y,c);
		case 1: plot(screen,x2--,y,c);
		case 0: plot(screen,x2--,y,c);
	}

	// Write one short at the end if we are not on a 32bit boundary

	if(x2&1)
	{
		*ADDRESS(screen,x2,y)=lineColourw[c];
		x2-=4;
	}

	a=(unsigned long *)ADDRESS(screen,x,y);

	// Write one short at the start if we are not on a 32bit boundary
	if(x&1)
	{
		*((unsigned short *)a)=lineColourw[c];
		x+=4;

		a=(unsigned long *)(2+(unsigned int)a);
	}	

	if(x2>x)
	{
		unsigned int i;

		for(i=(x2-x)/8+1;i;i--) *a++=lineColourl[c];
	}
}

void vline(screen screen,unsigned int x,unsigned int y,unsigned int y2,unsigned int c)
{
	unsigned short col=colours[x&3][c],m=masks[x&3];

	if(y2>y)
	{
		unsigned short *address=((unsigned short *)screen)+y*64+x/4;

		for(y2-=y;y2;y2--)
		{
		        *address=(*address&m)|col;
			address+=64;
		}
	}
	else 
	{
		unsigned short *address=((unsigned short *)screen)+y2*64+x/4;

		for(y-=y2;y;y--)
		{
		        *address=(*address&m)|col;
			address+=64;
		}
	}
}

// Draw a line between two points
//
// THE EXTREMELY FAST LINE ALGORITHM Variation D (Addition Fixed Point)
// 
// Additionally optimised for horizontal and vertical lines

void line(screen screen,unsigned int x,unsigned int y,unsigned int x2,unsigned int y2,unsigned int c)
{
        if((y==y2)&&(abs(x2-x)>7)) // Horizontal line?
        {
		hline(screen,x,x2,y,c);
        }
	else if(x==x2) // Vertical line?
	{
		vline(screen,x,y,y2,c);
	}
        else
        {
        	int yLonger=0;
	        int incrementVal=1,endVal;
	        int shortLen=y2-y;
	        int longLen=x2-x;
	        int decInc,j=0;

                if(abs(shortLen)>abs(longLen))
                {
			SWAP(shortLen,longLen);
                        yLonger=1;
                }

                endVal=longLen;

                if(longLen<0)
                {
                        incrementVal=-1;
                        longLen=-longLen;
                }

		decInc=(longLen==0)?0:((shortLen<<16)/longLen);

                if(yLonger)
                {
	                register unsigned int i;

                        for(i=0;i!=endVal;i+=incrementVal)
                        {
                                plot(screen,x+(j>>16),y+i,c);
                                j+=decInc;
                        }
                }
                else
                {
	                register unsigned int i;

                        for(i=0;i!=endVal;i+=incrementVal)
                        {
                                plot(screen,x+i,y+(j>>16),c);
                                j+=decInc;
                        }
                }

		plot(screen,x2,y2,c);
        }
}

// Triangles
//

struct vertice
{
        int x,y;
};

#define TRI 256

void fillBottomFlatTriangle(screen screen,int x1,int y1,int x2,int y2,int x3,int y3,unsigned int c)
{
	if(y2==y1) return;
	
	if(1)
	{
	        unsigned int invslope1 = ((x2 - x1)*TRI) / (y2 - y1);
	        int invslope2 = ((x3 - x1)*TRI) / (y3 - y1);
	
	        unsigned int curx1 = x1*TRI;
	        unsigned int curx2 = curx1;
	
	        for(;y1<=y2;y1++)
	        {
	                line(screen,curx1/TRI, y1,curx2/TRI, y1,c);
	                curx1 += invslope1;
	                curx2 += invslope2;
	        }
	}
}

void fillTopFlatTriangle(screen screen,int x1,int y1,int x2,int y2,int x3,int y3,unsigned int c)
{
        int invslope1 = ((x3 - x1)*TRI) / (y3 - y1);
        int invslope2 = ((x3 - x2)*TRI) / (y3 - y2);

        int curx1 = x3*TRI;
        int curx2 = curx1;

        for(;y3>y1;y3--)
        {
                line(screen,curx1/TRI, y3,curx2/TRI, y3,c);
                curx1 -= invslope1;
                curx2 -= invslope2;
        }
}

void fillTriangle(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned int c)
{
        struct vertice vt1,vt2,vt3;

        vt1.x=x1; vt1.y=y1;
        vt2.x=x2; vt2.y=y2;
        vt3.x=x3; vt3.y=y3;

        /* at first sort the three vertices by y-coordinate ascending so v1 is the topmost vertice */


        if (vt1.y > vt2.y) 
        {
		SWAP(vt1.x,vt2.x); SWAP(vt1.y,vt2.y);
        }

        if (vt1.y > vt3.y) /* here v1.y <= v2.y */
        {
		SWAP(vt1.x,vt3.x); SWAP(vt1.y,vt3.y);
        }

        if (vt2.y > vt3.y) /* here v1.y <= v2.y and v1.y <= v3.y so test v2 vs. v3 */
        {
		SWAP(vt2.x,vt3.x); SWAP(vt2.y,vt3.y);
        }

	/* here we know that v1.y <= v2.y <= v3.y */
	/* check for trivial case of bottom-flat triangle */

        if (vt2.y == vt3.y)
        {
                fillBottomFlatTriangle(screen,vt1.x,vt1.y,vt2.x,vt2.y,vt3.x,vt3.y,c);
        }
        else if (vt1.y == vt2.y) /* check for trivial case of top-flat triangle */
        {
                fillTopFlatTriangle(screen,vt1.x,vt1.y, vt2.x,vt2.y, vt3.x,vt3.y,c);
        }
        else /* general case - split the triangle in a topflat and bottom-flat one */
        {
                int x4= (int)(vt1.x + ((float)(vt2.y - vt1.y) / (float)(vt3.y - vt1.y)) * (vt3.x - vt1.x));

                fillBottomFlatTriangle(screen,vt1.x,vt1.y,vt2.x,vt2.y,x4,vt2.y,c);
                fillTopFlatTriangle(screen, vt2.x,vt2.y, x4,vt2.y, vt3.x,vt3.y,c);
        }
}

void triangle(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned int c)
{
        line(screen,x1,y1,x2,y2,c);
        line(screen,x2,y2,x3,y3,c);
        line(screen,x1,y1,x3,y3,c);
}

// Square root of integer
unsigned int isqrt(unsigned int s)
{
	// Zero yields zero
	// One yields one
	if (s <= 1) return s;
	else
	{
    		// Initial estimate (must be too high)
		unsigned int x0 = s / 2;

		// Update
		unsigned int x1 = (x0 + s / x0) / 2;

		while (x1 < x0)	// Bound check
		{
			x0 = x1;
			x1 = (x0 + s / x0) / 2;
		}		
		return x0;
	}
}

void drawCircle(screen screen,int xc,int yc,int x,int y,unsigned int colour)
{
	plot(screen,xc+x, yc+y,colour);
	plot(screen,xc-x, yc+y,colour);
	plot(screen,xc+x, yc-y,colour);
	plot(screen,xc-x, yc-y,colour);
	plot(screen,xc+y, yc+x,colour);
	plot(screen,xc-y, yc+x,colour);
	plot(screen,xc+y, yc-x,colour);
	plot(screen,xc-y, yc-x,colour);
}

void circle(screen screen,unsigned int xc,unsigned int yc,int r,unsigned int colour)
{
	int x=0,y=r;
	int d=3-2*r;

	drawCircle(screen,xc, yc, x, y,colour);

	while(y>=x++)
	{
		// for each pixel we will draw all eight pixels
		// check for decision parameter and correspondingly update d, x, y

		if(d>0) d+=4*(x-(--y))+10;
		else d+=4*x+6;

		drawCircle(screen,xc, yc, x, y,colour);
	}
}

void fillCircle(screen screen,unsigned int ox,unsigned int oy,int r,unsigned int colour)
{
        int y,height;

        for(y=-r;y<r;y++)
        {       
                height=isqrt(r*r-y*y);

		line(screen,ox-height,y+oy,ox+height,y+oy,colour);
        }
}

#define FLOODBUFFERSIZE 4096

void floodFill(screen screen,unsigned int x,unsigned int y,unsigned int c)
{
	if(unplot(screen,x,y)!=c)
	{
		// Set up the ring buffer
		unsigned char *todo=myMalloc(sizeof(unsigned char)*FLOODBUFFERSIZE);
		unsigned int bottom=0,top=0;

		// First point
		plot(screen,x,y,c);
		todo[top++]=x; todo[top++]=y;

		while(top!=bottom)
		{
			x=todo[bottom++];
			y=todo[bottom++];

			bottom&=FLOODBUFFERSIZE-1;

			if((y>0)&&(unplot(screen,x,y-1)!=c))
			{
				plot(screen,x,y-1,c);
				todo[top++]=x; todo[top++]=y-1;
	
				top&=FLOODBUFFERSIZE-1;
			}
	
			if((y<254)&&(unplot(screen,x,y+1)!=c))
			{
				plot(screen,x,y+1,c);
				todo[top++]=x; todo[top++]=y+1;
	
				top&=FLOODBUFFERSIZE-1;
			}
	
			if((x>0)&&(unplot(screen,x-1,y)!=c))
			{
				plot(screen,x-1,y,c); 
				todo[top++]=x-1; todo[top++]=y;
	
				top&=FLOODBUFFERSIZE-1;
			}
	
			if((x<254)&&(unplot(screen,x+1,y)!=c))
			{
				plot(screen,x+1,y,c);
				todo[top++]=x+1; todo[top++]=y;
	
				top&=FLOODBUFFERSIZE-1;
			}

		}

		free(todo); // Release the ring buffer
	}
}

#define MDRAW_STOP           0
#define MDRAW_PLOT           1 // xpos, xpos, col
#define MDRAW_LINE           2 // x1, y1, x2, y2, col
#define MDRAW_BOX            3 // x1, y1, x2, y2, col
#define MDRAW_FILLEDBOX      4 // x1, y1, x2, y2, col
#define MDRAW_TRIANGLE	     5 // x1, y1, x2, y2, x3, y3, col
#define MDRAW_FILLEDTRIANGLE 6 // x1, y1, x2, y2, x3, y3, col
#define MDRAW_CIRCLE	     7 // x, y, r, col
#define MDRAW_FILLEDCIRCLE   8 // x, y, r, col

void multiDraw(screen screen,unsigned char *data)
{
	while(1)
	{
		switch(*data++)
		{
			case MDRAW_STOP: return;
			case MDRAW_PLOT: plot(screen,*data++,*data++,*data++); break;
			case MDRAW_LINE: line(screen,*data++,*data++,*data++,*data++,*data++); break;
			case MDRAW_BOX: box(screen,*data++,*data++,*data++,*data++,*data++); break;
			case MDRAW_FILLEDBOX: fillBox(screen,*data++,*data++,*data++,*data++,*data++); break;
			case MDRAW_TRIANGLE: triangle(screen,*data++,*data++,*data++,*data++,*data++,*data++,*data++); break;
			case MDRAW_FILLEDTRIANGLE: fillTriangle(screen,*data++,*data++,*data++,*data++,*data++,*data++,*data++); break;
			case MDRAW_CIRCLE: circle(screen,*data++,*data++,*data++,*data++); break;
			case MDRAW_FILLEDCIRCLE: fillCircle(screen,*data++,*data++,*data++,*data++); break;
		}
	}
}
