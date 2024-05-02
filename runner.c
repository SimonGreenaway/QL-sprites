#include <stdio.h>
#include <sms.h>

#include "image.h"

unsigned int frames2=0;

sprite *list=NULL;

void interruptRunner()
{
	sprite *s=list;

        frames2++;

	while(s!=NULL)
	{
		if(s->active)
		{

			if((s->timer.value<=frames2)&&((s->dx)||(s->dy)))
			{
				s->draw=0;
				spritePlot(SCREEN,s);
				s->x+=s->dx;
				s->y+=s->dy;
				s->draw=1;

				s->timer.value=frames2+s->timer.delta;
			}
	
			if(s->active)
			{
				spritePlot(SCREEN,s);
			}
		}

		s=s->next;
	}
}

void addSprite(sprite *s)
{
	s->next=list;
	list=s;
}

void clearSprites()
{
	sprite *s=list;

	while(s!=NULL)
	{
		sprite *last=s;
		s=s->next;

		if(s->active)
		{
			unsigned int d=last->draw;
			last->draw=0;
			spritePlot(SCREEN,last);
			last->draw=d;
		}

		free(s);
	}

	list=NULL;
}

void removeSprite(sprite *s)
{
	sprite *sl=list,*last=NULL;

	while(sl!=NULL)
	{
		if(sl==s)
		{
			if(last==NULL)
			{
				list=sl->next;
				free(sl);
				return;
			}
			else
			{
				last->next=sl->next;

		                if(sl->active)
       		         	{
		                        sl->draw=1;
		                        spritePlot(SCREEN,sl);
		                }

				free(sl);
				return;
			}
		}

		last=sl;
		sl=sl->next;
	}
}

QL_LINK_t t2;

void runner()
{
	t2.l_rtn=interruptRunner;

	sms_lpol(&t2);
}

int main(int argc,char *argv[])
{
	library lib;
	sprite s;

	loadLibrary(&lib,"test_lib",1);

	spriteSetup(&s,"test");
	spriteAddImage(&s,&lib,0);

	s.active=1;
	s.mask=1;
	s.draw=1;
	s.currentImage=0;
	s.timer.value=0;
	s.timer.delta=50;

	addSprite(&s);

	runner();
	
	while(1)
	{
		sleep(1000);
	}
}
