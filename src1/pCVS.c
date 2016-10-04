#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <i86.h>
#include <sys/types.h>
#include <unistd.h>
#include <conio.h>
#include <fstream.h>

#define SNT "home/new32/src123/sysinit"
//enum N_NUM {CPC1=1,CPC2,CPC3,CPC4,CPC5,
//			CPC6=1,CPC7,
//			CPC8=1,CPC9,CPC10=1,
//			CPC11=1,CPC12=1};
//const char *K_N[]={"_RLS.","_SORS.","_SPIAK.","_MO3A.","_6M.",NULL};
//const char *przn_PC[]={"1.1","2.2","3.3","4.4","5.5","6.1","7.2","8.1",
//					 "9.2","10.1","11.1","12.1",NULL};		   
struct my_comp {
	nid_t cpc_num; //number
    nid_t node_num; //node
	char sys_name[80]; // sysinit
	char przn_PC[10];
			   };

void main(int argc, char *argv[])
{
unsigned int requested_n; // nomer EBM
unsigned int i,przn_find=0;
nid_t node_n; // nomer uzla
//nid_t node_number[]={CPC1,CPC2,CPC3,CPC4,CPC5,CPC6,CPC7,
//			         CPC8,CPC9,CPC10,CPC11,CPC12};

//struct my_comp array_comp[12]; //trebuemiy uzel
//unsigned char command[80];
//char buf[3],str_6M[10],pnt[10];
FILE *fp;
//---Заполнение массива описания узлов комплекса
/*for(i=0;i<12;i++)
	{
	array_comp[i].cpc_num=i+1;
	array_comp[i].node_num=node_number[i];
	strcpy(array_comp[i].przn_PC,przn_PC[i]);	
	strcpy(array_comp[i].sys_name,SNT);
	if (i<=4) 
		strcat(array_comp[i].sys_name,K_N[0]);
	if (i>4 && i<=6)
		strcat(array_comp[i].sys_name,K_N[1]);
	if (i>6 && i<=8)
		strcat(array_comp[i].sys_name,K_N[2]);
	if (i==10 || i==9)
		strcat(array_comp[i].sys_name,K_N[3]);
	if (i==11)
		strcat(array_comp[i].sys_name,K_N[4]);
    if (i!=9 && i!=10)
    strcat(array_comp[i].sys_name,itoa(node_number[i], buf, 10));
    else
    {
    strcat(array_comp[i].sys_name,itoa(i+1, buf, 10));
    }
    printf("# %d Node %d sysinit %s \n",
	array_comp[i].cpc_num, array_comp[i].node_num, array_comp[i].sys_name);
	}  */
	//---Определение соответствия между номером узла и номером ЭВМ 

	outp(0x37a, inp(0x37a)|0x24);
	node_n=getnid();
	requested_n=inp(0x378)&0xF;
	if (requested_n == 0 || requested_n == 0xFF)
	{
		outp(0x3FC, 2);
		requested_n=inp(0x3FE)&0xF0;
		requested_n>>=4;
		if (requested_n == 0 || requested_n == 0xF)
		{
			printf("Not found CPC NUMBER, work throw przn_PC \n");
			/*fp=fopen("/przn_PC","r");
			if (fp!=NULL)
			{
				fgets(str_6M,5,fp);
				printf("READ %s\n",str_6M);
				i=0;
				while(1)
				{
					if (str_6M[i]=='.') break;
					pnt[i]=str_6M[i];
					i++;
				}  
				printf("READ %s\n",pnt);
				requested_n=atoi(pnt);		
				printf("READ %d\n",requested_n);

				fclose(fp);	
			}
			else {printf("I don't know what to do\n"); exit(-1);}
			*/
	    }
		else printf("PC Number from  3FE\n");

    }
	else printf("PC Number from  378\n");
	
	printf("Номер ЭВМ %d  Узел  %d\n", 
		requested_n,  node_n);
		
//--------------------Check file--------------------------------
	printf("file check \n");
	if ((fp=fopen("/home/test/przn_PC","r"))==NULL)
	{
		printf("file open null \n");
		
		//fp=fopen("/home/test/przn_PC","w");
		if (fp!=NULL)
		{
			//fputs(array_comp[requested_n-1].przn_PC,fp);
			printf("file error \n");
			fclose(fp);	
		}
	}
	else printf("else \n");
	fp=fopen("/home/test/przn_PC","w");
//---Проверка наличия файла przn_PC
	/* if ((fp=fopen("/przn_PC","r"))==NULL)
	{
		fp=fopen("/przn_PC","wr");
		if (fp!=NULL)
		{
			fputs(array_comp[requested_n-1].przn_PC,fp);
			fclose(fp);	
		}
	}

	for(i=0;i<12;i++) //???
	if ((requested_n == array_comp[i].cpc_num) && (node_n == array_comp[i].node_num)) 
	{
		przn_find=1;
		break;
	}
	if (przn_find) printf("NODE Number OK  %d\n", node_n);
	else 
	{
		printf("Номер ЭВМ %d  Узел  %d Требуемый Узел %d\n", 
		requested_n,  node_n, array_comp[requested_n-1].node_num );
//---Копирование соответствующего sysinit в sysinit нужного узла
	/*	strcpy(command,"cp ");
		strcat(command,array_comp[10].sys_name);
		printf("READ %d\n",requested_n);
		printf("array %s \n", array_comp[10].sys_name);
		strcat(command," ");
		strcat(command,SNT);
		strcat(command,".");
		strcat(command,itoa(array_comp[10].node_num,buf,10));
		printf("%s \n",command);
		system(command); */
//---Копирование соответствующего boot в .boot нужного узла 
	/*	strcpy(command,"cp /.boot.");
		strcat(command,itoa(requested_n, buf, 10));
		strcat(command,"_");
		strcat(command,itoa(array_comp[requested_n-1].node_num , buf, 10));
		strcat(command," /.boot");
		printf("%s\n",command);
		*/
		/*if (system(command) == 0) 
		{
			sprintf(command,"%s %d.%d %s", "echo", requested_n,array_comp[requested_n-1].node_num,"> /przn_PC");
			printf("%s\n",command);
			system(command);
			system("shutdown -f");
				
		} */
    //} 
}
