#include "system_variables.h"

// undef MAGIC to disable image checking
#define MAGIC 0xdeadbeef

// Enable second screen?
#undef SECONDSCREEN

#ifdef SECONDSCREEN
#define SCREEN2 ((char *)0x28000)
#endif

typedef void * screen;

extern screen SCREEN;
void init();
void* myMalloc(unsigned int i);

// Screens

screen createScreen();
void closeScreen(screen s);
void copyScreen(screen from,screen to,unsigned int yLow,unsigned int yHigh);
void copyAllScreen(screen from,screen to);
void showAll(screen screen);
void show(screen screen,unsigned int lowy,unsigned int highy);

//

void fill(screen screen,unsigned int xmin,unsigned int xmax,unsigned char c);
void plot(screen screen,unsigned short x,unsigned short y,unsigned char c);
unsigned int unplot(screen screen,unsigned short x,unsigned short y);
void box(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c);
void fillBox(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c);
void copyBox(screen screen,unsigned char **m,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c);
void drawBox(screen screen,unsigned char **m,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c);

void fillTriangle(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned int c);
void triangle(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned int c);
void line(screen screen, int x, int y, int x2, int y2,unsigned int c);

//

typedef struct
{
	#ifdef MAGIC
	unsigned int magic;
	#endif

	unsigned short y;
	unsigned short x;

	char *name;

	unsigned short *mask;
	unsigned short *data;

	unsigned short *datashifter[4],*maskshifter[4];
} image;

typedef struct
{
        unsigned int value,delta;
} timer;

struct sprite
{
	unsigned int moves;
	char name[32];
	unsigned int active;

	int images;
	image *image[8];

	int x,y,dx,dy,currentImage;
	unsigned int mask,draw;
	timer timer,timer2;

	struct sprite *next;
};

typedef struct sprite sprite;

typedef struct
{
	unsigned n;
	image *images;
} library;

void spriteSetup(sprite *s,char *name);
void spriteClearImages(sprite *s);
void spriteAddImage(sprite *s,library *lib,unsigned int i);
void spriteSetImage(sprite *s,unsigned int ci);

struct shifter
{
	union
	{
		unsigned char b[4];     // For writing to the screen
        	unsigned short w[2];    // For loading data
       		unsigned int l;         // For shifting
	} z;
};

void spritePlot(screen scr,sprite *sprite);
void spriteClear(screen scr,screen mask,sprite *sprite);

//void tilePlot(unsigned short x,unsigned short y,image *image);
//void imagePlot(unsigned int x,unsigned int y,image *image);

// Image library handling

void loadLibrary(library *library,char *filename,int shift);
void bLoadLibrary(library *library,char *filename,int shift);
void bSaveLibrary(library *library,char *filename);

void cls(screen screen);

unsigned short peek(screen screen,unsigned int y,unsigned int x);
unsigned short *screenAddress(screen screen,unsigned int y,unsigned int x);

// Print text

void setFontMasking(unsigned int m);
void printCharAt(screen screen,library *font,unsigned int x,unsigned int y,char c);
void printAt(screen screen,library *font,unsigned int x,unsigned y,char *s);
int loadScreen(unsigned char *scr,char *dir,char *file);

void initFrames();
unsigned int getFrames();
void framesClose();
void msleep(unsigned int delay);

