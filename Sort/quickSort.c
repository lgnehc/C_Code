#include <stdio.h>

/*学习资料---b站up:Tyrantlucifer*/

void printArray(int array[], int lenght){
    for(int i = 0; i < lenght; i++)  { 
        printf("%d ",array[i]); 
    }
    printf("\n");
}

//找出下标位置,i,j分别是两个指向下标索引
int partition(int array[], int i, int j){
    int pivot = array[i];     //选择第一个作为基准
     /* NOTE:外层的i<j是让程序进入循环，内层循环里面的i<j不能省略，因为进入循环后，i，j是会改变的，所以要带上i<j
     if的i<j,可以不用，内层while的一定要带上，不然排序错误 */
    while (i<j){
        //选择第一个作为基准，那么就是先从后面开始扫
        //情形1：先从后面的开始判断，如果不小于基准值，那么直接移动j,再判断，所以对比情形2用的循环
        while ((i < j) && (array[j] >= pivot ) ){
            j--;
        }
        //情形2：从后面的开始判断，如果小于基准值，那么填补到空出的位置上，然后从i开始判断
        if((i < j) && (array[j] < pivot) ){     
            array[i] = array [j];    //移动到空位置上
            i++;
        }
        //转到从前面开始扫，不停来回扫动判断，直到i=j
        //情形3：经过情形2，开始从前面判断，如果小于基准值，那么直接移动i,再判断，所以对比情形2用的循环
        while ((i < j) && (array[i] < pivot) ){
            i++;
        }
        //情形4：从前面的开始判断，如果大于等于基准值，那么填补到空出的位置上，然后从j开始判断
        if((i < j) && (array[i]) >= pivot){
            array[j] = array [i];  //移动到空位置上
            j--;
        }
    }
    //i=j时,跳出循环,也就找到下标位置partition,基准放入此位置
    array[i] = pivot;  //此时i=j,
    return i;

}

void quickSort(int array[], int i, int j){
    if(i < j) {      //i>=j时，作为递归出口                         
        int index = partition(array,i,j);
        printArray(array,8);   //打印每一步排序过程
        quickSort(array,i,index-1);
        quickSort(array,index+1,j);
    }
}


int main(){
    //测试
    int array[8] = {27,38,13,49,76,97,65,49};
    quickSort(array,0,7);
    printArray(array,8);

    return 0;
}