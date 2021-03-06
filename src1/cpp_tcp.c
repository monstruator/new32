  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/kernel.h>

  #include <netinet/in.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <netdb.h>
  #include <math.h>
  #include "../include/shared_mem.h"
  #include "../include/USOIwrk.h"
  #include "../include/CrSocket.h"
  #include "../include/MesForm.h" 

#define TIMEOUT_SEC		   0L	//0 ᥪ㭤
#define TIMEOUT_NSEC	10000000L	//����. �६� �������� 10 ��
#define LENBUFWR	80	//����� ���� ��।��
#define LnTitle		32		//����� ���������
#define LENBUFRD 	1400	//����� ���� �ਥ��
#define LnKdr	   512	//���� �᫮ ᫮�(2 ����) � ����
#define MaxKdr	  10000	//���� �᫮ �࠭���� ���஢
		  


  
#define MS 1000000
#define N_CHAN 2 //CPP SPC

#ifdef __USAGE
		  HELP�

	#endif
	
un short bufW [LENBUFWR], bufR [LENBUFRD];
pid_t proxy_time;
volatile un counter;
struct zag_CPP mes_cpp, *mes_fcpp;
struct from_cpp12 *f12;
struct to_cpp11 f11;
timer_t  tm10;
struct sigevent event_sig;
struct itimerspec timer_sig;
unsigned short *aaa,*bbb;
unsigned short ccc[100]={0xFFFF,0xFFFF,0x0B00,0x0203,0x0001,0x000B,0x0000,0x0000,0x0000,
						 0x0001,0x0000,0x0010,0x0010,0x010D,0x0001,0x00FF,0x0001,0x0001,
						 0x0001,0x01f8,0,0,0,0,0,0,0};
unsigned char work_point[6]={0x10,0x34,0x55,0x76,0x97,0xB8};

int T_ALRM =0; //prizn srabativani9 taimera
char *Host="CPP0_1",*port="4003";
int timer1=0;

int Seans=0; 
//--------- timer 50ms -----------------------------
pid_t far handler_time()
{
  if (( ++counter % 2)==0)	return (proxy_time);	
  return (0);			
} 
//------------------ SIGNAL --------------------------------
void SigHandler ( int signal_number )	
{
	if (p->verbose>2) printf("\n%s.    seanse: %d error",Host,Seans);
	//T_ALRM=1; 
}

short tcp_send_read(int );
short tcp_reqest(int );
//===============================================================================
//			MAIN	MAIN	MAIN	MAIN 	MAIN
main(int argc, char *argv[])
{
	
	int n,i,j,col,command,i1;
	
	packusoi p1;
    packcmd p2;
    short c_step=0,T0=0;	
    long cpp_timer=0;
    int data_read; //4tenie dannih 
	struct form193 *f193;
	int ustSS=0; // ustanovlennoe zna4enie
	//===============================================================================
	//			 timer 10ms
	event_sig.sigev_signo = SIGALRM;
	tm10 = timer_create(CLOCK_REALTIME,&event_sig ); // �������� ������� 
	if (tm10==-1) printf("\ntimer opening error: %s",strerror(errno));
	timer_sig.it_value.tv_sec        = 0L;
	timer_sig.it_value.tv_nsec       = 0L;
	timer_sig.it_interval.tv_sec     = 0L;
	timer_sig.it_interval.tv_nsec    = 0L;
	signal ( SIGALRM, SigHandler );

	//create_shmem();
	delay(2500);
	open_shmem();
	delay(1000);
	
	if (argc<3) 
	{
		if (p->cvs==10)	{		Host="CPP0_1";		port="4004"; 	}//4004	
		else			{		Host="CPP2";		port="4003"; 	}//4003			
		//else			{		Host="CPP0_1";		port="4004"; 	}//4003
		//printf("\nhost and port number dont entering\n");
	}
	else 
	{	
		memcpy(Host,argv[1],5);
		memcpy(port,argv[2],5);
	}	
	printf("START MO3A<->CPP Host=%s port=%s cvs=%d\n\n",Host,port,p->cvs);
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
						printf("if 1 ok status %d \n", p->work_com[c_step].s[i].status);
						if((p->verbose>1)&&(p->work_com[c_step].s[i].status==0)) printf("\nSTEP=%d    minicom for CPP : %d      status=%d time %d \n", p->cur_step,  p->work_com[c_step].s[i].n_com, p->work_com[c_step].s[i].status, p->sys_timer);
						memset((char *)&f11, 0, sizeof(struct to_cpp11));
						f11.zag.marker1=0xFFFF;
						f11.zag.marker2=0xFFFF;
						if (p->cvs==11) f11.zag.II=2; else f11.zag.II=3;
						f11.zag.TS=3;
						f11.zag.PS=1;
						//f11.zag.reserv=sizeof(struct form11)/2;
						f11.zag.KSS=sizeof(struct form11)/2;
						f11.data.nf=11;
						
						//if(p->verbose) printf("		KSS=%d %x\n",f11.zag.KSS,f11.zag.KSS);
						col = sizeof(f11);
						
						switch(p->work_com[c_step].s[i].n_com)
						{
							case 1: p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("			SVCH work \n");
									if (p->fromMN3.a_params[0]==1) 
										{
										f11.data.KU0=ustSS=0; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
										f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										}
									else {
										f11.data.ustKU0=1;
										f11.data.KU0=ustSS=1;
										}
									//col = sizeof(f11);
									col=tcp_send_read(col);
									if ((f12->data.SS1==ustSS)&&(col==0x14)&&(f12->data.SS0_all==1)) //(p->SS1==(p->work_com[n_s].s[n_mc].n_com==60)&&(p->fromMN3.a_params[0]==1)) //esli otet=sosto9nie 
									{
										//if (f12->data.SS0_all) 
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
									printf("param = %d SS1 =  %d     col %d    SSo_all %d ustSS %d \n", p->fromMN3.a_params[0] , f12->data.SS1, col , f12->data.SS0_all, ustSS);
                                    printf("col=%d status=%d\n",col/2,p->work_com[c_step].s[i].status);
									break;
							case 5: p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("			SVCH PRD-PRM CHAN \n");
									f11.data.KU6=f11.data.KU5=work_point[p->fromMN3.a_params[0]-1]; //// RT PRD 1 - 6
									f11.data.ustKU5=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									//f11.data.KU6=p->fromMN3.a_params[0]+6; //// RT PRM 7 - 13
									f11.data.ustKU6=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									printf("ustKU6 = %d  ustKU5 = %d \n",f11.data.ustKU6, f11.data.ustKU5);
									printf("status = %d  SSoprm = %d \n",p->work_com[c_step].s[i].status, f12->data.SS0_prm);
									//printf("SS4=%d SS5=%d \n",f12->data.SS4,f12->data.SS5);
									//p->work_com[n_s].t_stop =p->sys_timer+100;
									//col=tcp_send_read(col);
									if ((col==0x14)&&(p->fromMN3.a_params[0]==f12->data.SS4)) //esli otet=sosto9nie 
									{
										//if(p->verbose>1) printf("SS4=%d SS5=%d \n",f12->data.SS4,f12->data.SS5);
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									
									else p->work_com[c_step].s[i].status=3;
									printf("T_ALRM = %d n = %d col = %d param = %d  ss4 = %d \n",T_ALRM, n , col, p->fromMN3.a_params[0], f12->data.SS4);
									
                                    break;
							case 8: p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("			FM SHPS\n");
									f11.data.KU4=p->fromMN3.a_params[0]; //  0 - FM1, 1 - FM2 
									f11.data.ustKU4=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									if ((col==0x14)&&(p->fromMN3.a_params[0]==f12->data.SS3)) //esli otet=sosto9nie 
									{
										//if (f12->data.SS0_all) 
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
                                    if(p->verbose) printf("col=%d status=%d\n",col/2,p->work_com[c_step].s[i].status);
									break;
							case 12: 	
									/*p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("			SVCH TKI-RLI \n");
									f11.data.KU3=p->fromMN3.a_params[0]; //  0 - TKI, 1 - RLI 
									f11.data.ustKU3=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									printf("SS21=%d\n",f12->data.SS2_1);
									printf("param1=%d\n",p->fromMN3.a_params[0]);
									if ((col==0x14)&&(p->fromMN3.a_params[0]==f12->data.SS2_1)) //esli otet=sosto9nie 
									{
									printf("SS22=%d\n",f12->data.SS2_1);
									printf("param2=%d\n",p->fromMN3.a_params[0]);
										if(p->verbose>1) printf("SS2=%d\n",f12->data.SS2_1);
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
                                    break;
									*/
									if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("			SVCH TKI-RLI \n");
										f11.data.KU3=p->fromMN3.a_params[0]; //  0 - TKI, 1 - RLI 
										f11.data.ustKU3=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										col=tcp_send_read(col);
										//printf("SS2=%d\n",f12->data.SS2_1);
										//printf("param=%d\n",p->fromMN3.a_params[0]);
										p->work_com[c_step].t_start = p->sys_timer;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start > 100))
									{
										f11.zag.KSS=0;
										col = sizeof(struct zag_CPP);
										col=tcp_send_read(col);
										//printf("col=%d\n",col);
										if ((col==0x14)&&(p->fromMN3.a_params[0]==f12->data.SS2_1)) //esli otet=sosto9nie 
										{
											printf("SS2=%d\n",f12->data.SS2_1);
											//printf("param2=%d\n",p->fromMN3.a_params[0]);
											if(p->verbose>1) printf("SS2=%d\n",f12->data.SS2_1);
											//printf("OK1");
											p->work_com[c_step].s[i].status=2; // ispravnost'
											//printf("OK2/n");
										}
										else p->work_com[c_step].s[i].status=3;
									} 	
							/////////
									
                                    break;
							case 14: p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("			PRIEM ONN\n");
									f11.data.KU2=p->fromMN3.a_params[0]; 
									f11.data.ustKU2=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU1=0; 
									f11.data.ustKU1=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									printf("SS2_prm1=%d\n",f12->data.SS2_0);
									printf("param_prm1=%d\n",p->fromMN3.a_params[0]);
									if ((col==0x14)&&(p->fromMN3.a_params[0]==f12->data.SS2_0)) //esli otet=sosto9nie 
									{
										printf("SS2_prm2=%d\n",f12->data.SS2_0);
										printf("param_prm2=%d\n",p->fromMN3.a_params[0]);
										if(p->verbose>1) printf("SS2=%d\n",f12->data.SS2_0);
										printf("ok=%d\n",p->fromMN3.a_params[0]);
										p->work_com[c_step].s[i].status=2; // ispravnost'
										printf("ok=%d\n",p->fromMN3.a_params[0]);
									}
									else p->work_com[c_step].s[i].status=3;
									printf("ok=%d\n",p->fromMN3.a_params[0]);
                                    break;
							case 15: p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("			PEREDA4A ONN\n");
									f11.data.KU1=p->fromMN3.a_params[0];
									f11.data.ustKU1=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU2=0; 
									f11.data.ustKU2=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									printf("SS2_prd1=%d\n",f12->data.SS2_0);
									printf("param_prd1=%d\n",p->fromMN3.a_params[0]);
									if ((col==0x14)&&(p->fromMN3.a_params[0]==f12->data.SS2_0)) //esli otet=sosto9nie 
									{	
										printf("SS2_prd_2=%d\n",f12->data.SS2_0);
										printf("param_prd2=%d\n",p->fromMN3.a_params[0]);
										if(p->verbose>1) printf("SS2=%d\n",f12->data.SS2_0);
										printf("ok1=%d\n",p->fromMN3.a_params[0]);
										p->work_com[c_step].s[i].status=2; // ispravnost'
										printf("ok2=%d\n",p->fromMN3.a_params[0]);
									}
									else p->work_com[c_step].s[i].status=3;
									printf("ok3=%d\n",p->fromMN3.a_params[0]);
                                    break;
							case 30: p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("			SVCH ATT \n");
									f11.data.KU7=p->fromMN3.a_params[0]; // oslablenie 0 - 25
									f11.data.ustKU7=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									if ((col==0x14)&&(p->fromMN3.a_params[0]==f12->data.SS6)) //esli otet=sosto9nie 
									{
										if(p->verbose>1) printf("SS6=%d\n",f12->data.SS6);
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
                                    break;
							case 32: case 42: p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("		porog	MI \n");
									f11.data.KU10=p->fromMN3.a_params[0]; // porog MI 1 - 15
									f11.data.ustKU10=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									if ((col==0x14)&&( p->fromMN3.a_params[0]==f12->data.SS12))//esli otet=sosto9nie 
									{
										if(p->verbose>1) printf("SS6=%d\n",f12->data.SS12);
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
                                    break;
							case 33: case 43: p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("		porog	SS \n");
									f11.data.KU11=p->fromMN3.a_params[0]; // porog SS 1 - 15
									f11.data.ustKU11=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									if ((col==0x14)&&( p->fromMN3.a_params[0]==f12->data.SS11)) //esli otet=sosto9nie 
									{
										if(p->verbose>1) printf("SS6=%d\n",f12->data.SS11);
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
                                    break;
							case 61: p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("			SVCH status \n");
									f11.zag.KSS=0;
									col = sizeof(struct zag_CPP);
									col=tcp_send_read(col);
									if (col==0x14) //esli otet=sosto9nie 
									{
										//if (f12->data.SS0_all) 
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
                                    //printf("col=%d status=%d\n",col/2,p->work_com[c_step].s[i].status);
									break;
							case 65 : 
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									if(p->verbose) printf("		FK %d \n",p->fromMN3.a_params[0]);
									f11.data.KU0=1; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
									f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU8=p->fromMN3.a_params[0]; //FK 1 - 12
									f11.data.ustKU8=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									if ((col==0x14)&&(p->fromMN3.a_params[0]==f12->data.SS7)&&(f12->data.SS1==1)) //esli otet=sosto9nie 
									{
										if (f12->data.SS0_prm==0) p->toMN3.fk=1;
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
								}
								break;
							case 66 : 
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									if(p->verbose) printf("		FK 2 \n");
									f11.data.KU0=1; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
									f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU1=1; 	f11.data.ustKU1=1; //prd
									f11.data.KU2=0; 	f11.data.ustKU2=1; //prm
									f11.data.KU3=1; 	f11.data.ustKU3=1; //tki
									//f11.data.KU6=0; 	f11.data.ustKU6=1; //att
									f11.data.KU8=2; 	f11.data.ustKU8=1;  //fk
									col=tcp_send_read(col);
								
									if ((col==0x14)&&(f12->data.SS7==2)&&(f12->data.SS1==1)&&(f12->data.SS2_0==4)&&(f12->data.SS2_1==1)&&(f12->data.SS6==0)) //esli otet=sosto9nie 
									{
										if (f12->data.SS0_prm==0) p->toMN3.fk=1;
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
									if(p->verbose>1) printf(" ---- SS7=%d SS1=%d SS2_0=%d SS2_1=%d SS6=%d ----\n",f12->data.SS7,f12->data.SS1,f12->data.SS2_0,f12->data.SS2_1,f12->data.SS6);
								}
								break;
							case 67 : //A1 cpp FK3
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									if(p->verbose) printf("		FK3 \n");
									f11.data.KU0=1; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
									f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									
									col=tcp_send_read(col);
								
									if ((col==0x14)&&(f12->data.SS0_all==1)&&(f12->data.SS0_cpp==1)&&(f12->data.SS0_prm==1)&&(f12->data.SS0_prd==1)&&(f12->data.SS1==1)&&(f12->data.SS2_0==0)&&(f12->data.SS2_1==0)&&(f12->data.SS3==0)) //esli otet=sosto9nie 
									{
										//if (f12->data.SS0_prm==0) p->toMN3.fk=1;
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
									//if(p->verbose>1) printf(" ---- SS7=%d SS1=%d SS2_0=%d SS2_1=%d SS6=%d ----\n",f12->data.SS7,f12->data.SS1,f12->data.SS2_0,f12->data.SS2_1,f12->data.SS6);
								}
								break;
							case 68 : //A2 cpp FK3
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									if(p->verbose) printf("		FK3 \n");
									f11.data.KU0=1; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
									f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									
									col=tcp_send_read(col);
								
									if ((col==0x14)&&(f12->data.SS0_all==1)&&(f12->data.SS0_cpp==1)&&(f12->data.SS0_prm==1)&&(f12->data.SS0_prd==0)&&(f12->data.SS1==1)&&(f12->data.SS2_0==0)&&(f12->data.SS2_1==0)&&(f12->data.SS3==0)) //esli otet=sosto9nie 
									{
										//if (f12->data.SS0_prm==0) p->toMN3.fk=1;
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
									//if(p->verbose>1) printf(" ---- SS7=%d SS1=%d SS2_0=%d SS2_1=%d SS6=%d ----\n",f12->data.SS7,f12->data.SS1,f12->data.SS2_0,f12->data.SS2_1,f12->data.SS6);
								}
								break;
							case 90: //SVCH work
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									if(p->verbose) printf("			SVCH work \n");
									f11.data.KU0=0; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
									f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU2=1; //priem : 1 - vkl, 0 - otkl 
									f11.data.ustKU2=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU3=0;//  0 - TKI, 1 - RLI 
									f11.data.ustKU3=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU7=0;//  oslablenie 0 - 25
									f11.data.ustKU7=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									//col = sizeof(f11);
									col=tcp_send_read(col);
							
									if ((col==0x14)&&(f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS1==0)&&(f12->data.SS2_0==0)&&(f12->data.SS2_1==0)&&(f12->data.SS6==0))  //esli otet pravilnii 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
								}
								break;
								
							case 93: //ust svyaz' s AK
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									f11.zag.TS=3;
									f11.zag.II=2;
									f11.zag.KSS=15;
									f11.zag.PS=1;
									f11.data.KU0=1; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
									f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU2=1;
									f11.data.ustKU2=1;
									f11.data.KU3=0;
									f11.data.ustKU3=1;
									f11.data.KU7=0;
									f11.data.ustKU7=1;
									f11.data.KU8=13;
									f11.data.ustKU8=1;
									col=tcp_send_read(col);
							
									if ((col==0x14)&&(f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS0==1111)&&(f12->data.SS1==1)&&(f12->data.SS2_1==0)&&(f12->data.SS2_0==1)&&(f12->data.SS6==0)&&(f12->data.SS8==0)&&(f12->data.SS9==0))  //esli otet pravilnii 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
								}
								break;
								
							case 93: //ust svyaz' s AK
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									f11.zag.TS=3;
									f11.zag.KSS=15;
									f11.zag.II=2;
									f11.zag.PS=1;
									f11.data.KU0=0; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
									f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU2=0;
									f11.data.ustKU2=1;
									f11.data.KU3=1;
									f11.data.ustKU3=1;
									f11.data.KU7=0;
									f11.data.ustKU7=1;
									col=tcp_send_read(col);
							
									if ((col==0x14)&&(f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS0==1111)&&(f12->data.SS1==0)&&(f12->data.SS2_1==0)&&(f12->data.SS2_0==1)&&(f12->data.SS6==0)&&(f12->data.SS8==0)&&(f12->data.SS9==0))  //esli otet pravilnii 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
								}
								break;
								
								case 931: //ust svyaz' s AK
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									f11.zag.TS=20;
									f11.zag.PS=1;
									col=tcp_send_read(col);
							
									if ((col==0x14)&&(f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS8==1))  //esli otet pravilnii 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else 
									{
									p->work_com[c_step].s[i].status=3;
									printf(" SS13 = %d SS14 = %d SS15 = %d SS16 = %d SS17 = %d SS18 = %d\n SS19 = %d SS20 = %d SS21 = %d\n", f12->data.SS13,f12->data.SS14,f12->data.SS15,f12->data.SS16,f12->data.SS17,f12->data.SS18,f12->data.SS19,f12->data.SS20,f12->data.SS21);
								}
								break;
								
							case 103: if (p->work_com[c_step].s[i].status==0) //na4alo vipolneni9
                                    {   
                                        printf("Send to 1 chan\n");
                                        //p->work_com[c_step].s[i].t_start=p->sys_timer; // vrem9 starta
                                        //p->work_com[c_step].s[i].t_stop =p->sys_timer+300; //stop ne pozdnee
                                        T0=0; //ots4et vremeni (vremenno)
                                        p->work_com[c_step].s[i].status=1;
                                    }
                                    if (p->work_com[c_step].s[i].status==1) //zdem otveta
                                    {   
                                        if (data_read==1) //bilo 4tenie 
                                        {
                                            p->work_com[c_step].s[i].status=2;
                                            data_read=0;
                                        }
                                    }
                                    break;
							case 101: if (p->work_com[c_step].s[i].status==0) //na4alo vipolneni9
                                    {    
                                        if(p->verbose) printf("Check CPP link (TC=0)\n");
										//tcp_send_read();
                                        p->work_com[c_step].s[i].status=2;
                                    }
                                    break;
									
							/*case 93: if (p->work_com[c_step].s[i].status==0) //na4alo vipolneni9
                                    {   
										memset( f193, 0, sizeof(struct sac) );
										f193->s.ps = 1;
										if( p->fromMN3.a_params[1] ) {
										f193->s.vr = 1;
										f193->s.v0 = ( ( p->fromMN3.a_params[1] % 3600 ) / 60 ) % 10;
										f193->s.v1 = ( ( p->fromMN3.a_params[1] % 3600 ) / 60 ) / 10;;
										f193->s.v2 = ( p->fromMN3.a_params[1] / 3600 ) % 10 ;
										f193->s.v3 = ( p->fromMN3.a_params[1] / 3600 ) / 10;
										}
										else f193->s.vr = 0;
										f193->s.kvi = 2;
										f193->s.nf = 193;
										p->count_cpp_message++;
										f193->s.r0 = ( ( ( p->count_cpp_message % 10000 ) % 1000 ) % 100 ) % 10;
										f193->s.r1 = ( ( ( p->count_cpp_message % 10000 ) % 1000 ) % 100 ) / 10;
										f193->s.r2 = ( ( p->count_cpp_message % 10000 ) % 1000 ) / 100;
										f193->s.r3 = ( p->count_cpp_message % 10000 ) / 1000;										
										
										f193->a0 = ( ( ( ( p->fromMN3.a_params[2] % 100000 ) % 10000 ) % 1000 ) % 100 ) % 10;
										f193->a1 = ( ( ( ( p->fromMN3.a_params[2] % 100000 ) % 10000 ) % 1000 ) % 100 ) / 10;
										f193->a2 = ( ( ( p->fromMN3.a_params[2] % 100000 ) % 10000 ) % 1000 ) / 100;
										f193->a3 = ( ( p->fromMN3.a_params[2] % 100000 ) % 10000 ) / 1000;
										f193->a4 = ( p->fromMN3.a_params[2] % 100000 ) / 10000;
										f193->a5 = p->fromMN3.a_params[2] / 100000;
										f193->p0 = ( ( ( ( p->fromMN3.a_params[3] % 100000 ) % 10000 ) % 1000 ) % 100 ) % 10;
										f193->p1 = ( ( ( ( p->fromMN3.a_params[3] % 100000 ) % 10000 ) % 1000 ) % 100 ) / 10;
										f193->p2 = ( ( ( p->fromMN3.a_params[3] % 100000 ) % 10000 ) % 1000 ) / 100;
										f193->p3 = ( ( p->fromMN3.a_params[3] % 100000 ) % 10000 ) / 1000;
										f193->p4 = ( p->fromMN3.a_params[3] % 100000 ) / 10000;
										f193->p5 = p->fromMN3.a_params[3] / 100000;
										
										p->a0_cpp=f193->a0;  //�������� �����
										p->a1_cpp=f193->a1;
										p->a2_cpp=f193->a2;
										p->a3_cpp=f193->a3;
										p->a4_cpp=f193->a4;
										p->a5_cpp=f193->a5;
										p->p0_cpp=f193->p0;
										p->p1_cpp=f193->p1;
										p->p2_cpp=f193->p2;
										p->p3_cpp=f193->p3;
										p->p4_cpp=f193->p4;
										p->p5_cpp=f193->p5;
										
										f193.t2=0x1d; 
										
										//f193.pn=0;
										f193.kfs=43; 	
										//f193.x=0; 
										//f193.y=0;
										//f193.k=0;
										//f193.speed=0;
										
										f11.zag.TS=3;
										f11.zag.II=2;
										f11.zag.KSS=sizeof(struct form11)/2;
										f11.zag.PS=1;
										f11.data.KU0=0; f11.data.ustKU0=1; 
										f11.data.KU1=0; f11.data.ustKU1=1;
										f11.data.KU2=0; f11.data.ustKU2=1;
										f11.data.KU3=1; f11.data.ustKU3=1;
										f11.data.KU4=0; f11.data.ustKU4=1;
										f11.data.KU5=1; f11.data.ustKU5=1;
										f11.data.KU6=7; f11.data.ustKU6=1;
										f11.data.KU7=0; f11.data.ustKU7=1;
										f11.data.KU8=0; f11.data.ustKU8=1;
										f11.data.KU9=0; f11.data.ustKU9=1;
										f11.data.KU10=0; f11.data.ustKU10=1;
										f11.data.KU11=0; f11.data.ustKU11=1;
										f11.data.KU12=0; f11.data.ustKU12=1;
										
										  										
                                    }
                                    break;*/
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
					T0++;
					if (T0==30)
					{
						T0=0;	
						data_read=1;
					}		
					//-----------------------------------------------------------			
			}  //step>0
			else	{
//--------------------------reqets timer start----------------------------------------------------
			timer1++;
			if (timer1 == 100) {
			
			timer1 = 0;
			f11.zag.marker1=0xFFFF;
			f11.zag.marker2=0xFFFF;
			if (p->cvs==11) f11.zag.II=2; else f11.zag.II=3;
			f11.zag.TS=3;
			f11.zag.PS=1;
			f11.zag.KSS=sizeof(struct form11)/2;
			f11.data.nf=11;
						
			col = sizeof(f11);
			
			//p->work_com[c_step].s[i].status=1;
            //if(p->verbose) printf("			SVCH status \n");
			f11.zag.KSS=0;
			col = sizeof(struct zag_CPP);
			col=tcp_reqest(col);
			printf("SS10 %d SS19 %d SS20 %d\n", f12->data.SS10, f12->data.SS19,f12->data.SS20);						
			if (col==0x14) //esli otet=sosto9nie 
			{
			//if (f12->data.SS0_all) 
			//p->work_com[c_step].s[i].status=2; // ispravnost'
			}
			//else //p->work_com[c_step].s[i].status=3;
			}			
}			
		}//timer
	}//while
	timer_delete(tm10);
}


short tcp_send_read(int col)
{
	int sock1;
	short rez;
	int i,i1,n,j;
	short status,sum;

	//message
	/*mes_cpp.marker1=0xFFFF;
	mes_cpp.marker2=0xFFFF;
	mes_cpp.KSS=0;
	mes_cpp.II=0;
	mes_cpp.TS=0;
	mes_cpp.PS=1;
	*/

	//            starting connection
	for(i1=0;i1<3;i1++)
	{
		T_ALRM =0;
		timer_sig.it_value.tv_nsec = TIMEOUT_NSEC*5; //5*10ms
		rez=timer_settime( tm10, 0, &timer_sig,NULL); //start timer
		if (rez==-1)    printf("%s. seanse %d. start timer error\n",Host,Seans);     

		if (p->verbose>1) printf("Create Socket : %s", port);
		sock1 = CrSocket(Host,port);
		
		rez=1;
		if ((T_ALRM !=0)||(sock1==-1)) 
		{
			if (p->verbose>1) printf("error\n",Host,Seans);
			rez=0;
			//goto EndCeanc;
		}
		else 
		{
			if (p->verbose>1) printf("ok\n",Host,Seans);
			i1=3; //exit from "for"
		}
		timer_sig.it_value.tv_nsec = 0L;	timer_settime( tm10, 0, &timer_sig,NULL); // stop timer
		delay(100);
	}
	if (rez) //send message
	{
			i1=3; //exit from "for"
			T_ALRM =0;
			timer_sig.it_value.tv_nsec = TIMEOUT_NSEC*10;  
			timer_settime( tm10, 0, &timer_sig,NULL); ////start timer 
//-----------------------------------------------------------------
			bbb = (unsigned short *)&f11;
			sum=0;
			if (col>10) 
			{
				for(i=0;i<14;i++) sum^=bbb[i+5];
				//if(p->verbose>2) printf("ccc[%d]=%x CKH_SUM=%04x \n",i+5,ccc[i+5],sum);}
				bbb[col/2-1]=sum;
			}
			if(p->verbose>2) printf("CKH_SUM=%04x \n",sum);
			if(p->verbose>2) {printf("<-Send ");for(i1=0;i1<col/2;i1++) printf("%x ",bbb[i1]);printf("\n");}
			write(sock1, bbb, col);	Seans++;
			//sleep(500);
			//if(p->verbose>2) {printf("<-Send ");for(i1=0;i1<37;i1++) printf("%04x ",ccc[i1]);printf("\n");}
			//write(sock1, ccc, 54);	Seans++;
			n=read(sock1,bbb,1400);
			timer_sig.it_value.tv_nsec = 0L;	timer_settime( tm10, 0, &timer_sig,NULL); // ��⠭�� ⠩���
			close(sock1);
//-----------------------------------------------------------------			
			if ((n>0)&&(T_ALRM==0))
			{			
				if(p->verbose>1) {printf("->Read %d word : ",n/2); for (j=0;j<n/2;j++ ) printf(" %04x",bbb[j]); printf("\n");}
				//mes_fcpp = (struct zag_CPP *)bbb;
				f12 = (struct from_cpp12 *)bbb;
				if(p->verbose>1) printf("KSS=%d II=%d TS=%d      ", f12->zag.KSS,f12->zag.II,f12->zag.TS);
				switch(f12->zag.TS)
				{
					case 0x10 : if(p->verbose) printf("Check CPP link OK(TC=0x10)\n");
								break;
					case 0x11 : if(p->verbose) printf("Message loaded OK(TC=0x11)\n");
								break;
					case 0x12 : if(p->verbose) printf("Data recieved OK(TC=0x12)\n");
								break;
					case 0x13 : if(p->verbose) printf("No data from AK(TC=0x13)\n");
								break;
					case 0x14 : if(p->verbose) printf("CPP parameters (TC=0x14)\n");
								//if (f12->data.nf==12)
								{
									if(p->verbose>1) printf("SS0_prd=%d SS0_prm=%d SS0_cpp=%d SS0_all=%d \n",f12->data.SS0_prd,f12->data.SS0_prm,f12->data.SS0_cpp,f12->data.SS0_all);
									if(p->verbose>1) printf("SS1=%d SS2_0=%d SS2_1=%d SS3=%d SS4=%d SS5=%d SS6=%d SS7=%d\n",f12->data.SS1,f12->data.SS2_0,f12->data.SS2_1,f12->data.SS3,f12->data.SS4,f12->data.SS5,f12->data.SS6,f12->data.SS7);
									for(j=0;j<9;j++) p->toMN3.sost_kasrt[j]=f12->i.data_int[j];
									//if(p->verbose>1) printf("SS0=%x SS1=%x SS2=%x SS3=%x \n",p->toMN3.sost_kasrt[0],p->toMN3.sost_kasrt[1],p->toMN3.sost_kasrt[2],p->toMN3.sost_kasrt[3]);
										
									return 0x14;
								}
								//printf("nf=%d\n",f12->data.nf);
								
								break;
					default :   if(p->verbose) printf("Error TS (TC=%d)\n",f12->zag.TS);
								break;
			
				}
				
				
				if(p->verbose) printf("\n");
				//printf("nf=%d\n",f12->data.nf);
				p->toMN3.sost_spiak.Cpp=1; //ispavno CPP
				return f12->zag.TS;
			}
			else 
			{
				p->toMN3.sost_spiak.Cpp=0; //neispavno CPP
				return 0; //owibka soedineni9
			}//owibka priema
			T_ALRM=0;
	} //send-recieve
	else 
	{
		return 0; //owibka soedineni9
	
	}
	//delay(100);
	
	return 0;
}



//--------------------------------reqests---------------------------------------------------------------
//--------------------------------timer-----------------------------------------------------------------
short tcp_reqest(int col)
{
	int sock1;
	short rez;
	int i,i1,n,j;
	short status,sum;

	//message
	/*mes_cpp.marker1=0xFFFF;
	mes_cpp.marker2=0xFFFF;
	mes_cpp.KSS=0;
	mes_cpp.II=0;
	mes_cpp.TS=0;
	mes_cpp.PS=1;
	*/

	//            starting connection
	for(i1=0;i1<3;i1++)
	{
		T_ALRM =0;
		timer_sig.it_value.tv_nsec = TIMEOUT_NSEC*5; //5*10ms
		rez=timer_settime( tm10, 0, &timer_sig,NULL); //start timer
		if (rez==-1)    printf("%s. seanse %d. start timer error\n",Host,Seans);     

		//if (p->verbose>1) printf("Create Socket : %s", port);
		sock1 = CrSocket(Host,port);
		
		rez=1;
		if ((T_ALRM !=0)||(sock1==-1)) 
		{
			if (p->verbose>1) printf("error\n",Host,Seans);
			rez=0;
			//goto EndCeanc;
		}
		else 
		{
			//if (p->verbose>1) printf("ok\n",Host,Seans);
			i1=3; //exit from "for"
		}
		timer_sig.it_value.tv_nsec = 0L;	timer_settime( tm10, 0, &timer_sig,NULL); // stop timer
		delay(100);
	}
	if (rez) //send message
	{
			i1=3; //exit from "for"
			T_ALRM =0;
			timer_sig.it_value.tv_nsec = TIMEOUT_NSEC*10;  
			timer_settime( tm10, 0, &timer_sig,NULL); ////start timer 
//-----------------------------------------------------------------
			bbb = (unsigned short *)&f11;
			sum=0;
			if (col>10) 
			{
				for(i=0;i<14;i++) sum^=bbb[i+5];
				//if(p->verbose>2) printf("ccc[%d]=%x CKH_SUM=%04x \n",i+5,ccc[i+5],sum);}
				bbb[col/2-1]=sum;
			}
			//if(p->verbose>2) printf("CKH_SUM=%04x \n",sum);
			//if(p->verbose>2) {printf("<-Send ");for(i1=0;i1<col/2;i1++) printf("%x ",bbb[i1]);printf("\n");}
			write(sock1, bbb, col);	Seans++;
			//if(p->verbose>2) {printf("<-Send ");for(i1=0;i1<37;i1++) printf("%04x ",ccc[i1]);printf("\n");}
			//write(sock1, ccc, 54);	Seans++;
			n=read(sock1,bbb,1400);
			timer_sig.it_value.tv_nsec = 0L;	timer_settime( tm10, 0, &timer_sig,NULL); // ��⠭�� ⠩���
			close(sock1);
//-----------------------------------------------------------------			
			if ((n>0)&&(T_ALRM==0))
			{			
				//if(p->verbose>1) {printf("->Read %d word : ",n/2); for (j=0;j<n/2;j++ ) printf(" %04x",bbb[j]); printf("\n");}
				//mes_fcpp = (struct zag_CPP *)bbb;
				f12 = (struct from_cpp12 *)bbb;
				//if(p->verbose>1) printf("KSS=%d II=%d TS=%d      ", f12->zag.KSS,f12->zag.II,f12->zag.TS);
				switch(f12->zag.TS)
				{
					case 0x10 : if(p->verbose) printf("Check CPP link OK(TC=0x10)\n");
								break;
					case 0x11 : if(p->verbose) printf("Message loaded OK(TC=0x11)\n");
								break;
					case 0x12 : if(p->verbose) printf("Data recieved OK(TC=0x12)\n");
								break;
					case 0x13 : if(p->verbose) printf("No data from AK(TC=0x13)\n");
								break;
					case 0x14 : if(p->verbose) printf("CPP parameters (TC=0x14)\n");
								//if (f12->data.nf==12)
								{
									//if(p->verbose>1) printf("SS0_prd=%d SS0_prm=%d SS0_cpp=%d SS0_all=%d \n",f12->data.SS0_prd,f12->data.SS0_prm,f12->data.SS0_cpp,f12->data.SS0_all);
									//if(p->verbose>1) printf("SS1=%d SS2_0=%d SS2_1=%d SS3=%d SS4=%d SS5=%d SS6=%d SS7=%d\n",f12->data.SS1,f12->data.SS2_0,f12->data.SS2_1,f12->data.SS3,f12->data.SS4,f12->data.SS5,f12->data.SS6,f12->data.SS7);
									for(j=0;j<9;j++) p->toMN3.sost_kasrt[j]=f12->i.data_int[j];
									//if(p->verbose>1) printf("SS0=%x SS1=%x SS2=%x SS3=%x \n",p->toMN3.sost_kasrt[0],p->toMN3.sost_kasrt[1],p->toMN3.sost_kasrt[2],p->toMN3.sost_kasrt[3]);
										
									return 0x14;
								}
								//printf("nf=%d\n",f12->data.nf);
								
								break;
					default :   if(p->verbose) printf("Error TS (TC=%d)\n",f12->zag.TS);
								break;
			
				}
				
				
				if(p->verbose) printf("\n");
				//printf("nf=%d\n",f12->data.nf);
				p->toMN3.sost_spiak.Cpp=1; //ispavno CPP
				return f12->zag.TS;
			}
			else 
			{
				p->toMN3.sost_spiak.Cpp=0; //neispavno CPP
				return 0; //owibka soedineni9
			}//owibka priema
			T_ALRM=0;
	} //send-recieve
	else 
	{
		return 0; //owibka soedineni9
	
	}
	//delay(100);
	
	return 0;
}