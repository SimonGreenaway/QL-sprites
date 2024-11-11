#include <stdio.h>

#include "image.h"
#include "font_4x6.h"

void print4(unsigned int x,unsigned int y,unsigned char *s,unsigned int fg,unsigned int bg)
{
	unsigned int l=strlen(s);
	unsigned int cc;
	const unsigned char *p;

	for(cc=0;cc<l;cc++)
	{
		unsigned int yy,xx;
		unsigned char c=s[cc];

		p=&FONT_4x6_DATA[c*6];

		for(yy=0;yy<6;yy++)
		{
			for(xx=7;xx>3;xx--)
			{
				if(bg==-1)
				{
					if(p[yy]&(1<<xx))
						plot(SCREEN,cc*4+x+(7-xx),y+yy,fg);
				}
				else plot(SCREEN,cc*4+x+(7-xx),y+yy,(p[yy]&(1<<xx))==0?bg:fg);

				//while(scanKey()==0);
			}
		}
	}
}

int main(int argc,char **argv)
{
	char *message="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	init(8);

	while(1)
	{
		print4(fastRandInt(256-26*4),fastRandInt(256-6),message,fastRandInt(8),fastRandInt(8));
	}

	return 0;
}
