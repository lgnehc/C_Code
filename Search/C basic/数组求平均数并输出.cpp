#include <stdio.h>
#include <stdbool.h>


int main()

{
	int x=0;
	int index; 
	double sum=0;
	int cnt=0;
	 printf("����Ҫ���ƽ�����ĸ�����") ;
	 scanf("%d",&index);
	 int num[index]; 
	 
	printf("����%d�����ݣ�����-1��������",index) ;
	scanf("%d",&x);
	
	while(x!=-1){    //�������� 
	num[cnt]=x;
	sum+=num[cnt];
	cnt++;	
	scanf("%d",&x);	

	}
	
	if(cnt>0){        //����ƽ��ֵ 
		int i; 
		double average=sum/cnt;
		printf("average=%lf\n",average);
		
		for(i=0;i<cnt;i++)  //�ж��Ƿ���� ����Ϊ�����ƻ�cnt,���Դ��¶����±� 
		{
		  if(num[i]>average){
		  	printf("����ƽ�������У�%d\n",num[i]);
		  }
		
		}
		 
	}
	
    
    
	return 0;	
	
 } 
 

