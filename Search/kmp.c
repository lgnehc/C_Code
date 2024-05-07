#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
https://www.bilibili.com/video/BV1hW411a7ys/?spm_id_from=333.337.search-card.all.click&vd_source=017cc0a5f238638bc0ba4f55c269f5e8
学习资料：up主：正月点灯笼
*/

//构建prefix_table，
//pattern[]是需要匹配的字符串，prefix是对应的前缀表,n是需要匹配的字符的长度
void prefix_table(char pattern[],int prefix[],int n){
    prefix[0] = 0 ;       //单个字符的前缀=0  
    int len   = 0 ;       //len是已经匹配的长度
    int i     = 1 ;       //i是循环用的，构造前缀表是依次增加后面一个字符
    
    while(i < n){
        //成功匹配，prefix+1
        if(pattern[len] == pattern[i]){
            len++;
            prefix[i] = len;
            i++;
        }
        //匹配失败,    这里原理没懂！！！！！
        else{
            if(len > 0){
                len = prefix[len-1];
            }
            else{
                prefix[i] = 0;
                i++;
            }
                     
        }
    }
}

void move_prefix_table(int prefix[],int n){
    for(int i=n-1; i>0; i--)  { prefix[i] = prefix[i-1]; }
    prefix[0] = -1;
}

void kmp_search(char text[], char pattern[]){
    //需要先转换成prefix数组
    int n = strlen(pattern);
    int* prefix = (int*)malloc(sizeof(int) * n);
    prefix_table(pattern,prefix,n);
    move_prefix_table(prefix,n);

    //定义指向pattern和text的下标： text[i]   len(text) = m;  pattern[j]  len(pattern)=n; 
    int i=0;
    int j=0;
    int m = strlen(text); 
    
    while(i < m){
        //找到后的打印，
        if((j == n-1)  && (text[i] == pattern[j]) ){
            printf("pattern is found at %d\n",i-j);   
            j = prefix[j];   //找到第一个后移动到相应的位置，在找是否有第2个匹配的  
        } 

        //这里才是开始匹配查找
        if(pattern[j] == text[i]){
            i++; 
            j++;
        }
        else{
            j = prefix[j];
            if(j == -1){         //特殊情况，prefix直接往后移动一位 
                i++;
                j++;
            }
        }
    }
}



int main(){
    char pattern[]="ABABCABAA";
    char text[]   ="ABABABCABAAABABAB";
    kmp_search(text,pattern);
    /*
    //测试prefix_table函数
    int  prefix[9];
    int  n=9;
    prefix_table(pattern,prefix,n);
    for(int i=0;i<n;i++)  { printf("%d\n",prefix[i]); }  
    */

    return 0;
}