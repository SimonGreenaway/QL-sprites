#include "image.h"

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
        const unsigned short *bitCache=colours[x&3];
                
        *address=(*address&bitCache[8])|bitCache[c];
}

