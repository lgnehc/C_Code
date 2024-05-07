#include <stdio.h>


//这个程序可以确定是在哪个文件输出的这个，有什么用？就是如果有一个软链接到这个程序，可以判断是本程序还是软链接在执行，
                                                     //在Linux有用，因为Linux一般是用文件名来执行的 

int main(int argc,char const *argv[])
{
	int i;
	for (i=0;i<argc;i++){
		printf("行%d:%s\n",i,argv[i]);
	}
	
	return 0;
 } 
