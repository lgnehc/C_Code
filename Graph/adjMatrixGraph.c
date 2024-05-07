#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "malloc.h"


//https://blog.csdn.net/m0_45311187/article/details/106613867+陈越note

#define  INF 65532
#define  maxVertex 5
typedef  char VertexType;  //顶点类型
typedef  int  WeightType;  //权重类型  

typedef struct matrixGraph{
    int vexNum;    //计数使用
    int edgeNum;   //计数使用
    int matrix[maxVertex][maxVertex];  //假设开始最多5个结点
    VertexType data[maxVertex];      //下标和数据ABC/123对应起来，矩阵实际用的时候是下标 
}MGraph;


//定义一个边结点，一条边是有2个顶点和权重决定,后面插入边的时候用
typedef struct EdgeNode{
    VertexType V1,V2;
    WeightType Weight;
}EdgeNode;


//初始化,知道节点数，但是边的关系未确定,对于无向图不连接赋值无穷大，对于有向图赋值0
MGraph* creatGraph(int vertexNum){
   VertexType v,w;    
   MGraph* Pgraph = (MGraph*)malloc(sizeof(MGraph));
   Pgraph->edgeNum = 0; 
   Pgraph->vexNum = vertexNum;
   for( v=0; v<maxVertex ;v++){
    for( w=0 ;w<maxVertex; w++){
        Pgraph->matrix[v][w] = 0 ;   //有向图使用
        //Pgraph->matrix[v][w] = INF ;   //无向图使用
    }
   }
   return Pgraph;
}

//插入节点,插入的数据是val,  Elemtype data[maxVertex];
void addVertex(MGraph* Pgraph, VertexType val){
    //节点满了不能插入
  if (Pgraph->vexNum >= maxVertex)    return;  
   //结点未满可以插入节点
   Pgraph->data[Pgraph->edgeNum] = val;
   Pgraph->edgeNum ++;

}

//插入边，修改矩阵
void addEdge(MGraph* pgraph,EdgeNode* E, int vexNum){
    //需要先找到输入的输入的边结点的源节点和目标节点的对应的二维matrix下标
    int a,b; 
    for(int i =0 ;i< vexNum;i++){
            if(pgraph->data[i] == E->V1)  a = i;
            if(pgraph->data[i] == E->V2)  b = i; 
    }
   // printf("%c,%c对应的下标分别是:%d,%d\n",E->V1,E->V2,a,b);
    //找出对应的下标后，开始插入边
   pgraph->matrix[a][b] = E->Weight;
   pgraph->matrix[b][a] = E->Weight;   //无向图还得赋值
  // pgraph->matrix[E->V2][E->V1] = E->Weight;  //无向图
  // pgraph->edgeNum ++;
   }


//动态输入创建图,
MGraph* buildMgraph()
 {
    MGraph* pgraph = NULL;
    int i;
    //输入创建的节点数
    int vexNUM;
    printf("intput the number of vertex:");
    scanf("%d", &vexNUM);
    //创建有顶点无边的图,并初始化
    pgraph = creatGraph(vexNUM); 
    
    for(i=0; i<vexNUM ;i++){
        printf("输入第%d节点标识:",i+1);
        fflush(stdin);
        scanf("%c",&(pgraph->data[i]));
    }

    //创建边
    printf("input the number of edge:");
    scanf("%d",&(pgraph->edgeNum));
    //如果需要创建的边个数不为0
    if(pgraph->edgeNum !=0){
        EdgeNode* E = (EdgeNode*) malloc(sizeof(EdgeNode));
        for(i=0; i< pgraph->edgeNum ;i++){
            printf("请输入需要插入的边的信息（源节点,指向的结点和权值，空格隔开）：");
            fflush(stdin);
            scanf("%c %c %d",&(E->V1),&(E->V2),&(E->Weight));  //赋值失败
            addEdge(pgraph,E,vexNUM);
        }
    }
   return pgraph; 
}

//邻接矩阵的打印
void printGraph(MGraph* pgraph){

   for(int i=0; i<maxVertex; i++){
    for(int j=0 ;j<maxVertex; j++){
    
    /*   if(j == -1){
            for(int k=0;k<maxVertex;k++){
                printf("%c\t",pgraph->data[k]);
            }
            printf("\n");
        }  */ 
      printf("%d\t",pgraph->matrix[i][j]);
    }
    printf("\n"); 
   }
}


bool Visited[maxVertex] = {0};

//邻接矩阵的深度遍历
void DFS(MGraph* pgraph,int v)
{  
  printf("%c->",pgraph->data[v]);
  Visited[v] = 1;    

   for(int w=0; w<pgraph->vexNum; w++){
    if(pgraph->matrix[v][w] == 1   &&  Visited[w] == 0){
        DFS(pgraph,w);
    }
   }
}

/*    这个二维数组的初始化还有待调整
如何求任意两个顶点之间的最短路径，可以包括dijstra
实现方式：1）直接对每个顶点使用dijstre算法，2）使用Floyd算法
学习参考：https://www.bilibili.com/video/BV1W64y1z7jh?p=30&spm_id_from=pageDriver&vd_source=017cc0a5f238638bc0ba4f55c269f5e8 
算法实现核心：使用2个二维数组，shortest，front_point,进行初始化；
             3for循环实现，循环1用于每次加入一个新的结点试探；循环2.3用于更新2个2维数组

void flodyd(MGraph* pgraph){
    //1)定义2个2维辅助数组，然后进行初始化
    int shortest[pgraph->vexNum][pgraph->vexNum];
    int front_point[pgraph->vexNum][pgraph->vexNum];
    
    for(int i=0; i<pgraph->vexNum; i++){
        for(int j=0; j<pgraph->vexNum; j++){
            shortest[i][j]  = pgraph->matrix[i][j];
            if (pgraph->matrix[i][j] >0  && pgraph->matrix[i][j] != INF)  {front_point[i][j] = i; }    
            else    front_point[i][j] = -1;
        }
    }
    
    //初始化之后打印测试
    for(int i = 0; i < pgraph->vexNum; i++){
        for(int j = 0; j < pgraph->vexNum; j++){ 
            printf("%d\t",shortest[i][j]);   
            }
            printf("\n");
        }
    printf("\n");
    for(int i = 0; i < pgraph->vexNum; i++){
        for(int j = 0; j < pgraph->vexNum; j++){ 
            printf("%d\t",front_point[i][j]);   
            }
            printf("\n");
        }
    printf("\n");   
    

    //核心3for循环,i循环是指依次加入一个中转节点试探；j二维数组的src,k是二维数组的dest
    for(int i = 0; i < pgraph->vexNum; i++){
        for(int j = 0; j < pgraph->vexNum; j++){    
            for(int k = 0; k < pgraph->vexNum; k++){
                 if(shortest[j][i] + shortest[i][k] < shortest[j][k]){
                      shortest[j][k] = shortest[j][i] + shortest[i][k];
                      front_point[j][k] = front_point[i][k];
                 }  
            }
        }
    }
    
    //打印测试
    for(int i = 0; i < pgraph->vexNum; i++){
        for(int j = 0; j < pgraph->vexNum; j++){ 
            printf("%d\t",shortest[i][j]);   
            }
            printf("\n");
        }
    printf("\n");
    for(int i = 0; i < pgraph->vexNum; i++){
        for(int j = 0; j < pgraph->vexNum; j++){ 
            printf("%d\t",front_point[i][j]);   
            }
            printf("\n");
        }
    printf("\n");

}     */

int main(){
    MGraph* pgraph =  buildMgraph();
    printGraph(pgraph);
    
    printf("DFS:");
    DFS(pgraph,0);
    printf("\n");

    //flodyd(pgraph);
    
    return 0;
}