#include <stdio.h>

#include "image.h"

void convert(char *from,char *to)
{
	library lib;

	loadLibrary(&lib,from,1,1);
	bSaveLibrary(&lib,to);
}

int main(int argc,char *argv[])
{
	unsigned int i;
	char *from=NULL,*to=NULL;

	for(i=1;i<argc;i++)
	{
		if(from==NULL) from=argv[i];
		else if(to==NULL) to=argv[i];
	}

	if((from==NULL)||(to==NULL))
	{
		puts("Usage: converter <from> <to>");
		exit(1);
	}

	convert(from,to);

	return 0;
}
