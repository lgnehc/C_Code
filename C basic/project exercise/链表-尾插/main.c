#include <stdio.h>
#include <stdlib.h>
#include  "node.h" 



int main(int argc, char *argv[]) 
{
    node* head=NULL;	
	int num;
	do{
		scanf("%d",&num);   //�������ݴ������� 
		
		if(num != -1){       //�ж��Ƿ���Ҫ�������� 
		node* p=(node*)malloc(sizeof(node));   
		p->value =num;
		p->next =NULL;     //��num����malloc����Ľṹ���ڴ棬������������ĩβ�����һ��ָ����NULL
		node* last=head;     //��Ҫ��ԭ������������ĵ�ַNULL��Ϊָ���²���������� 
		                     //������Ҫ��head�����ҳ�ԭ��δ��������ǰ��NULL 
		                     //Ϊʲô��Ҫ���¶���һ��lastָ�룬��Ϊ��������ǻᱻ�޸ĵ� 
		if(last != NULL) {    //���if���Ѿ��нڵ���������� 
		     
		while(last->next != NULL){    //���ﵽ26�ж��ǿ��ǵ�ԭ���Ѿ������ݵ�����²���        
			last=last->next ;
		                         }    	
		last->next =p;    //�ҵ���ԭ��δ��������ǰ��NULL��Ϊָ���²���Ľ�� 
	    }else{
			last=p;}    //�����Ǵ���ԭ��û�н����������Ҫ��last����ʱ����=head��ָ������´����Ľ�� 
		
		}
		
		
		
	}while(num != -1);
	
//	printf("111 %d",head->value ); 
	
	node* p;
    for(p=head->next ;p;p=p->next ){
    	
    	printf("test");         //�����ӡʧ�� 
    	printf("%d\n",p->value );
       
	}
	
	
	return 0;
}
