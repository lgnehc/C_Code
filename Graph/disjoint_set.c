#include <stdio.h>
#include <stdlib.h>

/*学习资料：B站up：正月点灯笼
https://www.bilibili.com/video/BV13t411v7Fs/?p=2&spm_id_from=pageDriver&vd_source=017cc0a5f238638bc0ba4f55c269f5e8z 
*/

#define VERTICES 6

//初始化parent数组   
void init_parent(int parent[]){
   for( int i=0; i<VERTICES ;i++)  {
        parent[i] = -1;  
    }
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


int main(){

   int parent[VERTICES];
   init_parent(parent);

   //测试
   int edge[6][2] = {
    {0,1},{1,2},{1,3},
    {2,4},{3,4},{2,5}
   };
   for(int i=0; i<6; i++){
    int x = edge[i][0];
    int y = edge[i][1];
    if (union_set(x,y,parent) == 0) {
        printf("cycle detected!\n");
        exit(0);
    } 
   }
   printf("no cycle\n");

    return 0;
}