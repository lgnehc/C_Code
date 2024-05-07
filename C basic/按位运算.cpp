#include <stdio.h> 

int main(){
	
	unsigned char c=0xAA;
	unsigned int a=123;
	printf(" c=%hhx\n",c);
	printf("~c=%hhx\n",(char)~c);
	printf("-c=%hhx\n",(char)-c);
	
	
	printf("（5&4）=%d\n",5&6);      //单个&是取后面的 
	printf("（5&&4）=%d\n",5&&4);   //&&是变成1&1--->1 
	
	printf("（5|4）=%d\n",5|6);
	printf("（5||4）=%d\n",5||4);
	
	printf("%hhx\n",c<<2);    //16---2--移位---16进制 
	printf("%d\n",a<<2);      //*2的2次方 
	printf("%hhx\n",a<<2);

	
	return 0;
}
