#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{ 
   
   /* 1.����ʹ�� 
  {
	char s[]="hello";
    char *p;
    p=strchr(s,'l') ;   //��Ϊ����������ص���ָ�����ͣ�������Ҫָ����� 
    printf("%s",p);    
  } */
  
 
 /*2.������2���ַ� 
   {
 	char s[]="hello"; 
    char *p;
     char *p2;
    p=strchr(s,'l') ;   //�ҳ���һ��l 
    p2=strchr(p+1,'l'); //��p+1������ַ����ҳ�l   �򻯳� printf("%s",strchr(p+1,'l'))�� 
    printf("%s",p2); 
 	
    }     */
    
    
    /*3.���������� 
     {
 	char s[]="hello"; 
    char *p;
    p=strchr(s,'l');
    char *t=(char*)malloc(strlen(p)+1);
     
    strcpy(t, p);
    printf("%s\n",t); 
 	free(t);
    }    */
    
    
    /*4.������������ӡǰ��� 
    {
 	char s[]="hello"; 
    char *p;
    p=strchr(s,'l');
    char c=*p;        //���渴ԭҪ�ã��ȼ�¼����ַ�
    *p='\0'; 
    printf("s=%s\n",s);  //�޸ĺ�s���ַ� 
    char *t=(char*)malloc(strlen(s)+1);   //�ַ�������������汾��ָ��汾 
    
     
    strcpy(t, s);
    printf("t=%s\n",t);
	*p=c;                //s��ԭ��ȥ
 	free(t);
 	printf("s=%s\n",s);  //s��ԭ��ȥ������ 
 
    }    */
    
    //5.�ַ����������ַ���
	{
		char *s="hello,world,hhh";
		char *a="or";
		
		char *t=strstr(s,a); 
		printf("%s",t);
		
		
		
	 } 
 
  return 0; 
	
 } 
 

