#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
拓扑排序：主要适用于工程上有先后关系的结点之间的安排是否合理（比如先学c--再学数据结构），
根据拓扑排序：如果最后拓扑排序的结点不是完整的话，图上的直观就是逐步剪到最后剩下的结点之间是有环的，
表示先后关系是有冲突的，反映到课程安排就是不知道先学习什么
学习资料：https://www.bilibili.com/video/BV1W64y1z7jh?p=31&vd_source=017cc0a5f238638bc0ba4f55c269f5e8
*/

typedef char VertexType;

typedef struct Graph {
    VertexType* vexs;      //保存结点标识的信息
    int** matrix;          //邻接矩阵
    int vexNum;
    int arcNum;
}MGraph;

//创建空图
MGraph* creatGraph(int vexNum) {
    MGraph* pgraph = (MGraph*)malloc(sizeof(MGraph));
    pgraph->vexs   = (char*)malloc(sizeof(char)*vexNum);
    pgraph->matrix = (int**)malloc(sizeof(int*)*vexNum);
    for(int i = 0 ; i < vexNum; i++) {      
     //for(int i = 0 ; i < pgraph->vexNum; i++)    error因为此时pgraph->vexNum还没赋值
        pgraph->matrix[i] = (int*)malloc(sizeof(int)* vexNum); 
    }
    pgraph->vexNum = vexNum;
    pgraph->arcNum = 0;       //开始无连接定义为0
    return pgraph;
}

//创建图，加上边信息,需要的参数有图，
void buildGraph(MGraph* pgraph, VertexType* vexs, int* matrix) {
    for (int i = 0 ; i < pgraph -> vexNum; i++) {
        pgraph -> vexs[i] = vexs[i];                     // 赋值结点标识
        for (int j = 0; j < pgraph -> vexNum; j++) {     //对二维矩阵赋值
            //这个用于计算偏移量,因为矩阵在内存也是线性连续存储的，地址加j是往后移动j个单元 
            pgraph -> matrix[i][j] = *(matrix + (i * (pgraph->vexNum)) + j);
             //计算边的数量，如果边有赋值，边的数量+1
            if (pgraph -> matrix[i][j] != 0)      pgraph -> arcNum ++;
        }
    }
    pgraph->arcNum /= 2;   //因为无向图
}


void DFS(MGraph* pgraph, int* visited, int index) {
    printf("%c\t", pgraph -> vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < pgraph ->vexNum; i++) {
        if (pgraph -> matrix[index][i] == 1 && !visited[i]) {
            DFS(pgraph, visited, i);
        }
    }
}


//stack操作
typedef struct Node {
    int data;
    struct Node* next;
}Node;

Node* initStack() {
    Node* stack = (Node*)malloc(sizeof(Node));
    stack -> data = 0;
    stack -> next = NULL;
    return stack;
}

int isEmpty(Node* stack) {
    if (stack -> next == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

void push(Node* stack, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node -> data = data;
    node -> next = stack -> next;
    stack -> next = node;
    stack -> data ++;
}

int pop(Node* stack) {
    if (!isEmpty(stack)) {
        Node* node = stack -> next;
        stack -> next = node -> next;
        return node -> data;
    }
    else {
        return -1;
    }
}

//计算入读，保存在一个数组indregees[]中
int* findInDegrees(MGraph* pgraph){
    //定义一个数组并初始化，用来保存入度个数，入度是竖着统计个数
    int* inDegrees = (int*)malloc(sizeof(int)*pgraph->vexNum);
    for(int i = 0; i < pgraph->vexNum; i++)      {inDegrees[i] = 0;}
    //统计入度个数
    for(int i = 0; i < pgraph->vexNum; i++){
        for(int j = 0; j < pgraph->vexNum; j++){
            if(pgraph->matrix[i][j] != 0)
            inDegrees[j] = inDegrees[j]+1;
        }
    }
    return inDegrees;     //inDegrees是数组头指针
}

//topologicalsort函数
void topologicalSort(MGraph* pgraph){
    int* inDegrees = findInDegrees(pgraph);
    for(int i = 0; i < pgraph->vexNum; i++)   {
         printf("%d ",inDegrees[i]); 
    }
    printf("\n");
    
    //定义一个topo数组用来保存找到的拓扑点
    int index = 0;   //index是topo下标用的
    int* topo = (int*)malloc(sizeof(int)*pgraph->vexNum);   //这个是数组 == int topo[]
    for(int i = 0; i < pgraph->vexNum; i++)      { topo[i] = -1; }
    
    /*  逐步找出入度为0的入栈，（不一定要栈，直接用循环也可以，这里用栈可以避免一些循环）
        如果同时有两个入度为0，那么先入栈的是下标小的，出栈时是先大的下标，     */
    Node* stack = initStack();
    for(int i=0; i < pgraph->vexNum; i++){
        if(inDegrees[i] == 0){
            push(stack,i);  //这里入栈的是对应结点的下标
        }
    }
    //栈不空出栈，并把出栈的数据保存到topo数组
    while(! isEmpty(stack)){
       int vex  = pop(stack);
       topo[index ++] = vex;
       //选出顶点后，把这个顶点指向的边剪掉，重新更新入度信息，更新完重新判断是否需要入栈
       for(int i=0; i<pgraph->vexNum; i++){
           if( pgraph->matrix[vex][i] != 0){
                inDegrees[i] = inDegrees[i] -1;
                //更新完重新判断是否压栈
                if(inDegrees[i] == 0){
                    push(stack,i);
                }
           }
       }
    }
    /*输出topo排序  到这里拓扑排序选出的结点信息是保存在topo[]数组里了，
    如果结点不满，表示原图是有环的，安排有误，这里没写判断函数 */
    for(int i = 0; i < index; i++) { 
        printf("%c  ",pgraph->vexs[topo[i]]);
     }
    printf("\n");
}

int main() {
    MGraph* pgraph = creatGraph(6);     //需要给出结点个数
    int* visited = (int*)malloc(sizeof(int) * pgraph -> vexNum);    //创建节点数组
    for (int i = 0; i < pgraph -> vexNum; i++)    visited[i] = 0;   //结点数组初始化为0
       
    int matrix[6][6] = {     //手动输入边的信息
            0,1,1,1,0,0,
            0,0,0,0,0,0,
            0,1,0,0,1,0,
            0,0,0,0,1,0,
            0,0,0,0,0,0,
            0,0,0,1,1,0
    };
    buildGraph(pgraph, "abcdef", (int*)matrix);   //疑问：这里为什么要强制转换成(int*)才可以，直接取地址不行

    printf("DFS:\t");
    DFS(pgraph, visited, 0);
    printf("\n");

    topologicalSort(pgraph);


    return 0;
}