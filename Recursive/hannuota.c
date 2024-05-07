#include <stdio.h>

/*主要步骤
【1】如果是一个盘子，直接从A移动到C；
【2】如果时n个盘子，先将n-1个盘子借助C移动到B
 [3]在把第n个盘子直接从A移动到C,
 [4]最后把B柱子上的n-1个借助A移动到，这里就是开始新一轮的移动了，不过初始柱子变了（如何移动，借助n-2）
 
 当盘子只有3个时 1：A-C  2:A-B  1:C-B  3:A-C  1:B-A  2:B-C  1:A-C  
*/



//函数参数意义，将n个盘子，借助B，从A移动到C
void hannuota(int n,char A,char B,char C){
    if(1 == n)
       printf("将编号为%d的盘子直接从%c移动到%c\n",n,A,C);
    else{
        hannuota(n-1,A,C,B);
        printf("将编号为%d的盘子直接从%c移动到%c\n",n,A,C);
        hannuota(n-1,B,A,C);
    }
}

int main(){
    int n;
    char ch1='A';
    char ch2='B';
    char ch3='C';

    printf("输入需要移动的数量：");
    scanf("%d",&n);

    hannuota(n,ch1,ch2,ch3);
}