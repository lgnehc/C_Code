#include <stdio.h>
int main()


{
	{
	//指针定义的字符串数组不能修改，只读  ；数组定义的字符串可以修改
	char *s="Hello";      //指针定ID字符串只读不写；
	
	char *s2="Hello";    //s和s2存放地址是一样的；  指针形式定义的字符串地址在常量池 ，比较小  
	char s3[]="Hello";   //字符串形式定义的地址是和以前的int整数在差不多位置的 
	s3[0]='B';           //这种才可以修改； 
//	s[0]='B';            //不能修改 
 	printf("%p\n",s);	
	printf("%c\n",*s);
	 
	printf("%p\n",s2);	
	printf("%c\n",*s2);
	

	printf("%p\n",s3);	
	printf("%c\n",s3[0]);
	}        	
	
			{ //输入输出字符串--空格 
				char word[8];
				printf("please input:");
				scanf("%s",word);    //scanf函数读入一个单词是以空格/tab/回车作为截止的 
				printf("%s\n",word);
				printf("%3s\n",word);  //这个应该只能输出3个字符的；但是这个可能版本不同 
				printf("%7s\n",word);
			 
			}
			
			
			   {
			   	char buffer[100]=""; //空字符串
				char buffer1[]="";   //这个数组长度只有1,里面没有空格 
				printf("buffer[5]=%c-end\n",buffer[5]); 
				printf("buffer=%s-end\n",buffer); 
				printf("buffer1[5]=%c-end\n",buffer1[5]); 
			   }
	
	return 0;
	
	
 } 
