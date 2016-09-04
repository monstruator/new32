//------ подсчет контрольной суммы --------------------------------
    void  KSumPrm(int size_all)
{   int i;
	unsigned int ksum=0;
	for( i=0;i < size_all;i++)			ksum=ksum*3+read_data.buffer[i];
	read_data.buffer[size_all-2] = ksum;
	read_data.buffer[size_all-1] = ksum>>16;
}
int  Initinf (unsigned short size) // 0<=size<=50
{
	int y,z,virav=0;
	printf("size = %d \n", size);
	//for(y=0; y<62; y++) read_data.buffer[y] =0; 
	read_data.Read_inf.OICH=(size+9)*16;    //????
    read_data.Read_inf.Protokol=0x0400;
    read_data.Read_inf.N_Port=0;
    read_data.Read_inf.N_Can=0;
	read_data.Read_inf.Sach.ps = 1;
	//----------------------------SACH------------------------------------
	if (p->fromMN3.a_params[1]!=0) // esli p[rinznak ustanovki vremeni ne reven 0
	{
		read_data.Read_inf.Sach.vr =1; //priznak ustanovki vremeni v sach
		read_data.Read_inf.Sach.v0 = ( ( p->fromMN3.a_params[1] % 3600 ) / 60 ) % 10; 
		read_data.Read_inf.Sach.v1 = ( ( p->fromMN3.a_params[1] % 3600 ) / 60 ) / 10;
		read_data.Read_inf.Sach.v2 = ( p->fromMN3.a_params[1] / 3600 ) % 10 ;
		read_data.Read_inf.Sach.v3 = ( p->fromMN3.a_params[1] / 3600 ) / 10;
	}
	else read_data.Read_inf.Sach.vr = read_data.Read_inf.Sach.v0 = read_data.Read_inf.Sach.v1 = read_data.Read_inf.Sach.v2 = read_data.Read_inf.Sach.v3 = 0;
	
	read_data.Read_inf.Sach.rez1 = 0;
	read_data.Read_inf.Sach.kvi = 2; //?? ne yasno
	read_data.Read_inf.Sach.rez2 = 0;
	read_data.Read_inf.Sach.nf = 193;
	
	read_data.Read_inf.Sach.a0 = ( ( ( ( ( p->fromMN3.a_params[2] % 1000000 ) % 100000 ) % 10000 ) % 1000) % 100) % 10;
	read_data.Read_inf.Sach.a1 = ( ( ( ( ( p->fromMN3.a_params[2] % 1000000 ) % 100000 ) % 10000 ) % 1000) % 100) / 10;
	read_data.Read_inf.Sach.a2 = ( ( ( ( p->fromMN3.a_params[2] % 1000000 ) % 100000 ) % 10000 ) % 1000) / 100;
	read_data.Read_inf.Sach.a3 = ( ( ( p->fromMN3.a_params[2] % 1000000 ) % 100000 ) % 10000 ) / 1000;

	read_data.Read_inf.Sach.a4 = ( ( p->fromMN3.a_params[2] % 1000000 ) % 100000 ) / 10000;
	read_data.Read_inf.Sach.a5 = ( p->fromMN3.a_params[2] % 1000000 ) / 100000;
	read_data.Read_inf.Sach.p0 = ( ( ( ( ( p->fromMN3.a_params[3] % 1000000 ) % 100000 ) % 10000 ) % 1000) % 100) % 10;
	read_data.Read_inf.Sach.p1 = ( ( ( ( ( p->fromMN3.a_params[3] % 1000000 ) % 100000 ) % 10000 ) % 1000) % 100) / 10;

	read_data.Read_inf.Sach.p2 = ( ( ( ( p->fromMN3.a_params[3] % 1000000 ) % 100000 ) % 10000 ) % 1000) / 100;
	read_data.Read_inf.Sach.p3 = ( ( ( p->fromMN3.a_params[3] % 1000000 ) % 100000 ) % 10000 ) / 1000;
	read_data.Read_inf.Sach.p4 = ( ( p->fromMN3.a_params[3] % 1000000 ) % 100000 ) / 10000;
	read_data.Read_inf.Sach.p5 = ( p->fromMN3.a_params[3] % 1000000 ) / 100000;

	p->count_cpp_message++;
	read_data.Read_inf.Sach.r0 = ( ( ( p->count_cpp_message % 10000 ) % 1000 ) % 100 ) % 10;
	read_data.Read_inf.Sach.r1 = ( ( ( p->count_cpp_message % 10000 ) % 1000 ) % 100 ) / 10;
	read_data.Read_inf.Sach.r2 = ( ( p->count_cpp_message % 10000 ) % 1000 ) / 100;
	read_data.Read_inf.Sach.r3 = ( p->count_cpp_message % 10000 ) / 1000;
   //------------------------------DATA-----------------------------------------------------
	//for (z=0; z<=size; z++) read_data.Read_inf.Data = buf[z];
	if (size%2!=0) virav = 1;
	
	//------------------------CHECK SUMM-----------------------------------------------------
	
	KSumPrm(size+virav+12);
	printf("size = %d virav = %d \n", size, virav);
	for (y=0; y<size+virav+12; y++) 
	{
		printf("%04x ", read_data.buffer[y]);
		if (y==3) printf("\n");
		if (y==9) printf("\n");
		if (y==(size+virav+9)) printf("\n");
	}
	printf("\n");
	return (size+virav+12);
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