#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
关键路径主要步骤：拓扑排序--求事件指标（最早/晚）--求活动指标（最早/晚）--求时间余量--时间余量=0即为关键路径
学习资料：https://www.bilibili.com/video/BV1W64y1z7jh?p=33&spm_id_from=pageDriver&vd_source=017cc0a5f238638bc0ba4f55c269f5e8
关键路径针对的是有向图：有向图对角结点赋值为0，联通即为weight，不联通即为INF
*/

#define  INF 65532
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
            if (pgraph -> matrix[i][j] > 0  &&  pgraph -> matrix[i][j] != INF)  
                 pgraph -> arcNum ++;
        }
    }
    
}


void DFS(MGraph* pgraph, int* visited, int index) {
    printf("%c \t", pgraph -> vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < pgraph ->vexNum; i++) {
        if ((pgraph -> matrix[index][i] >0 ) && (pgraph -> matrix[index][i] != INF) && (!visited[i])) {
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
            if((pgraph->matrix[i][j] > 0)  && (pgraph->matrix[i][j] != INF))
            inDegrees[j] = inDegrees[j]+1;
        }
    }
    return inDegrees;     //inDegrees是数组头指针
}

//topologicalsort函数  ,返回topo数组的指针
int*  topologicalSort(MGraph* pgraph){
    int* inDegrees = findInDegrees(pgraph);
    //打印入度信息
    printf("indegrees:\n");
    for(int i = 0; i < pgraph->vexNum; i++)   {
         printf("%d \t",inDegrees[i]); 
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
           if(( pgraph->matrix[vex][i] > 0)  &&  ( pgraph->matrix[vex][i] != INF) ){
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
    printf("topologicalSort:\n");
    for(int i = 0; i < index; i++) { 
        printf("%c \t",pgraph->vexs[topo[i]]);
     }
    printf("\n");

    return topo;
}


//
int getIndex(int* topo,MGraph* pgraph,int i){
    int j;
    for(j=0; j<pgraph->vexNum ; j++){
        if(topo[j] == i){
            break;
        }
    }
    return j;
}

//关键路径函数:拓扑排序--求事件指标（最早/晚）--求活动指标（最早/晚）--求时间余量--时间余量=0即为关键路径
void criticalPath(MGraph* pgrapg){
    //1)进行拓扑排序,topo是数组指针
    int* topo = topologicalSort(pgrapg);
    //2)求事件指标，先定义2个数组，初始化，计算赋值
    int* vex_early = (int*)malloc(sizeof(int)*pgrapg->vexNum);
    int* vex_late = (int*)malloc(sizeof(int)*pgrapg->vexNum);
    for(int i=0; i<pgrapg->vexNum; i++){
        vex_early[i] = 0;
        vex_late[i]  = 0;
    } 
    /*2.1)计算事件最早发生时间：需要遍历所有节点：遍历顺序想要的是依据topo里面的结点顺序（A D F C B E H G I）来找的，
    先找A的early,在找D的early，不是按照ABC...顺序找      */
    for(int i=0; i<pgrapg->vexNum; i++){
           //i循环是所有节点都要求解early， 要按照topo字母来找early，需要把i和topo下标联系起来--topo[i],,topo[1]=下标3=D 
        int max = 0 ;  //就是如果没有前驱结点的最早开始时间定义为0
        for(int j=0; j<pgrapg->vexNum; j++){   
              /*j循环是找的topo[i]的入度，找的前驱节点，这个前驱还需要对应到topo[j]中去 
                找D的earl，需要先找出D是否有前驱，有多个前驱在找出max{前驱earl + weigh}*/
              if((pgrapg->matrix[j][topo[i]] > 0)  && (pgrapg->matrix[j][topo[i]] != INF) ){
                 int index = getIndex(topo,pgrapg,j); 
                 if(vex_early[index] + (pgrapg->matrix[j][topo[i]])  > max  ){
                    max = vex_early[index] + (pgrapg->matrix[j][topo[i]]);
                 }
              }
        }
        vex_early[i] = max ;
    }
    //测试early是否正确
    printf("vex_early:\n");
    for(int i = 0; i < pgrapg->vexNum; i++)      { printf("%d \t",vex_early[i]); }
    printf("\n");

    //计算事件最晚发生时间,从最后一个开始计算
    vex_late[pgrapg->vexNum -1] = vex_early[pgrapg->vexNum -1];  //最后一个结点的最早最迟时间一样的
    for(int i = ((pgrapg->vexNum)-2) ; i>=0 ;i-- ){
        int min = INF;
        for(int j=0 ;j<pgrapg->vexNum; j++){
            if(pgrapg->matrix[topo[i]][j] >0  &&   pgrapg->matrix[topo[i]][j] != INF ){
                int index = getIndex(topo,pgrapg,j);
                if(vex_late[index] - pgrapg->matrix[topo[i]][j]  < min ){
                     min = vex_late[index] - pgrapg->matrix[topo[i]][j];
                }
            }
        }
    vex_late[i] = min; 
    }
    //测试vex_late是否正确
    printf("vex_late:\n");
    for(int i = 0; i < pgrapg->vexNum; i++)      { printf("%d \t",vex_late[i]); }
    printf("\n");
  
   //
   for(int i=0; i<pgrapg->vexNum ;i++){
      for(int j =0; j<pgrapg->vexNum; j++){
        if(pgrapg->matrix[i][j] >0  && pgrapg->matrix[i][j] != INF){
            int start = getIndex(topo,pgrapg,i);
            int end = getIndex(topo,pgrapg,j);
            if( (vex_late[end] - pgrapg->matrix[i][j]) - vex_early[start]  == 0 ){
                printf("start = %d ,end = %d\n",i,j);
            }
        }
      }
   }
}





int main() {
    MGraph* pgraph = creatGraph(9);     //需要给出结点个数
    int* visited = (int*)malloc(sizeof(int) * pgraph -> vexNum);    //创建节点数组
    for (int i = 0; i < pgraph -> vexNum; i++)    visited[i] = 0;   //结点数组初始化为0
       
    int matrix[9][9] = {     //手动输入边的信息
            0,6,4,5,INF,INF,INF,INF,INF,
            INF,0,INF,INF,1,INF,INF,INF,INF,
            INF,INF,0,INF,1,INF,INF,INF,INF,
            INF,INF,INF,0,INF,2,INF,INF,INF,
            INF,INF,INF,INF,0,INF,9,7,INF,
            INF,INF,INF,INF,INF,0,INF,4,INF,
            INF,INF,INF,INF,INF,INF,0,INF,2,
            INF,INF,INF,INF,INF,INF,INF,0,4,
            INF,INF,INF,INF,INF,INF,INF,INF,0
    };
    buildGraph(pgraph, "ABCDEFGHI", (int*)matrix);   //疑问：这里为什么要强制转换成(int*)才可以，直接取地址不行

    printf("DFS:\n");
    DFS(pgraph, visited, 0);
    printf("\n");

    //topologicalSort(pgraph);
    criticalPath(pgraph);


    return 0;
}