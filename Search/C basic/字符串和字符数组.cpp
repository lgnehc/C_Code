#include <stdio.h>
int main()


{
  char word[]={'a','b','c','d'};          //�ַ����� 
  char word1[]={'a','b','c','d','\0'};    //�ַ��� 
  char word2[]="abcd";                   //�ַ�����ʼ�� 
  char *word3="abcd";                    //�ַ�����ʼ��
//  char word4[5]="abcdef";              //����ʧ�� 
  
  
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
 
   printf("an,""on\n"); //��������
   printf("an,\
        on\n");  //�ո����������������ַ������� 
		 

	
	return 0;
	
	
 } 
