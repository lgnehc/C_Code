#include <stdio.h>
#include <stdbool.h>
int main()
{
   const int num=10;
   int i,x;
   int count[num];
   
   for(i=0;i<num;i++){   //����ÿ������ʼ��Ϊ0 ��������������ֵ��ʽ 
   	count[i]=0;
   }
   
   
   	printf("������Ҫͳ�Ƶ�����(-1����)��");  //ͳ�Ƹ��� 
    scanf("%d",&x); 
    while(x!=-1) 
	{
		if(x>=0 && x<=9){
		count[x]++ ;	   //����ͳ�ƵĹؼ� 
		}
     scanf("%d",&x); 
	}
 
   for(i=0;i<num;i++)       //��������������� 
   {
   printf("%d:%d\n",i,count[i]);
	} 

    
    
	return 0;	
	
 } 
