#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

//头结点+尾结点动态，封装成函数的话只需要返回头指针赋值给主函数的头指针即可


typedef struct node{
	int date;
	struct node* pNext;
}NODE,*PNODE;  

//函数声明 
PNODE creat_list(void);             //创建链表--尾插入形式 
void traverse_list(PNODE pHEAD);    



int main(void){
	
	PNODE pHead=NULL;
	pHead=creat_list();
	traverse_list(pHead);
	
	
	return 0;
} 


PNODE creat_list(void)
{
	int i,val,len;
	
    PNODE pHead=(PNODE)malloc(sizeof(NODE));  
    if(pHead==NULL){        //分配空间失败检测 
    	printf("分配失败,程序终止ֹ");
		exit(-1);    
	}
	
	PNODE pTail=pHead;
    pTail->pNext=NULL;                            //开始error的原因  pTail=NULL
    
    printf("输入节点个数:len=");
    scanf("%d",&len);
    
    for(i=0;i<len;i++){
    	printf("输入第%d个结点数据:",i+1);
    	scanf("%d",&val);
    	
    	PNODE pNew=(PNODE)malloc(sizeof(NODE) ); // 新加入的结点命名为pnew,输入的数据加入到链表中 
                	if(pNew==NULL){        
    				printf("分配失败,程序终止ֹ");
					exit(-1);    
									}
	
		pNew->date =val;                //如果分配成功 
		pTail->pNext=pNew;                        //error失败了 why	
		pNew->pNext=NULL;
		pTail=pNew;                    //把最后结点重新命名为 ptail;也保证ptail指向空地址
	
	}
    return pHead; 
}

void traverse_list(PNODE pHead)   
{
	PNODE p = pHead->pNext;
	while(p != NULL){
		printf("%d  ",p->date );
		p=p->pNext;
	}
	printf("\n");
}


