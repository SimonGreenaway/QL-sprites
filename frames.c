#include <sms.h>

#include "image.h"

/////////////////////
// TIME AND short //
/////////////////////

unsigned int frames=INT_MAX;
unsigned int active=1;

void interrupt()
{
        if(active) frames++;
}

QL_LINK_t t;

void framesInit()
{
	t.l_rtn=interrupt;

	sms_lpol(&t);

	frames=0;
}

void frameActive(unsigned int a)
{
	active=a;
}

void framesClose()
{
	sms_rpol(&t);
}

inline unsigned int getFrames()
{
	//if(frames==INT_MAX) framesInit();
        
	return frames;
}

void msleep(unsigned int delay)
{
        unsigned int end=getFrames()+delay;

        while(getFrames()<end); // printf("%d %d\n",getFrames(),end);
}

void mpause(unsigned int delay)
{
	unsigned int p;
        unsigned int end=getFrames()+delay;

	do
	{
		unsigned int i;

		p=0;
		for(i=0;i<8;i++) if(keyrow(i)) p++;
	}	
	while(p);

        while((delay==0)||(getFrames()<end))
	{
		unsigned int i;

		for(i=0;i<8;i++) if(keyrow(i)) return;
	}
}
