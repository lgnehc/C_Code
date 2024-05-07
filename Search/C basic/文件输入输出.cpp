#include <stdio.h>

int main(){
	
	FILE *p_file=fopen("D:\\C code exercise\\mark.txt","r");   //文件路径是双斜杠，单斜杠转义字符要用 
	int i;

		if(p_file !=0){
		int num;
		fscanf(p_file,"%d",&num);
	    printf("%d\n",num);
	    fclose(p_file);
	}else{
		printf("cann't open the file");
	}
		


	
	return 0;
} 
