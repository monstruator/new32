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
  
  void main()
  {
  
	delay(1500);
	open_shmem();
	delay(1000);
	printf("start printing");
	
	while(1)
	{
		printf("count RLI %d \n", p->count_cpp_rli);
		printf("count CPP %d \n", p->count_cpp_message);
		delay(500);
		if (kbhit()) break;
	}
  }