#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{ 
   
   /* 1.基本使用 
  {
	char s[]="hello";
    char *p;
    p=strchr(s,'l') ;   //因为这个函数返回的是指针类型，所以需要指针接受 
    printf("%s",p);    
  } */
  
 
 /*2.搜索第2个字符 
   {
 	char s[]="hello"; 
    char *p;
     char *p2;
    p=strchr(s,'l') ;   //找出第一个l 
    p2=strchr(p+1,'l'); //从p+1后面的字符串找出l   简化成 printf("%s",strchr(p+1,'l'))； 
    printf("%s",p2); 
 	
    }     */
    
    
    /*3.搜索并复制 
     {
 	char s[]="hello"; 
    char *p;
    p=strchr(s,'l');
    char *t=(char*)malloc(strlen(p)+1);
     
    strcpy(t, p);
    printf("%s\n",t); 
 	free(t);
    }    */
    
    
    /*4.搜索出来并打印前面的 
    {
 	char s[]="hello"; 
    char *p;
    p=strchr(s,'l');
    char c=*p;        //后面复原要用，先记录这个字符
    *p='\0'; 
    printf("s=%s\n",s);  //修改后s的字符 
    char *t=(char*)malloc(strlen(s)+1);   //字符串定义有数组版本和指针版本 
    
     
    strcpy(t, s);
    printf("t=%s\n",t);
	*p=c;                //s还原回去
 	free(t);
 	printf("s=%s\n",s);  //s还原回去输出结果 
 
    }    */
    
    //5.字符串中搜索字符串
	{
		char *s="hello,world,hhh";
		char *a="or";
		
		char *t=strstr(s,a); 
		printf("%s",t);
		
		
		
	 } 
 
  return 0; 
	
 } 
 

