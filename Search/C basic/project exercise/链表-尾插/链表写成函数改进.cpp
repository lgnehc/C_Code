#include <stdio.h>
#include <stdlib.h>

void add(List* plist,int num);

typedef struct _node{
	int value;
	struct _node *next;
}node;  


typedef struct _list{
   node* head;	
	
}List;


int main(int argc, char *argv[]) 
{
    List list;
    list->head=NULL;
   	
	int num;
	do{
		scanf("%d",&num);   //�������ݴ������� 
		
		if(num != -1){       //�ж��Ƿ���Ҫ��������                       
        add(&list,number);
		}
	}
		while(num != -1);
	
 
	
	
	return 0;
} 
void add(List* plist,int num)
   {
   	//add to linked-list 
		node* p=(node*)malloc(sizeof(node));   
		p->value =num;
		p->next =NULL;     
		node* last=*phead;     
		                     
		if(last != NULL) {    
		     
		while(last->next != NULL){        
			last=last->next ;
		                         }    	
		last->next =p;    
	    }else{
			plist->head =p;}    
   
   }
	
