#include "image.h"

// Clear the screen to black
                
void cls(screen screen)
{
        memset((unsigned char *)screen,0,32768);
}

// Return the 16 bit pixel data for the 4 pixels containing this pixel

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
const unsigned char shifts[]={6,4,2,0};

// Plot a point in the given colour
//
// (1) Find address of the 16bit area containing the require color data
// (2) Mask out the bit with zeros
// (3) Set the colour via a pre-shifted 16bit value for each colour
//
// Can't see a way to speed this up. We need to read the screen, mask it with an AND,OR in the new colour and then write back to the screen.

void plot(screen screen,unsigned int x,unsigned int y,unsigned char c)
{
        register unsigned short *address=ADDRESS(screen,x,y);

       	*address=(*address&masks[x&3])|colours[x&3][c];
}

// Return colour at the given screen location

unsigned int unplot(screen screen,unsigned short x,unsigned short y)
{
        unsigned short *address=ADDRESS(screen,x,y);

        switch((*address&~masks[x&3])>>shifts[x&3])
        {
                case 0: return 0;
                case 1: return 1;
                case 2: return 2;
                case 3: return 3;
                case 512: return 4;
                case 513: return 5;
                case 514: return 6;
                case 515: return 7;
                default: return 8;
        }
}

// Draw a box

void box(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c)
{
        unsigned int i;

	line(SCREEN,x1,y1,x2,y1,c);
	line(SCREEN,x2,y1,x2,y2,c);
	line(SCREEN,x2,y2,x1,y2,c);
	line(SCREEN,x1,y2,x1,y1,c);
}

void fillBox(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c)
{
        unsigned int i;

        for(i=y1;i<=y2;i++)
                line(screen,x1,i,x2,i,c);
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

const unsigned short lineColors[]={0x0000,0x0055,0x00AA,0x00FF,0xAA00,0xAA55,0xAAAA,0xAAFF};
const unsigned long lineColors2[]={0x00000000,0x00550055,0x00AA00AA,0x00FF00FF,0xAA00AA00,0xAA55AA55,0xAAAAAAAA,0xAAFFAAFF};

// Draw a line between two points
//
// THE EXTREMELY FAST LINE ALGORITHM Variation D (Addition Fixed Point)

void line(screen screen,unsigned int x,unsigned int y,unsigned int x2,unsigned int y2,unsigned int c)
{
        register unsigned int i;
        int yLonger=0;
        int incrementVal, endVal;
        int shortLen=y2-y;
        int longLen=x2-x;
        int decInc,j=0;

        if((y==y2)&&(abs(x2-x)>7)) // Horizontal line?
        {
                unsigned short *a,col;
		unsigned long *al,coll;
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

                a=ADDRESS(screen,x2,y);

                if((((unsigned long)a)&2)==0)
                {
                        *a=lineColors[c];
                        x2-=4;
                }

                a=ADDRESS(screen,x,y);
		if(((unsigned long)a)&2)
		{
			*a++=lineColors[c]; //printf("S-"); sleep(2);
			x+=4;
		}
		al=(unsigned long *)ADDRESS(screen,x,y);

		coll=lineColors2[c];

		if(x2>x)
		{
			end=(x2-x)/8;
       	        	for(i=0;i<=end;i++) *al++=coll;
		}
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
                if(abs(shortLen)>abs(longLen))
                {
                        int swap=shortLen;
                        shortLen=longLen;
                        longLen=swap;
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
        float x,y;
};

void fillBottomFlatTriangle(screen screen,struct vertice v1,struct  vertice v2, struct vertice v3,unsigned int c)
{
        int scanlineY;

        float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
        float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);

        float curx1 = v1.x;
        float curx2 = v1.x;

        for(scanlineY = v1.y; scanlineY <= v2.y; scanlineY++)
        {
                line(screen,(int)curx1, scanlineY, (int)curx2, scanlineY,c);
                curx1 += invslope1;
                curx2 += invslope2;
        }
}

void fillTopFlatTriangle(screen screen,struct vertice v1,struct vertice v2,struct vertice v3,unsigned int c)
{
        int scanlineY;

        float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
        float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

        float curx1 = v3.x;
        float curx2 = v3.x;

        for(scanlineY = v3.y; scanlineY > v1.y; scanlineY--)
        {
                line(screen,(int)curx1, scanlineY, (int)curx2, scanlineY,c);
                curx1 -= invslope1;
                curx2 -= invslope2;
        }
}
void fillTriangle(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned int c)
{
        struct vertice vt1,vt2,vt3,vTmp;

        vt1.x=x1; vt1.y=y1;
        vt2.x=x2; vt2.y=y2;
        vt3.x=x3; vt3.y=y3;

        /* at first sort the three vertices by y-coordinate ascending so v1 is the topmost vertice */


        if (vt1.y > vt2.y)
        {
            vTmp = vt1;
            vt1 = vt2;
            vt2 = vTmp;
        }
        /* here v1.y <= v2.y */
        if (vt1.y > vt3.y)
        {
            vTmp = vt1;
            vt1 = vt3;
            vt3 = vTmp;
        }
        /* here v1.y <= v2.y and v1.y <= v3.y so test v2 vs. v3 */
        if (vt2.y > vt3.y)
        {
            vTmp = vt2;
            vt2 = vt3;
            vt3 = vTmp;
        }
       /* here we know that v1.y <= v2.y <= v3.y */
        /* check for trivial case of bottom-flat triangle */

        if (vt2.y == vt3.y)
        {
                fillBottomFlatTriangle(screen,vt1, vt2, vt3,c);
        }
          /* check for trivial case of top-flat triangle */
        else if (vt1.y == vt2.y)
        {
                fillTopFlatTriangle(screen, vt1, vt2, vt3,c);
        }
        else
        {
                /* general case - split the triangle in a topflat and bottom-flat one */
                struct vertice v4;

                v4.x= (int)(vt1.x + ((float)(vt2.y - vt1.y) / (float)(vt3.y - vt1.y)) * (vt3.x - vt1.x));
                v4.y= vt2.y;
                fillBottomFlatTriangle(screen, vt1, vt2, v4,c);
                fillTopFlatTriangle(screen, vt2, v4, vt3,c);
        }
}

void triangle(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned int c)
{
        line(screen,x1,y1,x2,y2,c);
        line(screen,x2,y2,x3,y3,c);
        line(screen,x1,y1,x3,y3,c);
}

