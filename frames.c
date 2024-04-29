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

void checkRand()
{
        unsigned int i,j;
        unsigned long t;

        t=sms_rrtc();
        while(sms_rrtc()==t);

        i=getFrames();

        t=sms_rrtc()+3;
        while(sms_rrtc()<=t);

        j=getFrames();
        tickRate=(unsigned int)((j-i)/4.0+0.5);
        printf("Tick rate is %d hz.\n",tickRate);
        sleep(3);
}

void msleep(unsigned int frames)
{
        unsigned int end=getFrames()+frames;

        while(getFrames()<end);
}
