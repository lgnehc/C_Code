#include <stdio.h>

int main(){
	
	FILE *p_file=fopen("D:\\C code exercise\\mark.txt","r");   //�ļ�·����˫б�ܣ���б��ת���ַ�Ҫ�� 
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
