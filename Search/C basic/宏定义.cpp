#include <stdio.h>

#define  PI 3.14    
#define  PI1 PI*2
#define  FORMAT "%f\n"
#define  PRT printf("output \
  %f\n",PI1)                 //宏定义可以换行，需要  \erter  

int main()
{

	printf( FORMAT,PI*2); 
	PRT; 
	printf("%s  %d\n",__FILE__,__LINE__);  //两个下划线 
	printf("%s  %s\n",__DATE__,__TIME__);
	
	return 0;
}  


