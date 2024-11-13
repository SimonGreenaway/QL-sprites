#include <qdos.h>

#include "system_variables.h"

// undef MAGIC to disable image checking
#define MAGIC 0xdeadbeef

// Enable second screen?
#undef SECONDSCREEN

#ifdef SECONDSCREEN
#define SCREEN2 ((char *)0x28000)
#endif

#define ADDRESS(screen,x,y) (((unsigned short *)screen)+y*64+x/4)
#define ADDRESS4(screen,x,y) (((unsigned short *)screen)+y*64+x/8)
#define SWAP(a,b) { (a)^=(b); (b)^=(a); (a)^=(b);  }

typedef void * screen;

extern screen SCREEN;
void init(unsigned int colours);
void* myMalloc(unsigned int i);
void *makeHigh(void *p,unsigned int size);

#define BLACK 0
#define BLUE 1
#define RED  2
#define MAGENTA 3
#define GREEN 4
#define CYAN 5
#define YELLOW 6
#define WHITE 7

// Keyboard

unsigned char scanKey();
unsigned char scanRawKey();

// Screens

screen createScreen();
void closeScreen(screen s);
void copyScreen(screen from,screen to,unsigned int yLow,unsigned int yHigh);
void copyAllScreen(screen from,screen to);
void showAll(screen screen);
void show(screen screen,unsigned int lowy,unsigned int highy);

//

extern const unsigned short colours[4][9];

#define PLOT(screen,x,y,c) { unsigned short *address=ADDRESS((screen),(x),(y)); *address=(*address&masks[(x)&3])|colours[(x)&3][c]; }


void fill(screen screen,unsigned int xmin,unsigned int xmax,unsigned char c);
void plot(screen screen,unsigned short x,unsigned short y,unsigned char c);
void ploti(screen screen,unsigned int x,unsigned int y,unsigned char c);
void plot4(screen screen,unsigned int x,unsigned int y,unsigned char c);
unsigned int unplot(screen screen,unsigned short x,unsigned short y);
void box(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c);
void fillBox(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c);
void copyBox(screen screen,unsigned char **m,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c);
void drawBox(screen screen,unsigned char **m,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c);

void fillTriangle(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned int c);
void triangle(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned int c);
void line(screen screen,unsigned int x,unsigned int y,unsigned int x2,unsigned int y2,unsigned int c);
void hline(screen screen,int x,int x2,unsigned int y,unsigned int c);
void vline(screen screen,unsigned int x,unsigned int y,unsigned int y2,unsigned int c);

void circle(screen screen,unsigned int x,unsigned int y,int radius,unsigned int colour);
void fillCircle(screen screen,unsigned int ox,unsigned int oy,int r,unsigned int colour);
void floodFill(screen screen,unsigned short x,unsigned short y,unsigned short c);

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
	unsigned short *datamaskshifter[4];
} image;

typedef struct
{
        unsigned int value,delta;
} timer;

#define MAXIMAGES 24

struct sprite
{
	char name[32];
	unsigned int active;

	unsigned int images;
	image *image[MAXIMAGES];

	int x,y,dx,dy,currentImage;
	unsigned int mask,draw;
	timer timer,timer2;

	struct sprite *next;

	void(*movement)(struct sprite *s);
	void(*boundsCheck)(struct sprite *s);
};

typedef struct sprite sprite;

typedef struct
{
	unsigned n;
	image *images;
} library;

void spriteSetup(sprite *s,char *name);
void spriteSetupFull(sprite *s,char *name,unsigned int active,unsigned int mask,unsigned int draw);
void spriteClearImages(sprite *s);
void spriteAddImageFromLibrary(sprite *s,library *lib,unsigned int i);
void spriteAddImage(sprite *s,image *i);
void spriteSetImage(sprite *s,unsigned int ci);

void grabImage(screen scr,image *image,unsigned int x,unsigned int y,unsigned int w,unsigned int h);

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

// Image library handling

void preShift(image *image);
int superLoad(library *lib,char *bfilename,char *filename,unsigned int verbose);
int loadLibrary(library *library,char *filename,int shift,int verbose);
int bLoadLibrary(library *library,char *filename,int shift);
void bSaveLibrary(library *library,char *filename);

void cls(screen screen);	// Clear screen to black
void clsColour(screen screen,unsigned int colour); // Clear to screen to colour

unsigned short peek(screen screen,unsigned int y,unsigned int x);
unsigned short *screenAddress(screen screen,unsigned int y,unsigned int x);

// Print text

void setFontMasking(unsigned int m);
void printCharAt(screen screen,library *font,unsigned int x,unsigned int y,char c);
void printAt(screen screen,library *font,unsigned int width,unsigned int x,unsigned y,char *s);
void print4(unsigned int x,unsigned int y,unsigned char *s,unsigned int fg,unsigned int bg);

void printCharAtBlock(screen screen,library *font,unsigned int x,unsigned y,char c);
void printStringAtBlock(screen screen,library *font,unsigned int width,unsigned int x,unsigned y,char *s);
int loadScreen(unsigned char *scr,char *dir,char *file);

// QDOS text

chanid_t wopen(unsigned int x,unsigned int y,unsigned int width,unsigned int height);
int wclose(chanid_t chid);
int wat(chanid_t chid,short x,short y);
int wcls(chanid_t chid);
int wcursor(chanid_t chid,int on);
int wborder(chanid_t chid,unsigned char colour,short width);
int wclose(chanid_t chid);
int wputc(chanid_t chid,char c);
int wfputs(chanid_t chid,char *s);
void wink(chanid_t chid,unsigned int c);
void wpaper(chanid_t chid,unsigned int c);
int wsize(chanid_t chid,short width,short height);

// Time

void framesInit();
unsigned int getFrames();
void framesClose();
void frameActive(unsigned int a);
void msleep(unsigned int delay);
void mpause(unsigned int delay);

void multiDraw(screen screen,unsigned char *data);

//extern const unsigned short colours[4][8];
//extern const unsigned short masks[];

//#define PLOT(screen,x,y,c) { unsigned short *address=ADDRESS((screen),(x),(y)); *address=(*address&masks[(x)&3])|colours[(x)&3][(c)]; }

void fastSrand(int seed);
inline unsigned int fastRand(void);
inline unsigned int fastRandInt(int i);

inline unsigned int pointHit(unsigned int x,unsigned int y,unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1);
inline unsigned hitBox(unsigned int px0,unsigned int py0,unsigned int px1,unsigned int py1,
                    unsigned int ax0,unsigned int ay0,unsigned int ax1,unsigned int ay1);
