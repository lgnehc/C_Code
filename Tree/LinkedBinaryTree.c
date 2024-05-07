#include <stdio.h>
#include <malloc.h>

/*问题点记录：
1.判断条件是n == 0；如果是n=0,地址会被赋值为NULL,导致出错
2.输入char型的判断是 n=='0';
3.这个程序在int型没有问题，但是在输入char型时会出现跳过scanf输入数据，解决办法：执行scanf前清楚缓冲区fflush(stdin);
*/

typedef  int Elemtype;

typedef struct  BinaryLinkedTreeNode
{
    Elemtype data;
    struct  BinaryLinkedTreeNode* PLeft;
    struct  BinaryLinkedTreeNode* PRight;
}BLTNode ,*PBLTNode;


//【1】静态创建二叉树,注意不是满二叉树--后面会改进
PBLTNode CreatTree(void){
  //【1.1】创建节点，这里简单粗暴用静态创建，节点多了不适用
  PBLTNode PA = (PBLTNode)malloc(sizeof(BLTNode));
  PBLTNode PB = (PBLTNode)malloc(sizeof(BLTNode));
  PBLTNode PC = (PBLTNode)malloc(sizeof(BLTNode));
  PBLTNode PD = (PBLTNode)malloc(sizeof(BLTNode));
  PBLTNode PE = (PBLTNode)malloc(sizeof(BLTNode));

   //【1.2】节点数据域赋值
    PA->data='A';
    PB->data='B';
    PC->data='C';
    PD->data='D';
    PE->data='E';
  //【1.3】节点指针域指向需要的结点；
   PA->PLeft = PB;
   PA->PRight =PC;
   PB->PLeft = PB->PRight =NULL;
   PC->PLeft = PD;
   PC->PRight = NULL;
   PD->PLeft = NULL;
   PD->PRight = PE;
   PE->PLeft = PE->PRight = NULL;

  //函数调用返回参数
  return PA; 
}

//静态创建二叉树的改进---使用先序遍历创建二叉树
void  CreatTree_Pre(BLTNode** PPT)     //这个是二级指针，传入的是指向第一个结点的指针的指针？？？  为什么
{
   Elemtype n;    
   printf("请输入当前节点的数据(0表示当前节点为NULL):");   

   fflush(stdin);    //清楚缓存区  int型没有问题，但是char型会出问题

   scanf("%d",&n);

   if(n == 0)    
   {
      *PPT = NULL;
      return ;        //就是直接退出，后面的语句不在执行
   }else{             //输入不是0的话，创建节点
   
     PBLTNode Pnode =  (PBLTNode)malloc(sizeof(BLTNode));
     Pnode->data = n;
     *PPT = Pnode;
     //先序遍历创建当前节点的左子树
     CreatTree_Pre(&((*PPT)->PLeft));
     //后序遍历创建当前节点的左子树S
     CreatTree_Pre(&((*PPT)->PRight));

   }

}

//【2】深度优先遍历
//【2.1】先序遍历二叉树
void PreTraverseTree (PBLTNode PT)
{
    if(PT == NULL){   //需要递归出口，判断是==,一个=是赋值为空error
      return;
    }
    else {
        //【2.1】先访问根节点
       // printf("先序输出结果为：");   加上的话每次调用都会输出一次
        printf("%d ",PT->data);

        //【2.2】先序访问左子树--当做一颗规模小点的子树--递归实现
        PreTraverseTree(PT->PLeft);

        //【2.3】先序访问右子树--当做一颗规模小点的子树--递归实现
        PreTraverseTree(PT->PRight);

    }
  
}


//【2.2】中序遍历二叉树
void MidTraverseTree (PBLTNode PT)
{
   if(PT == NULL){   //需要递归出口
      return;
    }
    else {
        //【2.2】先序访问左子树--当做一颗规模小点的子树--递归实现
        MidTraverseTree(PT->PLeft);

        //【2.1】先访问根节点
        printf("%d ",PT->data);

        //【2.3】先序访问右子树--当做一颗规模小点的子树--递归实现
        MidTraverseTree(PT->PRight);

    }
  
}

//【2.3】后序遍历二叉树
void PostTraverseTree (PBLTNode PT)
{
   if(PT == NULL){   //需要递归出口
      return;
    }
    else {
        //【2.2】先序访问左子树--当做一颗规模小点的子树--递归实现
        PostTraverseTree(PT->PLeft);

        //【2.3】先序访问右子树--当做一颗规模小点的子树--递归实现
        PostTraverseTree(PT->PRight);

         //【2.1】先访问根节点
        printf("%d ",PT->data);

    }
  
}


//【3】广度优先算法  --用对列实现（c++有库函数创建队列）
void LevelOrder_TraverseTree (PBLTNode PT){

}


//【4】后序遍历求树高
int getHeight(PBLTNode proot){
  if(proot == NULL)  { return 0;}
  else {
    int leftHeight = getHeight(proot->PLeft);
    int rightHeight = getHeight(proot->PRight);
    int height = (leftHeight > rightHeight) ? leftHeight :rightHeight;
    return height+1;

  }

}


void test (){
  BLTNode* T = NULL;  //定义空树
  printf("空树树高：%d\n",getHeight(T));

  //初始化一棵树
   CreatTree_Pre(&T);
    printf("先序输出结果为：");
    PreTraverseTree (T);
    printf("\n");
    printf("中序输出结果为：");
    MidTraverseTree (T);
    printf("\n");

  printf("树高为：%d\n",getHeight(T));
}

int main(){
   
   // PBLTNode PT = CreatTree();
 /*
   //创建一个空树
   PBLTNode PT = NULL;
   CreatTree_Pre(&PT);

    printf("先序输出结果为：");
    PreTraverseTree (PT);
    printf("\n");  

    printf("中序输出结果为：");
    MidTraverseTree (PT);
    printf("\n");

    printf("后序输出结果为：");
    PostTraverseTree (PT);
    printf("\n");

    printf("广度优先遍历结果为：");
    PostTraverseTree (PT);
    printf("\n");
  */
    test();
    return 0;
}