#include <stdio.h> 
#include <malloc.h>
#include <stdlib.h>



typedef struct node{
	int date;
	struct node* PNext;
}NODE,*PNODE;  

typedef struct Stack{    
	PNODE PTop;
	PNODE PBottom; 
}STACK,*PSTACK;



void init(PSTACK) ;
void push(PSTACK,int);
void traverse(PSTACK); 
bool pop(PSTACK,int* );
bool empty(PSTACK PS);

int main(){
	
  STACK S;   
  int val;
  
  init(&S);
  push(&S,1);
  push(&S,2);
  push(&S,3);
  push(&S,4);
  push(&S,5);	
  traverse(&S); 	
  
 if(pop(&S,&val))
     printf("出栈成功,the number of pop is :%d\n",val);
  else 
     printf("出栈失败\n") ;
     
  
  traverse(&S);
	
	return 0;
}


void init(PSTACK PS){    

    PS->PBottom = (PNODE)malloc(sizeof(NODE));   
    if(PS->PBottom = NULL) 
	         {printf("内存分配失败");exit(-1); } 
    else{
    	 PS->PTop =PS->PBottom ;                   
	   //  PS->PBottom->PNext = NULL;   //error 
	     printf("初始化成功\n");
	}    
	
}

void push(PSTACK PS,int val)
{
		PNODE PNew=(PNODE)malloc(sizeof(NODE));
		PNew->date =val;
		PNew->PNext =PS->PTop ;   
		PS->PTop =PNew;
		
		return;
}


void traverse(PSTACK PS)
{
	PNODE P = PS->PTop ;
	while(P != PS->PBottom ){
		printf("%d",P->date);
		P=P->PNext ;
		printf("\n");
	}
	
}

bool empty(PSTACK PS)
{
	if (PS->PTop =PS->PBottom )
     	return true;
	else
		return false;
}



bool pop(PSTACK PS,int* pval)
{
	if(empty(PS))
	    return false;
	else
	{
		PNODE tem = PS->PTop;  
		PS->PTop = PS->PTop->PNext ;        //error 
		
		*pval=tem->date;
		free(tem);   
		tem =NULL;
		
		return true;
	}
}