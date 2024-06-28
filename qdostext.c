#include "image.h"

chanid_t wopen(unsigned int x,unsigned int y,unsigned int width,unsigned int height)
{
        WINDOWDEF_t wdef;

        wdef.border_colour=7;
        wdef.border_width=0;
        wdef.paper=0;
        wdef.ink=7;
        wdef.width=width;
        wdef.height=height;
        wdef.x_origin=x;
        wdef.y_origin=y;

        return ut_con(&wdef);
}

int wborder(chanid_t chid,unsigned char colour,short width)
{
        return sd_bordr(chid,0x400,colour,width);
}

int wclose(chanid_t chid)
{
        return io_close(chid);
}

int wputc(chanid_t chid,char c)
{
        return io_sbyte(chid,0x400,c);
}

int wfputs(chanid_t chid,char *s)
{
        unsigned int l=strlen(s);
        return io_sstrg(chid,0x400,"Hello world! ",l);
}

void wink(chanid_t chid,unsigned int c)
{
        sd_setin(chid,0x400,c);
}

void wpaper(chanid_t chid,unsigned int c)
{
        sd_setpa(chid,0x400,c);
}

int wsize(chanid_t chid,short width,short height)
{
        switch(width)
        {
                case 6: width=0; break;
                case 8: width=1; break;
                case 12: width=2; break;
                case 16: width=3; break;
                default: return -999;
        }

        switch(height)
        {
                case 10: height=0; break;
                case 20: height=1; break;
                default: return -999;
        }

        return sd_setsz(chid,0x400,width,height);
}

int wat(chanid_t chid,short x,short y)
{
        return sd_pixp(chid,0x400,x,y);
}

int wcls(chanid_t chid)
{
        return sd_clear(chid,0x400);
}

int wcursor(chanid_t chid,int on)
{
        return on?sd_cure(chid,0x400):sd_curs(chid,0x400);
}

