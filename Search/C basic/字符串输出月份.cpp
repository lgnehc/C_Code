#include <stdio.h>
int main()
{
    char *month[]={"January","February","March","April","May","June",\
	                "July","August","September","October","November","December"};
	                //��ʼ������ַ������� 
	int i; 
	char a[][12]={"January","February","March","April","May","June",\
	                "July","August","September","October","November","December",}; 
	              //�����ʾÿ���ַ����ĳ�����12�������ʼ���ַ�����12�����ʧ�� 
//	char b[][12]={"qwaszxqwaszx"};   //����ʧ�� 
	
	
	printf("�����·�:");
	scanf("%d",&i); 
    printf("%s",month[i-1]); 








  return 0; 
}
