#include <stdio.h>


//����������ȷ�������ĸ��ļ�������������ʲô�ã����������һ�������ӵ�������򣬿����ж��Ǳ���������������ִ�У�
                                                     //��Linux���ã���ΪLinuxһ�������ļ�����ִ�е� 

int main(int argc,char const *argv[])
{
	int i;
	for (i=0;i<argc;i++){
		printf("��%d:%s\n",i,argv[i]);
	}
	
	return 0;
 } 
