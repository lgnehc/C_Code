#include <stdio.h>
 
 
int main(){
	int num;
	
	
	printf("%9d end\n",12345);    //+ǿ�Ƶ���˼ 
	printf("%09d end\n",12345);   //��0�ǿ�λ�����0 
	printf("%+9d end\n",12345);
	printf("%-9d end\n",12345);
	printf("%+-9d end\n",12345);
	printf("%-+9d end\n",12345);
	printf("%e end\n",12345);   //ָ����� ������ 
	
	printf("%*d end\n",10,12345); 
	printf("%*.2f end\n",9,123.0);   //����С����ͺ����С��һ��9λ 
	
//	printf("%d %n end\n",12345,&num);   //%n�ǿ�ǰ������˶��ٸ��ַ� 
//	printf("num=%d\n",num);       //����û����ȷ���numֵ 
	
	{
		int n1,n2; 
		int p1=scanf("%d %d",&n1,&n2);
		//int p2=scanf("%d %d",&n1,&n2);
		int p2=printf("%d\n",n1);  // �ո�Ҳ�� 
		printf("%d %d",p1,p2);   
	}
	
	return 0;
} 
