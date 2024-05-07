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
    list->num  = 0;   

    return list;
}

//尾部插入元素
void listAdd(List* list,int data){
    list->data[list->num] = data;
    (list->num)++;
    if(list->num > list->lenght){
        list->lenght ++;
    }
}

//打印list
void printList(List* list){
    for(int i=0; i<list->num; i++){
        printf("%d->",list->data[i]);
    }
    printf("\n");
}

//搜索函数1，循环实现
int binarySearch(List* list,int key){
    int start = 0;
    int end = (list->num)-1;
    int mid;
    while(start < end){                  //start >= end时停止查找
        mid = (start + end)/2;
        if(list->data[mid] > key){       //往左边找
            //start = start;
            end = mid - 1;
        }
        else if(list->data[mid] < key){  //往右边找
            start = mid + 1;
            //end = end;
        }
        //list->data[mid] == key
        else {
            return mid;
        }
    } 
    return -1;     //没找到
}

//二分查找递归实现
int binarySearchRecursion(List* list,int key,int start,int end){
    //递归出口
    if(start >= end){
        if(list->data[start] == key)   { return start; }
        else  return -1;
    }

     int mid = (start + end)/2;
     if(list->data[mid] > key){
        return binarySearchRecursion(list,key,start,mid-1);
     }
     else if(list->data[mid] < key){
        return binarySearchRecursion(list,key,mid+1,end);
     }
     else 
        return mid;
}


int main(){
    List* list = initList(5);  //第0个是保存key的，
    listAdd(list,1);
    listAdd(list,2);
    listAdd(list,3);
    listAdd(list,4);
    listAdd(list,5);
    listAdd(list,6);
    listAdd(list,7);
    //printf("num=%d,lenght=%d,\n",list->num,list->lenght);
    printList(list);

    printf("data %d 的 index=%d\n",4,binarySearch(list,4));
    printf("data %d 的 index=%d\n",2,binarySearch(list,2));
    printf("data %d 的 index=%d\n",6,binarySearch(list,6));
    printf("data %d 的 index=%d\n",8,binarySearch(list,8));
    
    printf("data %d 的 index=%d\n",4,binarySearchRecursion(list,4,0,list->num));
    printf("data %d 的 index=%d\n",2,binarySearchRecursion(list,2,0,list->num));
    printf("data %d 的 index=%d\n",6,binarySearchRecursion(list,6,0,list->num));
    printf("data %d 的 index=%d\n",8,binarySearchRecursion(list,8,0,list->num));
    return 0;
}