#include <stdio.h>
#include <stdlib.h>

/*学习资料---b站up:Tyrantlucifer*/

typedef struct{
    int* data;     //数组保存数据
    int lenght;    //数组总长度，包括第0个
    int num;       //数据个数，不包括第0个
}List;


//初始化长度为lenght的List
List* initList(int lenght){
    List* list = (List*)malloc(sizeof(List));
    list->data = (int*)malloc(sizeof(int)*lenght);
    list->lenght = lenght;
    list->num  = 0;   //第0个作为哨兵，保存查找元素key
    list->data[0] = 0;

    return list;
}

//尾部插入元素
void listAdd(List* list,int data){
    list->data[(list->num)+1] = data;
    (list->num)++;
    if(list->num == list->lenght){
        list->lenght ++;
    }
}

//打印list
void printList(List* list){
    for(int i=0; i<=list->num; i++){
        printf("%d->",list->data[i]);
    }
    printf("NULL\n");
}

//搜索函数,从后面开始查找，找到返回i,if返回i=0就是没找到，
int search(List* list,int key){
    int i;
    list->data[0] = key;
    //printList(list);
    for( i=list->num; list->data[i] != key; i--);   //这里分号是因为循环没有语句
    //返回的i是data[i],data[0]是查找元素
    return i;   
}

int main(){
    List* list = initList(5);  //第0个是保存key的，
    listAdd(list,4);
    listAdd(list,8);
    listAdd(list,5);
    listAdd(list,7);
    listAdd(list,6);
    listAdd(list,9);
    printf("num=%d,lenght=%d,\n",list->num,list->lenght);
    printf("在第%d个位置\n",search(list,5));
    
    printList(list);


    return 0;
}