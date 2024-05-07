#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "malloc.h"

//https://blog.csdn.net/m0_45311187/article/details/106613867+陈越note

#define  maxVertex 10
#define  INF 65532
typedef  char VertexType;  //顶点类型
typedef  int  WeightType;  //权重类型 

//定义邻结点的结构
typedef struct AdjListNode{
 int ver_index;                //邻结点类型对应的下标
 WeightType weight;            //权重
 struct AdjListNode* pnext;    //指向下一个节点的指针
}Node;

//定义头指针的结点结构   
typedef struct headnode{
    //int count;                        //记录头结点的个数  
    VertexType alp;                  //记录这个顶点对应的字母，可以不用
    struct AdjListNode* pfirstEdge;  //指向头结点的地址
} headnode;

//定义邻接表的结构
typedef struct LGraph{
    int vexNum;    //计数使用
    int edgeNum;   //计数使用   如果输入是只输入一边的，对于无向图需要*2，
    headnode G[maxVertex];  //定义头结点数组指针   //headnode* G[maxVertex];  error
}LGraph;

//定义边结点
typedef struct EdgeNode{
    VertexType src,dest;
    WeightType Weight;
}EdgeNode;


//初始化LGraph，确定节点数，边数为0
LGraph* creatGraph(int vertexNum){  
   LGraph* PLgraph = (LGraph*)malloc(sizeof(LGraph));

   PLgraph->edgeNum = 0; 
   PLgraph->vexNum = vertexNum;
  
   for(int  v=0; v<maxVertex ;v++){
     PLgraph->G[v].pfirstEdge = NULL;  //error  ,G[V]没有初始化
    }
   return PLgraph;
}

//找出输入的字符对应的pgraph->G[i]的i下标,alp是传进来需要判断的字符
int find_index(LGraph* pgraph, VertexType alp1){
   for(int i =0 ;i< maxVertex;i++){
        if(pgraph->G[i].alp == alp1) {
         //   printf("%c对应的下标是%d\n",alp1,i);
            return  i;
        }   
    } 
    return -1;
}

//插入边,头插法
void addEdge(LGraph* pgraph,EdgeNode* E, int vexNum){
    //需要先找到输入的边结点的源节点和目标节点的对应的G[i]下标
            /* int a,b; 
                for(int i =0 ;i< vexNum;i++){
                   if(pgraph->G[i].alp == E->src)  a = i;
                 if(pgraph->G[i].alp == E->dest)  b = i; 
                 }
                printf("%c,%c对应的下标分别是:%d,%d\n",E->src,E->dest,a,b);  */
   int i = find_index(pgraph,E->src);   
   int j = find_index(pgraph,E->dest);
    
    //头插法插入边
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->pnext = pgraph->G[i].pfirstEdge ;
    newnode->ver_index = j;
    newnode->weight = E->Weight;
    pgraph->G[i].pfirstEdge = newnode;
    //如果无向图还需在添加一个
    Node* newnode2 = (Node*)malloc(sizeof(Node));
    newnode2->pnext = pgraph->G[j].pfirstEdge ;
    newnode2->ver_index = i;
    newnode2->weight = E->Weight;
    pgraph->G[j].pfirstEdge = newnode2;

   }

//创建邻接表
LGraph* buildMgraph()
 {
    LGraph*  pgraph = NULL;
    int i;
    //输入创建的节点数
    int verNUM;
    printf("intput the number of vertex:");
    scanf("%d", &verNUM);
    //创建有顶点无边的图,并初始化
    pgraph = creatGraph(verNUM); 
    //确定结点对应的标识
    for(i=0; i<verNUM ;i++){
        printf("输入第%d节点标识:",i+1);
        fflush(stdin);
        scanf("%c",&(pgraph->G[i].alp));
    }

    //创建边
    printf("input the number of edge:");
    scanf("%d",&(pgraph->edgeNum));
    //如果需要创建的边个数不为0，开始创建边
    if(pgraph->edgeNum !=0){
        EdgeNode* E = (EdgeNode*) malloc(sizeof(EdgeNode));
        for(i=0; i< pgraph->edgeNum ;i++){
            printf("请输入需要插入的边的信息(src,dest和weight,空格隔开):");
            fflush(stdin);
            scanf("%c %c %d",&(E->src),&(E->dest),&(E->Weight));  
            addEdge(pgraph,E,verNUM);
        }
    }
   return pgraph; 
}

//打印邻接表
void printGraph(LGraph* pgraph){
   for(int i=0; i<maxVertex; i++){
     Node* ptem = pgraph->G[i].pfirstEdge;
     while(ptem != 0){
     printf("%c--%d--%c\t",pgraph->G[i].alp, ptem->weight, pgraph->G[ptem->ver_index].alp);
     ptem = ptem->pnext;
     }
    printf("\n"); 
   }
}

bool visited[maxVertex]={0};
//清除标记的数组
void  clear_visited(bool visited[maxVertex]){
    for(int i=0; i<maxVertex; i++){
        visited[i] = 0;
    }
} 

//深度遍历,a是开始遍历的结点
void DFS(LGraph* pgraph,int index)
{  
    printf("%c->",pgraph->G[index].alp);
    visited[index] = 1;

    Node* ptem = pgraph->G[index].pfirstEdge; 
    while( ptem != NULL){
        if ( visited[ptem->ver_index] == 0)    
        {
            DFS(pgraph,ptem->ver_index);
        }
        ptem = ptem->pnext;
    }
}



//初始化parent数组   
void init_parent(int parent[]){
   for( int i=0; i<maxVertex ;i++)  {parent[i] = -1;  }
}

//查找根节点
int find_root(int x,int parent[]){
    int x_root = x;   //这个是考虑自己就是parent的情况，后面可以统一返回
    while(parent[x_root] != -1)   { 
       x_root = parent[x_root];
    }
    return x_root;
}

//set合并函数:如果可以合并返回1，不可以合并返回0
int union_set(int x,int y,int parent[]){
    //判断能不能合并，需要先找到x,y个root
    int x_root = find_root(x,parent);
    int y_root = find_root(y,parent);
    
    if(x_root == y_root)   {return 0;}
    else {
        parent[x_root] = y_root;    //把x的root结点指向到y的root
        return 1;
    }

}

//compare函数，qsort使用的
int compare(const void*a,const void*b ){
    EdgeNode* pa = (EdgeNode*)a;
    EdgeNode* pb = (EdgeNode*)b;
    int num1 = pa->Weight;
    int num2 = pb->Weight;
    if(num1 - num2 > 0)  return 1;
    else                return -1; 
}

//kruskal--MST  下面程序是有向图的例子
void kruskal(LGraph* pgraph){
    int i=0,j=0,k=0;
    //创建数组用来记录顶点的root信息
    int parents[pgraph->vexNum];
    init_parent(parents);
    //用来保存输入的边结点的所有信息,这里因为是已经创建好了邻接表，所以需要从邻接表读出数值赋值给到edges_inf
    EdgeNode  edges_inf[pgraph->edgeNum];
    //1)怎么把邻接表信息给到edges_inf  ,这里直接赋值的是下标 
    for (i=0;i<pgraph->vexNum;i++){
        Node* ptem = pgraph->G[i].pfirstEdge;
        while(ptem != NULL){
            edges_inf[j].src = find_index(pgraph,pgraph->G[i].alp);
            edges_inf[j].dest= ptem->ver_index;
            edges_inf[j].Weight = ptem->weight;
            j++;
            ptem=ptem->pnext; 
             }   
    }
    /* //邻接表赋值打印测试
     for(k=0;k<pgraph->edgeNum; k++){printf("(%d %d)--%d\n",edges_inf[k].src,edges_inf[k].dest,edges_inf[k].Weight);}*/
   //2)对权值进行排序，调用qsort
   qsort(edges_inf,pgraph->edgeNum,sizeof(EdgeNode),compare);
   //for(k=0;k<pgraph->edgeNum; k++)  { printf("(%d %d)--%d\n",edges_inf[k].src,edges_inf[k].dest,edges_inf[k].Weight);} 
    
    //3)开始生成mst,对edges-inf数组的每条都进行判断
    for(int a=0; a<pgraph->edgeNum ; a++){
        //找edge-Inf【a】的根节点
        int src_root  = find_root(edges_inf[a].src,parents);
        int dest_root = find_root(edges_inf[a].dest,parents);
        //根据根节点判断是否会形成回路
        if(src_root != dest_root){
            //定义dest为根节点
            parents[src_root] = dest_root; 
           // printf("(%d %d)-->%d\n",edges_inf[a].src,edges_inf[a].dest,edges_inf[a].Weight);
            printf("(%c %c)-->%d\n",pgraph->G[(edges_inf[a].src)].alp,pgraph->G[(edges_inf[a].dest)].alp,edges_inf[a].Weight ); 
        }
    }
}
   
//定义getMin函数，从shortest[]数组找出最短路径长度min,并把对应的数组下标返回，dijstra算法使用的
int getMin(LGraph* pgraph,int* isfind, int* shortest){
    int min = INF;
    int index;
    for(int i=0; i<pgraph->vexNum; i++){
        if(isfind[i] ==0 && shortest[i] < min ){
            min = shortest[i];
            index = i;
        }
    }
    return index;
}


//dijstra,index是src点的下标   这个用无向图举例的,这个用来求解起始点到其他各个顶点的最短路径
//举例数据见https://www.bilibili.com/video/BV1W64y1z7jh?p=28&spm_id_from=pageDriver&vd_source=017cc0a5f238638bc0ba4f55c269f5e8

void dijstra(LGraph* pgraph,int index){
      /*1)需要3个辅助数组，这里用动态分配创建，直接创建也可以
      isfind表示是否已经找到最短路径了，找到标记为1，自己到自己标记0
      front_point表示前驱结点，假设a--b--c,那么front_point【2】记下b的结点下标1，没有前驱结点记为-1，
      shortest[]表示最短路径的长度，自己到自己标记为0，不联通标记为无穷INF */
     //  int isfind[pgraph->vexNum]  可以直接创建
      int* isfind = (int*)malloc(sizeof(int)*pgraph->vexNum);
      int* front_point = (int*)malloc(sizeof(int)*pgraph->vexNum); 
      int* shortest = (int*)malloc(sizeof(int)*pgraph->vexNum);  

     //2)3个数组的初始化 ，这里3个分开初始化，一起初始化的代码见视频
     //2.1)初始化isfind[]数组,只需要把自己到自己的标记为即可
     for(int i=0; i<pgraph->vexNum; i++){
         if(i == index)  isfind[i] = 1;
         else   isfind[i] = 0;
     }
    //2.2)初始化front_point数组 ,先把全部赋值为-1,在把和初始顶点直接连接的赋值为其下标index
     for(int i=0; i<pgraph->vexNum; i++)  {front_point[i] =-1; } 
       Node* ptem1 = pgraph->G[index].pfirstEdge;
       while (ptem1 != NULL ){
            front_point[ptem1->ver_index] = index;
            ptem1 =ptem1->pnext; 
     }
    //2.3)初始化shortest数组，首先全部初始化为INF,然后自己到自己的赋值为0，和起始点直接连接的赋值为其权重
    for(int i=0; i<pgraph->vexNum; i++)  {shortest[i] = INF; } 
    shortest[index] = 0;
    Node* ptem2 = pgraph->G[index].pfirstEdge;
    while(ptem2 != NULL){
        shortest[ptem2->ver_index] = ptem2->weight;
        ptem2 =ptem2->pnext;
    }
    //赋值初始化打印测试
    //for(int i=0; i<pgraph->vexNum; i++)   {printf("%d %d %d\n",isfind[i],front_point[i],shortest[i]);}
    
    //开始判断调整
    //从shortest数组找出最短路径长度及其index
    for(int i=0;i<pgraph->vexNum -1; i++){ 
        int index = getMin(pgraph, isfind,shortest);    //isfind,shortest本身就是指针
           //找到后更新isfind数组
        isfind[index] = 1;

        // 假设找到和a连接的最短路径是b后，这里就需要更新a通过b之后到各个节点的shortest和front_point数组了，后面每次找到一个点，跟新一次
        Node* ptem = pgraph->G[index].pfirstEdge;
        while(ptem != NULL){
           //在最短路径isfind没找到且增加一个节点后路径更短后才更新 
           if(isfind[ptem->ver_index] == 0 &&  shortest[index] + ptem->weight < shortest[ptem->ver_index]){     
                shortest[ptem->ver_index] = shortest[index] + ptem->weight;    
                 front_point[ptem->ver_index] = index; 
            }
            ptem = ptem->pnext;
        }    
    }
    //全部找完，打印测试,此时输出信息是保存在这三个数组里，详细路径输出还得另外写个函数输出
    for(int i=0; i<pgraph->vexNum; i++)   {printf("%d %d %d\n",isfind[i],front_point[i],shortest[i]);}
}



/*如何求任意两个顶点之间的最短路径，可以包括dijstra
实现方式：1）直接对每个顶点使用dijstre算法，2）使用Floyd算法
学习参考：https://www.bilibili.com/video/BV1W64y1z7jh?p=30&spm_id_from=pageDriver&vd_source=017cc0a5f238638bc0ba4f55c269f5e8 
算法实现核心：使用2个二维数组，shortest，front_point,进行初始化；
             3for循环实现，循环1用于每次加入一个新的结点试探；循环2.3用于更新2个2维数组*/

void flodyd(LGraph* pgraph){
    //1)定义2个2维辅助数组，然后进行初始化
    int shortest[pgraph->vexNum][pgraph->vexNum];
    int front_point[pgraph->vexNum][pgraph->vexNum];
    //数组初始化---这个如果直接邻接矩阵更直接赋值，这里试一下邻接表的
    //1.1）先全部初始化为INF,然后赋值对角线，然后直接连接的重新赋值权重
    for(int i=0; i<pgraph->vexNum; i++){
        for(int j=0; j<pgraph->vexNum; j++){
            shortest[i][j]    = INF;     //INF表示不联通，
            front_point[i][j] = -1;      //-1表示没有前驱节点
        }
    }
    //自己到自己的路径定义为0
    for(int i=0; i<pgraph->vexNum; i++){
        for(int j=0; j<pgraph->vexNum; j++){
            if(i == j)  shortest[i][j] = 0;  
        }
    }
    //1.3） 联通的进行赋值
    for(int i=0; i<pgraph->vexNum; i++){
        Node* ptem = pgraph->G[i].pfirstEdge;
        while(ptem != NULL){
            shortest[i][ptem->ver_index] = ptem->weight;
            front_point[i][ptem->ver_index] = i;  //邻接表保存的都是连接的
            ptem = ptem->pnext;
        }
    }
   /* //初始化之后打印测试
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
    printf("\n");   */
    

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

}

    


int main(){
    VertexType alp1='a';
    LGraph* pgraph =  buildMgraph();
    printGraph(pgraph);

    int index = find_index(pgraph,alp1);
    //clear_visited visited[maxVertex]; 
    printf("DFS:");
    DFS( pgraph,index);
    printf("\n");

   // kruskal(pgraph);        这个是用的单向图
   //dijstra(pgraph,index);  //index是a的下标   这个用的双向图
   flodyd(pgraph);           //这个用的双向图
   
    return 0;
}