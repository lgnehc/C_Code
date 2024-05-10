#include <stdio.h>

/*
*学习资料：B站up:正月点灯笼
*堆的特点：1）必须是完全二叉树；2）大顶堆：parent值 > child值 （同理有小顶堆）

*这个堆排序用的是大顶堆：完全二叉树的存储方式用数组，结点i的父节点为（i-1）/2;左孩子为2i+1;右孩子为2i+2;
*步骤：heapity把完全二叉树变成堆，然后进行堆排序
**如何把一颗乱序的二叉树变成堆：从导数第二层（h-1层）的第一个结点开始对整层做heapity,然后依次向上层的每个节点做heapity
*/

//打印函数
void printArray(int arr[],int length){
    for (int i=0; i<length; i++)  { printf("%d ",arr[i]); }
    printf("\n");
}

//交换i,j
void swap(int arr[],int i,int j){
    int tem = arr[i];
    arr[i] = arr[j];
    arr[j] = tem;
}


//单个节点的heapity过程：把完全二叉树转化为堆
//参数说明：tree是数组存储的完全二叉树,nodeNum是结点总个数，i表示对tree[i]这个结点做heapity
//tree[i]这个结点做heapity过程：找出左孩子和右孩子的max，然后判断max和tree[i]大小，如果max>tree[i],做交换，然后对max结点做heapity

//note:这个heapify对于结点i本生是max的{10 3 6 5 1 2}无法创建大根堆，所以后面build_heap是从最后一个非叶子结点往上递归创建的
void heapify(int tree[],int nodeNum,int i){
    //递归出口
    if(i >= nodeNum){   
        return;
    }
     int lchild = 2*i +1;
     int rchild = 2*i +2;
     //找出max值
     int max = i;
     //lchild < nodeNum是判断边界条件的，如果这个结点没有孩子，不用heapify
     if(lchild < nodeNum && tree[lchild] > tree[max]){
        max = lchild;   
     }
     if(rchild < nodeNum && tree[rchild] > tree[max]){
        max = rchild;
     }
    //判断是否交换
    if(max != i){
        swap(tree,max,i);
        heapify(tree,nodeNum,max);   //递归调用之后节点数应该改变  (max-nodeNum)待调试
    }
}


//创建堆：对所有所有非叶子节点做heap，从最后一个非叶子节点逆序开始做heapity
void build_heap(int tree[],int nodeNum){
    int last_node = nodeNum - 1;
    int parent = (last_node-1)/2;   //找到最后一个非叶子结点
    for(int i = parent; i >= 0; i--){
        heapify(tree,nodeNum,i);
    }
}

//堆排序
void heapSort(int tree[],int nodeNum){
    build_heap(tree,nodeNum);
    for(int i = nodeNum-1; i>=0; i--){
        swap(tree,i,0);
        heapify(tree,i,0);
    }
}

int main(){
    int tree[] = {4,1,10,16,3,8};
    int length =6;
    heapify(tree,length,0);
    printArray(tree,length);

    heapSort(tree,length);
    printArray(tree,length);
    return 0;
}