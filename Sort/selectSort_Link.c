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
void select_sort_list(PNODE pHead) ;       //链表排序 

 

int main(void){
	
	PNODE pHead=NULL;
	pHead=creat_list();
	traverse_list(pHead);

	select_sort_list(pHead);
    printf("排序结果：");
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


void select_sort_list(PNODE pHead)	
{
	PNODE turn=pHead->pNext ;
	PNODE move=pHead->pNext->pNext;
	PNODE max=turn;
	//PNODE max=pHead->pNext;
	
	while(turn->pNext != NULL){
		
		//内循环找出最大结点 
		while(move  != NULL){    //
			if(max->date < move->date ){
			max=move;	
		   }
		   move=move->pNext ;
		}
		//交换结点
		if(max != turn)
		{
			NODE tem;
			tem.date  =turn->date;   //error
			turn->date=max->date ;
			max->date=tem.date ;	
		} 
		//准备进入下一轮外循环，指针归位
		turn=turn->pNext ;
		move=turn->pNext;
		max=turn; 
	
	}

}