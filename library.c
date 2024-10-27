#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include <qdos.h>
#include <math.h>

#include "image.h"

int superLoad(library *lib,char *bfilename,char *filename,unsigned int verbose)
{                       
        if(bLoadLibrary(lib,bfilename,1)!=1) // Try for binary load
        {               
                if(loadLibrary(lib,filename,1,verbose)==-1) return 0;
                        
                bSaveLibrary(lib,bfilename); // Save a binary version
                unlink(filename); // And delete the big version - so beware!
        }

	return 1;
}  

char *readLine(FILE *in,char *buffer)
{
        do
        {
                if(feof(in))
                {
                        puts("Error reading library!\n");
                        exit(1);
                }

                fgets(buffer,80,in);
        }
        while(buffer[0]=='#');

        return buffer;
}

int bLoadLibrary(library *library,char *filename,int shift)
{
	unsigned int i,n,b;
	char buffer[80];
	unsigned short *d,*m;
	FILE *in;

	in=fopen(filename,"rb");

	if(in==NULL)
	{
		//if(verbose) printf("Error: Cannot open '%s' to read\n",filename);
		return 0;

	}

	fread(&library->n,sizeof(unsigned int),1,in);

        library->images=(image *)(myMalloc(sizeof(image)*library->n));

	for(i=0;i<library->n;i++)
	{
		#ifdef MAGIC
		library->images[i].magic=MAGIC;
		#endif
	
        	readLine(in,buffer);
                buffer[strcspn(buffer, "\r\n")] = 0;

	printf("e %d %s\n",strlen(buffer),buffer);
                library->images[i].name=(char *)myMalloc(strlen(buffer)+1);
                strcpy(library->images[i].name,buffer);
	printf("d %d %s\n",strlen(library->images[i].name),library->images[i].name);

		fread(&library->images[i].x,sizeof(unsigned short),1,in);
		fread(&library->images[i].y,sizeof(unsigned short),1,in);

	printf("c %d %s\n",strlen(library->images[i].name),library->images[i].name);
                n=2*sizeof(unsigned short)*library->images[i].x*library->images[i].y;

                if(n==0) continue;

                d=library->images[i].data=(unsigned short *)(myMalloc(n));
                m=library->images[i].mask=(unsigned short *)(myMalloc(n));

		printf("b %d %s\n",strlen(library->images[i].name),library->images[i].name);
                for(b=0;b<library->images[i].y;b++)
                {
			fread(d,sizeof(unsigned short),library->images[i].x,in);
			fread(m,sizeof(unsigned short),library->images[i].x,in);

			d+=library->images[i].x;
			m+=library->images[i].x;
                }

		printf("a %d %s\n",strlen(library->images[i].name),library->images[i].name);

                if(shift)
                {
                        preShift(&library->images[i]);

                        free(library->images[i].data);
                        free(library->images[i].mask);
                }

	}

	return 1;
}

void bSaveLibrary(library *library,char *filename)
{
	FILE *out;
	unsigned int i,b;
        unsigned short *d,*m;

	out=fopen(filename,"wb");

	if(out==NULL)
	{
		printf("Error: Cannot open '%s' to write\n",filename);
		exit(2);
	}

	fwrite(&library->n,sizeof(unsigned int),1,out); // n

	for(i=0;i<library->n;i++)
	{
		fprintf(out,"%s\n",library->images[i].name);

                fwrite(&library->images[i].x,sizeof(unsigned int),1,out);
                fwrite(&library->images[i].y,sizeof(unsigned int),1,out);

                d=library->images[i].data;
                m=library->images[i].mask;

                for(b=0;b<library->images[i].y;b++)
                {
                        fwrite(d,sizeof(unsigned short),library->images[i].x,out);
                        fwrite(m,sizeof(unsigned short),library->images[i].x,out);

                        d+=library->images[i].x;
                        m+=library->images[i].x;
                }
	}

	fclose(out);
}

int loadLibrary(library *library,char *filename,int shift,int verbose)
{
	int i,a,b;
	unsigned short *d,*m,*d0,*m0;

	FILE *in;
	char buffer[80];

	if(verbose) puts("Loading library...");

	in=fopen(filename,"r");

	if(in==NULL)
	{
		if(verbose) printf("ERROR: Cannot read %s\n",filename);
		return -1;
	}

	readLine(in,buffer); library->n=atoi(buffer);

	if(verbose) printf(" images: %d\n",library->n);
	
	library->images=(image *)(myMalloc(sizeof(image)*library->n));

	for(i=0;i<library->n;i++)
	{
		int n;

		#ifdef MAGIC
		library->images[i].magic=MAGIC;
		#endif

		readLine(in,buffer);
		buffer[strcspn(buffer, "\r\n")] = 0;
		if(verbose)  printf("  Image %d is called '%s'\n",i,buffer);

		library->images[i].name=(char *)myMalloc(strlen(buffer)+1);
		strcpy(library->images[i].name,buffer);

		readLine(in,buffer); library->images[i].x=atoi(buffer); 
		readLine(in,buffer); library->images[i].y=atoi(buffer); 

		n=2*sizeof(unsigned short)*library->images[i].x*library->images[i].y;

		if(n==0)
		{
			if(verbose) printf("N is zero! %d x %d - skipping!\n",library->images[i].x,library->images[i].y);
			continue;
		}

		d0=d=library->images[i].data=(unsigned short *)(myMalloc(n));

		//printf("d loc %d -> %d : %d\n",library->images[i].data,n+(char *)library->images[i].data,&n);
		//
		m0=m=library->images[i].mask=(unsigned short *)(myMalloc(n));

		for(b=0;b<library->images[i].y;b++)
		{
			for(a=0;a<library->images[i].x;a++)
			{
				readLine(in,buffer); *d++=(unsigned short)atoi(buffer);
				readLine(in,buffer); *m++=(unsigned short)atoi(buffer);

				if((char *)d-(char *)d0>=n)
				{
					printf("loadLibrary: load data buffer overrun\n");
					exit(3);
				}
				else if((char *)m-(char *)m0>=n)
				{
					printf("loadLibrary: load  buffer overrun\n");
					exit(3);
				}
			}
		}

		for(a=0;a<2*library->images[i].x*library->images[i].y;a+=2)
		{
			unsigned short hi,lo;

			//printf("%d\t%d\n",a*sizeof(short),n);

			if(a*sizeof(short)>=n)
			{
				printf("loadLibrary: data conversion overrun %d>=%d\n",a*sizeof(short),n);
				exit(3);
			}

			hi=(library->images[i].data[a+1]&255)
                          |(library->images[i].data[a]<<8);

			lo=(library->images[i].data[a]&0xff00)
			  |(library->images[i].data[a+1]>>8);

			//printf("ZZ=%d %d : %d %d\n",((char *)&library->images[i].data[a+1])-((char *)library->images[i].data),n,(unsigned int)&library->images[i].data[a+1],&n);
			library->images[i].data[a]=hi;
			library->images[i].data[a+1]=lo;

			//printf("  data[%d]=%d data[%d]=%d\n",a,hi,a+1,lo);

			hi=(library->images[i].mask[a+1]&255)
                          |(library->images[i].mask[a]<<8);

			lo=(library->images[i].mask[a]&0xff00)
			  |(library->images[i].mask[a+1]>>8);

			library->images[i].mask[a]=hi;
			library->images[i].mask[a+1]=lo;
		}

                if(shift)
		{
			//printf("Preshifting '%s'...\n",library->images[i].name);

			preShift(&library->images[i]);

			//free(library->images[i].data);
			//free(library->images[i].mask);
		}
	}

	fclose(in);

	if(verbose) printf("Loaded %d sprites.\n",library->n);

	return library->n;
}
