
 unsigned short count625_cmd,count625_inf;
//------ ������� ����������� ����� --------------------------------
         int  KSumPrm(unsigned short* buf, int size)
 {                int i;
		 unsigned int ksum=0;
		for( i=0;i < size-2;i++)
			ksum=ksum*3+buf[i];
//  unsigned long* p= (unsigned long*) &buf[size-2];

/*��������� ������������ ����������� �����  � �������� ��������-���  �����*/
              //  if(*p==ksum)
			return ksum;//���������� �����
	       //	else
		//	return ksum;//������
}

//        int  KSumPrm1(unsigned short* buf, int size)
// {                int i;
//		 unsigned long ksum=0;
//		for( i=0;i < size-2;i++)
//			ksum=ksum*3+buf[i];
//  unsigned long* p= (unsigned long*) &buf[size-2];

/*��������� ������������ ����������� �����  � �������� ��������-���  �����*/
              //  if(*p==ksum)
//			return ksum;//���������� �����
	       //	else
		//	return ksum;//������
//}


int  initinf (unsigned short *buf,unsigned short size)
{
// ------- inition structure---------------------------
     int i;
	 for(i=0; i<62; i++) read_data.buffer[i] =0; 
     read_data.Read_inf.OICH=(size+3)*16;
     read_data.Read_inf.Protokol=0x0400;
     read_data.Read_inf.N_Port=0;
     read_data.Read_inf.N_Can=0;
	 if (size>=6)	for (i=6;i<size;i++) read_data.Read_inf.Data[i]=buf[i];
	 size = size +4;
	 
	 read_data.Read_inf.Sach.ps = 1;
     read_data.Read_inf.Sach.vr = 1;
     read_data.Read_inf.Sach.rez1 = 0;
     read_data.Read_inf.Sach.kvi = 2;
     read_data.Read_inf.Sach.rez2 = 0;
     read_data.Read_inf.Sach.nf = 193;

     read_data.Read_inf.Sach.a0 = 5;
     read_data.Read_inf.Sach.a1 = 5;
     read_data.Read_inf.Sach.a2 = 5;
     read_data.Read_inf.Sach.a3 = 0;

     read_data.Read_inf.Sach.a4 = 0;
     read_data.Read_inf.Sach.a5 = 0;
     read_data.Read_inf.Sach.p0 = 1;
     read_data.Read_inf.Sach.p1 = 6;

     read_data.Read_inf.Sach.p2 = 1;
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
	if (size%2!=0)
	{
		size = size+1;
		buf[size] = 0;
	}
	read_data.Read_inf.Summa = KSumPrm(read_data.buffer,size);
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