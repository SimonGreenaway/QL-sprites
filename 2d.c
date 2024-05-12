#include "image.h"

// Clear the screen to black
                
void cls(screen screen)
{
        bzero((unsigned char *)screen,32768);
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
}

const unsigned short masks[]={0x3F3F,0xCFCF,0xF3F3,0xFCFC};

const unsigned short colours[4][8]={
				{0,1<<6,2<<6,3<<6,512<<6,513<<6,514<<6,515<<6},
				{0,1<<4,2<<4,3<<4,512<<4,513<<4,514<<4,515<<4},
				{0,1<<2,2<<2,3<<2,512<<2,513<<2,514<<2,515<<2},
				{0,1,2,3,512,513,514,515}
				};

const unsigned short masks4[]={0x7F7F,0xBFBF,0xDFDF,0xEFEF,0xF7F7,0xFBFB,0xFDFD,0xFEFE};

const unsigned short colours4[8][4]={
					{0,0x80,0x8000,0x8080},
					{0,0x40,0x4000,0x4040},
					{0,0x20,0x2000,0x2020},
					{0,0x10,0x1000,0x1010},
					{0,0x8,0x800,0x808},
					{0,0x4,0x400,0x404},
					{0,0x2,0x200,0x202},
					{0,0x1,0x100,0x101}
				   };

const unsigned char shifts[]={6,4,2,0};

// Plot a point in the given colour
//
// (1) Find address of the 16bit area containing the require colour data
// (2) Mask out the bit with zeros
// (3) Set the colour via a pre-shifted 16bit value for each colour
//
// Can't see a way to speed this up. We need to read the screen, mask it with an AND,OR in the new colour and then write back to the screen.

void plot(screen screen,unsigned int x,unsigned int y,unsigned char c)
{
	unsigned short *address=ADDRESS(screen,x,y);

	*address=(*address&masks[x&3])|colours[x&3][c];
}

void plot4(screen screen,unsigned int x,unsigned int y,unsigned char c)
{
	unsigned short *address=ADDRESS4(screen,x,y);

	*address=(*address&masks4[x&7])|colours4[x&7][c];
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

const unsigned short lineColourw[]={0x0000,0x0055,0x00AA,0x00FF,0xAA00,0xAA55,0xAAAA,0xAAFF};
const unsigned long lineColourl[]={0x00000000,0x00550055,0x00AA00AA,0x00FF00FF,0xAA00AA00,0xAA55AA55,0xAAAAAAAA,0xAAFFAAFF};

// Draw a line between two points
//
// THE EXTREMELY FAST LINE ALGORITHM Variation D (Addition Fixed Point)
// 
// Additionally optimised for horizontal and vertical lines

void line(screen screen,unsigned int x,unsigned int y,unsigned int x2,unsigned int y2,unsigned int c)
{
        if((y==y2)&&(abs(x2-x)>7)) // Horizontal line?
        {
		register unsigned int i;
		unsigned long *a,col;
                unsigned int pre,end;

		if(x>x2) // Make sure x2>x
		{
			x^=x2; x2^=x; x^=x2;
	        }

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

		col=lineColourl[c];

		if(x2>x) for(i=0;i<=(x2-x)/8;i++) *a++=col;
        }
	else if(x==x2) // Vertical line?
	{
		unsigned short col=colours[x&3][c],m=masks[x&3];

		if(y2>y)
		{
			unsigned short *address=((unsigned short *)screen)+y*64+x/4;

			for(y;y<=y2;y++)
			{
			        *address=(*address&m)|col;
				address+=64;
			}
		}
		else 
		{
			unsigned short *address=((unsigned short *)screen)+y2*64+x/4;

			for(y2;y2<=y;y2++)
			{
			        *address=(*address&m)|col;
				address+=64;
			}
		}
	}
        else
        {
		register unsigned int i;
        	int yLonger=0;
	        int incrementVal, endVal;
	        int shortLen=y2-y;
	        int longLen=x2-x;
	        int decInc,j=0;

                if(abs(shortLen)>abs(longLen))
                {
                        shortLen^=longLen;
                        longLen^=shortLen;
                        shortLen^=longLen;

                        yLonger=1;
                }

                endVal=longLen;

                if (longLen<0)
                {
                        incrementVal=-1;
                        longLen=-longLen;
                } else incrementVal=1;

                if (longLen==0) decInc=0;
                else decInc = (shortLen << 16) / longLen;

                if(yLonger)
                {
                        for(i=0;i!=endVal;i+=incrementVal)
                        {
                                plot(screen,x+(j >> 16),y+i,c);
                                j+=decInc;
                        }
                }
                else
                {
                        for(i=0;i!=endVal;i+=incrementVal)
                        {
                                plot(screen,x+i,y+(j >> 16),c);
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

void fillBottomFlatTriangle(screen screen,int x1,int y1,int x2,int y2,int x3,int y3,unsigned int c)
{
        unsigned int scanlineY;

        unsigned int invslope1 = ((x2 - x1)*128) / (y2 - y1);
        int invslope2 = ((x3 - x1)*128) / (y3 - y1);

        unsigned int curx1 = x1*128;
        unsigned int curx2 = curx1;

        for(scanlineY = y1; scanlineY <= y2; scanlineY++)
        {
                line(screen,curx1/128, scanlineY,curx2/128, scanlineY,c);
                curx1 += invslope1;
                curx2 += invslope2;
        }
}

void fillTopFlatTriangle(screen screen,int x1,int y1,int x2,int y2,int x3,int y3,unsigned int c)
{
        unsigned int scanlineY;

        int invslope1 = ((x3 - x1)*128) / (y3 - y1);
        int invslope2 = ((x3 - x2)*128) / (y3 - y2);

        int curx1 = x3*128;
        int curx2 = curx1;

        for(scanlineY = y3; scanlineY > y1; scanlineY--)
        {
                line(screen,curx1/128, scanlineY,curx2/128, scanlineY,c);
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
