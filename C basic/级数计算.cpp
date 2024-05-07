#include <stdio.h>
int main()

//级数求和   1-1/2+1/3...
{
	
	
	int i=0;
    double sum=0;
    int x;
    int sign=1; 
    
    printf("输入需要的n项和：");
   // scanf("%d",&x);
   x=1000;
   for(i=1;i<=x;i++) 
   {  
        sum += sign*(1.0/i);
        sign=-sign;
				
    }
    
	printf("f(%d)=%f\n",x,sum);
			   
	   
	
	         	
	return 0;		
 } 
