#include <stdio.h>
#include <stdlib.h>

int compare(const void*a ,const void*b);
void readDate();
void displayDate();


struct student{
	char name[20];
	int chinese;
	int math;
	int english;
};

struct student students[4];

int main()
{
	readDate();
	displayDate();
   
	float arr[]={8.0,5.0,6.2,1.2,3.5,4.4,2,7};
	int num=sizeof(arr)/sizeof(arr[0]);
	
	qsort(arr,num,sizeof(float),compare);
	
	int i;
	for(i=0;i<num;i++)
	{
	printf("%.1f\n",arr[i]);
	}
	
 	
	 
	
	return 0;
} 



int compare(const void*a ,const void*b){   //a-b返回正值，是小到大排序
	float* pa=(float*)a;                       //需要先确定指针类型； 
	float* pb=(float*)b;                       //赋值具体变量给指针 
	float num1= *pa;
	float num2= *pb;
   //	return num1-num2;  和函数返回值冲突；需要修改
   if(num1-num2>0){
   	return 1;
   } else {
   return 0;
   }	
    }
    
    
    
void readDate()
{
	FILE *file=fopen("mark.txt","r");
	int i;
	 for(i=0;i<4;i++)
	 {
	 	fscanf("file %s",students[i].name);
	 	fscanf("file %d",&students[i].chinese);
	 	fscanf("file %d",&students[i].math);
	 	fscanf("file %d",&students[i].english);
	 }	 
	 fclose(file);
}


void displayDate()
{
	int i;
	for(i=0;i<4;i++)
	 {
	 	printf(" %s\t",students[i].name);
	    printf(" %d\t",students[i].chinese);
	 	printf(" %d\t",students[i].math);
	 	printf(" %d\t",students[i].english);
	 }
	
}
