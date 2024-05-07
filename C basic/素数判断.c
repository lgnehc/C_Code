#include <stdio.h>
int main()

//0-100µÄËØÊıÅĞ¶Ï 
{
	
	
	int i=0;
    int num=0;
    int x;


   for(num=2;num<100;num++) 
   {        
   	        int isprime=1; 
		   	for(i=2;i<num;i++)
		    {
		        if(num%i==0)
		   	    {
				isprime=0;
		   	    break;
				   }
		   	}				
			 
			
			if(isprime==1) {
				printf("%d is sushu\n",num);
			    }
    }
    
	
	   
	
	         	
	return 0;
	
	
 } 
