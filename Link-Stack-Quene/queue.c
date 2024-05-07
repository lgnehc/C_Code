#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//[1]定义静态顺序表的最大长度和动态顺序表的初试空间
#define   Maxsize 10
#define  Initsize 10

typedef int Elemtype;

//定义静态分配结构体，数组
typedef struct Sq_array{
    Elemtype data[Maxsize];
    int length;
}Sq_array,*PSq_array;

//定义动态结构体，链表
typedef struct Sq_list{
    Elemtype * Pdata;  //等价于int data[Maxsize],为什么是指针？？这里使用动态指针分配数组，所以用指针类型
    //后面初始化是给了一个存放10个int型数据的内存，这是这个内存的地址，sqlist.Pdata[i]这个来访问int数据
    //  ar[i]和*(ar+i)这两个表达式都是等价的。无论ar是数组名还是指针变量，这两个表达式都没问题。但是，只有当ar是指针变量时，才
    //   能使用ar++这样的表达式。 
    int len;
    int maxsize;
}Sq_list ,*PSq_list;


//初始化
//静态队列的初始化
bool init_sq_array(PSq_array L){
    L->length=0; 
    // for(int i=0;i<Maxsize;i++){
    //  L->data[i]=0;
    //}
   return true;
}


//链表队列的初始化
bool init_sq_list(PSq_list L){
    L->len=0; 
    L->maxsize = Initsize; //初始化队列长度为10
    L->Pdata = (Elemtype*)malloc(sizeof(Elemtype)*Initsize);
    return true;
}


//静态队列输出
bool Sq_array_print(Sq_array array)
{
    if(array.length == 0){
        printf("this is empty\n");
        return false;
    } 
    else{
         printf("Sq_array:\n");
         int i;
        for(i=0;i<array.length;i++){
           printf("%d-->",array.data[i]);
            
        }
        printf("end\n");

        return true;
    }
}


//链表队列输出
bool Sq_List_print(Sq_list  sqlist){
    if(sqlist.len == 0){
        printf("this is empty\n");
        return false;
    } 
    else{
         printf("SqList:\n");
         int i;
        for(i=0;i<sqlist.len;i++){
           printf("%d-->",sqlist.Pdata[i]);   //sqlist.Pdata[i] == *(sqlist.Pdata+i)
            
        }
        printf("end\n");

        return true;
    }
}




//插入
//静态队列的插入  ，在第i个位置插入数据val
bool sqarrayinsert(PSq_array PL1,int i, Elemtype val)
{ //<1>判断是否可以插入
  if(i<1 || i>PL1->length+1){
    printf("插入位置无效\n");
    return false;
  }
   if(PL1->length > Maxsize){
    printf("队列已满，插入失败\n");
    return false;
  }
  //<2>开始插入
  for(int j=PL1->length;j>=i ;j--) {
    PL1->data[j]=PL1->data[j-1];
  }
    PL1->data[i-1] =val;
    PL1->length++;
    return true;
}

//动态队列插入
bool sqlistinsert(PSq_list PL2,int i, Elemtype val)
{ //<1>判断是否可以插入
  if(i<1 || i>PL2->len+1){
    printf("插入位置无效\n");
    return false;
  }
   if(PL2->len > PL2->maxsize){
    printf("队列已满，插入失败\n");
    return false;
  }
  //<2>开始插入
  for(int j=PL2->len;j>=i ;j--) {   //在中间位置插入
    PL2->Pdata[j]=PL2->Pdata[j-1];
  }
    PL2->Pdata[i-1] =val;
    PL2->len++;
    return true;
}


//队列删除
//静态删除，删除第i个位置的值，并返回删除的值
bool sqarraydelete(PSq_array PL1,int i, Elemtype *val){
  //判断i位置合法性
  if(i<1 || i>PL1->length+1)
  {

    printf("删除位置无效\n");
    return false;
  }
  //判断是否满或空
   if(PL1->length <= 0){
    printf("队列是空的，删除失败\n");
    return false;
  }
  //判断合法开始删除
  *val=PL1->data[i-1];
  //把后面的数据往前移位
  for(int j=i;j <= PL1->length;j++){
    PL1->data[j-1]=PL1->data[j];
  }
  PL1->length--;
  return true;  
}

//动态删除，删除第i个位置的值，并返回删除的值
bool sqlistdelete(PSq_list PL2,int i, Elemtype *val){
  //判断i位置合法性
  if(i<1 || i>PL2->len+1)
  {
    printf("删除位置无效\n");
    return false;
  }
  //判断是否满或空
   if(PL2->len <= 0){
    printf("队列是空的，删除失败\n");
    return false;
  }
  //判断合法开始删除
  *val=PL2->Pdata[i-1];
  //把后面的数据往前移位
  for(int j=i;j <= PL2->len;j++){
    PL2->Pdata[j-1]=PL2->Pdata[j];
  }
  PL2->len--;
  return true;  
}


//按位查找，查找某个数在队列的位置
//静态查找
int SqarrayLocElem(Sq_array L1,Elemtype val)
{
  for(int i=0; i < L1.length; i++){
    if(L1.data[i] == val){
      return i+1;
    } 
  }
  return 0;
}

//动态查找
int SqlistLocElem(Sq_list  L2,Elemtype val)
{
  for(int i=0; i < L2.len; i++){
    if(L2.Pdata[i] == val){
      return i+1;
    } 
  }
  return 0;
}


//动态队列的扩容，把数据全部移动到一个更大的空间并释放原来的内存
bool IncreaseSize(PSq_list PL,int len2)     //len2是需要增加的容量
{
  // [1]生成指向原来空间的地址，后面释放使用
  Elemtype* ptem = PL->Pdata;
  //【2】开一个更大的空间
  PL->Pdata = (Elemtype*)malloc(sizeof(Elemtype)*(PL->len+len2));
  //【3】转移数据
  for(int i=0; i<PL->len; i++){
    PL->Pdata[i] = ptem[i];
  }
  //【4】修改长度
  PL->maxsize +=len2;
  //【5】释放空间
  free(ptem);
  return true;
}


int main()
{
    Sq_array L1;
    Sq_list  L2;
    
    //初始化
    init_sq_array(&L1);
    init_sq_list(&L2);

   //测试初始化是否成功
   /*/ L2.maxsize =1;   //???  测试初试化的，如果初始化成功会变成10
    init_sq_list(&L2);
    printf("%d\n",L2.maxsize); */

    //插入一些元素
   sqarrayinsert(&L1 ,1,1);
   sqarrayinsert(&L1 ,2,2);
   sqarrayinsert(&L1 ,3,333);
   sqarrayinsert(&L1 ,4,4);
   sqarrayinsert(&L1 ,5,5);
   sqarrayinsert(&L1 ,6,6);
   sqarrayinsert(&L1 ,7,7);
   sqarrayinsert(&L1 ,8,8);

   sqlistinsert(&L2,1,1);
   sqlistinsert(&L2,2,2);
   sqlistinsert(&L2,3,3);
   sqlistinsert(&L2,4,4);
   sqlistinsert(&L2,5,5);
   sqlistinsert(&L2,6,6);
   sqlistinsert(&L2,7,7);
   sqlistinsert(&L2,8,888);
   
   Sq_array_print(L1);
   Sq_List_print(L2);
  
  //删除操作
   int val1,val2;
   sqarraydelete(&L1,3,&val1);
   sqlistdelete(&L2,8,&val2);

   Sq_array_print(L1);
   Sq_List_print(L2);
   printf("sqarray删除的值是:%d\n",val1);
   printf("sqlist删除的值是:%d\n",val2);

   //按位查找
   printf("在sqarray第%d个位置\n",SqarrayLocElem(L1,5));
   printf("在sqlist第%d个位置\n",SqlistLocElem(L2,5));

   //扩容操作
   IncreaseSize(&L2,20);
   Sq_List_print(L2);
   printf("扩容后长度为：%d",L2.maxsize);


    return 0;
}