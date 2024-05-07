#include <stdio.h>
#include <stdlib.h>

#include  "max.h"   //""是先从当前目录下寻找，再从系统指定目录找 
//int max(int a,int b); 


int main(int argc, char *argv[])
 {
	double a=9.5;
	double b=5.4;
	printf("%.2f",max(a,b));
	

	return 0;
}


