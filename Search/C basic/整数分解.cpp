#include <stdio.h>
int main()
{
	
	//�����ֽ�
	int num=0;
	int mask=1;
	int x=0;
	 
	printf("input a number:");
		scanf("%d",&num); 
	
	if(num==0){printf("%d ",num); //����������ж�0����������ȵ����ų�0����� 
	} else{                       //�ų�0֮���жϼ�λ�� 
		x=num/mask;
		 while(x>0){
      	mask=mask*10;
		x=num/mask;
	
	      }
	mask/=10;
	    printf("%d\n",mask);
	//�ֽ����    
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
