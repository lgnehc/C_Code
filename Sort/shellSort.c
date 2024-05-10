#include <stdio.h>

/*    学习视频：b站up:Tyrantlucifer  
      步骤：先按步长分组，分别进行插入排序，然后逐步缩小步长，重复前面的步骤，直到步长为1
 */

void printArray(int array[],int length){
    for (int i=0; i<length; i++)  { printf("%d ",array[i]); }
    printf("\n");
}

void shellSort(int array[],int length,int step){
    //最外层循环是所有数字都要进行分组
    //这里应该有重复：{i=0时，arr[0]，arr[5],arr[10]...},{i=5时，arr[5]，arr[10]又重复排序}----待优化
    for(int i = 0; i < length; i++){
        //开始分组：i=0时，根据步长选出和arr[0]同一组的进行插入排序，然后依次和选出arr[i]同组的进行排序，
        //比如：i=0时，依次选出的arr[j]={arr[0],arr[0+ step*1],arr[0+ step*2]...},进行插入排序，插入排序第一个不用排序
        for(int j = i + step; j < length; j += step ){
            //对具体某一组开始插入排序,这里插入排序是从前面开始判断插入位置的
            //这个for循环是判断arr[j]插入位置的
           for(int k = i; k < j; k += step){
                if( array[k] > array[j] ){   //对第一组插入排序：arr[k] = arr[0] ;arr[j]= arr[0+step]，依次类推 
                //if判断后确定出插入位置是arr[k],需要开始移位，把arr[k]位置空出
                    int tem = array[j];
                    //后面的开始移位
                    for(int l = j-step; l >= k; l -= step){
                        array[l+step] = array[l];
                    }
                    array[k] = tem;
                }  
            }    
           /*
           for(int k = i+step; k <= j; k += step){    //因为这里j是对应下标，和insertSort.c的n(是长度，)不一样
                int key = array[k];
                while(array[k-step] > key){
                    array[k] = array[k-step];
                    k = k - step;
                    if(k==i)  { break; }
                }
                array[k] = key;  
            }
            */
        }
    }
}

int main(){
    int array[10] = {49,38,65,97,76,13,27,49,55,4};
    int step[3] ={5,3,1};
    for(int i = 0; i < 3; i++){
        shellSort(array,10,step[i]);
        printArray(array,10);
    }


    return 0;
}