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
 
char*  mycpy( char *dst,const char *src)  //char*�Ƿ���ָ�����ͣ�char�Ƿ����ַ� 
 {
 /*	//�ַ�������汾 
 	int idx=0;
 	while(src[idx]!='\0'){
 		dst[idx]=src[idx]; 
 		idx++;
	 }
	 dst[idx]='\0';
	 return dst;   */
 	
 //ָ��汾	
   char *ret=dst;   //��¼�����ʼλ�ã���Ϊ�������޸ģ� 
   while(*src!='\0')
   {
   	*dst=*src;
    dst++;
    src++;
   }
  *dst='\0';
  
  return ret;    //ֱ�ӷ���dst�ᵼ���и���ַλ�ƣ���Ҫ���ǻ��Ǵ�ԭ����λ�� 
 	
 }
