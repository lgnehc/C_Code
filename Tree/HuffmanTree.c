#include <stdio.h>
#include <stdlib.h>
/* 学习视频：理论 b站王卓老师 + 代码 b站up:Tyrantlucifer
哈夫曼树：实现的是路径程度的权值之和最小（引入例子见王卓老师）
构造哈夫曼树的步骤：从权值列表中选出最小和次小的结点，组成一棵树，父节点的权值为2个节点权值相加，
父节点的权值放回权值列表中，再选出最小和次小的结点，循环直到最后列表只剩一个节点
*/

//这里使用数组实现的哈夫曼树

//定义树的结点的结构体
typedef struct TreeNode{
    int weight;
    int parent;
    int Rchild;    //构造是小的为左孩子，大的为右孩子
    int Lchild;
}TreeNode;

//定义树的结构体
typedef struct HFTree{  
   TreeNode* data;
   int lenght;        //表示总结点个数
}HFTree;

//初始化树
HFTree* initTree(int* weight,int lenght){
    HFTree* T = (HFTree*)malloc(sizeof(HFTree));
    T->data = (TreeNode*)malloc(sizeof(TreeNode)*(2*lenght - 1));   //观察的规律：需要的结点是2n-1
    T->lenght = lenght;
    //这里总共2n-1个结点，把前面n个结点的weight依次赋值为权值，后面的结点赋值在createTree函数
    for(int i = 0; i < lenght; i++){     
        T->data[i].weight = weight[i];
        T->data[i].parent = -1;     //-1表示没有父节点，没有左右孩子
        T->data[i].Rchild = -1; 
        T->data[i].Lchild = -1;
    }   
    return T;
}

//找出权重最小和次小的权值和index并返回
int* selectMin(HFTree* T){
     int min = 65532;
     int minIndex;
     int secondMin = 65532;
     int secondMinIndex; 

     //找出最小权值及其Index
     for(int i = 0; i < T->lenght; i++){
        if(T->data[i].parent == -1 ){      //T->data[i].parent == 0，已经被选过的parent不会是0，是排除已经选过的，第一次选可能考虑不到
            if(T->data[i].weight < min){
                min = T->data[i].weight;
                minIndex = i;
            }
        } 
     }
     //找出次小权值及其Index    
     for(int i = 0; i < T->lenght; i++){
        if(T->data[i].parent == -1 && (i != minIndex)){    //(i != minIndex)是排除最小的
            if(T->data[i].weight < secondMin){
                secondMin  = T->data[i].weight;
                secondMinIndex = i;
            }
        } 
     }
     //找到后把index带出去
     int* res = (int*)malloc(sizeof(int)*2);
     res[0] = minIndex;
     res[1] = secondMinIndex;
     return res;
}

//构建哈夫曼树
//Note:这个创建的哈夫曼树，如果有相等的权值A，那么孩子是在右边的权值下，左边的权值没有孩子
void creatTree(HFTree* T){
     int* res;
     int minIndex;
     int secondminIndex;
     int len = (T->lenght)*2 - 1;   
     //对lenght-->lenght*2 - 1的结点进行处理,前面的结点在initTree函数处理过的
     for(int i = T->lenght; i < len; i++){
        res = selectMin(T);
        minIndex = res[0];
        secondminIndex = res[1];
        //找到最小两个权值后构造成一棵树
        T->data[i].weight =  T->data[minIndex].weight + T->data[secondminIndex].weight;
        T->data[i].Lchild = minIndex;                //构造是小的为左孩子，大的为右孩子
        T->data[i].Rchild = secondminIndex; 
        T->data[i].parent = -1;                       //加入到下一轮找最小次小selectMin函数中，
        //构造成一棵树后，修改最小权值的2个结点的父节点
        T->data[minIndex].parent = i;
        T->data[secondminIndex].parent = i; 
        T->lenght ++;
     }
     
}


//“先序”遍历哈夫曼树
void preOrder(HFTree* T,int index){
    if(index != -1){
        printf("%d ",T->data[index].weight);
        preOrder(T,T->data[index].Lchild);
        preOrder(T,T->data[index].Rchild);
    }
}


//“中序”遍历哈夫曼树
void midOrder(HFTree* T,int index){
    if(index != -1){
        midOrder(T,T->data[index].Lchild);
        printf("%d ",T->data[index].weight);
        midOrder(T,T->data[index].Rchild);
    }
}


int main(){
    int weight[7] = {5,1,3,6,11,2,4};;
    HFTree* T = initTree(weight,7);
    /* selectMin测试
    int* res = selectMin(T);
    printf("min = %d  secondmin = %d\n",res[0],res[1]);
    */
    creatTree(T);
    preOrder(T,T->lenght-1);  //T->lenght-1 构造完后，length指向最后一个节点，就是哈夫曼树的第一个结点
    printf("\n");
    midOrder(T,T->lenght-1);   
    printf("\n");

    return 0;
}