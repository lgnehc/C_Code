#include <stdio.h>

//递归：不断细分为子规模的过程
//递归过程：用栈实现，保护现场（数据，和吓一跳指令的指针----类似单片机的中断）

//求n!:
int mux(int n){
    if (1 == n)
      return 1;
    else 
      return mux(n-1)*n;   //n*mux(n-1)会有问题
}

//求累加和1+2+3+...+n
int  sum(int n){
  if(1==n)
     return 1;
  else 
     return sum(n-1)+n;

}

int main(){
    int n; 
    printf("输入n的值:");
    scanf("%d",&n);
    printf("%d的阶乘是:%d\n",n,mux(n));
    printf("%d的累加和是:%d\n",n,sum(n));


    return 0;
}
