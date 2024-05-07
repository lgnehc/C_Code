#include <stdio.h>
#include <string.h>

int mylen(const char *s);
int main()


{ 
 char line[]="hello";
 printf("strlen=%lu\n",mylen(line));
  printf("sizeof=%lu\n",sizeof(line));

  return 0; 
	
 } 
 
 
 
 
 
 
 int mylen(const char *s)
 {
 	int idx=0;
 	int cnt=0;
 	while (s[idx]!='\0'){
 		idx++;
 		cnt++;
	 }
	 return cnt;
 }
