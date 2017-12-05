
#include <unistd.h>
#include "ts.h"
#include "cpuplus.h"
#include <sys/osinfo.h>

#include <time.h>
#include <process.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/dev.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>


int
F_Socket_Test()
	{
	short status = 0;
	char temp_msg[300], command[50];	
	FILE *fp,*fp1;
	int j;
	char *find[]={"Socklet","Socket","Tcpip",NULL};
	setenv("PATH",":/bin:/usr/bin:.",1);
	setenv("SHELL","ksh",1);
	setenv("LOGNAME","root",1);	

//	printf ("Net driver testing...\n");
	for (j=0;j<3;j++) {
	if (status == 1) return (status);
	sprintf (command, "sin -P %s", find[j]);
	fp = popen (command, "r");
	if (fp!=0)
		{
	while (fgets (temp_msg, sizeof(temp_msg), fp) != 0)
		{
//		printf ("temp_msg = %s\n", temp_msg);
		if (strstr (temp_msg, find[j]) != 0)  
				{
//			printf ("msg = %s\n", strstr (temp_msg, Net_Driver));
			printf("Driver found...\n");
			status = 1;
			break;
				}
		else
			{
			printf("No Driver found...\n");
			status = -1;
			}
		 }
	pclose(fp);
		 }
					 }	
	return (status);
	}
int
	connect_CMP (char *host_addr)
	{
	short status = 0;
	char Cmd[40],*point[6];
	FILE *fp;
    int find;
	char temp_msg[300];
	setenv("PATH",":/bin:/usr/bin:.:/usr/ucb",1);
	setenv("SHELL","ksh",1);
	setenv("LOGNAME","root",1);
	
//----Запуск утилиты ping c адресом заданного хоста
	sprintf(Cmd,"ping -c 10 %s",host_addr);
	printf("PING %s\n",Cmd);
	fp=popen(Cmd,"r");
	
	if (fp!=0)
	{
	while (fgets (temp_msg, sizeof(temp_msg), fp) != 0)
		{
	printf("HERE %s \n",temp_msg);
	if(strstr(temp_msg,"ret=-1") != 0)
			{
			status=-1;
			break;
			}
	if(strstr(temp_msg,host_addr) != 0) {find++;
	printf ("%s %d\n",host_addr,find);
									   }					

		}
	
	if (find) status++; 
	if (!find) printf("Не отвечает host %s\n",host_addr);
	
	}
	else status=4;
	
	printf("status %d\n",status);
	return (status);
	}

void main(int argc, char *argv[])
{
int status_PT=0,status_AT=0, status_MY=0;
char host_addr[80]="192.168.6.2";
char my_name[80]="192.168.6.1";

arginit(argc,argv,"Проверка запуска ПО TCP/IP\n");
argp("cmp=","%s",host_addr,"IP адрес для проверки соединения");
argp("my_n=","%s",my_name,"собственный IP адрес");

printf("HOST %s\n",host_addr);

oopen();
	status_PT=F_Socket_Test();
	if (status_PT < 0) {printf("Не запущен механизм сокетов\n");
					   }
	else
 	status_AT=connect_CMP (host_addr);
    if (status_AT <=0)
	{
	printf("%s\n",my_name);
 	status_MY=connect_CMP (my_name);
	}
if ((status_PT<0 || status_MY <=0) && status_AT <=0 ) err++;
if(err==0) rez=1; else rez=2;
  oclose(); exit(rez);
} 
