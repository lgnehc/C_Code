#include <stdio.h>
int main()


{
	{
	//ָ�붨����ַ������鲻���޸ģ�ֻ��  �����鶨����ַ��������޸�
	char *s="Hello";      //ָ�붨ID�ַ���ֻ����д��
	
	char *s2="Hello";    //s��s2��ŵ�ַ��һ���ģ�  ָ����ʽ������ַ�����ַ�ڳ����� ���Ƚ�С  
	char s3[]="Hello";   //�ַ�����ʽ����ĵ�ַ�Ǻ���ǰ��int�����ڲ��λ�õ� 
	s3[0]='B';           //���ֲſ����޸ģ� 
//	s[0]='B';            //�����޸� 
 	printf("%p\n",s);	
	printf("%c\n",*s);
	 
	printf("%p\n",s2);	
	printf("%c\n",*s2);
	

	printf("%p\n",s3);	
	printf("%c\n",s3[0]);
	}        	
	
			{ //��������ַ���--�ո� 
				char word[8];
				printf("please input:");
				scanf("%s",word);    //scanf��������һ���������Կո�/tab/�س���Ϊ��ֹ�� 
				printf("%s\n",word);
				printf("%3s\n",word);  //���Ӧ��ֻ�����3���ַ��ģ�����������ܰ汾��ͬ 
				printf("%7s\n",word);
			 
			}
			
			
			   {
			   	char buffer[100]=""; //���ַ���
				char buffer1[]="";   //������鳤��ֻ��1,����û�пո� 
				printf("buffer[5]=%c-end\n",buffer[5]); 
				printf("buffer=%s-end\n",buffer); 
				printf("buffer1[5]=%c-end\n",buffer1[5]); 
			   }
	
	return 0;
	
	
 } 
