#include <stdio.h>
#include <malloc.h>

/*
***学习资料：B站up:哈哈哈哈栋
平衡二叉树
1.为什么引入平衡二叉树
2.平衡二叉树特点
3.平衡因子怎么判定
4.如何调整失衡：左旋右旋
5.什么情况会导致失衡：插入失衡4种情形：删除失衡情形
6.平衡二叉树的失调情形判断：4种 
  举例：RL判断：先判断最小失衡二叉树-->判断失衡的结点在最小失衡二叉树的根节点的右边--》
        再判断失衡的结点是在（最小失衡二叉树的根节点的右子树）的左子树还是右子树
 7.插入失衡的4种情形的解决
 8.如何创建平衡二叉树：插入一个新节点：先按二叉搜索树插入--》在按平衡因子判断是否调整失衡 
 
 9.删除某个结点导致失衡：这里怎么判断是哪种失衡
*/

typedef struct  AVLTree_node{
    int data;   //数据域
    int height; //树高
    struct  AVLTree_node* PLeft;
    struct  AVLTree_node* PRight;
}AVLnode;

//[1]创建新节点,节点的值是val，并初始化
AVLnode* newnode(int val ){
   AVLnode* pnode =(AVLnode*)malloc(sizeof(AVLnode));
   pnode->data = val;
   pnode->height = 1;
   pnode->PLeft = NULL;
   pnode->PRight =NULL;

   return pnode;
}

//[2]获取树的高度
int getHeight(AVLnode* pnode){
   if(pnode == NULL)
      return 0;
    return pnode->height;
}

//[3]获取平衡因子函数:左子树高度-右子树高度
int getBalance(AVLnode* proot ){
    return getHeight(proot->PLeft) - getHeight(proot->PRight);
}

int max(int a, int b){
    return (a>b) ? a : b;
}

//找左子树的最大值
AVLnode* findmax(AVLnode* PT){
    if (PT == NULL) { 
     printf("树空\n");
     return NULL;
    }
    while (PT->PRight != NULL)       
     {  PT = PT->PRight; }
    return PT;   
}

//[4.1]定义左旋函数，直观图解见视频
AVLnode* leftRotate(AVLnode* proot){
//1.当前节点的右子树作为新树的根节点
//2.当前节点proot变成新树的根节点pnewroot左子树  
//如果新的树根，原来有左子树，原来有左子树就作为旧结点的右子树
  AVLnode* pnewroot = proot->PRight;  //定义新树根结点的地址
  AVLnode* T2 =pnewroot->PLeft;       //保存新树根原来的左子树结点地址为T2

  pnewroot->PLeft = proot;
  proot->PRight = T2;  
  //疑问：原来指向root的结点此时还是指向root，是否有问题？没关系最后返回的是newroot,作为新根了

  //更新树高，更新root 和 newroot
  //树高怎么求？根的左子树的高+1 or 根的右子树的高+1
  proot->height = 1+max(getHeight(proot->PLeft),getHeight(proot->PRight));
  pnewroot->height = 1+max(getHeight(pnewroot->PLeft),getHeight(pnewroot->PRight));

  return pnewroot;
}

//[4.2]定义右旋函数，直观图解见视频
AVLnode* rightRotate(AVLnode* proot){
//1.当前节点的左子树作为新树的根节点
//2.当前节点root变成新树的根节点newroot右子树  
//如果新的树根，原来有右子树，原来有右子树就作为旧结点的左子树
  AVLnode* pnewroot = proot->PLeft;  
  AVLnode* T2 =pnewroot->PRight;       

  pnewroot->PRight = proot;
  proot->PLeft = T2;  
  
  proot->height = 1+max(getHeight(proot->PLeft),getHeight(proot->PRight));
  pnewroot->height = 1+max(getHeight(pnewroot->PLeft),getHeight(pnewroot->PRight));

  return pnewroot;
}

//[5]定义插入结点的函数，插入节点导致失衡的有四种情形LL/LR/RR/RL ,插入时可以实现动态平衡
 AVLnode* insertNode(AVLnode* proot,int val){
    //1.先进行二叉搜索树的插入，后面在调整
    if(proot == 0)  
        return newnode(val);
    if(val < proot->data) 
        proot->PLeft = insertNode(proot->PLeft,val);
    else if(val > proot->data)
       proot->PRight = insertNode(proot->PRight,val);
    else 
      return proot;   //相等情况，直接返回即可

    //更新树高
    proot->height = 1+max(getHeight(proot->PLeft),getHeight(proot->PRight));

    //判断是否需要调整，需要平衡因子（|balance|≤1不用调整）来判断
    //结点A的balance定义：A的左子树高度（结点个数）- A的右子树高度,是不考虑这个结点的
    int balance = getBalance(proot);
    //LL型失衡调整：当前节点右旋
      //如何判断是LL型失衡:当前节点balance>1 ,并且当前节点的左子树的balance >0;
    if(balance >1 && getBalance(proot->PLeft)>0)
      return rightRotate(proot);   
    
    //LR型失衡调整:先对结点的左子树左旋，结点在右旋
    if(balance >1 && getBalance(proot->PLeft)<0){
       proot->PLeft = leftRotate(proot->PLeft);  //  ???
       return rightRotate(proot);
    }
       
    //RR型失衡调整:结点左旋
    if(balance < -1 && getBalance(proot->PRight) <0)
      return leftRotate(proot);
    
    //RL型失衡调整:结点的右子树右旋，结点左旋
    if(balance < -1 && getBalance(proot->PRight) >0){
       proot->PRight = rightRotate(proot->PRight);
       return leftRotate(proot);
    }

   //调整完返回地址
   return proot;
 }

//[5]删除节点导致的失衡调整
/* 前半部分：先按照二叉搜索树的删除
  后半部分：插入节点导致的失衡修改,RR/LL型要稍作调整. */

AVLnode* deleteNode(AVLnode* proot,int val){
  //[5.1] 二叉搜索树的删除
  if( proot == NULL)          {return NULL;}
  if(val < proot->data)       {proot->PLeft = deleteNode(proot->PLeft,val);}
  else if(val > proot->data)  {proot->PRight = deleteNode(proot->PRight,val);}
  else if(val == proot->data)   
  {

    if((proot->PLeft == NULL) && (proot->PRight == NULL)){
      free(proot);          //free是直接赋值random
      proot = NULL;         //赋值为NULL后，里面的random会全部置零    
    }
    else if(proot->PLeft != NULL && proot->PRight == NULL){
        AVLnode* ptem = proot; 
        proot = proot->PLeft; 
        free(ptem);
                     
    }
    else if(proot->PLeft == NULL && proot->PRight != NULL){
      AVLnode* ptem = proot; 
      proot = proot->PRight;   
      free(ptem);
           
    }
    else if(proot->PLeft != NULL && proot->PRight != NULL){
      AVLnode* cur = findmax(proot->PLeft);
      proot->data = cur->data;
      proot->PLeft = deleteNode(proot->PLeft,cur->data);
      //下面这种方式多次删除会有error
     /*cur->PRight = proot->PRight;
      AVLnode* ptem = proot;
      proot = proot->PLeft;
      free(ptem); */ 
     }

  }
  /*  return proot;  （在单独判断删除节点是直接这里return的），但是这里直接return会error，导致删除节点的失衡不能调整，
  因为后续的判断失衡是从最小失衡子树开始判断调整的，然后逐层往根结点判断的，这里直接return会回到根节点，导致最小删除失衡调整失败
  return 应该直接放到程序最后来返回     */
   
    

  //删除完成，下面开始调整
  if(proot == NULL)  { return proot; }
    //更新树高
    proot->height = 1+max(getHeight(proot->PLeft),getHeight(proot->PRight));

    //判断是否需要调整，需要平衡因子（|balance|≤1不用调整）来判断
    //结点A的balance定义：A的左子树高度（结点个数）- A的右子树高度,是不考虑这个结点的
    int balance = getBalance(proot);
    //LL型失衡调整：当前节点右旋
      //如何判断是LL型失衡:当前节点balance>1 ,并且当前节点的左子树的balance >0;
    if(balance >1 && getBalance(proot->PLeft) >= 0)
      return rightRotate(proot);   
    
    //LR型失衡调整:先对结点的左子树左旋，结点在右旋
    if(balance >1 && getBalance(proot->PLeft)<0){
       proot->PLeft = leftRotate(proot->PLeft);  //  ???
       return rightRotate(proot);
    }
       
    //RR型失衡调整:结点左旋
    if(balance < -1 && getBalance(proot->PRight) <= 0)
      return leftRotate(proot);
    
    //RL型失衡调整:结点的右子树右旋，结点左旋
    if(balance < -1 && getBalance(proot->PRight) >0){
       proot->PRight = rightRotate(proot->PRight);
       return leftRotate(proot);
    }

   //调整完返回地址
     return proot;
 }

  







//[6]先序遍历和中序遍历可以确定出树的结构
//[6.1]定义先序遍历
 void PreTraverseTree (AVLnode* PT)
{
    if(PT == NULL)
      return;
    else {
        printf("%d ",PT->data);
        PreTraverseTree(PT->PLeft);
        PreTraverseTree(PT->PRight);
    }
  
}

//[6.2]定义中序遍历
void MidTraverseTree (AVLnode* PT)
{
   if(PT == NULL)  
      return;
    else {
        MidTraverseTree(PT->PLeft);
        printf("%d ",PT->data);
        MidTraverseTree(PT->PRight);

    }
  
}

//[7]定义函数查找
AVLnode* search(AVLnode* proot,int val ,int* counter){
    AVLnode* cur = proot;
   // if(cur == NULL) return NULL;
    while( cur != NULL )
    {
     if (val < cur->data) {
        cur = cur->PLeft;
        (*counter)++; }
    else if(val > cur->data){
        cur = cur->PRight;
        (*counter)++; }
    else if (val == cur->data){
        return cur;
        (*counter)++;   //counter出错原因，这行直接跳过了 
        }  
         
    }
    //没找到数据
    return NULL;
}

//[8]定义测试函数
void test(){
    AVLnode* proot = NULL;

    //插入数字
    proot =insertNode(proot,10);
    proot =insertNode(proot,20);
    proot =insertNode(proot,30);
    proot =insertNode(proot,40);
    proot =insertNode(proot,50);
    proot =insertNode(proot,60);
    proot =insertNode(proot,70);

    //查找函数测试
    int counter =0;
    AVLnode* presult = search(proot,40,&counter);
    printf("找了%d次\n",counter);   //查找次数好像有误
    
    printf("先序输出结果为：");
    PreTraverseTree (proot);
    printf("\n");  

    printf("中序输出结果为：");
    MidTraverseTree (proot);
    printf("\n");

    //删除结点测试
    counter=0;
    proot = deleteNode(proot,10);
    proot = deleteNode(proot,20);
    proot = deleteNode(proot,50);

    presult = search(proot,40,&counter);
    printf("先序输出结果为：");
    PreTraverseTree (proot);
    printf("\n");  

    printf("中序输出结果为：");
    MidTraverseTree (proot);
    printf("\n");

}

int main()
{
    test();

    return 0;
}