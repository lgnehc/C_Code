#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

//头结点+尾结点动态，封装成函数的话只需要返回头指针赋值给主函数的头指针即可 


typedef struct node{
	int date;
	struct node* pNext;
}NODE,*PNODE;  

//函数声明 
PNODE creat_list(void);              //创建链表--尾插入形式 
void traverse_list(PNODE pHEAD);     //遍历 
bool is_empty(PNODE pHead);         //判断是否空链表 
int length_list(PNODE pHead);       //判断链表长度
void select_sort_list(PNODE pHead) ;    //链表选择排序 
bool insert_list(PNODE ,int ,int ) ;   //链表插入
bool delete_list(PNODE pHead,int pos,int* val ); 
 
 

int main(void){
	
	PNODE pHead=NULL;
	pHead=creat_list();
	traverse_list(pHead);

    {               //判断是否空链表 
		if(is_empty(pHead))
		printf("链表是空\n");
	else
	   printf("链表不空\n");  }
	
	
	int len=length_list(pHead);
	printf("链表长度为%d\n",len);
	
//	select_sort_list( pHead);
//	traverse_list(pHead);
	
	insert_list( pHead,3,33 );
	printf("插入一个数据后链表数据如下：\n");
	traverse_list(pHead);
	
	int val;
	if(delete_list(pHead,4,&val )){
		printf("删除成功，删除的元素是：%d\n",val);
	}else{
		printf("删除失败\n"); 
	}
	printf("删除一个数据后链表数据如下：\n");
	traverse_list(pHead);

	
	return 0;
} 


PNODE creat_list(void)
{
	int i,val,len;
	
    PNODE pHead=(PNODE)malloc(sizeof(NODE));  
    if(pHead==NULL){        //分配空间失败检测 
    	printf("分配失败,程序终止");
		exit(-1);    
	}
	
	PNODE pTail=pHead;
    pTail->pNext=NULL;                            //开始error的原因  pTail=NULL
    
    printf("输入节点个数：len=");
    scanf("%d",&len);
    
    for(i=0;i<len;i++){
    	printf("输入第%d个结点数据:",i+1);
    	scanf("%d",&val);
    	
    	PNODE pNew=(PNODE)malloc(sizeof(NODE) ); // 新加入的结点命名为pnew,输入的数据加入到链表中 
                	if(pNew==NULL){        //分配空间失败检测 
    				printf("分配失败,程序终止");
					exit(-1);    
									}
	
		pNew->date =val;                //如果分配成功 
		pTail->pNext=pNew;                      //error失败了 why 	
		pNew->pNext=NULL;
		pTail=pNew;                    //把最后结点重新命名为 ptail;也保证ptail指向空地址 
	
	}
    return pHead; 
}

void traverse_list(PNODE pHead)      //遍历链表 
{   
	PNODE p = pHead->pNext;
	while(p != NULL){
		printf("%d  ",p->date );
		p=p->pNext;
	
	}
	printf("\n");

}



bool is_empty(PNODE pHead){    //判断是否空 
	if(pHead->pNext ==NULL)
	    return true;
	else
	    return false;
	
}

int length_list(PNODE pHead)   //计算链表长度
{
	int len=0;
	PNODE p = pHead->pNext;
	while(p!= NULL){
		len++;
		p=p->pNext;
	}
	
	return len;
}

	
 void select_sort_list(PNODE pHead)        //链表选择排序 
 {
 	 PNODE turn=pHead->pNext ;       //控制轮数和初始节点
 	 PNODE move=turn->pNext; //从第二个开始移动； 
	 PNODE max=turn;          // 
	
	 while(turn->pNext  != NULL) {    //外循环控制轮数 ，为什么要指向 turn->pNext？？因为轮数实际不需要这么多 
	 
	  while(move  != NULL) {        //内循环找出最大数所在位置    
	  //为什么内循环move->pnext !=0??  move是个地址，move->pnext指向的是下个结点的地址 
	  	 	if(move->date > max->date ){
	  	 		max=move;               //max记录的就是最大结点，本身都是结构体 
			   }	                 //判断大小 
			move=move->pNext;         
	  }                              //可以找出一轮中最大值； 
	  
	   //找出最大值开始交换 
	 	 if(max != turn)           //如果一开始就是最大值，那么不用交换 
	 	 {
	 	 	NODE tem;
	 	 	tem.date  = turn->date ;
	 	 	turn->date = max->date ;
	 	 	max->date  = tem.date ;    // 数据交换 
			   
		  }
	  //交换完进入下一轮判断 
		 turn=turn->pNext ;
		 move=turn->pNext;    //move是在turn下一个结点；这里turn已经重新赋值了， 
		 max=turn; 
	 }
 	
 }


//链表插入 ： 第pos位置插入val值 
bool insert_list(PNODE pHead,int pos,int val ) 
{
	int i=0;
	PNODE p=pHead; 
	//判断是否可以插入节点
	if(pos<0)
	return false;
	
	while(i<pos-1 && p!=NULL){   //寻找第i-1个结点   i-1就是p 
		i++;
		p=p->pNext; 
	} 
	
	if(p==NULL)    //未找到i-1个位置 
	return false; 
	
	//判断后可以开始插入 
	PNODE PNew=(PNODE)malloc(sizeof(NODE));
   				if (PNew==NULL){
					printf("分配内存失败\n");
					exit(-1);
								}
							
	PNew->date =val;
	PNew->pNext=p->pNext ;
	p->pNext =PNew;
	
	return true; 	
}  


//链表删除pos位置结点 
bool delete_list(PNODE pHead,int pos,int* val ) 
{
	int i=0;
	PNODE p=pHead; 
	
	if(pos<0)
	return false;
	
	while(i<pos-1 && p->pNext != NULL){     //找出删除的POS位置的前一个结点位置 ，POS前一个位置为p; 
		i++;
		p=p->pNext; 
	} 
	
	if(p->pNext == NULL)    //未找到i-1个位置 
	return false; 
	
	//判断后可以开始删除
	PNODE q=p->pNext ;
	*val=q->date;  //待会返回删除节点的值 
	
	p->pNext =p->pNext->pNext ;
	free(q);
	q=NULL;
	
	return true; 	
}

