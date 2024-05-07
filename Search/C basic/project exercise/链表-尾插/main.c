#include <stdio.h>
#include <stdlib.h>
#include  "node.h" 



int main(int argc, char *argv[]) 
{
    node* head=NULL;	
	int num;
	do{
		scanf("%d",&num);   //输入数据存入链表 
		
		if(num != -1){       //判断是否需要加入链表 
		node* p=(node*)malloc(sizeof(node));   
		p->value =num;
		p->next =NULL;     //将num存入malloc分配的结构体内存，插入的是链表的末尾，最后一个指针是NULL
		node* last=head;     //需要把原来的链表的最后的地址NULL改为指向新插入的这个结点 
		                     //所以需要从head遍历找出原来未插入数据前的NULL 
		                     //为什么需要重新定义一个last指针，因为这个等下是会被修改的 
		if(last != NULL) {    //这个if是已经有节点新增的情况 
		     
		while(last->next != NULL){    //这里到26行都是考虑的原来已经有数据的情况下插入        
			last=last->next ;
		                         }    	
		last->next =p;    //找到后将原来未插入数据前的NULL改为指向新插入的结点 
	    }else{
			last=p;}    //这里是处理原来没有结点的情况，需要把last，此时还是=head，指向这个新创建的结点 
		
		}
		
		
		
	}while(num != -1);
	
//	printf("111 %d",head->value ); 
	
	node* p;
    for(p=head->next ;p;p=p->next ){
    	
    	printf("test");         //进入打印失败 
    	printf("%d\n",p->value );
       
	}
	
	
	return 0;
}
