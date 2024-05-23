#include <qdos.h>

#include "image.h"

unsigned char keyMatrix[2][8][8]={
		{
			{4,1,'5',2,3,5,'4','7'},
			{'\n',192,208,27,200,'\\',' ',216},
			{']','z','.','c','b',0,'m','\''},
			{'[',0,'k','s','f','=','g',';'},
			{'l','3','h','1','a','p','d','j'},
			{'9','w','i',0,'r','-','y','o'},
			{'8','2','6','q','e','0','t','u'},
			{0,0,0,'x','v','/','n',','}
		},
		{
			{4,1,'%',2,3,5,'$','&'},
			{'\n',192,208,27,200,'|',' ',216},
			{'}','Z','>','C','B','£','M','@'},
			{'}',0,'K','S','F','+','G',':'},
			{'L','£','H','!','A','P','D','J'},
			{'(','W','I',0,'R','_','Y','O'},
			{'*','"','^','Q','E',')','T','U'},
			{0,0,0,'X','V','?','N','<'}
		}
	};

unsigned char scanKey()
{
	unsigned char k=scanRawKey();

	if(k)
	{
		while(scanRawKey()==k);
	}

	return k;
}

unsigned char scanRawKey()
{
	unsigned int i;
	int k=keyrow(7);
	unsigned int shift=k&1;
	unsigned int control=k&2;

	for(i=0;i<10;i++)
	{
		int key=keyrow(i);
		char k2;

		if(i==7) key&=0xFF; // Zap the shift and control key

		if(key)
		{
			for(k=7;k>=0;k--) if(key&(1<<k)) break;

			if(control&&(i==1)&&(k==1)) return 8;

			k2=keyMatrix[shift][i][k];

			if(k2!=0) return k2;
			//else printf("%d %d\n",i,k);
		}
	}

	return 0;
}
