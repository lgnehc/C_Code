#include <stdio.h>
#include <math.h>
int main()

{
	    int i;	
	 	int num;
	 	int d;
		printf("input the num(range:3<=num<=7):");
		scanf("%d",&num); 
	 	
 //�жϿ�ʼ�� 
    switch(num)
	{
    case 3 : i=100;break;     
    case 4 : i=1000;break;
 	case 5 : i=10000;break;  
	case 6 : i=100000;break;
	}
	int first=i;
//	printf("%d",i); 
 //�����ֽ�  
   for (;i<first*10;i++){
   	int sum=0;
	int mask=first;
   	int mi=0;
   	int t=i;   //i�����Ҫ�����ж��Ƿ�ˮ�ɻ�����ȡ����λ�����ƻ�i,��t����i�ƻ� 
   	//�ֽ���i 
	   while (mask>0){
	   	
		
		d=t/mask;
	   	t=t%mask;
	   	mask=mask/10;
	   //	printf("%d",d);
	   	mi=pow(d,num);
		  sum=sum+mi;
	   }
	   if(i==sum){printf("%d\n",i);
	   }
   	
   } 
	
	         	
	return 0;
	
	
 } 
