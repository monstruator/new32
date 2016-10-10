#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <i86.h>
#include <sys/types.h>
#include <unistd.h>
#include <conio.h>
#include "../include/shared_mem.h"

#define SNT10 "/etc/config/sysinit.10"
#define SNT11 "/etc/config/sysinit.11"
#define tcpip10 "/etc/config/bin/tcpip.10"
#define tcpip11 "/etc/config/bin/tcpip.11"

unsigned int i,c;
char buf[3],str_6M[10],pnt[10];
FILE *fp;

void main()
{
	unsigned int cvs; // nomer EBM
	unsigned int i,przn_find=0;
	unsigned char test[80];
	nid_t node_n; // nomer uzla
	unsigned char command[80];
	char v[10];
	
	
//---Определение соответствия между номером узла и номером ЭВМ 
	outp(0x37a, inp(0x37a)|0x24);
	cvs=inp(0x378)&0xF;
	printf("CVS = %d \n", cvs); // ----TEST---
	//cvs = 10; //--------TEST!!!!!-------------
	if ((cvs != 10) && (cvs !=11))
	{
		printf("error number CVS! %d\n",cvs);
		exit(-1);
	}
//-------------------------chtenie file--------------------------------
	fp=fopen("/cvs","r");
	if (fp!=NULL)
	{
		fgets(str_6M,10,fp);
		c = atoi(str_6M);
		printf("READ number CVS %d\n",c);
		fclose(fp);	
	}
	else printf("file not found, make new file \n");
	
//-------------------sravnenie s tekushei versiey cvs-------------------
	printf("cvs = %s c = %d \n", str_6M, c);
	
	if (cvs != c)
	{
		itoa(cvs, v, 10);
		fp=fopen("/cvs","w");
		if (fp!=NULL)
		{
			fputs(v,fp);
			printf("WRITE %s\n",v);
			fclose(fp);	
		}
		else 
		{
			printf("Error creating file, exit program\n");
			exit(-1);
		}
		printf("copy file \n");
		//--------------copy sysinit.1------------------------
		strcpy(command,"cp ");
		if (cvs==10) strcat(command,SNT10);
		else strcat(command,SNT11);
		strcat(command," ");
		strcat(command,"/etc/config/sysinit.1");
		printf("%s \n",command);
		system(command); 
		//-------------copy tcpip.1---------------------------
		strcpy(command,"cp ");
		if (cvs==10) strcat(command,tcpip10);
		else strcat(command,tcpip11);
		strcat(command," ");
		strcat(command,"/etc/config/bin/tcpip.1");
		printf("%s \n",command);
		system(command);
		delay(500);
		system("shutdown -f");
	}
}