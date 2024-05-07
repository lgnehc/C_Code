#include <stdio.h>
int main()


{
  char word[]={'a','b','c','d'};          //字符数组 
  char word1[]={'a','b','c','d','\0'};    //字符串 
  char word2[]="abcd";                   //字符串初始化 
  char *word3="abcd";                    //字符串初始化
//  char word4[5]="abcdef";              //编译失败 
  
  
  //printf("1 %c\n",word);
  printf("2 %s\n",word);
  printf("3 %c\n",word[2]);
// printf("4 %s\n",word[2]);
  
 // printf("5 %c\n",word1);
  printf("6 %s\n",word1);
  printf("7 %c\n",word1[2]);
 //printf("8 %s\n",word1[2]);
 
 // printf("9 %c\n",word2);
  printf("10 %s\n",word2);
  
   printf("11 %s\n",word3);
   
 //  printf("12 %s\n",word4);
 
   printf("an,""on\n"); //会连起来
   printf("an,\
        on\n");  //空格会输出，这种连接字符串不好 
		 

	
	return 0;
	
	
 } 
