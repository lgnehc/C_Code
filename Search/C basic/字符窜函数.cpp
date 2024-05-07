#include <stdio.h>
#include <string.h>

int mycmp(const char *s1,const char *s2);
char mycpy(char *dst,const char *src);
int main()


{ 

 char s1[]="abc";
 char s2[]="abc";
 printf("%d\n",mycmp(s1,s2));

  
  return 0; 
	
 } 
 
 int mycmp(const char *s1,const char *s2)
 {
   while (*s1==*s2 && *s1!='\0')
    {
   	s1++;
    s2++;
    }
 return (*s1-*s2);
 	
 }
