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
  //#include "../include/func_IP.h"
  #include "../include/shared_mem.h"
  #define MS 1000000
  #define N_CHAN 6 

#ifdef __USAGE
		  HELPа

	#endif

// --------------my global--------------------
      unsigned short buffer[62];
      unsigned long k,sum;
      unsigned char byte_bufer[124];
      int i,jj,m,K,K_com,FLAG;                               
      int FLAG_Z,FLAG_DMW,FLAG_CV;
//--------------------------------------------                        

	void  KSumPrm(int);
	Initinf (unsigned short);
	int  send_zapros();
	int send_SVCH();
	int send_DMW();
	int sock, length, i , count_mes=0;
	static Udp_Client_t Uc41,Uc42;
	char bufi[1024];
	char bufo[1024];
    unsigned char buf625[31];
	char out_buf[1024];
	int timer2=0;
	int timer3=0;
	int iii;
	int x=0;
	int tri=0;
	unsigned int t625com;

	int verbose;
	char name[30] = "192.168.4.2";
		
      int port_src = 7118;
	  int port_src_dat=4000;	
  # define DST_PORT41 7118
  # define DST_PORT42 4000

	short MK2[15],buf;
	short byta2,T,len_OUT,sen,red,j;
    div_t   vol;    // vol.quot - количество полных томов
    char          pack_buf[1500];  // буфер задачи obm_41_31. Выходные данные в Socket
    char                 numb_pack,     // текущий номер пакета
                         numb_vol;      // текущий номер тома в пакете

//struct
 //  { 
 //    char      out_buf[max_len_OUT];  // данные для Socket'a
  // } ip_out; 

volatile unsigned int counter;

//===============================================================================
//			MAIN	MAIN	MAIN	MAIN 	MAIN
main(int argc, char *argv[])
{
	int cnt=0;
	int i1=0,ii=0;
	int rez,bytes;
	unsigned short buf[4];
	unsigned int K_Summa;
	unsigned int komanda;
	short    time625;    // time out
	long local_timer;

	int n,i,j,col,command;
	
	short c_step=0,T0=0;	
    long cpp_timer=0;
    int data_read; //4tenie dannih 
	struct form193 *f193;

	i = Udp_Client_Ini(&Uc41,name,DST_PORT41,port_src);
    i = Udp_Client_Ini(&Uc42,name,DST_PORT42,port_src_dat);
	if(p->cvs == 10) exit(0);
	delay(1500);
	open_shmem();
	delay(1000);
	
	p->cmd_625.count625_cmd=0;
    p->cmd_625.T625_on_off=0;
    p->komanda625=0;
    time625=50;    // что это?
	
	printf("START MO3A<->T625 \n\n");
//---------------------------------------------------------------------	
	while(1)
	{
		if (cpp_timer!=p->sys_timer) //timer
		{
			cpp_timer=p->sys_timer;
			if (p->cur_step!=0) //est' wag dl9 vipolnenni9
			{
				c_step=p->cur_step;
				for (i=0;i<p->work_com[c_step].num_mini_com;i++) //prosmotrim vse minicomandi na wage 
					//if((p->work_com[c_step].s[i].n_chan==N_CHAN)&&((p->work_com[c_step].s[i].status==0)||(p->work_com[c_step].s[i].status==1))) //na tekuwem wage (i - minikomanda) est' komanda dl9 nas		
					if((p->work_com[c_step].s[i].n_chan==N_CHAN)&&(p->work_com[c_step].s[i].status!=2)&&(p->work_com[c_step].s[i].status!=3)) //na tekuwem wage (i - minikomanda) est' komanda dl9 nas
					{
						if((p->verbose>1)&&(p->work_com[c_step].s[i].status==0)) printf("\nSTEP=%d    minicom for T625 : %d      status=%d time %d \n", p->cur_step,  p->work_com[c_step].s[i].n_com, p->work_com[c_step].s[i].status, p->sys_timer);
						//p->work_com[c_step].s[i].status=1;						
						switch(p->work_com[c_step].s[i].n_com)
						{
							case 1: send_zapros();														
									Udp_Client_Send(&Uc41,&read_7118,sizeof(read_7118));
									p->SOST625=1;
									for (ii=0;ii<sizeof(read_7118);ii++) read_7118.bufcom[ii]=0;
									local_timer=p->sys_timer;
									bytes=0;
									while  ((( bytes = Udp_Client_Read(&Uc41,&read_7118,sizeof(read_7118)))<=0)&&((p->sys_timer-local_timer)<time625)) delay(5);
									if (bytes>0)
									{
										p->SOST625=2; 
										p->cmd_625.count625_cmd++;
										p->toMN3.sost_spiak.T625=1;//ispravno T625
										if(read_7118.O_na_zapros.Tip==0x2)
										{
											p->toMN3.sost_spiak.rabota=p->toMN3.sost_spiak.reset=p->toMN3.sost_spiak.regl=0;
											p->toMN3.sost_spiak.konez=p->toMN3.sost_spiak.kontr=0; 
											
											p->cmd_625.T625_ok_nok= read_7118.O_na_zapros.Sost;
											p->cmd_625.T625_Result= read_7118.O_na_zapros.Opt;
											printf (" T625 : ");
											if (p->cmd_625.T625_ok_nok==0x40) p->toMN3.sost_spiak.ispr=1;
											else p->toMN3.sost_spiak.ispr=0;
											switch (p->cmd_625.T625_Result)
											{
												case 0: printf (" work");
												p->toMN3.sost_spiak.rabota=1;
												break;
												case 1: printf (" reboot");
												p->toMN3.sost_spiak.reset=1;
												break;
												case 2: printf (" reglament");
												p->toMN3.sost_spiak.regl=1;
												break;
												case 3: printf (" finish");
												p->toMN3.sost_spiak.konez=1;
												break;
												case 4: printf (" control");
												p->toMN3.sost_spiak.kontr=1;
												break;
											}
											printf("\n");
											p->work_com[c_step].s[i].status=2; // ispravnost'	
										}
										else p->work_com[c_step].s[i].status=3;
										/*if(read_7118.O_na_zapros.Tip==0x111)
										{ 
											p->cmd_625.T625_SV_Result=read_7118.O_na_kom.Result;
											printf (" Otvet na vybor SVC:  %d   %d    %d\n",
											read_7118.O_na_kom.Tip,
											p->cmd_625.T625_SV_Result,p->cmd_625.count625_cmd);
										}
										if(read_7118.O_na_zapros.Tip==0x113)
										{
											p->cmd_625.T625_DMW_Result=read_7118.O_na_kom.Result;
											printf (" Otvet na vybor DMW:  %d   %d    %d\n",
											read_7118.O_na_kom.Tip,
											p->cmd_625.T625_DMW_Result,p->cmd_625.count625_cmd);
										} */
									}
									else 
									{
										printf("T-625-Rqst no answer\n");
										p->cmd_625.T625_on_off=1;
										p->SOST625=3;
										p->work_com[c_step].s[i].status=3;
										p->toMN3.sost_spiak.T625=0;
									}
									break;
							case 2: switch(p->fromMN3.a_params[0])
									{
										case 0:		printf("SET SVCH\n");	send_SVCH(); break;
										case 1:		printf("SET DMV \n");	send_DMW(); break;
									}
				
									Udp_Client_Send(&Uc41,&read_7118,sizeof(read_7118));
									p->SOST625=1;
									for (ii=0;ii<sizeof(read_7118);ii++) read_7118.bufcom[ii]=0;
									local_timer=p->sys_timer;
									bytes=0;
									while  ((( bytes = Udp_Client_Read(&Uc41,&read_7118,sizeof(read_7118)))<=0)&&((p->sys_timer-local_timer)<time625)) delay(5);
									if (bytes>0)
									{
										p->SOST625=2; 
										p->cmd_625.count625_cmd++;
										/*if(read_7118.O_na_zapros.Tip==0x2)
										{
											p->cmd_625.T625_ok_nok= read_7118.O_na_zapros.Sost;
											p->cmd_625.T625_Result= read_7118.O_na_zapros.Opt;
											printf (" Otvet na zapros   :   sostoyanie-  %d   rshim raboti- %d   dlina-  %d  schetchik komand-  %d\n",
											p->cmd_625.T625_ok_nok, // sostoyanie 64 = 1 0x40
											p->cmd_625.T625_Result, // reshim raboti
											read_7118.O_na_zapros.Dlina, //dlina
											p->cmd_625.count625_cmd);
											if (p->cmd_625.T625_Result == 0) printf (" work");
											if (p->cmd_625.T625_Result == 1) printf (" reboot");
											if (p->cmd_625.T625_Result == 2) printf (" reglament");
											if (p->cmd_625.T625_Result == 3) printf (" finish");
											if (p->cmd_625.T625_Result == 4) printf (" control");
											fflush (stdout);
											
										} */
										if(read_7118.O_na_zapros.Tip==0x111)
										{ 
											p->cmd_625.T625_SV_Result=read_7118.O_na_kom.Result;
											printf (" Otvet na vybor SVC:  %d   %d    %d\n",
											read_7118.O_na_kom.Tip,
											p->cmd_625.T625_SV_Result,p->cmd_625.count625_cmd);
										}
										if(read_7118.O_na_zapros.Tip==0x113)
										{
											p->cmd_625.T625_DMW_Result=read_7118.O_na_kom.Result;
											printf (" Otvet na vybor DMW:  %d   %d    %d\n",
											read_7118.O_na_kom.Tip,
											p->cmd_625.T625_DMW_Result,p->cmd_625.count625_cmd);
										}
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else 
									{
										printf("T-625-Rqst no answer\n");
										p->cmd_625.T625_on_off=1;
										p->SOST625=3;
										p->work_com[c_step].s[i].status=3;
									}
									break;
									
							case 3: switch(p->fromMN3.a_params[0])
									{
										case 193:	
											 send_data.send_inf.Sach.ps = 1;
											 send_data.send_inf.Sach.vr = 1;
											 send_data.send_inf.Sach.rez1 = 0;
											 send_data.send_inf.Sach.kvi = 5;
											 send_data.send_inf.Sach.rez2 = 0;
											 send_data.send_inf.Sach.nf = 193;

											 send_data.send_inf.Sach.a0 = 3;
											 send_data.send_inf.Sach.a1 = 2;
											 send_data.send_inf.Sach.a2 = 1;
											 send_data.send_inf.Sach.a3 = 0;

											 send_data.send_inf.Sach.a4 = 0;
											 send_data.send_inf.Sach.a5 = 0;
											 send_data.send_inf.Sach.p0 = 6;
											 send_data.send_inf.Sach.p1 = 5;

											 send_data.send_inf.Sach.p2 = 4;
											 send_data.send_inf.Sach.p3 = 0;
											 send_data.send_inf.Sach.p4 = 0;
											 send_data.send_inf.Sach.p5 = 0;

											 send_data.send_inf.Sach.r0 = 9;
											 send_data.send_inf.Sach.r1 = 8;
											 send_data.send_inf.Sach.r2 = 9;
											 send_data.send_inf.Sach.r3 = 7;


											 send_data.send_inf.Sach.v0 = 5;
											 send_data.send_inf.Sach.v1 = 5;
											 send_data.send_inf.Sach.v2 = 4;
											 send_data.send_inf.Sach.v3 = 3; 
											//------------------DATA--------------------------------------------------
											 send_data.send_inf.Data[0] = 0x1D00; //data 7 tip upakovku/reserv !bin!
											 send_data.send_inf.Data[1] = 0x2300; //data 8 kod formalizovannogo soobsheniya/priznak napravleniya !bin!
											 send_data.send_inf.Data[2] = 0x2400; //data 9 koordinata X !bin!
											 send_data.send_inf.Data[3] = 0x2500; //data 10 koordinata Y !bin!
											 send_data.send_inf.Data[4] = 0x1D00; //data 11 kurs grad !bin!
											 send_data.send_inf.Data[5] = 0x001E; //data 12 skorost' m/s !bin!
											 send_data.send_inf.Data[6] = 0x1248; //data 13 vstavka 1 !bin!
											 send_data.send_inf.Data[7] = 0x1249; //data 14 vstavka 2 !bin!
											 send_data.send_inf.Data[8] = 0x1250; //data 15 vstavka 3 !bin!
											 send_data.send_inf.Data[9] = 0x1251; //data 16 vstavka 3 !bin!
											 send_data.send_inf.Data[10] = 0x0000; //data 17 reserv
											 send_data.send_inf.Data[11] = 0x0000; //data 18 reserv
											 send_data.send_inf.Data[12] = 0x0000; //data 19 reserv
											 send_data.send_inf.Data[13] = 0x0000; //data 20 reserv
										break;
										//case 2:	send_DMW(); break;
									}
							
									p->work_com[c_step].s[i].status=1;
									//for(ii=0; ii<62; ii++) buffer[ii] =0;
									for(ii=0;ii<6;ii++) buffer[ii]=ii;
									Initinf(ii);
									
									sen = Udp_Client_Send(&Uc42,&send_data,sizeof(send_data));
									p->SOST625=1;
									local_timer=p->sys_timer;
									bytes=0;
									while  ((( bytes = Udp_Client_Read(&Uc42,&send_data,sizeof(send_data)))<=0)&&((p->sys_timer-local_timer)<time625)) delay(5);
									//	if( (p->sys_timer-local_timer)>time625)
									if (bytes>0)
									{
										p->SOST625=2; 
										memcpy(&p->inf_625,&send_data,sizeof(send_data));
										p->cmd_625.count625_inf++;
										//printf(" formulyar       :         %x\n  dlinna       :         %d\n" ,	send_data.buffer[4],	p->cmd_625.count625_inf);
										//for (ii=0; ii<28; ii++) printf ("\k = %x\n", send_data.buffer[ii]);
										for (ii=0; ii<10; ii++) printf ("%04x  ",send_data.buffer[ii]); 
										printf("\n"); 
										p->cmd_625.T625_on_off=0;
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else 
									{
										printf("T-625-Inf no answer\n");
										p->cmd_625.T625_on_off=1;
										p->SOST625=3;
										p->work_com[c_step].s[i].status=3;
										//break;
									}
									break;
							case 922: 	// FK5 800bit
									p->work_com[c_step].s[i].status=1;
									for(ii=0;ii<50;ii++) send_data.send_inf.Data[ii]=ii; // 0x5555
									
									sen = Udp_Client_Send(&Uc42,&send_data,Initinf(50)); //1-50
									p->SOST625=1;
									local_timer=p->sys_timer;
									bytes=0;
									p->work_com[c_step].s[i].status=2;
									t625com = p->cmd_625.count625_inf;
									break;
							case 923: 	// FK5 800bit
									//printf("status %d \n", p->work_com[c_step].s[i].status);
									if(p->work_com[c_step].s[i].status==0)
									{
										p->work_com[c_step].s[i].status=1;
										tri=0;
										//t625com = p->cmd_625.count625_inf;
									}
									if (tri<150) 
									{
										if (t625com != p->cmd_625.count625_inf) 
										{
											for(iii=4;iii<60;iii++)
											{
												if (send_data.buffer[iii] != read_data.buffer[iii])
												{
													printf("IB ne sovpali %d \n", iii);
													p->work_com[c_step].s[i].status=3;
													x=0;
													tri=0;
													break;
													//printf("read(%04x ) send(%04x) %d \n", read_data.buffer[iii], send_data.buffer[iii]);
												}
											}
											//printf("step status %d \n", p->work_com[c_step].s[i].status);
											if(p->work_com[c_step].s[i].status==1) //esli status ewe ne 3
											{
												p->work_com[c_step].s[i].status=2;
												printf("Massivi IB sovpali \n");
												tri=0;
											}
										}
									}
									else
									{
										printf("800bit not data tri=%d t625com=%d p->cmd_625.count625_inf=%d\n",tri,t625com,p->cmd_625.count625_inf);
										p->work_com[c_step].s[i].status=3;
									}
									
									tri++;
									break;
						//------------FK5 END-----------------------------------------------------
						//------------Ustanovit' svyaz' s AK START--------------------------------
							case 93:  //ust svyaz' s AK
									send_SVCH();
									Udp_Client_Send(&Uc41,&read_7118,sizeof(read_7118));
									p->SOST625=1;
									for (ii=0;ii<sizeof(read_7118);ii++) read_7118.bufcom[ii]=0;
									local_timer=p->sys_timer;
									bytes=0;
									while  ((( bytes = Udp_Client_Read(&Uc41,&read_7118,sizeof(read_7118)))<=0)&&((p->sys_timer-local_timer)<time625)) delay(5);
									if (bytes>0)
									{
										p->SOST625=2; 
										p->cmd_625.count625_cmd++;
										/*if(read_7118.O_na_zapros.Tip==0x2)
										{
											p->cmd_625.T625_ok_nok= read_7118.O_na_zapros.Sost;
											p->cmd_625.T625_Result= read_7118.O_na_zapros.Opt;
											printf (" Otvet na zapros   :   sostoyanie-  %d   rshim raboti- %d   dlina-  %d  schetchik komand-  %d\n",
											p->cmd_625.T625_ok_nok, // sostoyanie 64 = 1 0x40
											p->cmd_625.T625_Result, // reshim raboti
											read_7118.O_na_zapros.Dlina, //dlina
											p->cmd_625.count625_cmd);
											if (p->cmd_625.T625_Result == 0) printf (" work");
											if (p->cmd_625.T625_Result == 1) printf (" reboot");
											if (p->cmd_625.T625_Result == 2) printf (" reglament");
											if (p->cmd_625.T625_Result == 3) printf (" finish");
											if (p->cmd_625.T625_Result == 4) printf (" control");
											fflush (stdout);
											
										} */
										if(read_7118.O_na_kom.N_kan==5)
										{ 
											p->cmd_625.T625_SV_Result=read_7118.O_na_kom.Result;
											printf (" Otvet na vybor SVC:  %d   %d  %d  %d\n",
											read_7118.O_na_kom.Tip,
											p->cmd_625.T625_SV_Result,read_7118.O_na_kom.Result,p->cmd_625.count625_cmd);
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
									}
									else 
									{
										printf("T-625-Rqst no answer\n");
										p->cmd_625.T625_on_off=1;
										p->SOST625=3;
										p->work_com[c_step].s[i].status=3;
									}
									break;
									
							case 931: 	// t625  po lvs 
									for(ii=0;ii<50;ii++) buffer[ii]=0x5555;
									Initinf(50);
									sen = Udp_Client_Send(&Uc42,&send_data,sizeof(send_data));
									p->SOST625=1;
									local_timer=p->sys_timer;
									bytes=0;
									while  ((( bytes = Udp_Client_Read(&Uc42,&send_data,sizeof(send_data)))<=0)&&((p->sys_timer-local_timer)<time625)) delay(5);
									//	if( (p->sys_timer-local_timer)>time625)
									if (bytes>0)
									{
										p->SOST625=2; 
										memcpy(&p->inf_625,&send_data,sizeof(send_data));
										p->cmd_625.count625_inf++;
										//printf(" formulyar       :         %x\n  dlinna       :         %d\n" ,	send_data.buffer[4],	p->cmd_625.count625_inf);
										//for (ii=0; ii<28; ii++) printf ("\k = %x\n", send_data.buffer[ii]);
										for (ii=0; ii<10; ii++) printf ("%04x  ",send_data.buffer[ii]); 
										printf("\n"); 
										p->cmd_625.T625_on_off=0;
										
									}
									else 
									{
										printf("T-625-Inf no answer\n");
										p->cmd_625.T625_on_off=1;
										p->SOST625=3;
										p->work_com[c_step].s[i].status=3;
										//break;
									}
									break;
							
							case 932: 	// t625  po lvs   
									if ((send_data.buffer[7]==send_data.send_inf.Data[0])&&(send_data.buffer[8]==send_data.send_inf.Data[1])&&(send_data.buffer[9]==send_data.send_inf.Data[2])&&(send_data.buffer[10]==send_data.send_inf.Data[3])&&(send_data.buffer[11]==send_data.send_inf.Data[3])&&(send_data.buffer[12]==send_data.send_inf.Data[4])&&(send_data.buffer[13]==send_data.send_inf.Data[5])&&(send_data.buffer[14]==send_data.send_inf.Data[6])&&(send_data.buffer[15]==send_data.send_inf.Data[7])&&(send_data.buffer[16]==send_data.send_inf.Data[8])) 
										{
										p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else 
										{
										printf("T-625-Inf no answer\n");
										p->cmd_625.T625_on_off=1;
										p->SOST625=3;
										p->work_com[c_step].s[i].status=3;
										}
										break;
						//------------Ustanovit' svyaz' s AK END-----------------------------------
						case 101: if (p->work_com[c_step].s[i].status==0) //na4alo vipolneni9
                                    {    
                                        p->work_com[c_step].s[i].status=2;
                                    }
                                    break;
							
							default: 
									if(p->verbose) printf("Bad minicom %d for %d chan : %d",p->work_com[c_step].s[i].n_com,N_CHAN);					
									p->work_com[c_step].s[i].status=3;
									
						}//switch (n_com)
						//-------------------------------------------------------
                        //esli previweno vrem9 ozhidani9
						//if ((p->work_com[c_step].s[i].status==1)&&(p->work_com[c_step].s[i].t_stop>p->sys_timer)) p->work_com[c_step].s[i].status=3;
                        
						//-------------------------------------------------------						
					}//ewe ne vipoln9li
		
					//if (p->work_com[c_step].s[i].w_answ[0]==2) //esli nado gdat' otveta
					//if (p->work_com[c_step].s[i].w_answ[1]=1)
					//-------VREMENNO PRIEM DANNIH-------------------------------
					//-----------------------------------------------------------				
			} //step>0
			else 
			{
				timer2++;
				if (timer2 == 100) // primerno 5 sec
				{
					send_zapros();
					Udp_Client_Send(&Uc41,&read_7118,sizeof(read_7118));
					p->SOST625=1;
					for (ii=0;ii<sizeof(read_7118);ii++) read_7118.bufcom[ii]=0;
					local_timer=p->sys_timer;
					bytes=0;
					while  ((( bytes = Udp_Client_Read(&Uc41,&read_7118,sizeof(read_7118)))<=0)&&((p->sys_timer-local_timer)<time625)) delay(5);
						if (bytes>0)
						{
							p->SOST625=2; 
							p->cmd_625.count625_cmd++;
							p->toMN3.sost_spiak.T625=1;//ispravno T625
							if(read_7118.O_na_zapros.Tip==0x2)
							{
								p->toMN3.sost_spiak.rabota=p->toMN3.sost_spiak.reset=p->toMN3.sost_spiak.regl=0;
								p->toMN3.sost_spiak.konez=p->toMN3.sost_spiak.kontr=0; 
								p->cmd_625.T625_ok_nok= read_7118.O_na_zapros.Sost;
								p->cmd_625.T625_Result= read_7118.O_na_zapros.Opt;
								//printf (" T625 : sostoyanie-0x%02x   rshim raboti-%d   dlina-  %d  schetchik komand-  %d\n",
								//p->cmd_625.T625_ok_nok, // sostoyanie 64 = 1 0x40
								//p->cmd_625.T625_Result, // reshim raboti
								//read_7118.O_na_zapros.Dlina, //dlina
								//p->cmd_625.count625_cmd);
								
								printf (" T625 : ");
								if (p->cmd_625.T625_ok_nok==0x40) p->toMN3.sost_spiak.ispr=1;
								else p->toMN3.sost_spiak.ispr=0;
								switch (p->cmd_625.T625_Result)
								{
									case 0: printf (" work");
									p->toMN3.sost_spiak.rabota=1;
									break;
									case 1: printf (" reboot");
									p->toMN3.sost_spiak.reset=1;
									break;
									case 2: printf (" reglament");
									p->toMN3.sost_spiak.regl=1;
									break;
									case 3: printf (" finish");
									p->toMN3.sost_spiak.konez=1;
									break;
									case 4: printf (" control");
									p->toMN3.sost_spiak.kontr=1;
									break;
								}
								printf("\n");
							}
						}
						else 
						{
							//printf("T625resul =%x T625ok =%x \n", p->cmd_625.T625_Result, p->cmd_625.T625_ok_nok);
							printf("T-625-Rqst no answer\n");
							p->cmd_625.T625_on_off=1;
							p->SOST625=3;
							p->toMN3.sost_spiak.T625=0; //ne ispravno T625
						}
					timer2 =0;
				}
			}
			timer3++;
			if (timer3 > 5) // zapros dannih c T-625
			{
				//printf("bytes=%d p->cmd_625.count625_inf=%d \n",bytes,p->cmd_625.count625_inf);
				bytes = Udp_Client_Read(&Uc42,&read_data,sizeof(read_data));
				if (bytes>0) 
				{	
					p->cmd_625.count625_inf++;
					printf("bytes=%d p->cmd_625.count625_inf=%d \n",bytes,p->cmd_625.count625_inf);
					for (iii=0;iii<bytes/2;iii++) printf("%04x ",read_data.buffer[iii]);printf("\n");
					for (iii=0;iii<bytes/2;iii++) printf("%04x ",send_data.buffer[iii]);printf("\n");
				}
				timer3 = 0;
			}
		}//timer
	}//while
	
}


//-------------------------------------1H--------------------------------------------------------
//------ яюфёўхЄ ъюэЄЁюы№эющ ёєьь√ --------------------------------
    void  KSumPrm(int size_all)
{   int i;
	unsigned int ksum=0;
	for( i=0;i < (size_all-2);i++)			ksum=ksum*3+send_data.buffer[i];
	send_data.buffer[size_all-2] = ksum;
	send_data.buffer[size_all-1] = ksum>>16;
}
int  Initinf (unsigned short size) // 0<=size<=50
{
	int y,z,virav=0;
	printf("size = %d \n", size);
	//for(y=0; y<62; y++) send_data.buffer[y] =0; 
	send_data.send_inf.OICH=(size+9)*16;    //????
    send_data.send_inf.Protokol=0x0400;
    send_data.send_inf.N_Port=0;
    send_data.send_inf.N_Can=0;
	send_data.send_inf.Sach.ps = 1;
	//----------------------------SACH------------------------------------
	if (p->fromMN3.a_params[1]!=0) // esli p[rinznak ustanovki vremeni ne reven 0
	{
		send_data.send_inf.Sach.vr =1; //priznak ustanovki vremeni v sach
		send_data.send_inf.Sach.v0 = ( ( p->fromMN3.a_params[1] % 3600 ) / 60 ) % 10; 
		send_data.send_inf.Sach.v1 = ( ( p->fromMN3.a_params[1] % 3600 ) / 60 ) / 10;
		send_data.send_inf.Sach.v2 = ( p->fromMN3.a_params[1] / 3600 ) % 10 ;
		send_data.send_inf.Sach.v3 = ( p->fromMN3.a_params[1] / 3600 ) / 10;
	}
	else send_data.send_inf.Sach.vr = send_data.send_inf.Sach.v0 = send_data.send_inf.Sach.v1 = send_data.send_inf.Sach.v2 = send_data.send_inf.Sach.v3 = 0;
	
	send_data.send_inf.Sach.rez1 = 0;
	send_data.send_inf.Sach.kvi = 2; 
	send_data.send_inf.Sach.rez2 = 0;
	send_data.send_inf.Sach.nf = 193;
	
	send_data.send_inf.Sach.a0 = ( ( ( ( ( p->fromMN3.a_params[2] % 1000000 ) % 100000 ) % 10000 ) % 1000) % 100) % 10;
	send_data.send_inf.Sach.a1 = ( ( ( ( ( p->fromMN3.a_params[2] % 1000000 ) % 100000 ) % 10000 ) % 1000) % 100) / 10;
	send_data.send_inf.Sach.a2 = ( ( ( ( p->fromMN3.a_params[2] % 1000000 ) % 100000 ) % 10000 ) % 1000) / 100;
	send_data.send_inf.Sach.a3 = ( ( ( p->fromMN3.a_params[2] % 1000000 ) % 100000 ) % 10000 ) / 1000;

	send_data.send_inf.Sach.a4 = ( ( p->fromMN3.a_params[2] % 1000000 ) % 100000 ) / 10000;
	send_data.send_inf.Sach.a5 = ( p->fromMN3.a_params[2] % 1000000 ) / 100000;
	send_data.send_inf.Sach.p0 = ( ( ( ( ( p->fromMN3.a_params[3] % 1000000 ) % 100000 ) % 10000 ) % 1000) % 100) % 10;
	send_data.send_inf.Sach.p1 = ( ( ( ( ( p->fromMN3.a_params[3] % 1000000 ) % 100000 ) % 10000 ) % 1000) % 100) / 10;

	send_data.send_inf.Sach.p2 = ( ( ( ( p->fromMN3.a_params[3] % 1000000 ) % 100000 ) % 10000 ) % 1000) / 100;
	send_data.send_inf.Sach.p3 = ( ( ( p->fromMN3.a_params[3] % 1000000 ) % 100000 ) % 10000 ) / 1000;
	send_data.send_inf.Sach.p4 = ( ( p->fromMN3.a_params[3] % 1000000 ) % 100000 ) / 10000;
	send_data.send_inf.Sach.p5 = ( p->fromMN3.a_params[3] % 1000000 ) / 100000;

	p->count_cpp_message++;
	send_data.send_inf.Sach.r0 = ( ( ( p->count_cpp_message % 10000 ) % 1000 ) % 100 ) % 10;
	send_data.send_inf.Sach.r1 = ( ( ( p->count_cpp_message % 10000 ) % 1000 ) % 100 ) / 10;
	send_data.send_inf.Sach.r2 = ( ( p->count_cpp_message % 10000 ) % 1000 ) / 100;
	send_data.send_inf.Sach.r3 = ( p->count_cpp_message % 10000 ) / 1000;
   //------------------------------DATA-----------------------------------------------------
	//for (z=0; z<=size; z++) send_data.send_inf.Data = buf[z];
	if (size%2!=0) virav = 1;
	
	//------------------------CHECK SUMM-----------------------------------------------------
	
	KSumPrm(size+virav+12);
	//printf("size = %d virav = %d \n", size, virav);
	//printf(" return %d \n", (2*(size+virav+12)));
	for (y=0; y<size+virav+12; y++)	
	{
		printf("%04x ", send_data.buffer[y]);
		if (y==3) printf("\n");
		if (y==9) printf("\n");
		if (y==(size+virav+9)) printf("\n");
	}
	printf("\n");
	return (2*(size+virav+12));
}

int  send_zapros()
{    read_7118.Read_com.Dlina=0x14;
	 read_7118.Read_com.Ident=0x00;
     read_7118.Read_com.Parol_ml=11;
     read_7118.Read_com.Zapros=1;
	 read_7118.Read_com.Error=0x0;
     read_7118.Read_com.Protokol=0x0030;
     read_7118.Read_com.Tip=0x0001;
	 read_7118.Read_com.Parol_st=0x00;
     read_7118.Read_com.T625=0x40;
	 read_7118.Read_com.Reserv=0x00;
     read_7118.Read_com.CVM_A=0x60;
     return 1;
    }
int send_SVCH()
{   
	read_7118.Read_com.Dlina=20;
	read_7118.Read_com.Ident=17;
    read_7118.Read_com.Parol_ml=0;
    read_7118.Read_com.Zapros=2;
    read_7118.Read_com.Protokol=0x30;
    read_7118.Read_com.Tip=0x110;
    read_7118.Read_com.T625=0x40;
	read_7118.Read_com.Reserv=0;
    read_7118.Read_com.CVM_A=0x60;
    return 1;
 }
int send_DMW()
{    read_7118.Read_com.Dlina=20;
	 read_7118.Read_com.Ident=17;
     read_7118.Read_com.Parol_ml=0;
     read_7118.Read_com.Zapros=2;
     read_7118.Read_com.Protokol=0x30;
     read_7118.Read_com.Tip=0x112;
     read_7118.Read_com.T625=0x40;
	 read_7118.Read_com.Reserv=0;
     read_7118.Read_com.CVM_A=0x60;
     return 1;
  }   