  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/kernel.h>

  #include <netinet/in.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <netdb.h>
  #include <math.h>
  
#include <sys/pci.h>
#include <i86.h>
#include <conio.h>
#include <stdio.h>
#include <sys/seginfo.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/my_pci_ts_new.h"
#include "../include/ts.h"
#define BAR0 0x10
#define BAR1 0x14
#define BAR2 0x18

#define D_cp384 0x5555
#define V_cp384 0x1556

//#define SET_BIT  (value, bit_n) ((value) |=  (1 << (bit_n)))
//#define UNSET_BIT(value, bit_n) ((value) &= ~(1 << (bit_n)))
 
#define TIMEOUT_SEC		   0L	//0 секунд
#define TIMEOUT_NSEC	10000000L	//макс. время ожидания 10 мс
#define LENBUFWR	80	//длина буфера передачи
#define LnTitle		32		//длина заголовка
#define LENBUFRD 	1400	//длина буфера приема
#define LnKdr	   512	//макс число слов(2 байта) в кадре
#define MaxKdr	  10000	//макс число хранимых кадров
		  
//#include "../include/shared_mem.h"
#include "../include/USOIwrk.h"

#define MS 1000000
#define N_CHAN 3 //RELE


timer_t  tm10;
struct sigevent event_sig;
struct itimerspec timer_sig;

unsigned short D_Bridge=D_cp384;
long V_Bridge=V_cp384,Base_adr0,Base_adr2,value1=0xFFFFFFFF;
struct conf_pci my_device;
char *ptr1=0,*addr1;
unsigned long ba;
unsigned short ba1;
char *ptr2,*addr2;
int i,ii;
int fd1;

//===============================================================================
//			MAIN	MAIN	MAIN	MAIN 	MAIN
main(int argc, char *argv[])
{
	
	int n,i,j,col,command,i1;
	unsigned char rele=0;// sosto9nie rele
    short c_step=0,T0=0;	
    long rele_timer=0;
	unsigned short save;
	int ind=0,chk_num,Time_out=5,Con1=0;
	
	//--------------------------------------------nastroika rele----------------------------
	arginit(argc,argv,"тест модуля cp384\n");
	argp("IO=", "%d", &ind, "Индекс модуля на шине CPCI");
	argp("V_Br=","%x",&V_Bridge,"ID производителя");
	argp("D_Br=", "%x", &D_Bridge, "ID устройства");
	argp("delay=", "%d", &Time_out, "Таймаут запуска теста");
	argp("Con1=", "%x", &Con1, "Режим надетой заглушки - 0 - нет");

	delay(Time_out);
	//Определение Базового адреса внутренних регистров моста
	i=new_func_read(D_Bridge,V_Bridge,&my_device,BAR0,ind);
	
}