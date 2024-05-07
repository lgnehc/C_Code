#include <stdio.h>
#include <stdbool.h>

int sum(int begin,int end); //函数声明，如果函数要写在后面 

int main()
{
   int begin1,end1;  //这里变量不能是begin，end,好像和函数调用重复，会出错 
   printf("请输入求和的起始数和结束数：");
   scanf("%d %d",&begin1,&end1);  
    int he=0;
    he=sum(begin1,end1);
  	printf("%d到%d的和是：%d\n",begin1,end1,he);   
    he=sum(15,20);
    printf("15到20的和是：%d\n",he);
    
    
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
	printf("%d到%d的和是：%d\n",begin,end,sum);
	
}
 

