#include <stdio.h>
#include <math.h>
//����������  --P79Video
 

int main()

{
   const int maxnumber=25;
   int isprime[maxnumber];
   int i;
   int x;
  
  //�����������ȱ��Ϊ1�����治�������ı��Ϊ0  
   for (i=0;i<maxnumber;i++)	 
    {
   	isprime[i]=1;               
	 }  
	
   //��ʼ��ǲ���������Ϊ0	
	for(x=2;x<maxnumber;x++) 
	{
	  if(isprime[x])     //�����������1����ִ�� 
	  {
	  	for(i=2;x*i<maxnumber;i++)   //��2x 3x�������ų� 
	  	{
	  	isprime[i*x]=0;	
		}
	  	
	  }	
	 
	}     

		//������    ��������������ݣ�10������
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
	
 
	//�������
	for(i=2;i<maxnumber;i++)
	{
		if(isprime[i])
		printf("������:%d \n",i);
	 } 
	         	
	return 0;
	
	
 } 
