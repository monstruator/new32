//obmen s mn3 i vibor comandi
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/kernel.h>
  #include <netinet/in.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <netdb.h>
  #include <math.h>
  //#include "../include/func_IP.h"
  #include "../include/IP_nb.h"
  #include "../include/shared_mem.h"
  #include <string.h>
  #include <i86.h>
  #include <conio.h>
  #define SNT "/home/new32/src1/test"
  #define SNT1 "/home/new32/"
  #define MS 1000000
  char          pack_buf[1500];  
  short ver_cvs(unsigned int );
  unsigned int ver;
   
struct my_comp {
	nid_t cpc_num;
    nid_t node_num;
	char sys_name[80];
	char przn_PC[10];
			   };

void main(int argc, char **argv)
{//--- KOHCTAHTbl npu6opa 1.0 ---//
		int sock, length, i , i32 , ii = 0, count_mes=0, i1 , i_p=0 , i2=0, i3=0 , j;
		static Udp_Client_t Uc42;
		static Udp_Client_t Uc43;
		short c_step=0,TC10=0;	
		short sen;
		short num_word=0;
		char bufi[1024];
		char bufo[1024];
		char out_buf[1024];
		//char name[30] ="SPIAK_N8_Eth2";// "192.168.3.1";
		char *name ="SPIAK_N8_Eth2";// "192.168.3.1";
//------------------------------------------TEST pribora 3.2-------------------------------------------
		char *name1 ="SPIAK_4_2"; // !!!!!!!!!!!!!!!! V processe!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		short SRC_PORT1=4005;
		short DST_PORT1=4005;
//---------------------------------------End test pribora 3.2------------------------------------------
		short SRC_PORT=4003;  //???
		short DST_PORT=4000;  //???
		int r,bytes,COM=0, newcmd=0;
		char cmd=0, cmd1 =0;
		short n_s=0; //nomer waga zapolneni9 komabdi
		short n_mc=0; //nomer mini comandi na tekuwem wage
		packusoi p1;
		packcmd p2;
    	timer_t id;
 		struct itimerspec timer;
    	struct sigevent event;
		struct from_cpp12 *f12;
		pid_t pid, proxym;
		long timer_mn3=0;
		unsigned char num_mess=0;


	delay(1500);
	open_shmem();
	delay(1000);
	p->verbose=0; //default
	p->cvs=0;  //default
	InitArgs( argc, argv );
	
	p->cvs = ver_cvs(ver);  //-------------------- opredelenie nomera CVS--------------------------
	printf("START M03A<->PULT cvs=%d verbose=%d\n",p->cvs,p->verbose);
	//printf("CVS = %d \n", ver);
	
	//outp(0x37a, inp(0x37a)|0x24);
	//node_n=getnid();
	//requested_n=inp(0x378)&0xF;
	//printf("nomer ebm %d \n", requested_n);
	p->cur_step=0;
	
	if (p->cvs==10) 
	{
		name="192.168.3.1";// ;"SPIAK_N8_Eth2"
		//name="192.168.1.2";
		SRC_PORT=4001;
		DST_PORT=4001;
	}
	else 
	{
		name ="SPIAK_N9_Eth4";// "192.168.1.2";
		SRC_PORT=4002;
		DST_PORT=4002;
		i = Udp_Client_Ini(&Uc43,name1,DST_PORT1,SRC_PORT1);
		printf("Udp_Init_3.2=%d	dst=%d src=%d %s \n", i,DST_PORT1,SRC_PORT1, name1);
	}
	i = Udp_Client_Ini(&Uc42,name,DST_PORT,SRC_PORT);
	printf("Udp_Init=%d	dst=%d src=%d %s \n", i,DST_PORT,SRC_PORT, name);
	

	while(1)
	{
	   	if (timer_mn3!=p->sys_timer) //timer
		{
		   // printf("timer %d timer mn3 %d  word=%d \n", p->sys_timer, timer_mn3,p->toMN3.Mem_Region2.Mem_Region_RLI.num_words);
			timer_mn3=p->sys_timer;
			//TCount++;
			TC10++;
			//printf("%d\n", TC10);
			if (TC10==2) 
			{
				TC10=0;
				bytes = Udp_Client_Read(&Uc42,bufi,1400);
				//if (p->cvs==11) bytes = Udp_Client_Read(&Uc43,bufi,1400);//--------------------TEST 3.2----------------
				if (bytes>0)
				{
					//printf(" Udp_READ1=%d	%d\n", bytes, ii++);
					//printf("\n<===== ");for(i=0;i<28;i++) printf(" %d ", bufi[i]);
					memcpy(&p->inbufMN3,&bufi,sizeof(packcmd));
					if (p->inbufMN3.cr_com != cmd) 
					{	
						cmd = p->inbufMN3.cr_com;
						newcmd = 1;
					}
					else newcmd = 0;
					//p->toMN3.Mem_Region_RLI.cr_data_pac++;
					
					memcpy(pack_buf,&p->toMN3,sizeof(packusoi)); ///!!!!!!
					pack_buf[0]=70;
					pack_buf[1]=num_mess++;
					pack_buf[2]=1;
					pack_buf[3]=1;
		
					//printf("cr_com->MO3 = %d \n",	p->toMN3.cr_com);
					//for(j=0;j<9;j++) printf("%08x ",p->toMN3.sost_kasrt[j]);  printf("\n");
					//if(p->verbose>1) printf("SS0=%x SS1=%x SS2=%x SS3=%x \n",p->toMN3.sost_kasrt[0],p->toMN3.sost_kasrt[1],p->toMN3.sost_kasrt[2],p->toMN3.sost_kasrt[3]);
	     			i = Udp_Client_Send(&Uc42,pack_buf,sizeof(packusoi));
					if (p->cvs==11) i = Udp_Client_Send(&Uc43,pack_buf,sizeof(packusoi));//---------------TEST 3.2-----------
					
					//printf("Send i = %d\n ",i);
					//printf("\n=====> ");for(i1=0;i1<i;i1++) printf(" %d ", pack_buf[i1]);printf("\n");
				}
				
				else if (p->cvs==11) 
				{
					bytes = Udp_Client_Read(&Uc43,bufi,1400);//------------------------------------
					if (bytes>0)
					{
						//printf(" Udp_READ2=%d	%d\n", bytes, ii++);
						//printf("\n<===== ");for(i=0;i<28;i++) printf(" %d ", bufi[i]);

						memcpy(&p->inbufMN3,&bufi,sizeof(packcmd));
						if (p->inbufMN3.cr_com != cmd1) 
						{	
							cmd1 = p->inbufMN3.cr_com;
							newcmd = 1;
						}
						else newcmd = 0;
						//p->toMN3.Mem_Region_RLI.cr_data_pac++;
					
						memcpy(pack_buf,&p->toMN3,sizeof(packusoi)); ///!!!!!!
						pack_buf[0]=70;
						pack_buf[1]=num_mess++;
						pack_buf[2]=1;
						pack_buf[3]=1;
		
						//printf("cr_com->MO3 = %d \n",	p->toMN3.cr_com);
						//for(j=0;j<9;j++) printf("%08x ",p->toMN3.sost_kasrt[j]);  printf("\n");
						//if(p->verbose>1) printf("SS0=%x SS1=%x SS2=%x SS3=%x \n",p->toMN3.sost_kasrt[0],p->toMN3.sost_kasrt[1],p->toMN3.sost_kasrt[2],p->toMN3.sost_kasrt[3]);
						//i = Udp_Client_Send(&Uc42,pack_buf,sizeof(packusoi));
						i = Udp_Client_Send(&Uc43,pack_buf,sizeof(packusoi));
	
						//printf("Send i = %d\n ",i);
						//printf("\n=====> ");for(i1=0;i1<10;i1++) printf(" %d ", pack_buf[i1]);printf("\n");
						//printf("\n=====> ");for(i1=11;i1<21;i1++) printf(" %d ", pack_buf[i1]);printf("\n");
					}
				}
			}
			
			if ((p->toMN3.Mem_Region2.Mem_Region_RLI.num_words>600)&&(p->cvs==10)) //есть данные РЛИ
			{
				memcpy(pack_buf,&p->toMN3,sizeof(packusoi)); 
				pack_buf[0]=70;
				pack_buf[1]=num_mess++;
				pack_buf[2]=1;
				pack_buf[3]=1;
				num_word=p->toMN3.Mem_Region2.Mem_Region_RLI.num_words;
				//printf("RLI=%d  t=%d str1=%d str2=%d str3=%d\n",
				//p->toMN3.Mem_Region2.Mem_Region_RLI.num_words, p->sys_timer,(p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_6[1]>>7)&0x1FF,(p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_6[203]>>7)&0x1FF,(p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_6[405]>>7)&0x1FF);
				i = Udp_Client_Send(&Uc42,pack_buf,sizeof(packusoi));
				p->toMN3.Mem_Region2.Mem_Region_RLI.num_words=0;
				//printf("Send2 %d RLI word timer %d  N_STRING=%d \n",num_word, p->sys_timer,p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_6[1]);
				//for(i3=0;i3<6;i3++)	printf(" %04x ",p->toMN3.Mem_Region2.Mem_Region_RLI.SVCH_FORM_SACH[i3]);printf("\n");
			}
           //--------------------------------------------------------------------------- 
			if ((newcmd) && (!p->cur_step)) // new command from MN3
//			if ((p->fromMN3.cr_com==0)||(p->fromMN3.cr_com!=p->inbufMN3.cr_com)) // new command from MN3
			{
                p->toMN3.num_com = p->inbufMN3.num_com;
                p->toMN3.lp2_param = p->inbufMN3.a_params[0];
                p->toMN3.kzv = 0;
                p->toMN3.k_o = 0;
               // p->toMN3.ended_loop = 0;
               // p->toMN3.krk = 0;
                p->toMN3.link = 0;
				newcmd = 0;
				p->fromMN3=p->inbufMN3; //utvergdaem komandu
					
				printf("\n-------------------   New command : %d , param: %d %d %d    time=%d   ---------\n",p->fromMN3.num_com,p->fromMN3.a_params[0],p->fromMN3.a_params[1],p->fromMN3.a_params[2],p->sys_timer);
				switch (p->fromMN3.num_com)
				{
				case 1 : 
					n_s=1;  n_mc=0;//nomer waga //s4et4ik mini komamdi
					p->work_com[n_s].s[n_mc].n_chan=2;
					p->work_com[n_s].s[n_mc].n_com=1; //SVCH work		
                    n_mc++; //kol-vo mini komand + 1
					
					if (p->cvs==10)
					{
						p->work_com[n_s].s[n_mc].n_chan=3; //rele
						if (p->fromMN3.a_params[0]) p->work_com[n_s].s[n_mc].n_com=51;
						else	p->work_com[n_s].s[n_mc].n_com=50;						
						n_mc++; //kol-vo mini komand + 1
					}
					//---------------------------------------------
					p->work_com[n_s].t_stop =p->sys_timer+200;
					//---------------------------------------------
					/*n_s=2;  n_mc=0; //nomer waga //s4et4ik mini komamdi
					p->work_com[n_s].s[n_mc].n_chan=6; //T625
					p->fromMN3.a_params[0]=0;
					p->work_com[n_s].s[n_mc].n_com=2; //vibor SVCH
					n_mc++; //kol-vo mini komand + 1						
					p->work_com[n_s].t_stop =p->sys_timer+600;
					p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s
						*/
 						break;
				case 4 :
						if (p->cvs==10)
						{
							n_s=1;  n_mc=0; //nomer waga //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=3;
							if (p->fromMN3.a_params[0]) p->work_com[n_s].s[n_mc].n_com=31; //rele 3 on/off
							else p->work_com[n_s].s[n_mc].n_com=30;
							n_mc++; //kol-vo mini komand + 1
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
							p->work_com[n_s].t_stop =p->sys_timer+100; 
							//-----------------------------------------------------------
							n_s=2;  n_mc=0; //nomer waga //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=3;
							if (p->fromMN3.a_params[1]) p->work_com[n_s].s[n_mc].n_com=10; //rele 1 on/off
							else p->work_com[n_s].s[n_mc].n_com=11;
							n_mc++; //kol-vo mini komand + 1
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
							p->work_com[n_s].t_stop =p->sys_timer+100;
							//-----------------------------------------------------------
							n_s=3;  n_mc=0; //nomer waga //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=3;
							if (p->fromMN3.a_params[0]) p->work_com[n_s].s[n_mc].n_com=61; //rele 6 on/off
							else p->work_com[n_s].s[n_mc].n_com=60;
							n_mc++; //kol-vo mini komand + 1
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
							p->work_com[n_s].t_stop =p->sys_timer+100;
							//-----------------------------------------------------------
							if (p->fromMN3.a_params[0]) // R999 onn
							{
								n_s=4;  n_mc=0; //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=4;
								p->work_com[n_s].s[n_mc].n_com=4;  //R999 BASE SETUP 
								n_mc++; //kol-vo mini komand + 1						
								p->work_com[n_s].t_stop =p->sys_timer+300;        //2 sec                
								p->work_com[n_s].num_mini_com=n_mc;   
								//-----------------------------------------------------------
								/*n_s=4;  n_mc=0; //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=3;
								p->work_com[n_s].s[n_mc].n_com=30;  //pause
								n_mc++; //kol-vo mini komand + 1						
								p->work_com[n_s].t_stop =p->sys_timer+100;        //2 sec                
								p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s 
								*/
								//-----------------------------------------------------------						
								n_s=5;  n_mc=0; //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=4;
								p->work_com[n_s].s[n_mc].n_com=80;  //reqest
								n_mc++; //kol-vo mini komand + 1						
								p->work_com[n_s].t_stop =p->sys_timer+300;        //2 sec                
								p->work_com[n_s].num_mini_com=n_mc;
								//-----------------------------------------------------------
							}
							/*n_s=6;  n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=3;
							p->work_com[n_s].s[n_mc].n_com=30;  //pause
							n_mc++; //kol-vo mini komand + 1						
							p->work_com[n_s].t_stop =p->sys_timer+200;        //2 sec                
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s 
							//-----------------------------------------------------------	
							n_s=7;  n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=4;
							p->work_com[n_s].s[n_mc].n_com=1;  //READ r999
							n_mc++; //kol-vo mini komand + 1						
							p->work_com[n_s].t_stop =p->sys_timer+300;        //2 sec                
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s 
							//-----------------------------------------------------------	
							*/
						}
						else
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;
							p->work_com[n_s].s[n_mc].n_com=101;//all ok status=2
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
							p->work_com[n_s].t_stop =p->sys_timer+100;
							//p->kol_step=n_s; //obwee kol-vo wagov na dannom wage  
						}
						p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
						break;
				case 5 :
					if (p->cvs==11)
					{
						if ((p->fromMN3.a_params[0]>0)&&(p->fromMN3.a_params[0]<7))
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;
							p->work_com[n_s].s[n_mc].n_com=5;//SVCH PRD-PRM CHAN
							n_mc++; //kol-vo mini komand + 1
							p->work_com[n_s].t_stop = p->sys_timer+300;
							//---------------------------------------------
							//p->kol_step=n_s; //obwee kol-vo wagov na dannom wage 
							
						}
						else 
						{
							printf("Bad param0 : %d\n",p->fromMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
					}
					else
					{
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=2;
						p->work_com[n_s].s[n_mc].n_com=101;//all ok status=2
						n_mc++; //kol-vo mini komand + 1
						p->work_com[n_s].t_stop =p->sys_timer+100;
						//---------------------------------------------
					}
					
						break;
				case 10 : case 11 :
							if ((p->fromMN3.a_params[0]>=0)&&(p->fromMN3.a_params[0]<40)&&
							    (p->fromMN3.a_params[1]>=0)&&(p->fromMN3.a_params[1]<4)&&
								(p->fromMN3.a_params[2]>=0)&&(p->fromMN3.a_params[2]<4))
							{	
								n_s=1;  //nomer waga
								n_mc=0; //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=4;
								p->work_com[n_s].s[n_mc].n_com=p->fromMN3.num_com;
								n_mc++; //kol-vo mini komand + 1
								//---------------------------------------------
								p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
								p->work_com[n_s].t_stop =p->sys_timer+100; 
								
								n_s=2;  n_mc=0; //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=4;
								p->work_com[n_s].s[n_mc].n_com=80;  //reqest
								n_mc++; //kol-vo mini komand + 1						
								p->work_com[n_s].t_stop =p->sys_timer+200;        //2 sec                
							}
							else 
							{
								printf("Bad param0 : %d\n",p->fromMN3.a_params[0]);
								p->toMN3.kzv=1;
								p->toMN3.cr_com++;
							}
							break;		
				case 8 : case 12 :
						if ((p->fromMN3.a_params[0]>=0)&&(p->fromMN3.a_params[0]<2))
						{
							n_s=1; n_mc=0; //nomer waga //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;
							p->work_com[n_s].s[n_mc].n_com=p->fromMN3.num_com; //nado naoborot
							n_mc++; //kol-vo mini komand + 1
							
							//---------------------------------------------
							p->work_com[n_s].t_stop =p->sys_timer+500;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->fromMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
				case 14 :
					if ((p->fromMN3.a_params[0]>=0)&&(p->fromMN3.a_params[0]<2))
						{
							if (p->cvs==11) 
							{
								n_s=1;  n_mc=0;//nomer waga  //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=2;
								p->work_com[n_s].s[n_mc].n_com=p->fromMN3.num_com;
								n_mc++; //kol-vo mini komand + 1
								p->work_com[n_s].t_stop =p->sys_timer+100;  
							}
							else 
							{
								n_s=1;  n_mc=0;//nomer waga //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=3;//rele
								p->work_com[n_s].s[n_mc].n_com=40;
								n_mc++; //kol-vo mini komand + 1
								//---------------------------------------------
								p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
								p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
								p->work_com[n_s].t_stop =p->sys_timer+100;  
							}
							/*
							n_s=2;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=3;
							p->work_com[n_s].s[n_mc].n_com=50;
							n_mc++; //kol-vo mini komand + 1
							
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
							p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
							p->work_com[n_s].t_stop =p->sys_timer+200;  					
							*/
						}
						else 
						{
							printf("Bad param0 : %d\n",p->fromMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
				case 15 : 
						if ((p->fromMN3.a_params[0]>=0)&&(p->fromMN3.a_params[0]<2))
						{
							if (p->cvs==11) 
							{
								n_s=1;  //nomer waga
								n_mc=0; //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=2;
								p->work_com[n_s].s[n_mc].n_com=p->fromMN3.num_com;
								n_mc++; //kol-vo mini komand + 1
								//---------------------------------------------
								p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
								p->work_com[n_s].t_stop =p->sys_timer+100;  
							}
							else 
							{
								n_s=1;  n_mc=0;//nomer waga//s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=3;//rele
								p->work_com[n_s].s[n_mc].n_com=41;
								n_mc++; //kol-vo mini komand + 1
								p->work_com[n_s].t_stop =p->sys_timer+100;  
							}

							/*n_s=2;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=3;
							p->work_com[n_s].s[n_mc].n_com=40;
							n_mc++; //kol-vo mini komand + 1
							
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
							p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
							p->work_com[n_s].t_stop =p->sys_timer+200;  
							*/						
						}
						else 
						{
							printf("Bad param0 : %d\n",p->fromMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;					
				case 25 : // vkluchenie peredachi na r999
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=3;
						if (p->fromMN3.a_params[0]) p->work_com[n_s].s[n_mc].n_com=21;
						else p->work_com[n_s].s[n_mc].n_com=20; //! 20
						n_mc++; //kol-vo mini komand + 1
						p->work_com[n_s].t_stop =p->sys_timer+100; 
						//---------------------------------------------
						break;
				case 30 :
					if (p->cvs==11)
					{
						if ((p->fromMN3.a_params[0]>=0)&&(p->fromMN3.a_params[0]<26))
						{
							//printf("2!!\n");
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;
							p->work_com[n_s].s[n_mc].n_com=p->fromMN3.num_com; //SVCH ATT
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].t_stop =p->sys_timer+100;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->fromMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 					}
					else 						
					{
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=2;
						p->work_com[n_s].s[n_mc].n_com=101;//all ok status=2
						n_mc++; //kol-vo mini komand + 1
						//---------------------------------------------
						p->work_com[n_s].t_stop =p->sys_timer+100;
					}  
					break;
				case 32 : case 33: case 42 : case 43:
						if ((p->fromMN3.a_params[0]>=0)&&(p->fromMN3.a_params[0]<26))
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;
							p->work_com[n_s].s[n_mc].n_com=p->fromMN3.num_com;
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].t_stop =p->sys_timer+100;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->fromMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
				case 60 : 	  // rabota
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=2;
						p->work_com[n_s].s[n_mc].n_com=63; //rabota
						n_mc++; //kol-vo mini komand + 1
					//---------------------------------------------
						p->work_com[n_s].t_stop =p->sys_timer+200;                        
 						break;	
				case 61 : 	  
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=2;
						p->work_com[n_s].s[n_mc].n_com=61; //SVCH status
						n_mc++; //kol-vo mini komand + 1
					//---------------------------------------------
						p->work_com[n_s].t_stop =p->sys_timer+100;                        
 						break;	
				case 62 : //t625 rqst
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=6; //t625
						if (p->cvs==11) p->work_com[n_s].s[n_mc].n_com=1;
						else p->work_com[n_s].s[n_mc].n_com=101;
						n_mc++; //kol-vo mini komand + 1
						//---------------------------------------------
						p->work_com[n_s].t_stop =p->sys_timer+300;   
						break;
				case 63 : //t625 SVCH/DMW
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=6; //t625
						p->work_com[n_s].s[n_mc].n_com=2;
						n_mc++; //kol-vo mini komand + 1
						//---------------------------------------------
						p->work_com[n_s].t_stop =p->sys_timer+100;   
						break;
						
				case 65 : //FK2
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=2; //cpp
						p->work_com[n_s].s[n_mc].n_com=64;
						n_mc++; //kol-vo mini komand + 1
						//---------------------------------------------
						p->work_com[n_s].t_stop =p->sys_timer+100;   
						break;
						
				case 78 :    
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=1;
						p->work_com[n_s].s[n_mc].n_com=2;
						n_mc++; //kol-vo mini komand + 1						
                        p->work_com[n_s].t_stop =p->sys_timer+100;                        
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
					//---------------------------------------------
						n_s=2;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=1;
						p->work_com[n_s].s[n_mc].n_com=2;
						n_mc++; //kol-vo mini komand + 1						
                        p->work_com[n_s].t_stop =p->sys_timer+200;                        
						//printf("­®¬Ґа Є ­ «  ­  ­г«Ґў®¬ и ЈҐ = %d\n",p->work_com[0].s[0].n_chan);
 						break;
				case 80 :    
					n_s=1;  n_mc=0; //s4et4ik mini komamdi
					p->work_com[n_s].s[n_mc].n_chan=4;
					p->work_com[n_s].s[n_mc].n_com=80;  //reqest
					n_mc++; //kol-vo mini komand + 1						
					p->work_com[n_s].t_stop =p->sys_timer+200;        //2 sec                 
					//--------------------------------------------
					//printf("­®¬Ґа Є ­ «  ­  ­г«Ґў®¬ и ЈҐ = %d\n",p->work_com[0].s[0].n_chan);
 						break;
				case 90 :   
					printf("Check work start \n");				
					if (p->cvs==11)
					{
						n_s=1;  n_mc=0;//nomer waga //s4et4ik mini komamdi
						printf("status %d \n", p->work_com[c_step].s[i].status);// -----vremenno
						p->work_com[n_s].s[n_mc].n_chan=2;
						p->work_com[n_s].s[n_mc].n_com=90; //SVCH work
						n_mc++; //kol-vo mini komand + 1
						p->work_com[n_s].t_stop =p->sys_timer+300;
					}
					else
					{
						n_s=1;  n_mc=0;//nomer waga //s4et4ik mini komamdi
						printf("status %d \n", p->work_com[c_step].s[i].status);// -----vremenno
						p->work_com[n_s].s[n_mc].n_chan=2;
						p->work_com[n_s].s[n_mc].n_com=90; //SVCH work
						n_mc++; //kol-vo mini komand + 1
						p->work_com[n_s].t_stop =p->sys_timer+300;
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
					//---------------------------------------------	
						/*n_s=2;  n_mc=0; 
						p->work_com[n_s].s[n_mc].n_chan=3; //rele
						if (p->fromMN3.a_params[0]) p->work_com[n_s].s[n_mc].n_com=51;
						else	p->work_com[n_s].s[n_mc].n_com=50;						
						n_mc++; //kol-vo mini komand + 1						
						p->work_com[n_s].t_stop =p->sys_timer+600;
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s
						*/
					} 
					
 					break;
				case 92 : //FK SPIAK
					switch (p->fromMN3.a_params[0])
					{
					case 1 : //FK 1-1	
							n_s=1;  n_mc=0; //nomer waga //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;
							if (p->cvs==11) p->work_com[n_s].s[n_mc].n_com=65;
							else p->work_com[n_s].s[n_mc].n_com=651;
							n_mc++; //kol-vo mini komand + 1
							p->work_com[n_s].t_stop =p->sys_timer+300;
						break;
					case 2 : //FK 1-2	
							n_s=1;  n_mc=0; //nomer waga //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;
							if (p->cvs==10) p->work_com[n_s].s[n_mc].n_com=652;
							else p->work_com[n_s].s[n_mc].n_com=653;
							n_mc++; //kol-vo mini komand + 1
							p->work_com[n_s].t_stop =p->sys_timer+300;
							break;
					case 3 : //FK 2	
							n_s=1;  n_mc=0; //nomer waga //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;
							p->fromMN3.a_params[0]=1; //FK 1 CPP
							if(p->cvs==11) p->work_com[n_s].s[n_mc].n_com=66;   //FK
							else p->work_com[n_s].s[n_mc].n_com=101;
							n_mc++; //kol-vo mini komand + 1
							p->work_com[n_s].t_stop =p->sys_timer+300;  
							break;
					case 4 : //FK 3	
							n_s=1;  n_mc=0; //nomer waga //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;
							p->work_com[n_s].s[n_mc].n_com=67;   //FK
							n_mc++; //kol-vo mini komand + 1
							p->work_com[n_s].t_stop =p->sys_timer+300;
							break;
					case 5 :  // FK4
							n_s=1;  n_mc=0; //nomer waga //s4et4ik mini komamdi
							if(p->cvs==11) 
							{	
								p->work_com[n_s].s[n_mc].n_chan=6; //T625
								p->work_com[n_s].s[n_mc].n_com=1;   //CHECK
							}
							else 
							{
								p->work_com[n_s].s[n_mc].n_chan=2;  //Cpp
								p->work_com[n_s].s[n_mc].n_com=101; // Command OK
							}
							n_mc++; //kol-vo mini komand + 1
							p->work_com[n_s].t_stop =p->sys_timer+300;  
							break;
					case 6 : //FK 5	
							if(p->cvs==11) 
							{
								n_s=1;  n_mc=0; //nomer waga //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=2;    //Cpp
								p->work_com[n_s].s[n_mc].n_com=921;   //FK13_CPP
								n_mc++; //kol-vo mini komand + 1
								p->work_com[n_s].t_stop =p->sys_timer+100;
								p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
					//---------------------------------------------
								n_s=2;  n_mc=0; //nomer waga //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=6; //T625
								p->fromMN3.a_params[1]=48900; //vrem9
								p->fromMN3.a_params[2]=555;
								p->fromMN3.a_params[3]=161;
								p->work_com[n_s].s[n_mc].n_com=922; //T625 peredacha fomulyara
								n_mc++; //kol-vo mini komand + 1						
								p->work_com[n_s].t_stop =p->sys_timer+600;
								p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s
					//---------------------------------------------
								n_s=3;  n_mc=0; //nomer waga //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=2; //Cpp
								p->work_com[n_s].s[n_mc].n_com=922; //IB zagruzhen
								p->fromMN3.a_params[4]=1;
								n_mc++; //kol-vo mini komand + 1						
								p->work_com[n_s].t_stop =p->sys_timer+600;
								p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s
					//---------------------------------------------
								n_s=4;  n_mc=0; //nomer waga //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=2; //Cpp
								p->work_com[n_s].s[n_mc].n_com=923; //IB peredan
								//p->fromMN3.a_params[4]=2;
								n_mc++; //kol-vo mini komand + 1						
								p->work_com[n_s].t_stop =p->sys_timer+600;
								p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s
					//---------------------------------------------
					/*			n_s=6;  n_mc=0; //nomer waga //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=2; //Cpp
								p->work_com[n_s].s[n_mc].n_com=924;
								n_mc++; //kol-vo mini komand + 1						
								p->work_com[n_s].t_stop =p->sys_timer+600;
								p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s
					*/
					//---------------------------------------------
					/*			n_s=5;  
								n_mc=0; //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=6; //t625
								p->work_com[n_s].s[n_mc].n_com=923; //nomer waga   sravnenie massiva
								n_mc++; //kol-vo mini komand + 1						
								p->work_com[n_s].t_stop =p->sys_timer+1000;
								p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s
							*/
							}
					
							else 
							{
								n_s=1;  n_mc=0;
								p->work_com[n_s].s[n_mc].n_chan=2;    //Cpp
								p->work_com[n_s].s[n_mc].n_com=101; // Command OK
								p->work_com[n_s].t_stop =p->sys_timer+300;
								p->work_com[n_s].num_mini_com=n_mc;
							}
							break;	
					case 7 :  // FK6
							n_s=1;  n_mc=0; //nomer waga //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;  //Cpp
							p->work_com[n_s].s[n_mc].n_com=68; // fk
							n_mc++; //kol-vo mini komand + 1
							p->work_com[n_s].t_stop =p->sys_timer+300;  
							break;
						
					case 8 :  // FK7
							n_s=1;  n_mc=0; //nomer waga //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;  //Cpp
							p->work_com[n_s].s[n_mc].n_com=69; // fk
							n_mc++; //kol-vo mini komand + 1
							p->work_com[n_s].t_stop =p->sys_timer+300;  
							break;
						default : 
						printf("Bad param0 : %d\n",p->fromMN3.a_params[0]);
						p->toMN3.kzv=1;
						p->toMN3.cr_com++;						
					}
 					break;
				case 100 : //rele_off
						if ((p->fromMN3.a_params[0]>=0)&&(p->fromMN3.a_params[0]<9))
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=3;
							p->work_com[n_s].s[n_mc].n_com=10*p->fromMN3.a_params[0];
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].t_stop =p->sys_timer+100;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->fromMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
				case 101 : //rele_onn
						if ((p->fromMN3.a_params[0]>=0)&&(p->fromMN3.a_params[0]<9))
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=3;
							p->work_com[n_s].s[n_mc].n_com=10*p->fromMN3.a_params[0]+1;
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].t_stop =p->sys_timer+100;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->fromMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
					case 102 : //n_chan r999
						if ((p->fromMN3.a_params[0]>=0)&&(p->fromMN3.a_params[0]<40))
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=4;
							p->work_com[n_s].s[n_mc].n_com=1;
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].t_stop =p->sys_timer+100;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->fromMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
					case 103 : //power r999
						if ((p->fromMN3.a_params[0]>=0)&&(p->fromMN3.a_params[0]<4))
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=4;
							p->work_com[n_s].s[n_mc].n_com=2;
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].t_stop =p->sys_timer+100;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->fromMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
					
					case 93 : //ust svyaz' s AK
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=2; //cpp_tcp
						p->work_com[n_s].s[n_mc].n_com=93;
						n_mc++; //kol-vo mini komand + 1
						p->work_com[n_s].t_stop =p->sys_timer+200;   
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
					//---------------------------------------------
						n_s=2;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi 12.08.2016
						p->work_com[n_s].s[n_mc].n_chan=6; //T625
						p->work_com[n_s].s[n_mc].n_com=93;
						n_mc++; //kol-vo mini komand + 1						
                        p->work_com[n_s].t_stop =p->sys_timer+200;
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s 
					//---------------------------------------------
						n_s=3;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=6; //T625
						p->work_com[n_s].s[n_mc].n_com=931;
						n_mc++; //kol-vo mini komand + 1						
                        p->work_com[n_s].t_stop =p->sys_timer+200;
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s
					//---------------------------------------------						
						n_s=4;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=2; //cpp_tcp
						p->work_com[n_s].s[n_mc].n_com=931;
						n_mc++; //kol-vo mini komand + 1
						p->work_com[n_s].t_stop =p->sys_timer+200;   
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s 
					//---------------------------------------------						
						n_s=5;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=2; //cpp_tcp
						p->work_com[n_s].s[n_mc].n_com=932;
						n_mc++; //kol-vo mini komand + 1
						p->work_com[n_s].t_stop =p->sys_timer+200;   
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s 	
					//---------------------------------------------						
						n_s=6;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=2; //cpp_tcp
						p->work_com[n_s].s[n_mc].n_com=933;
						n_mc++; //kol-vo mini komand + 1
						p->work_com[n_s].t_stop =p->sys_timer+200;   
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s 
					//---------------------------------------------						
						n_s=7;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=2; //cpp_tcp
						p->work_com[n_s].s[n_mc].n_com=934;
						n_mc++; //kol-vo mini komand + 1
						p->work_com[n_s].t_stop =p->sys_timer+200;   
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s 
					//---------------------------------------------
						n_s=8;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=6; //T625
						p->work_com[n_s].s[n_mc].n_com=932;
						n_mc++; //kol-vo mini komand + 1						
                        p->work_com[n_s].t_stop =p->sys_timer+200;
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s
						break;
					
					case 193 : //t625 inf
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=6; //t625
						p->work_com[n_s].s[n_mc].n_com=3;
						n_mc++; //kol-vo mini komand + 1
						//---------------------------------------------
						p->work_com[n_s].t_stop =p->sys_timer+300;   
						break;
				//	case 111 : //t625 rqst
				//		n_s=1;  //nomer waga
				//		n_mc=0; //s4et4ik mini komamdi
				//		p->work_com[n_s].s[n_mc].n_chan=6; //t625
				//		p->work_com[n_s].s[n_mc].n_com=1;	
				//		n_mc++; //kol-vo mini komand + 1
						//---------------------------------------------
				//		p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
				//		p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
				//		p->work_com[n_s].t_stop =p->sys_timer+100;   
				//		break;
					default:    
                        printf("Bad command : %d\n",p->fromMN3.num_com);
						p->toMN3.kzv=1;
						p->toMN3.cr_com++;
				} //switch komandi
				
				p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s (poslednem) 
				p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
						
				
				if (p->toMN3.kzv!=1) 
				{
					p->cur_step=1;
					
				}
	
			} //nova9 komanda
			
			//Proverka wagov vipolneni9 komandi--------------------------
			if (p->cur_step!=0)
			{
				//printf("done_com=%d", p->work_com[c_step].done_mini_com);
				c_step=p->cur_step;
				p->work_com[c_step].done_mini_com=0; //zanovo s4itaem kol-vo vopolnennih
				for (i=0;i<p->work_com[c_step].num_mini_com;i++) //prosmotrim vse statusi
				{
					if(p->work_com[c_step].s[i].status==2) //esli wag vipolnen
						p->work_com[c_step].done_mini_com++; //zanovo s4itaem kol-vo vopolnennih
					if(p->work_com[c_step].s[i].status==3) //esli owibka
					{
						printf("Command %d error , time=%d . ",p->fromMN3.num_com,p->sys_timer);
						printf("Step=%d Interf=%d . \n",c_step,p->work_com[c_step].s[i].n_chan);
						// NADO GOTOVIT' AVARIINOE ZAVERW KOMANDI---------------
						//------------------------------------------------------
						//------------------------------------------------------	
						//------------------------------------------------------
						p->toMN3.kzv=1;
						p->toMN3.cr_com++;
						ResetCom();
												
					}
				}
				//if(p->verbose>2) printf("wipolneno na %d wage %d comand, time %d\n",c_step, p->work_com[c_step].done_mini_com, timer_mn3);
				if (p->toMN3.kzv!=1)
				{
					if(p->work_com[c_step].t_stop<p->sys_timer) //esli timer istek
					{
						printf("Command %d timeout , time=%d . ",p->fromMN3.num_com,p->sys_timer);
						printf("Step=%d Interf=%d . \n",c_step,p->work_com[c_step].s[i].n_chan);
						// NADO GOTOVIT' AVARIINOE ZAVERW KOMANDI---------------
						//------------------------------------------------------
						//------------------------------------------------------	
						//------------------------------------------------------
						p->toMN3.kzv=1;
						p->toMN3.cr_com++;
						ResetCom();		
					}
					else 
					if (p->work_com[c_step].done_mini_com==p->work_com[c_step].num_mini_com) //vipolneni vse
					{	 printf("step=%d time=%d\n",p->cur_step,p->sys_timer);p->cur_step++;}
				}
			}
			if ((p->cur_step > p->kol_step) && (p->kol_step!=0)) //vse wagi proideni, komanda vopolnena
			{
				printf("\n-------------------   Command %d complete , time=%d   -------------------\n",p->fromMN3.num_com,p->sys_timer);
				// NADO GOTOVIT' DANNIE DL9 MN3 ------------------------
				//------------------------------------------------------
				//------------------------------------------------------	
				//------------------------------------------------------
				p->toMN3.kzv=0;
				p->toMN3.cr_com++;
			
				ResetCom();		

			}

		}//proxy timer
	}//while   
}

void InitArgs( int argc, char **argv )
{
   int c;

   while( ( c = getopt( argc, argv, "c:v" ) ) != -1 ) {
      switch( c ) {
      
      case 'c':
         //p->cvs = atoi( optarg );
         break;
      case 'v':
         p->verbose++;
         break;
      default:
         errno = EINVAL;
         perror( argv[0] );
         break;
      }
   }
} 

short ver_cvs(unsigned int ver)
{
unsigned int requested_n; // nomer EBM
unsigned int i,przn_find=0;
unsigned char command[80];
unsigned char test[80];
nid_t node_n; // nomer uzla

//---Определение соответствия между номером узла и номером ЭВМ 
	outp(0x37a, inp(0x37a)|0x24);
	//node_n=getnid();
	requested_n=inp(0x378)&0xF;
	printf("Номер ЭВМ %d \n", 
		requested_n);
		return requested_n;
		ver = requested_n;
}