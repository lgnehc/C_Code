#include <stdio.h> 
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


typedef int ElemType;
typedef struct node{
	ElemType date;  //数据域
	struct node* PNext;  
   }NODE,*PNODE;  

typedef struct LinkedStack{    
	PNODE PTop;
    int size;  
	     //PNODE PBottom; 
   }LinkedStack,*P_LinkedStack;

//函数声明
void initStack(P_LinkedStack  pstack);
bool isempty(LinkedStack stack);
int size_stack(LinkedStack stack);
bool pushstack(P_LinkedStack pstack, ElemType val);
ElemType  popstack(P_LinkedStack pstack);
ElemType peek(LinkedStack stack );
void print_stack(LinkedStack stack);



int main()
{
    LinkedStack linkstack;
   
    initStack(&linkstack);
    assert(isempty(linkstack));      //断言成功返回空
    assert(size_stack(linkstack) == 0);

   int i;                  //入栈
    for (i=1;i<=5;i++){
        pushstack(&linkstack,i);
    }
    print_stack(linkstack);

   

    for(i=5;i>=1;i--){   //出栈
       printf("此时栈顶元素是:%d\n",peek(linkstack));
       printf("第%d次出栈成功,出栈数据是：%d\n",i,popstack(&linkstack)) ;
    }

    printf("此时栈长度是:%d\n",linkstack.size);
    assert(isempty(linkstack) == 1);  
    print_stack(linkstack);
    return 0;
}


//初始化链栈
void initStack(P_LinkedStack  pstack)
{
  pstack->PTop=NULL;
  pstack->size = 0;
}


//判断是否空栈
bool isempty(LinkedStack stack){    //返回1表示是空栈
    return stack.PTop == NULL;
}

//判断栈长度
int size_stack(LinkedStack stack){
    return stack.size;
}


//入栈操作
bool pushstack(P_LinkedStack pstack, ElemType val)
{

    PNODE  pnewnode=(PNODE)malloc(sizeof(NODE)) ;
     if(pnewnode == NULL){
        printf("分配失败\n");
     }else
     {
        pnewnode->date = val;
        pnewnode->PNext = pstack->PTop;
        pstack->PTop = pnewnode;
        pstack->size++;
        
        return true ;
     }
}


//出栈,弹出栈顶元素
ElemType  popstack(P_LinkedStack pstack)
{
  if(pstack->size == 0)   //因为判断isempty是给的栈，不是指针，这里用size判断更好
  {
    printf("是空栈，无法弹出\n");
  }
   else{
    
     PNODE p_poppedstack = pstack->PTop;
     ElemType poppedElem = p_poppedstack->date; 
     pstack->PTop = pstack->PTop->PNext;
     pstack->size--;
     free(p_poppedstack);
     return poppedElem;
   }
}



//读取栈顶元素，不删除
ElemType peek(LinkedStack stack )
{

  if(isempty(stack))   
  {
    printf("是空栈，无法读取栈顶数据\n");
  }
   else{
   return stack.PTop->date;

   }
}


//打印栈数据，从栈顶到栈底
void print_stack(LinkedStack stack)
{
    PNODE tem = stack.PTop;
    while(tem != NULL){
        printf("%d\t ",tem->date);
        tem=tem->PNext;
    }
    printf("\n");
}