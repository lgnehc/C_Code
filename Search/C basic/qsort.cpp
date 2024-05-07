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



int compare(const void*a ,const void*b){   //a-b������ֵ����С��������
	float* pa=(float*)a;                       //��Ҫ��ȷ��ָ�����ͣ� 
	float* pb=(float*)b;                       //��ֵ���������ָ�� 
	float num1= *pa;
	float num2= *pb;
   //	return num1-num2;  �ͺ�������ֵ��ͻ����Ҫ�޸�
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
