
 unsigned short count625_cmd,count625_inf;
//------ подсчет контрольной суммы --------------------------------
         int  KSumPrm(unsigned short* buf, int size)
 {                int i;
		 unsigned int ksum=0;
		for( i=0;i < size-2;i++)
			ksum=ksum*3+buf[i];
//  unsigned long* p= (unsigned long*) &buf[size-2];

/*сравнение подсчитанной контрольной суммы  и принятой контроль-ной  суммы*/
              //  if(*p==ksum)
			return ksum;//правильный прием
	       //	else
		//	return ksum;//ошибка
}

//        int  KSumPrm1(unsigned short* buf, int size)
// {                int i;
//		 unsigned long ksum=0;
//		for( i=0;i < size-2;i++)
//			ksum=ksum*3+buf[i];
//  unsigned long* p= (unsigned long*) &buf[size-2];

/*сравнение подсчитанной контрольной суммы  и принятой контроль-ной  суммы*/
              //  if(*p==ksum)
//			return ksum;//правильный прием
	       //	else
		//	return ksum;//ошибка
//}


int  initinf (unsigned short *buf,unsigned short size)
{
// ------- inition structure---------------------------
     int i;
	for(i=0; i<62; i++) read_data.buffer[i] =0; 
     read_data.Read_inf.OICH=(size+3)*16;
     read_data.Read_inf.Protokol=0x400;
     read_data.Read_inf.N_Port=0;
     read_data.Read_inf.N_Can=0;
	 //if (size>=6)
     //{for (i=6;i<size;i++) read_data.Read_inf.Data[i]=buf[i];}
	 size = size +4;
	 //read_data.buffer[0] = read_data.Read_inf.OICH;
	 //read_data.buffer[1] = read_data.Read_inf.Protokol;
	 //read_data.buffer[2] = read_data.Read_inf.N_Port;
	 //read_data.buffer[3] = read_data.Read_inf.N_Can;
	 //for (i=4;i<9;i++) read_data.buffer[i] = read_data.Read_inf.Sach[i];
	 //read_data.buffer[4] = 0x80C1; //sach 1    ???/nomer formulyara !dec! 26-1A, 27-1B, 193-C1
	 //read_data.buffer[5] = 0x0123; //sach 2 000123 adress poluchatela A2A3
	 //read_data.buffer[6] = 0x5600; //sach 3 000456 adress otpravitela P3A1
	 //read_data.buffer[7] = 0x0004; //sach 4 P1P2
	 //read_data.buffer[8] = 0x8888; //sach 5
	 //read_data.buffer[9] = 0x8888; //sach 6
	 
	 read_data.Read_inf.Sach.ps = 1;
     read_data.Read_inf.Sach.vr = 1;
     read_data.Read_inf.Sach.rez1 = 0;
     read_data.Read_inf.Sach.kvi = 5;
     read_data.Read_inf.Sach.rez2 = 0;
     read_data.Read_inf.Sach.nf = 193;

     read_data.Read_inf.Sach.a0 = 3;
     read_data.Read_inf.Sach.a1 = 2;
     read_data.Read_inf.Sach.a2 = 1;
     read_data.Read_inf.Sach.a3 = 0;

     read_data.Read_inf.Sach.a4 = 0;
     read_data.Read_inf.Sach.a5 = 0;
     read_data.Read_inf.Sach.p0 = 6;
     read_data.Read_inf.Sach.p1 = 5;

     read_data.Read_inf.Sach.p2 = 4;
     read_data.Read_inf.Sach.p3 = 0;
     read_data.Read_inf.Sach.p4 = 0;
     read_data.Read_inf.Sach.p5 = 0;

     read_data.Read_inf.Sach.r0 = 9;
     read_data.Read_inf.Sach.r1 = 8;
     read_data.Read_inf.Sach.r2 = 9;
     read_data.Read_inf.Sach.r3 = 7;


     read_data.Read_inf.Sach.v0 = 5;
     read_data.Read_inf.Sach.v1 = 5;
     read_data.Read_inf.Sach.v2 = 4;
     read_data.Read_inf.Sach.v3 = 3; 
	 //------------------DATA--------------------------------------------------
	 read_data.Read_inf.Data[1] = 0x1D00; //data 7 tip upakovku/reserv !bin!
	 read_data.Read_inf.Data[2] = 0x2300; //data 8 kod formalizovannogo soobsheniya/priznak napravleniya !bin!
	 read_data.Read_inf.Data[3] = 0x2400; //data 9 koordinata X !bin!
	 read_data.Read_inf.Data[4] = 0x2500; //data 10 koordinata Y !bin!
	 read_data.Read_inf.Data[5] = 0x1D00; //data 11 kurs grad !bin!
	 read_data.Read_inf.Data[6] = 0x001E; //data 12 skorost' m/s !bin!
	 read_data.Read_inf.Data[7] = 0x1248; //data 13 vstavka 1 !bin!
	 read_data.Read_inf.Data[8] = 0x1249; //data 14 vstavka 2 !bin!
	 read_data.Read_inf.Data[9] = 0x1250; //data 15 vstavka 3 !bin!
	 read_data.Read_inf.Data[10] = 0x1251; //data 16 vstavka 3 !bin!
	 read_data.Read_inf.Data[11] = 0x0000; //data 17 reserv
	 read_data.Read_inf.Data[12] = 0x0000; //data 18 reserv
	 read_data.Read_inf.Data[13] = 0x0000; //data 19 reserv
	 read_data.Read_inf.Data[14] = 0x0000; //data 20 reserv
	 
	 //for (i=10;i<(size-2);i++) read_data.buffer[i] = i;
	 if (size%2==0);
	 else {
	 size = size+1;
	 buf[size] = 0;
	 }
	 //buf[size-1]=0;
	 //buf[size]=0;
	 //read_data.Read_inf.Summa=KSumPrm(read_data.buffer,size);
	 read_data.Read_inf.Summa = KSumPrm(read_data.buffer,size);
	 //read_data.buffer = read_data.Read_inf.Summa;
	 
	 //printf("\nsum=%d k=%d\n",read_data.Read_inf.Summa,size);
	 printf("\nsum=%d k=%d\n",buf[size],read_data.Read_inf.Summa);
	 for (i=0; i<size; i++) printf ("%04x  ",read_data.buffer[i]); 
	 printf("\n"); 
     return 1;
	 
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
{    read_7118.Read_com.Dlina=20;
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