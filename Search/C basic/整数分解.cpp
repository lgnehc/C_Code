#include <stdio.h>
int main()
{
	
	//整数分解
	int num=0;
	int mask=1;
	int x=0;
	 
	printf("input a number:");
		scanf("%d",&num); 
	
	if(num==0){printf("%d ",num); //下面程序不能判断0情况，这里先单独排除0情况； 
	} else{                       //排除0之后，判断几位数 
		x=num/mask;
		 while(x>0){
      	mask=mask*10;
		x=num/mask;
	
	      }
	mask/=10;
	    printf("%d\n",mask);
	//分解输出    
	int a; 
	int b=0;
	b=num;   
	while(mask>0)
	{
		a=num/mask;
		b=num%mask;
	    num=num%mask;
		mask=mask/10;
		printf("%d ",a);
	}
		
	}
     
//	printf("%d",b);
	
	
	
	
	
	return 0;
 } 
