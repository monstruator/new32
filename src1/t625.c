  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/kernel.h>

  #include <netinet/in.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <netdb.h>
  #include <math.h>


  #include "../include/IP_nb.h"
  #include "../include/shared_mem.h"
//  #include "../include/packets.h"
  #include "../include/1.h"


 // --------------my global--------------------
      unsigned short buffer[62];
      unsigned long k,sum;
      unsigned char byte_bufer[124];
      int i,jj,m,K,K_com,FLAG;                               
      int FLAG_Z,FLAG_DMW,FLAG_CV;
//--------------------------------------------                        


	int sock, length, i , count_mes=0;
	static Udp_Client_t Uc41,Uc42;
	char bufi[1024];
	char bufo[1024];
    unsigned char buf625[31];
	char out_buf[1024];

	int verbose;
	char name[30] = "192.168.1.2";
		
      int port_src = 7118;
	  int port_src_dat=4010;	
# define DST_PORT41 7119
# define DST_PORT42 4011

	short MK2[15],buf;
	short byta2,T,len_OUT,sen,j;
    div_t   vol;    // vol.quot - количество полных томов
    char          pack_buf[1500];  // буфер задачи obm_41_31. Выходные данные в Socket
    char                 numb_pack,     // текущий номер пакета
                         numb_vol;      // текущий номер тома в пакете

//struct
//   { 
 //    char      out_buf[max_len_OUT];  // данные для Socket'a
 //  } ip_out; 

	  
main ( )
{
//unsigned short cr_com; //порядковый номер предыдущей команды
//		short		V,dV;
int cnt=0;
int i1=0;
int rez,bytes;
unsigned short buf[4];
unsigned int K_Summa;
unsigned int komanda;
short    time625;    // time out
long local_timer;
//packcmd	inb;
//packusoi outb;
//----------------------------
//outb.kzv=outb.k_o=0;
//----------------------------



//------------инициализация канала UDP---------------------
	i = Udp_Client_Ini(&Uc41,name,DST_PORT41,port_src);
    i = Udp_Client_Ini(&Uc42,name,DST_PORT42,port_src_dat);

//------------initialization timer-------------------------
    delay(3000);
	open_shmem();
START:   //  p->cmd_625.count625_inf=0;
     p->cmd_625.count625_cmd=0;
     p->cmd_625.T625_on_off=0;
    p->komanda625=0;
    time625=300;    // что это?

 //-------------------my text---------------------------
	

while(1)
{
//------------------ZAPROS/KOMANDA-----------------------------

    local_timer=p->sys_timer;
    while((p->sys_timer-local_timer)<=20);// delay 200msec
    // comment
    if(p->komanda625==3)
     {
      //-----------------data_inf--------------------
       i=initinf();
		//  Вычисление контр суммы       
       read_data.Read_inf.Summa=KSumPrm(read_data.buffer,62);
//-----------------------write------------------------ 
	sen = Udp_Client_Send(&Uc42,&read_data,sizeof(read_data));
    p->SOST625=1;
    local_timer=p->sys_timer;
    bytes=0;
//--------------read---------------------------------
  while  (( bytes = Udp_Client_Read(&Uc42,&read_data,sizeof(read_data)))<=0)    
     if( (p->sys_timer-local_timer)>time625)
       {printf("T-625 Отключено  Inf\n");p->cmd_625.T625_on_off=1;
      p->SOST625=3;//goto START;
    }
      
	  if(p->cmd_625.T625_on_off==0)
     {p->SOST625=2; 
      memcpy(&p->inf_625,&read_data,sizeof(read_data));
      p->cmd_625.count625_inf++;
      printf(" p->cmd_625.count625_inf       :         %d\n",
      p->cmd_625.count625_inf);}
      p->cmd_625.T625_on_off=0;
      p->komanda625=0;
     }      
    // comment
    if(p->komanda625==0) i=send_zapros();
    if(p->komanda625==1) i=send_SVCH();
    if(p->komanda625==2) i=send_DMW();
    p->SOST625=1;
	sen = Udp_Client_Send(&Uc41,&read_7118,sizeof(read_7118));
    p->SOST625=1;
    for (i=0;i<sizeof(read_7118);i++) read_7118.bufcom[i]=0;
    local_timer=p->sys_timer;
    bytes=0;
//----------------read-----------------------------------
 while  (( bytes = Udp_Client_Read(&Uc41,&read_7118,sizeof(read_7118)))<=0)
    { if( (p->sys_timer-local_timer)>time625)
      {printf("T-625 Отключено  C\n");p->cmd_625.T625_on_off=1;
       p->SOST625=3;	//goto START;
      }};
//--------------------------------------------------------
    if(p->cmd_625.T625_on_off==0)
    {  p->SOST625=2; 
    p->cmd_625.count625_cmd++;
      if(read_7118.O_na_zapros.Tip==0x2)
         {p->cmd_625.T625_ok_nok= read_7118.O_na_zapros.Sost;
          p->cmd_625.T625_Result= read_7118.O_na_zapros.Opt;
          printf (" Otvet na zapros   :   %d   %d    %d\n",
          p->cmd_625.T625_ok_nok,
          p->cmd_625.T625_Result,
          p->cmd_625.count625_cmd);}
      if(read_7118.O_na_zapros.Tip==0x111)
         { p->cmd_625.T625_SV_Result=read_7118.O_na_kom.Result;
	             printf (" Otvet na vybor SVC:  %d   %d    %d\n",
                 read_7118.O_na_kom.Tip,
                 p->cmd_625.T625_SV_Result,p->cmd_625.count625_cmd);}
       if(read_7118.O_na_zapros.Tip==0x113)
         { p->cmd_625.T625_DMW_Result=read_7118.O_na_kom.Result;
	             printf (" Otvet na vybor DMW:  %d   %d    %d\n",
                 read_7118.O_na_kom.Tip,
                 p->cmd_625.T625_DMW_Result,p->cmd_625.count625_cmd);}

    }
         p->komanda625++;
         if(p->komanda625==4) p->komanda625=0;
         p->cmd_625.T625_on_off=0;
} 
}

