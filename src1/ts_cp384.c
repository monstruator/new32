#include <stdlib.h>
#include <sys/pci.h>
#include <i86.h>
#include <conio.h>
#include <stdio.h>
#include <sys/seginfo.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "my_pci_ts_new.h"
#include "ts.h"
#define BAR0 0x10
#define BAR1 0x14
#define BAR2 0x18

#define D_cp384 0x5555
#define V_cp384 0x1556


unsigned short D_Bridge=D_cp384;
long V_Bridge=V_cp384,Base_adr0,Base_adr2,value1=0xFFFFFFFF;
struct conf_pci my_device;
char *ptr1=0,*addr1;
unsigned long ba;
unsigned short ba1;
char *ptr2,*addr2;
int i,ii;
int fd1;
void main(int argc, char *argv[])
{
char txt[100],buf[10];
int fd[3];
unsigned short save;
int ind=0,j,chk_num,Time_out=5,Con1=0;
unsigned short etalon_1[]={0x5555,0x5556,0x5559,0x5565,0x5595,0x5655,0x5955,0x6555,0x9555};
unsigned short etalon_2[]={0xAAA9,0xAAA6,0xAA9A,0xAA6A,0xA9AA,0xA6AA,0x9AAA,0x6AAA};
arginit(argc,argv,"тест модуля cp384\n");
argp("IO=", "%d", &ind, "Индекс модуля на шине CPCI");
argp("V_Br=","%x",&V_Bridge,"ID производителя");
argp("D_Br=", "%x", &D_Bridge, "ID устройства");
argp("delay=", "%d", &Time_out, "Таймаут запуска теста");
argp("Con1=", "%x", &Con1, "Режим надетой заглушки - 0 - нет");

delay(Time_out);
oopen();

     rez=-1; podswID();	rez=1;

//Определение Базового адреса внутренних регистров моста
i=new_func_read(D_Bridge,V_Bridge,&my_device,BAR0,ind);

if (i==-1) {error("Мост отсутствует");err++;}
else {
if (PCI_IS_MEM(mass[BAR0])) {
//Отображение портов модуля в PCI Memory Space
printf ("Memory %08x\n",ba=PCI_MEM_ADDR(mass[BAR0]));

//----Попытка работать с памятью
fd1=shm_open("Physical",O_RDWR,0777);
ptr1=(char *)mmap(0,64*1024,PROT_READ|PROT_WRITE|PROT_NOCACHE,MAP_SHARED,fd1,
PCI_MEM_ADDR(mass[BAR0])&~4095);
printf ("ptr1 = %x %8x\n",ptr1,ba); 
if (ptr1==(char *)-1) {printf ("FAULT\n"); exit (-1);}
addr1=ptr1 + (ba&4095);
printf ("Memory configuration addr = %x\n",addr1);
*(unsigned int*)(addr1)=0xFFFFFFFF;

if (1) {

if (1) {
i=1;
printf("WRITE O_CTL %x %x\n",0x2000 + 0x400*i,*(unsigned int*)(addr1 +0x2000 + 0x400*i)=0);
i++;
printf("READ O_STA_A %x, %x\n",0x2000 + 0x400*i,*(unsigned int*)(addr1 +0x2000 + 0x400*i));

i++;

printf("WRITE I_CTL %x\n",*(unsigned int*)(addr1 +0x4400)=0x80);

printf("WRITE OUT DATA %x %x\n",0x2000 + 0x400*i,*(unsigned int*)(addr1 +0x2000 + 0x400*i)=0);
delay(10);
printf("READ DATA %x\n",*(unsigned int*)(addr1 + 0x4C00));

for(ii=0;ii<8;ii++) 
            {
printf("WRITE OUT DATA %x %x\n",0x2000 + 0x400*i,*(unsigned int*)(addr1 +0x2000 + 0x400*i)=(1<<ii));
delay(10);
printf("READ INPUT DATA %x\n",save=*(unsigned int*)(addr1 + 0x4C00));
//printf("=>>Etalon %x\n",etalon_1[ii+1]);
if (save&etalon_1[ii+1]) printf("etalon OK \n"); else err++;
			}


printf("WRITE OUT DATA %x %x\n",0x2000 + 0x400*i,*(unsigned int*)(addr1 +0x2000 + 0x400*i)=0);
delay(10);
printf("READ DATA %x\n",*(unsigned int*)(addr1 + 0x4C00));

for(ii=0;ii<8;ii++) 
            {
printf("WRITE OUT DATA %x %x\n",0x2000 + 0x400*i,*(unsigned int*)(addr1 +0x2000 + 0x400*i)=~(1<<ii));
delay(10);
printf("READ INPUT DATA %x\n",save=*(unsigned int*)(addr1 + 0x4C00));
//printf("=>>Etalon %x\n",etalon_2[ii]);
if (save&etalon_2[ii]) printf("etalon OK \n"); else err++;			
}


		  }
else { //автоматический тест если нет заглушки
;
     }
			}

						   }
	} //Если PCI устройство обнаружено
if(err==0) rez=1; else {rez=2; error("Модуль неисправен");}
//podswID();
oclose();
munmap(ptr1,4096);
close(fd1);
exit (rez);
}