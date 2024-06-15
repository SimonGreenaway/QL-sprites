#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
//#include <qdos.h>

#include "image.h"

/*
Point rotate(Point p, double a) {
    return new Point(p.x * Math.cos(a) - p.y * Math.sin(a), p.x * Math.sin(a) + p.y * Math.cos(a));
}

static Point rotate(Point p, Point c, double a) {
    return new Point(c.x + (p.x - c.x) * Math.cos(a) - (p.y - c.y) * Math.sin(a),
                   c.y + (p.x - c.x) * Math.sin(a) + (p.y - c.y) * Math.cos(a));
}
*/

void buildSprites()
{
	const int size=8;
	const int images=8;

	unsigned int i,j;
	int cx=128,cy=128;

	double p[6]={sin(0)     *size+128,128-cos(0)     *size,
		    sin(2*PI/3)  *size+128,128-cos(2*PI/3)*size,
		    sin(4*PI/3)*size+128,128-cos(4*PI/3)*size};
	double p2[6];

	sprite s;
	image image[images];

	spriteSetup(&s,"Blah");

	for(j=0;j<images;j++)
	{
		float a=j*2*PI/images;

		for(i=0;i<5;i+=2)
		{
			p2[i]  =cx+(p[i]-cx)*cos(a)-(p[i+1]-cy)*sin(a);
			p2[i+1]=cy+(p[i]-cx)*sin(a)+(p[i+1]-cy)*cos(a);
		}

		cls(SCREEN);
		fillTriangle(SCREEN,(unsigned int)p2[0],(unsigned int)p2[1],(unsigned int)p2[2],(unsigned int)p2[3],(unsigned int)p2[4],(unsigned int)p2[5],1);

		grabImage(SCREEN,&image[j],128-8,128-8,16,16);
		spriteAddImage(&s,&image[j]);
	}

	s.x=128;
	s.y=128;
	s.draw=1;
	s.mask=0;

	while(1)
	{
		unsigned int f=getFrames();

		for(i=0;i<images;i++)
		{
			s.currentImage=i;
			spritePlot(SCREEN,&s);

			while(f==getFrames());
			f=getFrames();
		}
	}
}

//////////
// main //
//////////

char *drive="MDV1_";

int main(int argc, char *argv[],char *argp[])
{
	if(getenv("DRIVE")!=NULL) strcpy(drive,getenv("DRIVE"));

	printf("Default drive is '%s'\n",drive);

	// Parse the args

	setSysBase((unsigned char *)0x28000);
	init(8);

	buildSprites();

	return 0;
}
