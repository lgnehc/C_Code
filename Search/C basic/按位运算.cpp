#include <stdio.h> 

int main(){
	
	unsigned char c=0xAA;
	unsigned int a=123;
	printf(" c=%hhx\n",c);
	printf("~c=%hhx\n",(char)~c);
	printf("-c=%hhx\n",(char)-c);
	
	
	printf("��5&4��=%d\n",5&6);      //����&��ȡ����� 
	printf("��5&&4��=%d\n",5&&4);   //&&�Ǳ��1&1--->1 
	
	printf("��5|4��=%d\n",5|6);
	printf("��5||4��=%d\n",5||4);
	
	printf("%hhx\n",c<<2);    //16---2--��λ---16���� 
	printf("%d\n",a<<2);      //*2��2�η� 
	printf("%hhx\n",a<<2);

	
	return 0;
}
