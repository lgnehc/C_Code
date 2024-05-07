#include <stdio.h>
#include <string.h>

char*  mycpy( char *dst,const char *src);
int main()


{ 

 char src[]="abc";
 char dst[]="aaa";
 mycpy(dst,src);
 
 printf("%s\n",dst);
 printf("strlen(dst)=%d\n",strlen(dst));
 printf("sizeof(dst)=%d\n",sizeof(dst));

  return 0; 
	
 } 
 
char*  mycpy( char *dst,const char *src)  //char*是返回指针类型；char是返回字符 
 {
 /*	//字符串数组版本 
 	int idx=0;
 	while(src[idx]!='\0'){
 		dst[idx]=src[idx]; 
 		idx++;
	 }
	 dst[idx]='\0';
	 return dst;   */
 	
 //指针版本	
   char *ret=dst;   //记录数组初始位置，因为后面有修改， 
   while(*src!='\0')
   {
   	*dst=*src;
    dst++;
    src++;
   }
  *dst='\0';
  
  return ret;    //直接返回dst会导致有个地址位移，想要的是还是从原来的位置 
 	
 }
