#include <stdio.h>
#include <stdbool.h>

int sum(int begin,int end); //�����������������Ҫд�ں��� 

int main()
{
   int begin1,end1;  //�������������begin��end,����ͺ��������ظ�������� 
   printf("��������͵���ʼ���ͽ�������");
   scanf("%d %d",&begin1,&end1);  
    int he=0;
    he=sum(begin1,end1);
  	printf("%d��%d�ĺ��ǣ�%d\n",begin1,end1,he);   
    he=sum(15,20);
    printf("15��20�ĺ��ǣ�%d\n",he);
    
    
	return 0;	
	
 } 
 
 
int sum(int begin,int end)
{
	int i=0;
	int sum=0;
	for(i=begin;i<=end;i++)
	{sum+=i;
	}
	return sum;
	printf("%d��%d�ĺ��ǣ�%d\n",begin,end,sum);
	
}
 

