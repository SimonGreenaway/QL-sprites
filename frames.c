#include <sms.h>

#include "image.h"

/////////////////////
// TIME AND short //
/////////////////////

unsigned int frames=0;

void interrupt()
{
        frames++;
}

QL_LINK_t t;

void framesInit()
{
	t.l_rtn=interrupt;

	sms_lpol(&t);
}

void framesClose()
{
	sms_rpol(&t);
}

unsigned int getFrames()
{
        return frames;
}

void msleep(unsigned int delay)
{
        unsigned int end=getFrames()+delay;

        while(getFrames()<end); // printf("%d %d\n",getFrames(),end);
}
