#define BU1	1 //nomer interfeisa 
#define CPP	2 //nomer interfeisa

struct sac {
      unsigned short ps: 1;
      unsigned short vr: 1;
      unsigned short rez1: 1;
      unsigned short kvi: 4;
      unsigned short rez2: 1;
      unsigned short nf: 8;

      unsigned short a0: 4;
      unsigned short a1: 4;
      unsigned short a2: 4;
      unsigned short a3: 4;

      unsigned short a4: 4;
      unsigned short a5: 4;
      unsigned short p0: 4;
      unsigned short p1: 4;

      unsigned short p2: 4;
      unsigned short p3: 4;
      unsigned short p4: 4;
      unsigned short p5: 4;

      unsigned short r0: 4;
      unsigned short r1: 4;
      unsigned short r2: 4;
      unsigned short r3: 4;


      unsigned short v0: 4;
      unsigned short v1: 4;
      unsigned short v2: 4;
      unsigned short v3: 4;
   }; 

struct sostSPIAK {
      unsigned char Spiak: 1;
      unsigned char Cpp:   1;
      unsigned char T625:  1;
      unsigned char rez1:  5;
	 
	  unsigned char ispr:  1;
	  unsigned char rabota:1;
	  unsigned char reset: 1;
	  unsigned char regl:  1;
	  unsigned char konez: 1;
	  unsigned char kontr: 1;
	  unsigned char rez2:  2;
	  
	  unsigned short rez3;     
   }; 

 typedef struct
       {
       struct Tabl_4_6_8
        {
        unsigned short Dlina;     // aeeia a aaeoao
        unsigned short Ident;     // auai? ioi?aaeoaey
        unsigned int   Parol_ml;  // ie aaeou ia?iey
        unsigned short Zapros;    // oei niiauaiey
        unsigned short Error;     // ioeaea
        unsigned short Protokol;  // oi?aaeaiea T-625
        unsigned short Tip;       // oei iaeaoa
        unsigned char  Parol_st ; // no aaeo ia?iey
        unsigned char  T625 ;     // oei iieo?aoaey
        unsigned char  Reserv ;   // ?aca?a
        unsigned char  CVM_A ;    // oei ioi?aaeoaey
        } Read_com ;              // aeeia 20 aaeo
     //-------------------------
        struct Tabl_5
        {
        unsigned short Dlina;     // aeeia a aaeoao
        unsigned short Ident;     // auai? ioi?aaeoaey
        unsigned int   Parol_ml;  // ie aaeou ia?iey
        unsigned short Zapros;    // oei niiauaiey
        unsigned short Error;     // ioeaea
        unsigned short Protokol;  // oi?aaeaiea T-625
        unsigned short Tip;       // oei iaeaoa
        unsigned char  Parol_st ; // no aaeo ia?iey
        unsigned char  T625 ;     // oei iieo?aoaey
        unsigned char  reserv ;   // ?aca?a
        unsigned char  CVM_A ;    // oei ioi?aaeoaey
        unsigned char  Sost;       // oae ninoiyiea
        unsigned int   Reserv1;     // ?aca?a
        unsigned short Opt;        // ?a?ei ?aaiou
        } O_na_zapros;              // aeeia 27 aaeo
    //---------------------------------------------------
        struct Tabl_7_9
        {
        unsigned short Dlina;     // aeeia a aaeoao
        unsigned short Ident;     // auai? ioi?aaeoaey
        unsigned int   Parol_ml;  // ie aaeou ia?iey
        unsigned short Zapros;    // oei niiauaiey
        unsigned short Error;     // ioeaea
        unsigned short Protokol;  // oi?aaeaiea T-625
        unsigned short Tip;       // oei iaeaoa
        unsigned char  Parol_st ; // no aaeo ia?iey
        unsigned char  T625 ;     // oei iieo?aoaey
        unsigned char  reserv ;   // ?aca?a
        unsigned char  CVM_A ;    // oei ioi?aaeoaey
        unsigned short N_kan;     // iiia? eaiaea
        unsigned int   Ident_r;   // eaaioeo ii?aaaey?uee ?a?ei eaiaea
        unsigned short R1;        // ?aca?a
        unsigned short R2;        // ?aca?a
        unsigned char  Result;    // ?acoeuoao onoaiiaee
        }  O_na_kom;               // aeeia 31 aae
        } STR625;

       union  {
        unsigned char bufcom[31];
        struct Tabl_4_6_8 Read_com;
        struct Tabl_5 O_na_zapros;
        struct Tabl_7_9 O_na_kom;} read_7118;   
 //-----------------------------------------------
    struct Tabl_2
        {
        unsigned short OICH;
        unsigned short Protokol;
        unsigned short N_Port;
        unsigned short N_Can;
        struct sac Sach;
        unsigned short Data[52];
        //unsigned int Summa; //?? nuzhna li ona? v 193 formulyare netu kontrol'noy summi
        };

       union  {
	   unsigned short buffer[62];
       unsigned char byte_bufer[124];
	   struct Tabl_2 Read_inf;}
	   read_data;
	    //-----------------------------------------------
   
       union  {
	   unsigned short buffer[62];
       unsigned char byte_bufer[124];
	   struct Tabl_2 send_inf;}
	   send_data;
	   
	typedef            struct RLI_data
			{
			unsigned short SACH[6];  //oich formulyara 18
			unsigned short kolvo_slov; // kolichestvo informacionnih slov v aormulyare
			unsigned short form_5; // chastniy formulyar 5
			unsigned short form_6[9]; // chastniy formulyar 6
			//unsigned short nomer_str[203]; // nomer stroki 0
			} Read_rli;
			
			union  {
			//unsigned short buffer[219];
			unsigned short pic[400][219];
			unsigned char byte_bufer[175200];
			struct RLI_data Read_rli;}
			read_rli;
   
typedef   struct 
{   
    unsigned int  count625_cmd ;  // s4et4ik prynjatyx cmd 625
    unsigned int  count625_inf ; // s4et4ik prinjatyx paketov dannyx 625
    unsigned char T625_on_off;
    unsigned char T625_ok_nok;
    unsigned char T625_Result;
    unsigned char T625_SV_Result;
    unsigned char T625_DMW_Result; 
} cmd625;
 

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short num_words;

	short	SVCH_FORM_1[9];		//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_2[4];		//8 байт (Формуляр ТР)
	short	SVCH_FORM_3[80];	//(20 байт) * 8 фомуляров (Формуляр НЦ)

	short	null_bytes[519];	//620 - 101 = 519

} Mem_Region23_NO_t;	//202 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short num_words;

	short	SVCH_FORM_1[9];	//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_4[88];	//(22 байт) * 8 фомуляров (Формуляр РЭС)

	short	null_bytes[515];	//620 - 105 = 515

} Mem_Region23_REO_t;	//210 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];

	short	SVCH_FORM_1[9];		//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_3[10];	//20 байт (Формуляр НЦ)

	short	null_bytes[594];	//620 - 26 = 594

} Mem_Region23_CpNC_t;	//52 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];

	short	SVCH_FORM_1[9];	//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_4[11];	//22 байт (Формуляр РЭС)

	short	null_bytes[593];	//620 - 27 = 593

} Mem_Region23_CpRES_t;	//54 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];

	short	SVCH_FORM_1[9];		//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_2[4];		//8 байт (Формуляр ТР)

	short	null_bytes[600];	//620 - 20 = 600

} Mem_Region23_VZ_t;	//40 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short num_words;
	short	SVCH_FORM_5[8];
	short	SVCH_FORM_6[606];
	unsigned short cr_transm_takt;


} Mem_Region23_RLI_t;	//1240 б.инф.

typedef	union {
	short buf[623];

	Mem_Region23_NO_t 		Mem_Region_NO;		//Освещение НО	(kvi = 5)
	Mem_Region23_REO_t 		Mem_Region_REO;		//Освещение РЭО	(kvi = 7)
	Mem_Region23_CpNC_t 	Mem_Region_CpNC;	//Целепоказ НЦ	(kvi = 6)
	Mem_Region23_CpRES_t 	Mem_Region_CpRES;	//Целепоказ РЭС	(kvi = 8)
	Mem_Region23_VZ_t 		Mem_Region_VZ;		//Взаимодействие	(kvi = 2)
	Mem_Region23_RLI_t 		Mem_Region_RLI;		//Режим РЛИ			(kvi = 9)

}Mem_Region23_t;

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short num_words;

	short	SVCH_FORM_1[9];		//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_2[4];		//8 байт (Формуляр ТР)
	short	SVCH_FORM_3[40];	//(20 байт) * 4 фомуляров (Формуляр НЦ)

} Mem_Region4_NO_t;	//122 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short num_words;

	short	SVCH_FORM_1[9];		//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_4[44];	//(22 байт) * 4 фомуляров (Формуляр РЭС)

} Mem_Region4_REO_t;	//122 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];

	short	SVCH_FORM_1[9];		//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_2[4];		//8 байт (Формуляр ТР)

	short	null_bytes[41];	//122 - 40 = 82

} Mem_Region4_VZ_t;	//40 б.инф.


 typedef union{
//	short buf[97];
//	Mem_Region4_NO_t 	Mem_Region_NO;		//Освещение НО		(kvi = 5)
//	Mem_Region4_REO_t 	Mem_Region_REO;		//Освещение РЭО		(kvi = 7)
//	Mem_Region4_VZ_t 	Mem_Region_VZ;		//Взаимодействие	(kvi = 4)
	short buf[61];	//Изменение протокола: дмв - как свч (pdn 08.04.2016)
	Mem_Region4_NO_t 	Mem_Region_NO;		//Освещение НО		(kvi = 5)
	Mem_Region4_REO_t 	Mem_Region_REO;		//Освещение РЭО		(kvi = 7)
	Mem_Region4_VZ_t 	Mem_Region_VZ;		//Взаимодействие	(kvi = 4)

} Mem_Region4_t;

 

typedef struct 
 {
      short num_out;
      short num_in;
      int time; //double
      float car_freq;
      float imp_freq;
      float inp_len;
      short mod_type;
      float scan_time;
      float targ_bear;
      float bear_sko;
      float targ_vip;
      float latitude;
      float longitude;
      float course;
      float speed;
      float div_course;
   } formrls;

//////////////////////////////////////

typedef struct {
	  unsigned char temp[4];   //?????
      unsigned short cr_com;  //poryadkoviy nomer posledney vidanoi komandi
      short num_com;  //nomer poslednei komandi po perchnu
      int a_params[5];  // parametri
	  float x_hk;  // koordinata x hk
	  float y_hk;  // koordinata y hk
	  float kurs_hk;  // kurs hk
	  float speed_hk;  //skorost' hk
      //short pr_bearing; 
      //float p;
      //float k;
      //short nform;
      //formrls form[3];
   } packcmd;

/////////////////////////////////////
   
typedef   struct  {
	  unsigned char temp[4];
      unsigned short cr_com; //por9dkovii nomer
      short num_com; //nomer poslednei
      unsigned int lp2_param; //1 parametr komandi
      short kzv; //kod zaverweni9 (0 - norma)
      short k_o; //kod owibki
      short fk; //kod FK (0 - norma / 1 - ne norma)
      short link; 

      unsigned int sost_kasrt[9];
      struct sostSPIAK sost_spiak  ;
	  unsigned int sost_r999;

      Mem_Region23_t Mem_Region2;
	  Mem_Region4_t Mem_Region4;
   } packusoi;

  
   
typedef struct 
{
	//unsigned short n_step; //nomer waga vipolneni9 comandi
	unsigned short n_chan; //nomer intergeisa
	unsigned short n_com;  //nomer komandi dl9 zadannogo interfeisa
    short          status; //status vipolneni9
	/*unsigned short w_answ[2]; //neobhodimost' zdat' otvet, otvet polu4en //1-gdat' 2-gotovo
	unsigned short n_answ;	//neobhodimii nomer otveta, polu4ennii otvet
	*/
	
} step_UPR;  //opisanie mini comandi dl9 kazdogo intergeisa na tekuwem wage
   
typedef struct 
{
	unsigned short num_mini_com; //kol-vo mini komand na kagdom wage
	unsigned short done_mini_com; //kol-vo mini vipolnennih komand na kagdom wage
    long 		   t_start; //vrem9 starta (v tikah taimera dispet4era)
	long 		   t_stop;  //vrem9 okon4ani9
	step_UPR s[10]; //nabor mini komand dl9 interfeisov na tekuwem wage 
} c_UPR;  //komanda upravleni9 
 
typedef struct 
{
	long sys_timer; //s4et4ik timera
	packcmd fromMN3;	//komanda iz MN3	(provereno i prin9to k ispolneniu)
	packcmd inbufMN3;	//komanda iz MN3	(bufer priema dl9 kanala MN3)	
	packusoi  toMN3;	//otvet v MN3
	short cvs; //10 ili 11
	c_UPR work_com[10]; //wagi vipolneni9 tekuwei komandi upravleni9
	short cur_step; //tekuwii wag vipolneni9 komandi
	short kol_step; //kol-vo wagov vipolneni9 komandi
	short verbose;	//detalizaci9 pe4ati
	
	short    komanda625;
	short    SOST625;
	cmd625   cmd_625;   //otvet iz t625 
	struct Tabl_2 inf_625;   //inf for t625
	
	short count_cpp_status;   //kolichestvo soobsheniy cpp
	short count_cpp_rli;   //kolichestvo soobsheniy cpp
	short count_cpp_message;
	short count_r999_message;   //kolichestvo soobsheniy r999
	
	
	unsigned short a0_cpp: 4;
    unsigned short a1_cpp: 4;
    unsigned short a2_cpp: 4;
    unsigned short a3_cpp: 4;
	  
	unsigned short a4_cpp: 4;
    unsigned short a5_cpp: 4;
    unsigned short p0_cpp: 4;
    unsigned short p1_cpp: 4;
	  
    unsigned short p2_cpp: 4;
    unsigned short p3_cpp: 4;
    unsigned short p4_cpp: 4;
    unsigned short p5_cpp: 4;
		
	unsigned short a0_r999: 4;
    unsigned short a1_r999: 4;
    unsigned short a2_r999: 4;
    unsigned short a3_r999: 4;
	  
	unsigned short a4_r999: 4;
    unsigned short a5_r999: 4;
    unsigned short p0_r999: 4;
    unsigned short p1_r999: 4;
	  
    unsigned short p2_r999: 4;
    unsigned short p3_r999: 4;
    unsigned short p4_r999: 4;
    unsigned short p5_r999: 4;
	
}SHMEM_MO3A;


