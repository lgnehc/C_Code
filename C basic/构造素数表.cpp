#include <stdio.h>
#include <math.h>
//构建素数表  --P79Video
 

int main()

{
   const int maxnumber=25;
   int isprime[maxnumber];
   int i;
   int x;
  
  //把所有数据先标记为1，后面不是素数的标记为0  
   for (i=0;i<maxnumber;i++)	 
    {
   	isprime[i]=1;               
	 }  
	
   //开始标记不是素数的为0	
	for(x=2;x<maxnumber;x++) 
	{
	  if(isprime[x])     //里面的数据是1即可执行 
	  {
	  	for(i=2;x*i<maxnumber;i++)   //把2x 3x等依次排除 
	  	{
	  	isprime[i*x]=0;	
		}
	  	
	  }	
	 
	}     

		//调试用    输出所有数组数据，10个换行
	{
		for(i=0;i<maxnumber;i++)
	   {
		
		printf("%d ",isprime[i]);
		
	
		 if((i+1)%10==0)
		 {
		 printf("\n");
		 
		 }
		}
	printf("\n");
	 } 
	
 
	//输出素数
	for(i=2;i<maxnumber;i++)
	{
		if(isprime[i])
		printf("素数有:%d \n",i);
	 } 
	         	
	return 0;
	
	
 } 
