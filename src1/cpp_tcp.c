  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/kernel.h>

  #include <netinet/in.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <netdb.h>
  #include <math.h>
  #include <time.h>
  #include "../include/shared_mem.h"
  #include "../include/USOIwrk.h"
  //#include "../include/CrSocket.h"
  #include "../include/IP_nb.h"
  #include "../include/MesForm.h" 

#define TIMEOUT_SEC		   0L	//0 секунд
#define TIMEOUT_NSEC	10000000L	//макс. время ожидания 10 мс
#define LENBUFWR	80	//длина буфера передачи
#define LnTitle		32		//длина заголовка
#define LENBUFRD 	1400	//длина буфера приема
#define LnKdr	   512	//макс число слов(2 байта) в кадре
#define MaxKdr	  10000	//макс число хранимых кадров
		  


  
#define MS 1000000
#define N_CHAN 2 //CPP SPC

#ifdef __USAGE
		  HELPа

	#endif
	
static Udp_Client_t Uc42;
unsigned short pic[400][219];	
un short bufW [LENBUFWR], bufR [LENBUFRD];
pid_t proxy_time;
volatile un counter;
struct zag_CPP mes_cpp, *mes_fcpp;
struct from_cpp12 *f12;
struct from_cpp18 *f18;
struct form181 f181;
struct to_cpp11 f11,F11Rqst;
timer_t  tm10;
struct sigevent event_sig;
struct itimerspec timer_sig;
unsigned short *aaa,*bbb,*bbb1,*cccc,*cccc1;
unsigned char *cccc2;
unsigned short ccc[100]={0xFFFF,0xFFFF,0x0B00,0x0203,0x0001,0x000B,0x0000,0x0000,0x0000,
						 0x0001,0x0000,0x0010,0x0010,0x010D,0x0001,0x00FF,0x0001,0x0001,
						 0x0001,0x01f8,0,0,0,0,0,0,0};
unsigned char work_point[6]={0x10,0x34,0x55,0x76,0x97,0xB8};
unsigned short bpic[219];

int T_ALRM =0; //prizn srabativani9 taimera
char *name="CPP0_1";
short SRC_PORT;
short DST_PORT;
int timer1=0,timer2=0,verbose=0;
//clock_t start_time, stop_time;
 


short tcp_send_read(int );
short tcp_reqest( );
short rli_reqest( );
//===============================================================================
//			MAIN	MAIN	MAIN	MAIN 	MAIN
main()
{
	
	int n,i,j,col,command,i1;
	int tri =0, y = 0;
	packusoi p1;
    packcmd p2;
    short c_step=0,T0=0,i2;	
    long cpp_timer=0;
    int data_read; //4tenie dannih 
	struct form193 *f193;
	int ustSS=0; // ustanovlennoe zna4enie
	
	
	delay(2500);
	open_shmem();
	delay(1000);
	f181.n_form = 0;
	
	SRC_PORT=DST_PORT=4003; 
	if (p->cvs==10)	name="CPP0_1";
	else			name="CPP2";	
	
	i = Udp_Client_Ini(&Uc42,name,DST_PORT,SRC_PORT);
	
	printf("START MO3A<->CPP Host=%s port=%s cvs=%d\n\n",name,SRC_PORT,p->cvs);
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
						col = sizeof(f11);
						//p->work_com[c_step].s[i].status=1; // check
						switch(p->work_com[c_step].s[i].n_com)
						{
							case 1: p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("			SVCH work \n");
									if (p->fromMN3.a_params[0]==1) f11.data.KU0=0; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
									else f11.data.KU0=ustSS=0;
									f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									//col = sizeof(f11);
									col=tcp_send_read(col);
									if ((f12->data.SS1==ustSS)&&(col==0x14)&&(f12->data.SS0_all==1)) //(p->SS1==(p->work_com[n_s].s[n_mc].n_com==60)&&(p->fromMN3.a_params[0]==1)) //esli otet=sosto9nie 
									{
										//if (f12->data.SS0_all) 
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
                                    //printf("col=%d status=%d\n",col/2,p->work_com[c_step].s[i].status);
									break;
							case 5: if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("			SVCH PRD-PRM CHAN \n");
										f11.data.KU6=f11.data.KU5=work_point[p->fromMN3.a_params[0]-1]; //// RT PRD 1 - 6
										f11.data.ustKU5=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										//f11.data.KU6=p->fromMN3.a_params[0]+6; //// RT PRM 7 - 13
										f11.data.ustKU6=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										col=tcp_send_read(col);
										p->work_com[c_step].t_start = p->sys_timer;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start > 10))
									{
										f11.zag.KSS=0;
										col = sizeof(struct zag_CPP);
										col=tcp_send_read(col);
										//printf("col=%d\n",col);
										if ((col==0x14)&&(p->fromMN3.a_params[0]==f12->data.SS4)) //esli otet=sosto9nie 
										{
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else p->work_com[c_step].s[i].status=3;
										if(p->verbose>1) printf("SS4=%d SS5=%d \n",f12->data.SS4,f12->data.SS5);
									} 	
                                    break;
							case 8: if(p->work_com[c_step].s[i].status==0) 
									{
									p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("			FM SHPS\n");
									f11.data.KU4=p->fromMN3.a_params[0]; //  0 - FM1, 1 - FM2 
									f11.data.ustKU4=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									p->work_com[c_step].t_start = p->sys_timer;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start > 100))
									{
										f11.zag.KSS=0;
										col = sizeof(struct zag_CPP);
										col=tcp_send_read(col);
										if ((col==0x14)&&(p->fromMN3.a_params[0]==f12->data.SS3)) //esli otet=sosto9nie 
										{
											//if (f12->data.SS0_all) 
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else 
										{
											p->work_com[c_step].s[i].status=3;
										printf("aparam=%d ss3=%d \n", p->fromMN3.a_params[0], f12->data.SS3);
										}
										if(p->verbose) printf("col=%d status=%d\n",col/2,p->work_com[c_step].s[i].status);
									}
									break;
							case 12: 	
									if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("			SVCH TKI-RLI \n");
										f11.data.KU3=p->fromMN3.a_params[0]; //  0 - TKI, 1 - RLI 
										f11.data.ustKU3=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										col=tcp_send_read(col);
										p->work_com[c_step].t_start = p->sys_timer;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start < 400))
									{
										f11.zag.KSS=0;
										col=tcp_send_read(sizeof(struct zag_CPP));
										//printf("col=%d\n",col);
										if ((col==0x14)&&(p->fromMN3.a_params[0]==f12->data.SS2_1)) //esli otet=sosto9nie 
										{
											printf("SS2=%d\n",f12->data.SS2_1);
											if(p->verbose>1) printf("SS2=%d\n",f12->data.SS2_1);
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else 
										{
											//p->work_com[c_step].s[i].status=3;
											printf("col=%d param=%d SS2_1=%d \n", col, p->fromMN3.a_params[0], f12->data.SS2_1);
										}
									} 	
                                    break;
							case 14: p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("			PRIEM ONN\n");
									f11.data.KU2=p->fromMN3.a_params[0]; 
									f11.data.ustKU2=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU1=0; 
									f11.data.ustKU1=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									if ((col==0x14)&&(p->fromMN3.a_params[0]==f12->data.SS2_0)) //esli otet=sosto9nie 
									{
										if(p->verbose>1) printf("SS2=%d\n",f12->data.SS2_0);
										p->work_com[c_step].s[i].status=2; // ispravnost'
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
										if(p->verbose>1) printf("SS2=%d\n",f12->data.SS2_0);
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
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
									break;
							case 65 : if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("		FK %d \n",p->fromMN3.a_params[0]);
										f11.data.KU3=0; //ust TKI
										f11.data.ustKU3=1;
										col=tcp_send_read(col);
										p->work_com[c_step].t_start = p->sys_timer;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start < 300))
									{
										f11.zag.KSS=0;
										col=tcp_send_read(sizeof(struct zag_CPP));
										if ((col==0x14)&&(f12->data.SS10>200)&&(f12->data.SS10<800)&&(f12->data.SS2_1==0)) //esli otet=sosto9nie 
										{
											p->work_com[c_step].s[i].status=2; // ispravnost'
											p->toMN3.fk = 0;
											p->toMN3.kzv=0;
										}
										//else p->work_com[c_step].s[i].status=3;
									if(p->verbose) printf("SS10(50-70)=%d TKI(0)=%d \n",f12->data.SS10, f12->data.SS2_1);
									}
								break;
							case 651 : 
									if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("		FK %d \n",p->fromMN3.a_params[0]);
										col=tcp_send_read(col);
										p->work_com[c_step].t_start = p->sys_timer;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start < 300))
									{
										f11.zag.KSS=0;
										col=tcp_send_read(sizeof(struct zag_CPP));
										if ((col==0x14)&&(f12->data.SS10>10)&&(f12->data.SS10<50)) //esli otet=sosto9nie 
										{
											p->work_com[c_step].s[i].status=2; // ispravnost'
											p->toMN3.fk = 0;
											p->toMN3.kzv=0;
										}
										//else p->work_com[c_step].s[i].status=3;
										if(p->verbose) printf("SS10(10-30)=%d \n",f12->data.SS10);
									}
									break;
							case 652 : if(p->work_com[c_step].s[i].status==0) 
								{
								p->work_com[c_step].s[i].status=1;
                                if(p->verbose) printf("		FK %d \n",p->fromMN3.a_params[0]);
								f11.data.KU3=1; //ust RLI
								f11.data.ustKU3=1;
								col=tcp_send_read(col);
								p->work_com[c_step].t_start = p->sys_timer;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start < 300))
								{
									f11.zag.KSS=0;
									col=tcp_send_read(sizeof(struct zag_CPP));
									if ((col==0x14)&&(f12->data.SS10>200)&&(f12->data.SS10<800)) //esli otet=sosto9nie 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
										p->toMN3.fk = 0;
										p->toMN3.kzv=0;
									}
									//else p->work_com[c_step].s[i].status=3;
									if(p->verbose) printf("SS10(50-70)=%d\n",f12->data.SS10);
								}
								break;
							case 653 : if(p->work_com[c_step].s[i].status==0) 
								{
								p->work_com[c_step].s[i].status=1;
                                if(p->verbose) printf("		FK %d \n",p->fromMN3.a_params[0]);
								f11.data.KU3=1; //ust RLI
								f11.data.ustKU3=1;
								col=tcp_send_read(col);
								p->work_com[c_step].t_start = p->sys_timer;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start < 300))
								{
									f11.zag.KSS=0;
									col=tcp_send_read(sizeof(struct zag_CPP));
									if ((col==0x14)&&(f12->data.SS10>10)&&(f12->data.SS10<50)&&(f12->data.SS2_1==1)) //esli otet=sosto9nie 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
										p->toMN3.fk = 0;
										p->toMN3.kzv=0;
									}
									//else p->work_com[c_step].s[i].status=3;
									if(p->verbose) printf("SS10(10-30)=%d RLI(1)=%d  \n",f12->data.SS10, f12->data.SS2_1);
								}
								break;
							case 66 : if(p->work_com[c_step].s[i].status==0) 
								{
									p->work_com[c_step].s[i].status=1;
									if(p->verbose) printf("		FK %d \n",p->fromMN3.a_params[0]);
									f11.data.KU0=1; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
									f11.data.KU1=1;
									f11.data.KU2=0;
									f11.data.KU3=0;
									f11.data.KU6=1;
									f11.data.KU8=2;  //p->fromMN3.a_params[0]; //FK 1 - 12
									f11.data.ustKU0=f11.data.ustKU1=f11.data.ustKU2=f11.data.ustKU3=f11.data.ustKU6=f11.data.ustKU8=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									p->work_com[c_step].t_start = p->sys_timer;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start < 300))
								{
									f11.zag.KSS=0;
									col=tcp_send_read(sizeof(struct zag_CPP));
									if ((col==0x14)&&(f12->data.SS1==1)&&(f12->data.SS2_1==0)&&(f12->data.SS6==0)&&(f12->data.SS7==2)) //esli otet=sosto9nie 
									{
										//if (f12->data.SS0_prm==0) p->toMN3.fk=1;
										p->toMN3.k_o=0;
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									//else p->work_com[c_step].s[i].status=3;
									if(p->verbose>1) printf("SS1(1)=%d SS2_1(0)=%d col=%d SS6(0)=%d SS7(2)=%d param=%d \n",f12->data.SS1, f12->data.SS2_1, col, f12->data.SS6, f12->data.SS7, p->fromMN3.a_params[0]);
								}
								
								break;
							case 67 : //A1 cpp FK3
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									if(p->verbose) printf("		FK3 \n");
									col=tcp_send_read(col);
									if ((col==0x14)&&(f12->data.SS0_all==1)&&(f12->data.SS0_cpp==1)&&(f12->data.SS0_prm==1)&&(f12->data.SS0_prd==1)) //esli otet=sosto9nie 
										 p->work_com[c_step].s[i].status=2; // ispravnost'
									else p->work_com[c_step].s[i].status=3;
									printf("SS0All=%d SS0cpp=%d SS0prm=%d SS0prd=%d \n",f12->data.SS0_all, f12->data.SS0_cpp, f12->data.SS0_prm, f12->data.SS0_prd);
								}
								break;
							case 68 : if(p->work_com[c_step].s[i].status==0) //FK6
								{
									p->work_com[c_step].s[i].status=1;
									if(p->verbose) printf("		FK %d \n",p->fromMN3.a_params[0]);
									f11.data.KU0=1; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
									f11.data.KU8=4;  //p->fromMN3.a_params[0]; //FK 1 - 12
									f11.data.ustKU0=1;
									f11.data.ustKU8=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									p->work_com[c_step].t_start = p->sys_timer;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start < 300))
								{
									f11.zag.KSS=0;
									col=tcp_send_read(sizeof(struct zag_CPP));
									if ((col==0x14)&&(f12->data.SS1==1)&&(f12->data.SS7==4)) //esli otet=sosto9nie 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									//else p->work_com[c_step].s[i].status=3;
									if(p->verbose>1) printf("SS1(1)=%d SS7(4)=%d col=%d\n",f12->data.SS1, f12->data.SS7, col);
								}
								break;
							case 69 : if(p->work_com[c_step].s[i].status==0) //FK7
								{
									p->work_com[c_step].s[i].status=1;
									if(p->verbose) printf("		FK %d \n",p->fromMN3.a_params[0]);
									f11.data.KU0=1; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
									f11.data.KU8=8;  //p->fromMN3.a_params[0]; //FK 1 - 12
									f11.data.ustKU0=1;
									f11.data.ustKU8=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									p->work_com[c_step].t_start = p->sys_timer;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start < 300))
								{
									f11.zag.KSS=0;
									col=tcp_send_read(sizeof(struct zag_CPP));								
									if ((col==0x14)&&(f12->data.SS1==1)&&(f12->data.SS7==8)) //esli otet=sosto9nie 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									//else p->work_com[c_step].s[i].status=3;
									else printf("SS1(1)=%d SS7(8)=%d col=%d\n",f12->data.SS1, f12->data.SS7, col);
									if(p->verbose>1) printf("SS1(1)=%d SS7(8)=%d col=%d\n",f12->data.SS1, f12->data.SS7, col);
								}
								break;
							case 90:
								printf("status %d \n", p->work_com[c_step].s[i].status);// -----vremenno
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									if(p->verbose) printf("			SVCH work \n");
									f11.data.KU0=0; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
									f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU1=0; //rezim peredachi
									f11.data.ustKU1=1;// 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU2=1; //priem : 1 - vkl, 0 - otkl 
									f11.data.ustKU2=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU3=0;//  0 - TKI, 1 - RLI 
									f11.data.ustKU3=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU7=0;//  oslablenie 0 - 25
									f11.data.ustKU7=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									p->work_com[c_step].t_start = p->sys_timer;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start < 300))
								{
									f11.zag.KSS=0;
									col=tcp_send_read(sizeof(struct zag_CPP));
									if ((col==0x14)&&(f12->data.SS0_all==1)&&(f12->data.SS1==0)&&(f12->data.SS2_0==0)&&(f12->data.SS2_1==0)&&(f12->data.SS6==0)) //(p->SS1==(p->work_com[n_s].s[n_mc].n_com==60)&&(p->fromMN3.a_params[0]==1)) //esli otet=sosto9nie 
									{
										printf("ok SS0_all(1)=%d  SS1(0)=%d SS2_0(0)=%d  SS2_1(0)=%d  SS6(0)=%d\n", f12->data.SS0_all, f12->data.SS1, f12->data.SS2_0, f12->data.SS2_1, f12->data.SS6 );
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else 
									{
										//p->work_com[c_step].s[i].status=3;
										printf("error SS0_all(1)=%d  SS1(0)=%d SS2_0(0)=%d  SS2_1(0)=%d  SS6(0)=%d\n", f12->data.SS0_all, f12->data.SS1, f12->data.SS2_0, f12->data.SS2_1, f12->data.SS6);
									}
									//printf("col=%d status=%d\n",col/2,p->work_com[c_step].s[i].status);
								}
								break;
							case 921: //FK 5 - FK13_CPP
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									f11.data.KU0=1;// rezim raboti 0 - rabota, 1 - FK, 2 - SR
									f11.data.KU2=1;// priem : 1 - vkl, 0 - otkl 
									f11.data.KU3=0;// 0 - TKI, 1 - RLI 
									f11.data.KU7=0;// oslablenie 0 - 25
									f11.data.KU8=13;// FK 1 - 12
									f11.data.ustKU0=f11.data.ustKU2=f11.data.ustKU3=f11.data.ustKU7=f11.data.ustKU8=1;
									col=tcp_send_read(col);
									p->work_com[c_step].t_start = p->sys_timer;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start < 100))
								{
									f11.zag.KSS=0;
									col=tcp_send_read(sizeof(struct zag_CPP));
									if ((col==0x14)&&(f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS1==1)&&(f12->data.SS6==0)&&(f12->data.SS8==0)&&(f12->data.SS9==0))  //esli otet pravilnii 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
										printf("FK13_CPP ustanovlen \n");
									}
									else 
									{
										//p->work_com[c_step].s[i].status=3;
										printf("error step1 \n");
										printf("SS1(1)=%d SS2_1(0)=%d SS2_0(0)=%d SS6(0)=%d SS8(0)=%d SS9(0)=%d \n", f12->data.SS1, f12->data.SS2_1, f12->data.SS2_0, f12->data.SS6, f12->data.SS8, f12->data.SS9);
										printf("col=%x SS0(1)=%d \n", col, f12->data.SS0_all);
									}
								}	
								break;	
							case 922: //FK 5
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									p->work_com[c_step].t_start = p->sys_timer;
									verbose=p->verbose;
									p->verbose=0;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start > 20))
								{	
									f11.zag.KSS=0;
									col = sizeof(struct zag_CPP);
									col=tcp_send_read(col);
									if (tri>20) 
									{
										printf("IB ne zagruzhen, error step4 SS9=%d \n", f12->data.SS9);
										p->work_com[c_step].s[i].status=3;
										p->toMN3.k_o = 2;
										tri=0;
										p->verbose=verbose;
									}
									else 
										//if ((col==0x14)&&(f12->data.SS0_all==1)&&(f12->data.SS9==p->fromMN3.a_params[4]))  //esli otet pravilnii 
										if ((col==0x14)&&(f12->data.SS0_all==1)&&(f12->data.SS9==1))  //esli otet pravilnii 
										{
											p->work_com[c_step].s[i].status=2; // ispravnost'
											printf("IB Zagruzhen SS9=%d OK\n", f12->data.SS9);
											tri=0;
											p->verbose=verbose;
										}
									printf("SS9=%d tri=%d col=%02x SS0=%d par4=%d \n", f12->data.SS9, tri , col , f12->data.SS0_all, p->fromMN3.a_params[4] );	
									tri++;
								}	
								break;	
							case 923: //FK 5
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									p->work_com[c_step].t_start = p->sys_timer;
									if(p->verbose) printf("			IB peredan \n");
									verbose=p->verbose;
									p->verbose=0;
									f11.data.KU1=1;
									f11.data.ustKU1=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									//f11.data.KU2=0; 
									//f11.data.ustKU2=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
									//printf("SS2_prd1=%d\n",f12->data.SS2_0);
									tri=0;
									if ((col==0x14))//&&(p->fromMN3.a_params[0]==f12->data.SS2_0)) //esli otet=sosto9nie 
									{	
										printf("SS2=%d\n",f12->data.SS2_0);
										//p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start < 350))
								{	
									f11.zag.KSS=0;
									col = sizeof(struct zag_CPP);
									col=tcp_send_read(col);
									if (tri>20) 
									{
										printf("IB ne peredan, error step5 SS9=%d \n", f12->data.SS9);
										p->work_com[c_step].s[i].status=3;
										p->toMN3.k_o = 2;
										tri=0;
										p->verbose=verbose;
									}
									else 
										if ((col==0x14)&&(f12->data.SS0_all==1)&&(f12->data.SS9==2))  //esli otet pravilnii 
										{
											p->work_com[c_step].s[i].status=2; // ispravnost'
											printf("IB peredan, SS9=%d OK\n", f12->data.SS9);
											tri=0;
											p->verbose=verbose;
											break;
										}
									printf("SS9=%d SS2=%d tri=%d col=%02x SS0=%d par4=%d \n", f12->data.SS9, f12->data.SS2_0,tri , col , f12->data.SS0_all, p->fromMN3.a_params[4] );	
									tri++;
								}	
								break;		
							case 924: //FK 5
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									f11.zag.TS=3;
									f11.zag.KSS=15;
									f11.zag.II=2;
									f11.zag.PS=1;
									f11.data.KU1=0; 
									f11.data.ustKU1=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=tcp_send_read(col);
							
									if ((col==0x14)&&(f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1))  //esli otet pravilnii
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else 
									{
										printf("error step6 SS8 =%d ss0_all =%d \n",f12->data.SS8==1, f12->data.SS0_all);
										p->work_com[c_step].s[i].status=3;
										p->toMN3.k_o = 4;
									}
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
							
									if ((col==0x14)&&(f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS1==0)&&(f12->data.SS2_1==0)&&(f12->data.SS2_0==1)&&(f12->data.SS6==0)&&(f12->data.SS8==0)&&(f12->data.SS9==0))  //esli otet pravilnii 
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
									f11.zag.TS=3;
									f11.zag.KSS=0;
									f11.zag.II=2;
									f11.zag.PS=1;
									col=tcp_send_read(col);
							
									if ((col==0x14)&&(f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS9==1))  //esli otet pravilnii 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else 
									{
									p->work_com[c_step].s[i].status=3;
									//printf(" SS13 = %d SS14 = %d SS15 = %d SS16 = %d SS17 = %d SS18 = %d\n SS19 = %d SS20 = %d SS21 = %d\n", f12->data.SS13,f12->data.SS14,f12->data.SS15,f12->data.SS16,f12->data.SS17,f12->data.SS18,f12->data.SS19,f12->data.SS20,f12->data.SS21);
									}
								}
								break;
								
							case 932: //ust svyaz' s AK
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									f11.zag.TS=3;
									f11.zag.KSS=15;
									f11.zag.II=2;
									f11.zag.PS=1;
									f11.data.KU1=1;
									f11.data.ustKU1=1;
									col=tcp_send_read(col);
							
									if ((col==0x14)&&(f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS2_1==0)&&(f12->data.SS2_0==0)&&(f12->data.SS0_prd==1)&&(f12->data.SS6==0)&&(f12->data.SS9==2))  //esli otet pravilnii 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else 
									{
									p->work_com[c_step].s[i].status=3;
									//printf(" SS13 = %d SS14 = %d SS15 = %d SS16 = %d SS17 = %d SS18 = %d\n SS19 = %d SS20 = %d SS21 = %d\n", f12->data.SS13,f12->data.SS14,f12->data.SS15,f12->data.SS16,f12->data.SS17,f12->data.SS18,f12->data.SS19,f12->data.SS20,f12->data.SS21);
									}
								}
								break;
								
							case 933: //ust svyaz' s AK
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									f11.zag.TS=3;
									f11.zag.KSS=15;
									f11.zag.II=2;
									f11.zag.PS=1;
									f11.data.KU1=0;
									f11.data.ustKU1=1;
									f11.data.KU2=1;
									f11.data.ustKU1=1;
									col=tcp_send_read(col);
									if ((col==0x14)&&(f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS0_prm==0))  //esli otet pravilnii 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else 
									{
									p->work_com[c_step].s[i].status=3;
									//printf(" SS13 = %d SS14 = %d SS15 = %d SS16 = %d SS17 = %d SS18 = %d\n SS19 = %d SS20 = %d SS21 = %d\n", f12->data.SS13,f12->data.SS14,f12->data.SS15,f12->data.SS16,f12->data.SS17,f12->data.SS18,f12->data.SS19,f12->data.SS20,f12->data.SS21);
									}
								}
								break;
							case 934: //ust svyaz' s AK
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									f11.zag.TS=3;
									f11.zag.KSS=0;
									f11.zag.II=2;
									f11.zag.PS=1;
									col=tcp_send_read(col);
							
									if ((col==0x14)&&(f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS8==1))  //esli otet pravilnii 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else 
									{
									p->work_com[c_step].s[i].status=3;
									//printf(" SS13 = %d SS14 = %d SS15 = %d SS16 = %d SS17 = %d SS18 = %d\n SS19 = %d SS20 = %d SS21 = %d\n", f12->data.SS13,f12->data.SS14,f12->data.SS15,f12->data.SS16,f12->data.SS17,f12->data.SS18,f12->data.SS19,f12->data.SS20,f12->data.SS21);
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
										
										p->a0_cpp=f193->a0;  //сюЁЄютющ эюьхЁ
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
		
								
			}//step>0
			else
			{
				//------------------- timer oprosa ----------------------------------------
				if (p->cvs==11) // 
				{
					timer2++;
					if (timer2 > 40) // primerno 05 sec
					{
						tcp_reqest();		
						timer2 =0;
					}
				}
				// -------------------------- RLI timer --------------------------------------
				if (p->cvs==10) // RLI
				{
					timer2++;
					if (timer2 > 30) // primerno 05 sec
					{	
						timer2 =0;
						
						timer1++;
						
						if (timer1 == 7) //20*5 
						{	
							printf("ParamRqst TS= %d\n",tcp_reqest());		
							timer1 = 0;
							
						}
						else
						{
							printf("RliRqst=%d\n",rli_reqest());
							
							
							
						}
					}
				} //esli net waga
			} 
		}//timer
		delay(20);
	}//while
	timer_delete(tm10);
}
//-------------------------------------------------------------------------------------------------------

short tcp_send_read(int col)
{
	int sock1;
	short rez;
	int i,i1,n,j;
	short status,sum;

	
	bbb = (unsigned short *)&f11;
	sum=0;
	if (col>10) 
	{
		for(i=0;i<14;i++) sum^=bbb[i+5];
		//if(p->verbose>2) printf("ccc[%d]=%x CKH_SUM=%04x \n",i+5,ccc[i+5],sum);}
		bbb[col/2-1]=sum;
	}
		//if(p->verbose>2) printf("CKH_SUM=%04x \n",sum);
	if(p->verbose>2) {printf("<-Send ");for(i1=0;i1<col/2;i1++) printf("%x ",bbb[i1]);printf("\n");}
	n = Udp_Client_Send(&Uc42,bbb,col);
	delay(50);
		//if(p->verbose>2) {printf("<-Send ");for(i1=0;i1<37;i1++) printf("%04x ",ccc[i1]);printf("\n");}
	n = Udp_Client_Read(&Uc42,bbb1,1400);
//-----------------------------------------------------------------			
	if (n>0)
	{			
		if(p->verbose>1) {printf("->Read %d word : ",n/2); for (j=0;j<n/2;j++ ) printf(" %04x",bbb1[j]); printf("\n");}
		f12 = (struct from_cpp12 *)bbb1;
		if(p->verbose>1) printf("KSS=%d II=%d TS=%d      ", f12->zag.KSS,f12->zag.II,f12->zag.TS);
		if(p->cvs==10) f12->data.SS0_prd=f12->data.SS0_prm=f12->data.SS0_all=1; // podkraasheno chto rabotaet cpp na cvs10
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
						p->toMN3.sost_spiak.Cpp=1; //ispavno CPP
						
						for(j=0;j<9;j++) p->toMN3.sost_kasrt[j]=f12->i.data_int[j];
						//if(p->verbose>1) printf("SS0=%x SS1=%x SS2=%x SS3=%x \n",p->toMN3.sost_kasrt[0],p->toMN3.sost_kasrt[1],p->toMN3.sost_kasrt[2],p->toMN3.sost_kasrt[3]);
						return 0x14;
			default :   if(p->verbose) printf("Error TS (TC=%d)\n",f12->zag.TS);
						break;
		
		}
		if(p->verbose) printf("\n");
		return f12->zag.TS;
	}
	else 
	{
		p->toMN3.sost_spiak.Cpp=0; //neispavno CPP
		return 0; //owibka soedineni9
	}//owibka priema
}

//--------------------------------reqests---------------------------------------------------------------
//--------------------------------timer-----------------------------------------------------------------
short tcp_reqest()
{
	int i,i1,n,j;
	int col1;
	unsigned short *bbb1,*bbb2;
	F11Rqst.zag.marker1=0xFFFF;
	F11Rqst.zag.marker2=0xFFFF;
	F11Rqst.zag.II=2;
	F11Rqst.zag.PS=1;
	F11Rqst.zag.KSS=0;
	F11Rqst.zag.TS=3; //parametri
	col1 = sizeof(struct zag_CPP);
					
	bbb2 = (unsigned short *)&F11Rqst;
	
	//if(p->verbose>2) {printf("<-Send ");for(i1=0;i1<col/2;i1++) printf("%x ",bbb[i1]);printf("\n");}
	n = Udp_Client_Send(&Uc42,bbb2,col1);
	delay(50);
	if(p->verbose>2) {printf("<-Send ");for(i1=0;i1<col1/2;i1++) printf("%04x ",bbb2[i1]);printf("\n");}
	n = Udp_Client_Read(&Uc42,bbb1,1400);
//-----------------------------------------------------------------			
	if (n>0)
	{			
		if(p->verbose>1) {printf("Rqst->Read %d word : ",n/2); for (j=0;j<n/2;j++ ) printf(" %04x",bbb1[j]); printf("\n");}
		f12 = (struct from_cpp12 *)bbb1;
		//if(p->verbose>1) printf("KSS=%d II=%d TS=%d      ", f12->zag.KSS,f12->zag.II,f12->zag.TS);
		if(p->cvs==10) f12->data.SS0_prd=f12->data.SS0_prm=f12->data.SS0_all=1; // podkraasheno chto rabotaet cpp na cvs10
				
		switch(f12->zag.TS)
		{
			case 0x14 : //if(p->verbose>1) printf("SS0_prd=%d SS0_prm=%d SS0_cpp=%d SS0_all=%d \n",f12->data.SS0_prd,f12->data.SS0_prm,f12->data.SS0_cpp,f12->data.SS0_all);
				//if(p->verbose>1) printf("SS10=%d SS16=%d SS13=%d SS3=%d SS4=%d SS5=%d SS6=%d SS7=%d\n",f12->data.SS10,f12->data.SS16,f12->data.SS13,f12->data.SS3,f12->data.SS4,f12->data.SS5,f12->data.SS6,f12->data.SS7);
				p->toMN3.sost_spiak.Cpp=1; //ispavno CPP
				for(j=0;j<9;j++) p->toMN3.sost_kasrt[j]=f12->i.data_int[j];
					//if(p->verbose>1) printf("SS0=%x SS1=%x SS2=%x SS3=%x \n",p->toMN3.sost_kasrt[0],p->toMN3.sost_kasrt[1],p->toMN3.sost_kasrt[2],p->toMN3.sost_kasrt[3]);
				return 0x14;
			case 0x12 : //printf("Est' soobshenie v zaprose sosto9ni9\n");
				break;
			case 0x13 : //printf("Net soobsheniy  v zaprose sosto9ni9\n");
				break;
			default :   if(p->verbose) printf("Error TS (TC=%d)\n",f12->zag.TS);
				break;
		}						
		return f12->zag.TS;
	}
	else 
	{
		p->toMN3.sost_spiak.Cpp=0;
		return 0; //owibka soedineni9
	}//owibka priema
}
//--------------------------------RLI---------------------------------------------------------------
//--------------------------------timer-----------------------------------------------------------------
short rli_reqest()
{
	int sock1;
	short rez;
	unsigned short N_string=0;
	int i,i1,n,j,y=0,i3;
	short status,sum,i2;
	long timer_rli=0;
	long timer_read=0;
	int word181; //kol-vo slov v 181
	int wordRLI; //kol-vo slov v RLI dl9 Dani
	unsigned char buff;
	struct to_cpp11 f11Rli;
	int col2;
	
	f11Rli.zag.marker1=0xFFFF;
	f11Rli.zag.marker2=0xFFFF;
	f11Rli.zag.II=2;
	f11Rli.zag.PS=1;
	f11Rli.zag.KSS=0;
	f11Rli.zag.TS=2;  //zapros dannih
	col2 = sizeof(struct zag_CPP);
	
	cccc = (unsigned short *)&f11Rli;
	
	timer_rli=p->sys_timer+600; // ustanovka timera na 2 sec
	n = Udp_Client_Send(&Uc42,cccc,col2);
	delay(50);
	//if(p->verbose>1) {printf("->Read %d word : ",n/2); for (j=0;j<n/2;j++ ) printf(" %04x",cccc[j]); printf("\n");}
		
//-------------------------READ MESSAGE---------------------------------------------------
	for(i2=0; i2<14; i2++) // priem za raz ne bolee 20 soobcheniy
	{
		delay(5);
		timer_read=p->sys_timer+200; // ustanovka timera na 0.5 sec
		n = Udp_Client_Read(&Uc42,cccc1,1400);
		
		//if(p->cvs==10) f12->data.SS0_prd=f12->data.SS0_prm=f12->data.SS0_all=1; // podkraasheno chto rabotaet cpp na cvs10
		if((timer_rli>p->sys_timer)&&(timer_read>p->sys_timer)&&(n>0)) // timeri na 2 sec i na 0.5 sec
		{
		 //------------------------------------test---------------------------------------------
			
			if ((f181.n_form > 0)&&(p->toMN3.Mem_Region2.Mem_Region_RLI.num_words<614))
			{
				//f181 -> danye
				
				memcpy(p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_SACH, f181.Sach, 12);
				memcpy(p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_5, f181.form5, 16);
				if(p->toMN3.Mem_Region2.Mem_Region_RLI.num_words == 0) p->toMN3.Mem_Region2.Mem_Region_RLI.num_words = 8;
				//memcpy(&p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_6[p->toMN3.Mem_Region2.Mem_Region_RLI.num_words-8], (char *)f181.form6[f181.n_word-202], 404);
				word181=(f181.n_form-1)*202;
				wordRLI=p->toMN3.Mem_Region2.Mem_Region_RLI.num_words-8;
				for(i3=0;i3<202;i3++) p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_6[wordRLI+i3]=f181.form6[word181+i3];
				p->toMN3.Mem_Region2.Mem_Region_RLI.num_words += 202;
				f181.n_form--;
				//printf("//f181 -> danye 		form181=%d 		wRLI=%d 	str=%d\n",
				//f181.n_form,wordRLI,p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_6[1]>>7);
			}
			
			
			f18 = (struct from_cpp18 *)cccc1;
			
			printf("TS=%d\n",f18->zag.TS);
			
			switch (f18->zag.TS)
			{
				case 0x12:
					for(i3=0;i3<219;i3++) //perevorov baitov
					{
						buff = f18->mass1[i3*2] & 0xff;
						f18->mass1[i3*2] = f18->mass1[i3*2+1]& 0xff;
						f18->mass1[i3*2+1] = buff & 0xff;
						
					} 
					
					////////-----------------------	1 -------------------------------------------
					memcpy(p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_SACH, f18->data.Sach, 12);
					memcpy(p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_5, f18->data.form5, 16);
					memcpy(f181.Sach, f18->data.Sach, 12);
					memcpy(f181.form5, f18->data.form5, 16);
									
					if(p->toMN3.Mem_Region2.Mem_Region_RLI.num_words == 0) p->toMN3.Mem_Region2.Mem_Region_RLI.num_words = 8;
					/// -------------------------- 2 --------------------------------------
					if (p->toMN3.Mem_Region2.Mem_Region_RLI.num_words<614)
					{
						// ------------------------ 3 -----------------------------------------------
						memcpy(&p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_6[p->toMN3.Mem_Region2.Mem_Region_RLI.num_words-8], f18->data.form6, 404);
						p->toMN3.Mem_Region2.Mem_Region_RLI.num_words += 202;
					}
					else //f18 -> f181
					{
						word181=f181.n_form*202;
						//memcpy(&f181.form6[f181.n_word], f18->data.form6, 404);
						for(i3=0;i3<202;i3++) f181.form6[word181+i3]=f18->data.form6[i3];
						//printf("n_str=%d nstr_old=%d word=%d form=%d\n",f181.form6[word181+1]>>7,f18->data.form6[1]>>7,word181,f181.n_form);
						f181.n_form++;
					}
					p->toMN3.Mem_Region2.Mem_Region_RLI.cr_transm_takt=7;
					p->toMN3.Mem_Region2.Mem_Region_RLI.cr_data_pac++;
					N_string=f18->data.form6[1]>>7;
					printf("form18 = %d RLI.num_words = %d  N_STR=%d \n",
					f181.n_form,p->toMN3.Mem_Region2.Mem_Region_RLI.num_words,N_string&0x1FF);
		//-----------------------------test end-----------------------------------------------			
					
					//printf("stoka %d=%d prinyata %d timer %d kolvo slov %d y=%d \n" ,f18->data.form6[1],p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_6[1],i2,p->sys_timer, n/2,f181.data.n_word);
					if(f18->zag.PS==1) 
					{
						printf("Posledniya stroka \n");
						i2=20;  // proverka na poslednee soobshenie v cikle obmena
					}
				//----------------------test start ------------------------------------------
				/*for(i=0; i<203; i++)
				{
					if (f181.data.form6[((y-1)*203)+i] == f18->data.form6[i])
					{
						if (i==203) printf("%d lines DATA check ok \n", (y-1));
					}
					else 
					{
						i=204;
						printf("DATA error line %d not correct \n", (y-1));
					}
				} */
				//----------------------test end---------------------------------------------
					break;
				case 0x13: 
					//printf("Netu strok timer=%d n=%d TS=%04x \n", p->sys_timer, n, f18->zag.TS);
					i2=200;
					break;
				default:
					i2=400;
					//printf("error: ne tot TS %d\n", f18->zag.TS);
					
			}
		}
		else
		{
			i2=600;
			//printf("error: time out n=%d\n",n);
		}
	}
			
	//printf("timer=%d  timer_rli %d i2=%d PS=%d \n", timer_read, timer_rli, i2, f18->zag.PS);
//-----------------------------------------------------------------			
	if (n>0)
	{			
		//if(p->verbose>1) {printf("->Read %d word : ",n/2); for (j=0;j<n/2;j++ ) printf(" %04x",bbb[j]); printf("\n");}
		//printf("RLI download line %d \n", i2);
		//if(p->verbose>1) printf("KSS=%d II=%d TS=%d      ", f12->zag.KSS,f12->zag.II,f12->zag.TS);
		return n;
	}
	return 0;
	
}