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
  #include <process.h>
  #include "../include/shared_mem.h"
  #include "../include/USOIwrk.h"
  //#include "../include/CrSocket.h"
  #include "../include/func_IP.h"
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
	
	#if defined(_386_)
	# define FAR
	# define STACK_SIZE (4096*24)
	#else
	# define FAR _far
	# define STACK_SIZE (4096*48)
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
int timer1=0,timer2=0,verbose=0,num_f12=0,new_f12;
//clock_t start_time, stop_time;
int prev_str=0;


short cmd_send(int );
short status_request( );
short rli_request( );
void read1();
void read_rli1();
//===============================================================================
//			MAIN	MAIN	MAIN	MAIN 	MAIN
main()
{
	
	int i,col;
	packusoi p1;
    packcmd p2;
    short c_step=0,T0=0,i2;	
    long cpp_timer=0;
    int data_read; //4tenie dannih 
	int tri =0;
	struct form193 *f193;
	int ustSS=0; // ustanovlennoe zna4enie
	static char 		*stack_in;
	int word181; //kol-vo slov v 181
	int wordRLI; //kol-vo slov v RLI dl9 Dani
	int i3;//setprio(0,(getprio(0)+6));
	
	#if defined (_386_) 
  stack_in = (char *) malloc (STACK_SIZE);
#else
  stack_in = (char *) malloc (STACK_SIZE);
#endif
	
	
	delay(2500);
	open_shmem();
	delay(1000);
	p->count_cpp_status=0;
	
	SRC_PORT=DST_PORT=4003; 
	if (p->cvs==10)	name="CPP0_1";
	else			name="CPP2"; 
	
	
	i = Udp_Client_Ini(&Uc42,name,DST_PORT,SRC_PORT);
	_beginthread(read1,stack_in,STACK_SIZE,0);
	
	printf("START MO3A<->CPP Host=%s port=%d cvs=%d\n\n",name,SRC_PORT,p->cvs);
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
							case 1: 
									if (p->fromMN3.a_params[0]==1) f11.data.KU0=0; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
									else f11.data.KU0=ustSS=0;
									f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										
									if(p->work_com[c_step].s[i].status==0)
									{
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("			SVCH work \n");
										col=cmd_send();
										new_f12 = p->count_cpp_status;
									}
									if (p->verbose>1) printf("SS0=%d status=%d(1) newf12 %d != cpp_status %d\n",f12->data.SS0_all , p->work_com[c_step].s[i].status, new_f12, p->count_cpp_status);
									if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
									{
										printf("count=%d status=%d ss_all=%d\n",p->count_cpp_status,p->work_com[c_step].s[i].status, f12->data.SS0_all);
										if(f12->data.SS0_all==1) //(p->SS1==(p->work_com[n_s].s[n_mc].n_com==60)&&(p->fromMN3.a_params[0]==1)) //esli otet=sosto9nie 
										{
											//if (f12->data.SS0_all) 
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else 
										{
											new_f12 = p->count_cpp_status;
											col=status_request();
										}
									}
									if (f12->zag.TS != 20) 
									{
										p->work_com[c_step].s[i].status=3;
										printf("TS error TS=%d(20)", f12->zag.TS);
									}
									//printf("KSS=%04x TS=%04x II=%04x PS=%04x\n",f12->zag.KSS, f12->zag.TS, f12->zag.II, f12->zag.PS);
									//printf("SS1=%04x SS0_prd=%04x SS0_prm=%04x SS0_cpp=%04x SS0_all=%04x\n", f12->data.SS1, f12->data.SS0_prd, f12->data.SS0_prm, f12->data.SS0_cpp, f12->data.SS0_all);
									//printf("SS2_0=%04x SS2_1=%04x SS3=%04x SS5=%04x SS4=%04x\n", f12->data.SS2_0, f12->data.SS2_1, f12->data.SS3, f12->data.SS5, f12->data.SS4);
									//printf("SS7=%04x SS6=%04x SS9=%04x SS8=%04x SS10=%04x\n", f12->data.SS7, f12->data.SS6, f12->data.SS9, f12->data.SS8, f12->data.SS10);
									//printf("SS11=%04x SS12=%04x SS13=%04x SS14=%04x SS15=%04x\n", f12->data.SS11, f12->data.SS12, f12->data.SS13, f12->data.SS14, f12->data.SS15);
									//printf("SS16=%04x SS17=%04x SS18=%04x SS19=%04x SS20=%04x\n", f12->data.SS16, f12->data.SS17, f12->data.SS18, f12->data.SS19, f12->data.SS20);
									//printf("p->count_cpp_status%d\n", p->count_cpp_status);
									break;
									
							case 5: if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("			SVCH PRD-PRM CHAN \n");
										f11.data.KU6=f11.data.KU5=work_point[p->fromMN3.a_params[0]-1]; //// RT PRD 1 - 6
										f11.data.ustKU5=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										//f11.data.KU6=p->fromMN3.a_params[0]+6; //// RT PRM 7 - 13
										f11.data.ustKU6=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										col=cmd_send();
										new_f12 = p->count_cpp_status;
									}
									//printf("status = %d cpp_count = %d \n", p->work_com[c_step].s[i].status, p->count_cpp_status);
									if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
									{
										if (p->fromMN3.a_params[0]==f12->data.SS4) //esli otet=sosto9nie 
										{
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else 
										{
											//f11.zag.KSS=0;
											//col = sizeof(struct zag_CPP);
											new_f12 = p->count_cpp_status;
											col=status_request();
										}
										//printf("SS4=%d SS5=%d \n",f12->data.SS4,f12->data.SS5);
									} 
									else printf("error status = %d cpp_count = %d \n", p->work_com[c_step].s[i].status, p->count_cpp_status);
                                    break;
									
							case 8: if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("			FM SHPS\n");
										f11.data.KU4=p->fromMN3.a_params[0]; //  0 - FM1, 1 - FM2 
										f11.data.ustKU4=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										col=cmd_send();
										new_f12 = p->count_cpp_status;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
									{
										if (p->fromMN3.a_params[0]==f12->data.SS3) //esli otet=sosto9nie 
										{
											//if (f12->data.SS0_all) 
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else 
										{
											//f11.zag.KSS=0;
											//col = sizeof(struct zag_CPP);
											new_f12 = p->count_cpp_status;
											col=status_request();
										}
										//if(p->verbose) printf("col=%d status=%d\n",col/2,p->work_com[c_step].s[i].status);
									}
									break;
									
							case 12: 	
									if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("			SVCH TKI-RLI \n");
										f11.data.KU3=p->fromMN3.a_params[0]; //  0 - TKI, 1 - RLI 
										f11.data.ustKU3=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										col=cmd_send();
										new_f12 = p->count_cpp_status;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
									{
										if (p->fromMN3.a_params[0]==f12->data.SS2_1) //esli otet=sosto9nie 
										{
											if(p->verbose>1) printf("SS2=%d\n",f12->data.SS2_1);
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else 
										{
											//f11.zag.KSS=0;
											new_f12 = p->count_cpp_status;
											col=status_request();
										}
									} 	
                                    break;
							
							case 14: p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("			PRIEM ONN\n");
									f11.data.KU2=p->fromMN3.a_params[0]; 
									f11.data.ustKU2=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU1=0; 
									f11.data.ustKU1=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=cmd_send();
									new_f12 = p->count_cpp_status;
									if (0 == f12->data.SS2_0) //esli otet=sosto9nie 
									{
										if(p->verbose>1) printf("param %d = SS2=%d\n",p->fromMN3.a_params[0], f12->data.SS2_0);
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
									if(p->verbose) printf("ok=%d\n",p->fromMN3.a_params[0]);
                                    break;
							
							case 15: if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("			PEREDA4A ONN\n");
										f11.data.KU1= 1;//p->fromMN3.a_params[0];
										f11.data.ustKU1=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										f11.data.KU2=0; 
										f11.data.ustKU2=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										col=cmd_send();
										new_f12 = p->count_cpp_status;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
									{
										//if(p->verbose>1) printf("SS2=%d(1)\n",f12->data.SS2_0);
										if (1 == f12->data.SS2_0) //esli otet=sosto9nie 
										{	
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else col=status_request();
									}
                                    break;
							
							case 30: 
									if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("			SVCH ATT \n");
										f11.data.KU7=p->fromMN3.a_params[0]; // oslablenie 0 - 25
										f11.data.ustKU7=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										col=cmd_send();
										new_f12 = p->count_cpp_status;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
									{
										//if(p->verbose>1) printf("param %d = SS6 %d\n", p->fromMN3.a_params[0],f12->data.SS6);
										if (p->fromMN3.a_params[0]==f12->data.SS6) //esli otet=sosto9nie 
										{
											if(p->verbose>1) printf("SS6=%d\n",f12->data.SS6);
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else p->work_com[c_step].s[i].status=3;
									}
                                    break;
							
							case 32: case 42: p->work_com[c_step].s[i].status=1;
                                    if(p->verbose) printf("		porog	MI \n");
									f11.data.KU10=p->fromMN3.a_params[0]; // porog MI 1 - 15
									f11.data.ustKU10=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=cmd_send();
									new_f12 = p->count_cpp_status;
									if ( p->fromMN3.a_params[0]==f12->data.SS12)//esli otet=sosto9nie 
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
									col=cmd_send();
									new_f12 = p->count_cpp_status;
									if ( p->fromMN3.a_params[0]==f12->data.SS11) //esli otet=sosto9nie 
									{
										if(p->verbose>1) printf("SS6=%d\n",f12->data.SS11);
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else p->work_com[c_step].s[i].status=3;
                                    break;
							
							case 61: if(p->work_com[c_step].s[i].status==0) 
									{ 
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("			SVCH status\n");
										//f11.zag.KSS=0;
										//col = sizeof(struct zag_CPP);
										col=status_request();
										new_f12 = p->count_cpp_status;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
									{
										if (p->verbose>2) printf("TS %x\n", f12->zag.TS);
										if (f12->zag.TS == 0x14) //esli otet=sosto9nie 
										{
											if (f12->data.SS0_all) 
											p->work_com[c_step].s[i].status=2; // ispravnost'
											if (p->verbose>2) printf("TS = %x\n", f12->zag.TS);
										}
										else col=status_request();
									}
									break;
							
							case 63: if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										f11.data.KU0=0;
										f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										col=cmd_send();
										new_f12 = p->count_cpp_status;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
									{
										//if(p->verbose>1) printf("Error SS7=%d (0)\n",f12->data.SS1);
										if (0 == f12->data.SS1)//esli otet=sosto9nie 
										{
											if(p->verbose>1) printf("SS7=%d\n",f12->data.SS1);
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else col=status_request();
									}
                                    break;
							
							case 64: if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										f11.data.KU8=p->fromMN3.a_params[0]; // fk #
										f11.data.ustKU8=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										f11.data.KU0=1;
										f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										col=cmd_send();
										new_f12 = p->count_cpp_status;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
									{
										if ( p->fromMN3.a_params[0]==f12->data.SS7)//esli otet=sosto9nie 
										{
											if(p->verbose>1) printf("SS7=%d\n",f12->data.SS7);
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else 
										{
											p->work_com[c_step].s[i].status=3;
											if(p->verbose>1) printf("SS7=%d param=%d KU=%d SS1=%d(1)\n",f12->data.SS7, p->fromMN3.a_params[0], f11.data.KU8, f12->data.SS1);
										}
									}
                                    break;
							
							case 65 : if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("		FK %d \n",p->fromMN3.a_params[0]);
										f11.data.KU3=0; //ust TKI
										f11.data.ustKU3=1;
										col=cmd_send();
										new_f12 = p->count_cpp_status;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
									{
										if ((f12->data.SS10>50)&&(f12->data.SS10<800)&&(f12->data.SS2_1==0)) //esli otet=sosto9nie 
										{
											p->work_com[c_step].s[i].status=2; // ispravnost'
											p->toMN3.fk = 0;
											p->toMN3.kzv=0;
										}
										else 
										{
											//f11.zag.KSS=0;
											new_f12 = p->count_cpp_status;
											col=status_request();
										}
									if(p->verbose) printf("SS10(50-800)=%d TKI(0)=%d \n",f12->data.SS10, f12->data.SS2_1);
									}
								break;
							
							case 651 : 
									if(p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1;
										if(p->verbose) printf("		FK %d \n",p->fromMN3.a_params[0]);
										col=cmd_send();
										new_f12 = p->count_cpp_status;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
									{
										if ((f12->data.SS10>10)&&(f12->data.SS10<50)) //esli otet=sosto9nie 
										{
											p->work_com[c_step].s[i].status=2; // ispravnost'
											p->toMN3.fk = 0;
											p->toMN3.kzv=0;
										}
										else 
										{
											//f11.zag.KSS=0;
											new_f12 = p->count_cpp_status;
											col=status_request();
										}
										if(p->verbose) printf("SS10(10-50)=%d \n",f12->data.SS10);
									}
									break;
							
							case 652 : if(p->work_com[c_step].s[i].status==0) 
								{
								p->work_com[c_step].s[i].status=1;
                                if(p->verbose) printf("		FK %d \n",p->fromMN3.a_params[0]);
								f11.data.KU3=1; //ust RLI
								f11.data.ustKU3=1;
								col=cmd_send();
								new_f12 = p->count_cpp_status;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
								{
									if ((f12->data.SS10>50)&&(f12->data.SS10<800)) //esli otet=sosto9nie 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
										p->toMN3.fk = 0;
										p->toMN3.kzv=0;
									}
									else 
									{
										//f11.zag.KSS=0;
										new_f12 = p->count_cpp_status;
										col=status_request();
									}
									if(p->verbose) printf("SS10(50-800)=%d\n",f12->data.SS10);
								}
								break;
							
							case 653 : if(p->work_com[c_step].s[i].status==0) 
								{
								p->work_com[c_step].s[i].status=1;
                                if(p->verbose) printf("		FK %d \n",p->fromMN3.a_params[0]);
								f11.data.KU3=1; //ust RLI
								f11.data.ustKU3=1;
								col=cmd_send();
								new_f12 = p->count_cpp_status;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
								{
									if ((f12->data.SS10>10)&&(f12->data.SS10<50)&&(f12->data.SS2_1==1)) //esli otet=sosto9nie 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
										p->toMN3.fk = 0;
										p->toMN3.kzv=0;
									}
									else 
									{
										//f11.zag.KSS=0;
										new_f12 = p->count_cpp_status;
										col=status_request();
									}
									if(p->verbose) printf("SS10(10-50)=%d RLI(1)=%d  \n",f12->data.SS10, f12->data.SS2_1);
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
									col=cmd_send();
									new_f12 = p->count_cpp_status;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
								{
									if ((f12->data.SS1==1)&&(f12->data.SS2_1==0)&&(f12->data.SS6==0)&&(f12->data.SS7==2)) //esli otet=sosto9nie 
									{
										//if (f12->data.SS0_prm==0) p->toMN3.fk=1;
										p->toMN3.k_o=0;
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else 
									{
										//f11.zag.KSS=0;
										new_f12 = p->count_cpp_status;
										col=status_request();
									}
								}
								break;
							
							case 67 : //A1 cpp FK3
								if(p->work_com[c_step].s[i].status==0)
								{
									p->work_com[c_step].s[i].status=1;
									if(p->verbose) printf("		FK3 \n");
									col=cmd_send();
									new_f12 = p->count_cpp_status;
									if ((f12->data.SS0_all==1)&&(f12->data.SS0_cpp==1)&&(f12->data.SS0_prm==1)&&(f12->data.SS0_prd==1)) //esli otet=sosto9nie 
										 p->work_com[c_step].s[i].status=2; // ispravnost'
									else p->work_com[c_step].s[i].status=3;
									if(p->verbose)printf("SS0All=%d SS0cpp=%d SS0prm=%d SS0prd=%d \n",f12->data.SS0_all, f12->data.SS0_cpp, f12->data.SS0_prm, f12->data.SS0_prd);
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
									col=cmd_send();
									new_f12 = p->count_cpp_status;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
								{
									if ((f12->data.SS1==1)&&(f12->data.SS7==4)) //esli otet=sosto9nie 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else 
									{
										//f11.zag.KSS=0;
										new_f12 = p->count_cpp_status;
										col=status_request();
									}
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
									col=cmd_send();
									new_f12 = p->count_cpp_status;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
								{								
									if ((f12->data.SS1==1)&&(f12->data.SS7==8)) //esli otet=sosto9nie 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									//else p->work_com[c_step].s[i].status=3;
									else 
									{
										//f11.zag.KSS=0;
										new_f12 = p->count_cpp_status;
										col=status_request();
									}
								}
								break;
							
							case 90:
								if(p->verbose>1)printf("status %d \n", p->work_com[c_step].s[i].status);// -----vremenno
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
									if (p->cvs ==10) f11.data.KU3=1;//  0 - TKI, 1 - RLI 
									else f11.data.KU3=0;//  0 - TKI, 1 - RLI 
									f11.data.ustKU3=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									f11.data.KU7=0;//  oslablenie 0 - 25
									f11.data.ustKU7=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
									col=cmd_send();
									new_f12 = p->count_cpp_status;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
								{
									if ((f12->data.SS0_all==1)&&(f12->data.SS1==0)&&(f12->data.SS2_0==0)&&(f12->data.SS6==0)) //ne proveryaem tki/rli
									{
										if(p->verbose)printf("ok SS0_all(1)=%d  SS1(0)=%d SS2_0(0)=%d  SS2_1(0)=%d  SS6(0)=%d\n", f12->data.SS0_all, f12->data.SS1, f12->data.SS2_0, f12->data.SS2_1, f12->data.SS6 );
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else 
									{
										//f11.zag.KSS=0;
										new_f12 = p->count_cpp_status;
										col=status_request();
										printf("ok SS0_all(1)=%d  SS1(0)=%d SS2_0(0)=%d  SS2_1(0)=%d  SS6(0)=%d\n", f12->data.SS0_all, f12->data.SS1, f12->data.SS2_0, f12->data.SS2_1, f12->data.SS6 );
									}
									printf("col=%d status=%d\n",col/2,p->work_com[c_step].s[i].status);
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
									col=cmd_send();
									new_f12 = p->count_cpp_status;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
								{
									if ((f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS1==1)&&(f12->data.SS6==0)&&(f12->data.SS8==0)&&(f12->data.SS9==0))  //esli otet pravilnii 
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
										if(p->verbose)printf("FK13_CPP ustanovlen \n");
									}
									else 
									{
										//f11.zag.KSS=0;
										new_f12 = p->count_cpp_status;
										col=status_request();
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
									//f11.zag.KSS=0;
									//col = sizeof(struct zag_CPP);
									col=status_request();
									new_f12 = p->count_cpp_status;
									if (tri>20) 
									{
										if(p->verbose)printf("IB ne zagruzhen, error step4 SS9=%d \n", f12->data.SS9);
										p->work_com[c_step].s[i].status=3;
										p->toMN3.k_o = 2;
										tri=0;
										p->verbose=verbose;
									}
									else 
										//if ((col==0x14)&&(f12->data.SS0_all==1)&&(f12->data.SS9==p->fromMN3.a_params[4]))  //esli otet pravilnii 
										if ((f12->data.SS0_all==1)&&(f12->data.SS9==1))  //esli otet pravilnii 
										{
											p->work_com[c_step].s[i].status=2; // ispravnost'
											if(p->verbose)printf("IB Zagruzhen SS9=%d OK\n", f12->data.SS9);
											tri=0;
											p->verbose=verbose;
										}
									if(p->verbose)printf("SS9=%d tri=%d col=%02x SS0=%d par4=%d \n", f12->data.SS9, tri , col , f12->data.SS0_all, p->fromMN3.a_params[4] );	
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
									col=cmd_send();
									new_f12 = p->count_cpp_status;
									tri=0;
								}
								if ((p->work_com[c_step].s[i].status==1)&&(new_f12 != p->count_cpp_status))
								{	
									if (tri>20) 
									{
										if(p->verbose)printf("IB ne peredan, error step5 SS9=%d \n", f12->data.SS9);
										p->work_com[c_step].s[i].status=3;
										p->toMN3.k_o = 2;
										tri=0;
										p->verbose=verbose;
									}
									else 
									{
										//f11.zag.KSS=0;
										new_f12 = p->count_cpp_status;
										col=status_request();
										if ((f12->data.SS0_all==1)&&(f12->data.SS9==2))  //esli otet pravilnii 
										{
											p->work_com[c_step].s[i].status=2; // ispravnost'
											if(p->verbose)printf("IB peredan, SS9=%d OK\n", f12->data.SS9);
											tri=0;
											p->verbose=verbose;
											break;
										}
									}
									//printf("SS9=%d SS2=%d tri=%d col=%02x SS0=%d par4=%d \n", f12->data.SS9, f12->data.SS2_0,tri , col , f12->data.SS0_all, p->fromMN3.a_params[4] );	
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
									col=cmd_send();
									new_f12 = p->count_cpp_status;
									if ((f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1))  //esli otet pravilnii
									{
										p->work_com[c_step].s[i].status=2; // ispravnost'
									}
									else 
									{
										if(p->verbose)printf("error step6 SS8 =%d ss0_all =%d \n",f12->data.SS8==1, f12->data.SS0_all);
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
									col=cmd_send();
									new_f12 = p->count_cpp_status;
									if ((f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS1==0)&&(f12->data.SS2_1==0)&&(f12->data.SS2_0==1)&&(f12->data.SS6==0)&&(f12->data.SS8==0)&&(f12->data.SS9==0))  //esli otet pravilnii 
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
									col=cmd_send();
									new_f12 = p->count_cpp_status;
									if ((f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS9==1))  //esli otet pravilnii 
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
									col=cmd_send();
									new_f12 = p->count_cpp_status;
									if ((f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS2_1==0)&&(f12->data.SS2_0==0)&&(f12->data.SS0_prd==1)&&(f12->data.SS6==0)&&(f12->data.SS9==2))  //esli otet pravilnii 
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
									col=cmd_send();
									new_f12 = p->count_cpp_status;
									if ((f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS0_prm==0))  //esli otet pravilnii 
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
									col=cmd_send();
									new_f12 = p->count_cpp_status;
									if ((f12->data.SS0_all)&&(p->work_com[c_step].s[i].status==1)&&(f12->data.SS8==1))  //esli otet pravilnii 
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
										//cmd_send_read();
                                        p->work_com[c_step].s[i].status=2;
                                    }
                                    break;
							
							default: 
									if(p->verbose) printf("Bad minicom %d for %d chan : %d",p->work_com[c_step].s[i].n_com,N_CHAN);					
									p->work_com[c_step].s[i].status=3;
									
						}//switch (n_com)
						//-----------------------------------------------------------------
                        	
					}//ewe ne vipoln9li
		
								
			}//step>0
			else
			{
				//------------------- timer oprosa ----------------------------------------
				timer2++;
				if (timer2 > 30) 
				{
					rli_request();
					//timer2 =0;
				}
				/*if (timer2 > 40) 
				{
					status_request();
					timer2 =0;
				} */
				if ((f181.n_form > 0)&&(p->toMN3.Mem_Region2.Mem_Region_RLI.num_words<614)) //достать Дане долги
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
					p->toMN3.Mem_Region2.Mem_Region_RLI.cr_transm_takt=7;
					p->toMN3.Mem_Region2.Mem_Region_RLI.cr_data_pac++;
					//printf("//f181 -> danye 		form181=%d 		wRLI=%d 	str=%d\n",
					//f181.n_form,wordRLI,p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_6[1]>>7);
				}	
				//-------------------------------------------------------------------------
			} 
		}//timer
		delay(20);
	}//while
	timer_delete(tm10);
}
//------------------------------------------POTOK--------------------------------------------------------
void read1()
{
	int read_udp,j,read_timer=0,rep=0;
	
	while(1)
	{
		//delay(50);
		
		//if(read_timer!=p->sys_timer)
		{
			//read_timer=p->sys_timer;
			read_udp = Udp_Client_Read(&Uc42,bbb1,1400);
			if (read_udp>0)
			{			
				
				//if(p->verbose>1) {printf("->Read %d word : ",read_udp/2); for (j=0;j<read_udp/2;j++ ) printf(" %04x",bbb1[j]); printf("\read_udp");}
				f12 = (struct from_cpp12 *)bbb1;
				//if(p->verbose>1) printf("KSS=%d II=%d TS=%d      ", f12->zag.KSS,f12->zag.II,f12->zag.TS);
				if(p->cvs==10) f12->data.SS0_prd=f12->data.SS0_prm=f12->data.SS0_all=1; // podkraasheno chto rabotaet cpp na cvs10
				switch(f12->zag.TS)
					{
						case 0x10 : if(p->verbose) printf("Check CPP link OK(TC=0x10)\n");
							break;
						case 0x11 : if(p->verbose) printf("Message loaded OK(TC=0x11)\n");
							break;
						case 0x12 : if(p->verbose>3) printf("Data recieved OK(TC=0x12)\n");
								read_rli1();
								//f18 = (struct from_cpp18 *)bbb1;
								
								//printf("N_STR=%d Time %d\n",(f18->data.form6[1]>>7)&0x1FF, p->sys_timer);
								p->count_cpp_rli++;
							break;
						case 0x13 : if(p->verbose>3) printf("No data from AK(TC=0x13)\n");
								//printf("Netu strok timer=%d TS=%04x \n", p->sys_timer, f18->zag.TS);
							break;
						case 0x14 : if(p->verbose>3) printf("CPP parameters (TC=0x14)\n");
								p->count_cpp_status++;
								p->toMN3.sost_spiak.Cpp=1; //ispavno CPP
								for(j=0;j<9;j++) p->toMN3.sost_kasrt[j]=f12->i.data_int[j];
								//if(p->verbose>1) printf("SS0=%x SS1=%x SS2=%x SS3=%x \read_udp",p->toMN3.sost_kasrt[0],p->toMN3.sost_kasrt[1],p->toMN3.sost_kasrt[2],p->toMN3.sost_kasrt[3]);
							break;
						default :   if(p->verbose) printf("Error TS (TC=%d)\n",f12->zag.TS);
							break;
					}
				//if(p->verbose) printf("\read_udp");
				rep = 0;
			}	
			else 
			{
				rep++;
				if (rep > 120) 
				{
					p->toMN3.sost_spiak.Cpp=0; //neispavno CPP
					rep = 0;
				}
			}//owibka priema
			
		}
	}
}
//-------------------------------------------------------------------------------------------------------

//---------------------------------------READ RLI--------------------------------------------------------
void read_rli1()
{
	unsigned short N_string=0;
	int i3;
	int word181; //kol-vo slov v 181
	int wordRLI; //kol-vo slov v RLI dl9 Dani
	unsigned char buff;
	//struct to_cpp11 f11Rli;

		
		f18 = (struct from_cpp18 *)bbb1;
		for(i3=0;i3<219;i3++) //perevorov baitov
		{
			buff = f18->mass1[i3*2] & 0xff;
			f18->mass1[i3*2] = f18->mass1[i3*2+1]& 0xff;
			f18->mass1[i3*2+1] = buff & 0xff;			
		} 
		//for (i3=0; i3<8; i3++)
		//{
		//	printf("%04x ",f18->data.form5[i3]);
		//	if (i3 == 4) printf(" \n");
		//}			
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
		N_string=(f18->data.form6[1]>>7)&0x1FF;
		if ((N_string-prev_str)>1) 
		{	
			for (i3=prev_str+1;i3<N_string;i3++) printf("miss str %d\n",i3);
		}
		prev_str=N_string;
		//printf("form18 = %d RLI.num_words = %d  N_STR=%d Time %d\n", f181.n_form,p->toMN3.Mem_Region2.Mem_Region_RLI.num_words,N_string&0x1FF, p->sys_timer);
//-----------------------------test end-----------------------------------------------			
					
		//printf("stoka %d=%d prinyata %d timer %d kolvo slov %d y=%d \n" ,f18->data.form6[1],p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_6[1],i2,p->sys_timer, n/2,f181.data.n_word);
		if(f18->zag.PS==1) 
		{
			printf("Posledniya stroka \n");
		}

}

short cmd_send()
{
	int i,i1,n;
	short sum;
	unsigned short *bbb2;
	
	bbb2 = (unsigned short *)&f11;
	sum=0;
	
	for(i=0;i<14;i++) sum^=bbb2[i+5];
	//if(p->verbose>2) printf("ccc[%d]=%x CKH_SUM=%04x \n",i+5,ccc[i+5],sum);}
	bbb2[sizeof(f11)/2-1]=sum;
	//if(p->verbose>2) printf("CKH_SUM=%04x \n",sum);
	if(p->verbose>2) {printf("<-Send ");for(i1=0;i1<sizeof(f11)/2;i1++) printf("%x ",bbb2[i1]);printf("\n");}
	n = Udp_Client_Send(&Uc42,bbb2,sizeof(f11));
	return 1;
}

//--------------------------------reqests---------------------------------------------------------------
//--------------------------------timer-----------------------------------------------------------------
short status_request()
{
	int i1,n;
	int col1;
	unsigned short *bbb2;
	F11Rqst.zag.marker1=0xFFFF;
	F11Rqst.zag.marker2=0xFFFF;
	F11Rqst.zag.II=2;
	F11Rqst.zag.PS=1;
	F11Rqst.zag.KSS=0;
	F11Rqst.zag.TS=3; //parametri
	col1 = sizeof(struct zag_CPP);
					
	bbb2 = (unsigned short *)&F11Rqst;
	//printf("tcp_zapros \n");
	
	//if(p->verbose>2) {printf("<-Send ");for(i1=0;i1<col1/2;i1++) printf("%x ",bbb2[i1]);printf("\n");}
	n = Udp_Client_Send(&Uc42,bbb2,sizeof(struct zag_CPP));
	//printf("<-Send %d \n", n);
	//for(i1=0;i1<col1/2;i1++) printf("%04x ",bbb2[i1]);printf("\n");
	return 1;
}
//--------------------------------RLI---------------------------------------------------------------
//--------------------------------timer-----------------------------------------------------------------
short rli_request()
{
	struct to_cpp11 f11Rli;
	int col2,n;
	//printf("RLI_zapros \n");
	f11Rli.zag.marker1=0xFFFF;
	f11Rli.zag.marker2=0xFFFF;
	f11Rli.zag.II=2;
	f11Rli.zag.PS=1;
	f11Rli.zag.KSS=0;
	f11Rli.zag.TS=2;  //zapros dannih
	col2 = sizeof(struct zag_CPP);
	
	cccc = (unsigned short *)&f11Rli;
	
	
	n = Udp_Client_Send(&Uc42,cccc,col2);
	return 1;
}