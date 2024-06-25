#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
			if(s->timer.value<=frames2)
			{
				if(s->movement!=NULL)
				{
					s->movement(s);
				}
				else if(s->dx||s->dy)
				{
					s->draw=0;
					spritePlot(SCREEN,s);
					s->x+=s->dx;
					s->y+=s->dy;
					s->draw=1;

					if((s->x+s->image[s->currentImage]->x>=255)
					 ||(s->x<0)||(s->y<0)
					 ||(s->y+s->image[s->currentImage]->y>=255))
					{
						s->active=0;
					}
				}

				s->timer.value=frames2+s->timer.delta;
	
				if(s->active) spritePlot(SCREEN,s);
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

void m(struct sprite *s)
{
	if(s->x==0) s->dx=1;
	else if(s->x>=255-s->image[s->currentImage]->x*4) s->dx=-1;

	if(s->y==0) s->dy=1;
	else if(s->y>=255-s->image[s->currentImage]->y) s->dy=-1;

	s->draw=0;
	spritePlot(SCREEN,s);
	s->x+=s->dx;
	s->y+=s->dy;
	s->draw=1;
}

#define S 32
sprite s[S];

int sine(int a)
{
	return (64*(4*a*(180-a)))/(40500-a*(180-a));
}

int main(int argc,char *argv[])
{

	library lib;
	unsigned int i;

	init(8);

	loadLibrary(&lib,"test_lib",1,1);

	for(i=0;i<S;i++)
	{
		spriteSetup(&s[i],"test");

		spriteAddImageFromLibrary(&s[i],&lib,0);

		s[i].active=1;
		s[i].mask=1;
		s[i].draw=1;
		s[i].currentImage=0;
		s[i].timer.value=0;
		s[i].timer.delta=1;

		s[i].x=i*8;
		s[i].y=sine(i*(180/S))+128;

		s[i].dx=0;
		s[i].dy=1;
		s[i].movement=m;
	
		addSprite(&s[i]);
	}

	runner();
	
	while(1)
	{
		sleep(1000);
	}
}
