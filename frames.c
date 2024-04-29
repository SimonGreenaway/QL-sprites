#include <sms.h>

#include "image.h"


/////////////////////
// TIME AND short //
/////////////////////

unsigned int frameCounter=0,lastFrame,tickRate;

unsigned int getFrames()
{
        unsigned short frames=*SV_RAND;

        if(frames<lastFrame) frameCounter+=0x10000;
        lastFrame=frames;

        return  frameCounter+frames;
}

void msleep(unsigned int frames)
{
        unsigned int end=getFrames()+frames;

        while(getFrames()<end);
}
