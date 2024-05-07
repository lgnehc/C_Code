#include <stdio.h>
#include <stdbool.h>

//循环队列的实现，需要初始化，判断队空队满，入队，出队，打印元素首位元素，判断元素个数，打印所有元素

#define Maxsize 5

typedef struct Queue{
    int data[Maxsize];
    int front;
    int rear;
}Queue;


//初始化队列
void InitQueue(Queue* pq)
{
    pq->front =0;
    pq->rear=0;
}

//判断队空  //是空返回1,非空返回0
bool IsEmpty(Queue* pq){
    if(pq->front == pq->rear)
      return true;        
    else 
      return false ;
}

//判断队满
bool IsFull(Queue* pq){
    if( (pq->rear+1)%Maxsize == pq->front )
      return true;        
    else 
      return false ;
}

//入队 ,这里队列是front指向空，rear指向最后元素（也可以是rear指向空，front指向首元素）
void push(Queue* pq,int val){
    //判断是否队满
    if( IsFull(pq) ){
        printf("队满无法入队\n");
        return ;
    }else{

    pq->rear = ((pq->rear)+1) % Maxsize;
    pq->data[pq->rear] = val;
      
    } 
    
}

//出队
int pop(Queue* pq){
    //队列空本能出队
  if( IsEmpty(pq) )
  {
    printf("队空无法出队\n");
    return -1;
  }else
  {
   pq->front = (pq->front+1) % Maxsize;
   int val = pq->data[pq->front];
   return val;
  }
}


//判断队头元素      error，待调试
int getFront(Queue* pq){
  if ( IsEmpty(pq) ){
    printf("队列空，没有元素\n");
    return  -1;
  }else{
  //int tem = ((pq->front)+1)/Maxsize;
  //return pq->data[tem];
   int val = pq->data[((pq->front)+1)/Maxsize];     //error
   return val;}
}


//判断队尾元素
int getRear(Queue* pq){
  if ( IsEmpty(pq) ){
    printf("对空，没有元素\n");
    return -1;
  }else{
    return pq->data[pq->rear]; 
  }
}

//判断队列元素个数,空的那个不算
int sizeQueue(Queue* pq)
{
    int length;

   if( IsEmpty(pq) ){
    printf("队列是空，没有元素\n");
     length=0;
   }
   else{
    //如果非空判断此时队列有多少元素
    if(pq->rear > pq->front){
       length = (pq->rear)-(pq->front);
    }else{
       length = ((pq->rear)+Maxsize)-(pq->front);
    }  
}
  return length;
}


//打印所有元素
void PrintQueue(Queue* pq)
{  
    int tem = pq->front; 
    int i=1;
    printf("队列元素是:", i ,pq->data[tem]);

    while(tem != pq->rear){
     tem = (tem+1)%Maxsize;
     printf("%d-->",pq->data[tem]);
                       //tem = (tem+1)%Maxsize;  error
     i++;
     }

     printf("\n");
  }  


//测试函数
void test()
{
  int val;
  //定义一个队列 
  Queue q;
 //初始化
 InitQueue(&q);
 //判空
 IsEmpty(&q);

//入队5个元素,有一个无法入队
  push(&q,10);
  push(&q,20);
  push(&q,30);
  push(&q,40);
  push(&q,50);   //50无法入队
 
//打印队首队尾元素
printf("队列元素个数：%d\n",sizeQueue(&q));
printf("队首元素是：%d \n",getFront(&q));
printf("队尾元素是：%d \n",getRear(&q));
PrintQueue(&q);  //打印所有元素

//弹出元素,依次弹出10,20
  printf("%d ",pop(&q));      
  printf("%d ",pop(&q));   
  PrintQueue(&q);  
  
  printf("%d ",pop(&q));
  printf("%d ",pop(&q));
  printf("%d \n",pop(&q));    //队空，无法出队，应该返回-1

  push(&q,100);
  push(&q,200);

  printf("队列元素个数：%d\n",sizeQueue(&q));
  printf("队首元素是：%d \n",getFront(&q));
  printf("队尾元素是：%d \n",getRear(&q));
  PrintQueue(&q); 

}  


int main( void)
{
  
  test();
  return 0;
}