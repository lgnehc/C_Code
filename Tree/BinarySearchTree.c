#include <stdio.h>
#include <malloc.h>

/*二叉搜索树的特点：中序遍历就是从小到大排序好的*/

typedef  int Elemtype;

typedef struct  bstTree
{
    Elemtype data;
    struct  bstTree* PLeft;
    struct  bstTree* PRight;
}bstTree ;


/*【1】创建二叉搜索树,插入元素也可以使用
如何创建：是空树，直接创建一个节点；不是空树时，需要判断在哪个位置插入节点
这里创建二叉搜索树时需要注意输入节点的顺序,一般是按照结点-左-右或者右左创建，  
123456和235641 虽然中序输出一样，但是数的结构是不同的*/
void  Insert_bstTree(bstTree** PPbst,int val)     
{ 
    //判断是空树时，创建一个节点，然后把指向空树的指针指向这个结点，
    if(*PPbst == NULL){
        bstTree* pnode = (bstTree*)malloc(sizeof(bstTree));
        pnode->data = val;
        pnode->PLeft = NULL;
        pnode->PRight =NULL;
        *PPbst = pnode;
    }else{
   //如果不是空树情况
   //如果插入的数据比结点大，那么插入到右子树上
     if (val >   (*PPbst)->data){
        Insert_bstTree(&((*PPbst)->PRight),val);
     }else{
         //如果插入的数据小于等于结点数，那么插入到左子树上
        Insert_bstTree(&((*PPbst)->PLeft),val);
     }
    }    
}


//【2】中序遍历二叉树
void MidTraverseTree (bstTree* PT)
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

//【3】二叉搜索树查找：给出一个数，查看这个数在二叉搜索树中的位置，返回这个结点的地址
//[3.1]递归实现
bstTree* search1(bstTree* PT, int val){   //val是要找到的值
    //1）判断是空树情况
    if(PT == NULL){
        return NULL;
    }
    //1.2）判断不是空树情况
    //1.2.1）如果大于节点数，找右子树
    if(val > PT->data){
       return search1(PT->PRight,val);
    }else if((val < PT->data)){
    //1.2.2)如果小于节点数，找左子树
        return search1(PT->PRight,val);
    }else if(val == PT->data){
    //1.2.3）如果相等情形，直接返回此节点指针
        return PT;
    }
    //1.2.4）如果什么都没有找到
    return NULL;

}


//【3.2】迭代循环实现二叉树搜索
bstTree* search2(bstTree* PT, int val){
    bstTree* ptem = PT;
    while ( ptem != NULL )
    {
        if(val > ptem->data)       {ptem = ptem->PRight;}
        else if(val < ptem->data)  {ptem = ptem->PLeft;}
        else if(val == ptem->data) {return ptem;}    
    }  
    return NULL; //如果什么都没有找到,return ptem也可以，因为找到最后没有的话，return ptem就是指向NULL
}

//[4]找左子树最大/右子树最小数--循环/递归实现
bstTree* findmin(bstTree* PT){
    if (PT == NULL) { 
      printf("树空\n");
      return NULL;
    }
    while (PT->PLeft != NULL) 
     {  PT = PT->PLeft; }
    return PT;   
}

bstTree* findmax(bstTree* PT){
    if (PT == NULL) { 
     printf("树空\n");
     return NULL;
    }
    while (PT->PRight != NULL)
     {  PT = PT->PRight; }
    return PT;   
}


//【5】删除二叉搜索树中的元素
//这个程序执行完删除节点后，返回的都是数的头结点
//这个程序只能删除找到第一个数据，如果有重复的后面的没删除
bstTree* deleteNode(bstTree* PT,int val){
  //【5.1】如果是空树，直接返回NULL,同时也是递归出口
  if( PT == NULL)  {return PT;}

   //【5.2】如果不是空树，需要先查找删除的结点在哪
   //[5.2.1]如果要删除的结点小于当前节点的值，那么递归删除左子树上的结点

    //这里因为递归删除后结构是改变的，所以需要让节点指向新的结构
  else if(val < PT->data)   { PT->PLeft = deleteNode(PT->PLeft,val); } 
    //[5.2.2]如果要删除的结点大于当前节点的值，那么递归删除右子树上的结点
  else if(val > PT->data)  {PT->PRight = deleteNode(PT->PRight,val);  } 
   //这里PT是递归一层一层往后传进来的，此时执行的是不断递归的程序的最后那层，此时的这个PT是指向眼删除的结点了，
   
  else if(val == PT->data)  
  {
        //【5.2.3】找到了删除节点，如何删除--这时候要删除的结点有四种情况
        //note：经过上面的查找结点程序，此时PT已经是指向要删除的结点的了，
        //【5.3.1】情形1：要删除的结点左右子树都没有结点
        if(PT->PLeft == NULL && PT->PRight == NULL){
            free(PT);     //free只是和这个程序不在链接
            PT  = NULL;  //把原本指向这个的指针悬空还是为了后面返回PT要NULL才用的？？？
          //return PT;  //都是返回一样的，可以后面统一返回    //返回的值是赋值给到指向删除节点的父节点用的： PT->PLeft/ringht = deleteNode(PT->PLeft/right,val);
        }
        else if(PT->PLeft != NULL && PT->PRight == NULL){
        //[5.3.2]q情形2：要删除的结点有左子树，没有右子树
        //让左子树代替要删除的结点
        bstTree* ptem = PT;   //定义一个指向要删除的结点
        PT=PT->PLeft;
        free(ptem);      
        /*这里free逻辑和情形1好像不同，情形1好像多了一个释放后赋值为NULL的过程？？这是必须赋值为NULL吗？还是情形1只是为了返回值用的
        如果时为了给返回值用，不是一定要给删除的结点赋值null的话，是不是可以直接free（PT）然后return null，这样可以不用ptem指针了，*/
         //return PT;  //都是返回一样的，可以后面统一返回  //返回的值是赋值给到指向删除节点的父节点用的： PT->PLeft/ringht = deleteNode(PT->PLeft/right,val);
        }

        else if(PT->PLeft == NULL && PT->PRight != NULL){
        ////[5.3.2]情形3：要删除的结点有右子树，没有左子树
        //让右子树代替要删除的结点
        bstTree* ptem = PT;   //定义一个临时指针指向要要删除的结点，释放空间用
            PT = PT->PRight;     //只有一个孩子情况，直接指向要删除节点的有孩子即可
            free(ptem);     
        //return PT; //都是返回一样的，可以后面统一返回     //返回的值是赋值给到指向删除节点的父节点用的： PT->PLeft/ringht = deleteNode(PT->PLeft/right,val);
        } 

        else if (PT->PLeft != NULL && PT->PRight != NULL){
        //[5.3.3]情形4：要删除的结点左右子树都有
        /* 方法1:将删除节点的右子树挂到左子树的最大值上（这里需要先找到左子树的最大值），然后左子树代替要删除的结点，见视频图解；
            方法2：将删除节点的左子树挂到右子树的最小值上（这里需要先找到右子树的最小值），然后右子树代替要删除的结点，见视频图解*/
        //采用方法1代码实现，先找左子树的最大值

        bstTree* cur = findmax(PT->PLeft);     //cur就指向了剩下的左子树的最大的结点
        //法1
          PT->data = cur->data;
          PT->PLeft = deleteNode (PT->PLeft, cur->data);
        //法2 
        /*//把删除节点的右子树都挂到左子树最大结点上
           cur->PRight = PT->PRight;
           //释放节点
            bstTree* ptem = PT;
            PT = PT->PLeft;
            free(ptem);*/
        //return PT;  //返回PT的，可以后面统一返回   
      }
    //return PT; //这个原本是4种情形的统一返回，又统一到后面去了

  }
  //还有一种情形，没有找到要删除的结点,直接return PT; 
  return PT; 
  //这个返回是多个共用的, val < PT->data ;val > PT->data; val = PT->data里面的4种情形；没有找到要删除的结点共7个共用
}




int main(){

   //创建一个空树
   bstTree* PT = NULL;
   
   //输入数据创建二叉搜索树：假设10个
   for(int i=0; i<10 ;i++) 
   {
    int val;
    printf("请输入第%d/10个int数据:",i+1);
    scanf("%d",&val);
    Insert_bstTree(&PT, val);
   }

   //中序输出二叉搜索树
    printf("中序输出结果为：");
    MidTraverseTree (PT);
    printf("\n");

    
    //二叉树搜索
    //递归search1
    bstTree* pnode1 = search1(PT,9);
    if(pnode1 == NULL){
        printf("没有找到这个结点\n");
    }else{
        printf("找到了! %d\n",pnode1->data);
    }
    //循环search2
    bstTree* pnode2 = search2(PT,9);
    if(pnode2 == NULL){
        printf("没有找到这个结点\n");
    }else{
        printf("找到了! %d\n",pnode2->data);
    }

    //找最大/小值判断
    printf("min is %d\n",findmin(PT)->data);
    printf("max is %d\n",findmax(PT)->data);


    //error：如果9是最大的，有2个9的情况下，在删除第2个9时中序遍历会报错，3个9删除2个也不会报错，如果9不是最大也没有问题

    //删除节点测试，pt1是删除后的树的头结点   
    bstTree* PT1 = deleteNode(PT,9);
    printf("删除后中序输出结果为：");
    MidTraverseTree (PT1);
    printf("\n");
    // 如果有重复数据，需要二次调用删除，---是否可以循环/递归改进直接删除全部
    bstTree* PT2 = deleteNode(PT1,9);
    printf("删除后中序输出结果为：");
    MidTraverseTree (PT2);
    printf("\n");   

    return 0;
}