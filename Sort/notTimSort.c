#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/*
代码来源：https://www.jianshu.com/p/f80306282c7c
python解释:https://vladris.com/blog/2021/12/30/timsort.html
https://www.cnblogs.com/sunshuyi/p/12680918.html
https://www.youtube.com/watch?v=emeME__917E&ab_channel=GauravSen
*/


//最大栈大小
#define MAX_MERGE_PENDING 85
//判断数据顺序连续性的阈值
#define MIN_GALLOP 7
// 参与序列合并的最短长度
#define MIN_RUN_BOUND 64


//已排序的run
typedef struct _sortSlice
{
    int* pos;      //run片段的首地址
    int  len;      //run片段的长度
}sortSlice;

//保存run栈状态
typedef struct _MergeState
{
    int run_num;      //run栈的个数
    int min_gallop;
    //pending[]保存的是结构体sortslice数组    
    struct _sortSlice pending[MAX_MERGE_PENDING];   
}MergeState;

//打印函数
void printArray(int arr[],int length){
    for (int i=0; i<length; i++)  { printf("%d ",arr[i]); }
    printf("\n");
}

//这个start/end是数组下标,先用count_run计算出排序好的序列，arr【offset】前面的是已经排序好的序列
void binaryInsertSort(int arr[], int start,int offset,int end) {
    //对每个数据都要进行排序
    for(int i = offset + 1; i <= end; i++){
        int key  = arr[i];
        int left = start;
        int right = i-1;
        // if(key >= arr[right]) { continue; }
        //开始二分查找插入位置
        while(left <= right){
            int mid = (left + right)/2;
            if(arr[mid] > key)        //这个是小到大排序 ，往左边查找    
            //if(arr[mid] < key)      //这个是大到小排序
                right = mid - 1;
            else                      //往右边查找
                left = mid + 1;
        }
        //while循环结束后，找到插入位置left = right
        //把数据往后移动一位，空出插入位置
        for(int j = i-1; j >= left; j--){
            arr[j+1] = arr[j];
        }
        arr[left] = key;
        // printArray(arr,end+1);
    }
}



//反转数据
void reverseRange(int run[],int start,int end){
    int tem;
    int mid = (start + end)/2;
    for(int i = start; i <= mid; i++,end--){
        tem = run[i];
        run[i] = run[end];
        run[end] = tem;
    }
}


//算出minrun,MIN_RUN_BOUND=64,minrun:[32,63]
int merge_compute_minrun(int n){
    int r = 0;
    while(n>=MIN_RUN_BOUND){
        r |= n&1;
        n >>= 1;
    }
    return n+r;
}


//判断run长度函数
//参数说明，给定数组arr,arr下标从start到end，返回run长度
int count_run(int arr[], int start, int end){
    //start == end，表示数组长度为1，长度为1定义为已经排序好的序列
    if(start == end)   { return 0; }

    int run_hi = start;
    //非严格升序情形
    if(arr[start] <= arr[start+1]){
        while((run_hi < end) && arr[run_hi] <= arr[run_hi + 1]){
            run_hi++;
        }
    }
    //严格降序
    else if(arr[start] > arr[start+1]){
        while ((run_hi < end) && arr[run_hi] > arr[run_hi + 1])
        {
            run_hi++;
        }
        //降序反转为升序
        reverseRange(arr,start,run_hi);  
    }
    return run_hi - start;
}


/*
在一个序列中，将一个指定的key，查找它应当插入的位置；如果序列中存在与key相同的值(一个或者多个)，那返回这些值中最右边的位置，保持原有数组相同元素顺序。
用于key所在的数组在数组*a后面；
查找的规则：先使用跳跃式模糊查找确定大概位置区间： fn(x)=fn(x-1)*2+1,x>=1，其中fn(1)=1；在用二分法查找精确定位：a[fn(x-1)]<key<a[fn(x)]
key：指定要查找的数值
*z： 数组z的起始位置
len：数组z长度
offset：数组z中的偏移值，表示从offset开始查找
*/
//ssz.len > ssy.len 
int gallop_left(int key,int* z,int len,int offset){
    int lastofs = 0; //记录上一次ofs的偏移量
    int ofs = 1;

    //开始指数式（通过位移函数）搜索，确定大概范围，在用二分查找精确定位
    //1.key大于a[z+offset]的值，指数式往右边搜索
    if(key > *(z + offset)){
        int maxofs = len - offset;   //最大偏移量
        //1.1.循环进行指数搜索
        while(ofs < maxofs && key > *(z+offset+ofs)){
            lastofs = ofs;
            ofs = (ofs<<1)+1;       //16进制按位移动
            //1.2.判断位移ofs的边界条件，
            if(ofs <= 0){
                ofs = maxofs;
            }
        }
        //1.3.这个也是判断ofs的边界条件
        if(ofs > maxofs){
            ofs = maxofs;
        }
        //1.4.判断出大概位置后，先保存区间范围，后面精确查找使用
        //note:这里的lastofs和offset是针对的从z[0]开始的偏移量，前面的是针对的从z[offset]开始的
        lastofs = lastofs + offset;
        ofs = ofs + offset;
    }
    //2.(key <= *(a+offset))的情形，那么往左边指数级查找
    else{
        int maxofs = offset + 1;
        //2.1.循环进行指数搜索
        //note:这个是从z[offset]-->z[0]查找
        while(ofs < maxofs  &&  key <= *(z+offset-ofs)){
            lastofs = ofs;
            ofs = (ofs<<1)+1;
            //2.1.1判断边界条件
            if(ofs <= 0){
                ofs = maxofs;
            }
        }
        //2.2.判断边界条件
        if(ofs > maxofs){
            ofs = maxofs;
        }
        //2.3判断出大概位置后，先保存区间范围，后面精确查找使用，
        //转换数据确保lastofs<ofs,并且key位于区间[lastofs,ofs],后面方便统一二分查找
        int k = lastofs;
        lastofs = offset - ofs;
        ofs = offset - k;
    }
    lastofs ++;   //这个是为啥
    //3.二分查找找出精确位置
    while(lastofs < ofs){
        int mid = lastofs + ((ofs - lastofs)>>1);
        if(key > z[mid]){
            lastofs = mid + 1;
        }else{
            ofs = mid;
        } 
    }
    return ofs;
}


/*
在一个序列中，将一个指定的key，查找它应当插入的位置；如果序列中存在与key相同的值(一个或者多个)，那返回这些值中最右边的位置，保持原有数组相同元素顺序。
用于key所在的数组在数组*a后面；
查找的规则：先使用跳跃式模糊查找确定大概位置区间： fn(x)=fn(x-1)*2+1,x>=1，其中fn(1)=1；在用二分法查找精确定位：a[fn(x-1)]<key<a[fn(x)]
key：指定要查找的数值
*y：在数组y中查找key的位置
len：数组a长度
offset：数组a中的偏移值，表示从offset开始查找
*/
//ssz.len<=ssy.len 
int gallop_right(int key,int* y,int len,int offset){
    int lastofs = 0;
    int ofs = 1;
     //key小于于z[offset]所在值，那么key位置肯定小于offset,所以下标要前移ofs
    if(key < *(y + offset)){
        //相对于offset最大偏移值，实际位置为offset-ofs,ofs<=maxofs
        const int maxofs=offset+1;
        while(ofs < maxofs && key < *(y+offset-ofs)){
            lastofs = ofs;
            ofs = (ofs<<1)+1;
            if(ofs <= 0){      
                ofs = maxofs;
            }
        }
        if(ofs > maxofs){
            ofs = maxofs;
        }
        //转换数据确保lastofs < ofs,并且key位于区间[lastofs,ofs]
        int k = lastofs;
        lastofs = offset - ofs;
        ofs = offset - k;
    }else{
        //key大于z[offset]所在值，那么key位置肯定大于offset
        //相对与offset最大偏移值，实际位置为offset+ofs,ofs<=maxofs
        const int maxofs = len-offset;
        while(ofs < maxofs && key >= *(y+offset+ofs)){
            lastofs = ofs;
            ofs = (ofs<<1)+1;
            if(ofs <= 0){ //int overflow
                ofs = maxofs;
            }
        }
        if(ofs > maxofs){
            ofs = maxofs;
        }
        lastofs += offset;
        ofs += offset;
    }
    lastofs ++;

    //二分法查找精确定位位置:[lastofs,ofs]
    while(lastofs < ofs){
        int mid = lastofs + ((ofs-lastofs)>>1);
        if(key < y[mid]){
            ofs = mid;
        }else{
            lastofs = mid + 1;
        }
    }
    return ofs;
}

//ssz.len <= ssy.len,则数组起始位置开始合并
void merge_low(MergeState* ms,sortSlice ssz,sortSlice ssy){
    int* y = ssy.pos;
    int* z = ssz.pos;
    int len_y = ssy.len;
    int len_z = ssz.len;
    int z_size = len_z * sizeof(int);

    //申请一个ssz.len的临时空间，这个部分看YouTube解释
    //然后把ssz的数据赋值到ptem数组
    int* ptem = (int*) malloc(z_size);
    memcpy(ptem,z,z_size);
    
    //定义指向3个数组的下标，用于归并的
    int ptem_cursor = 0;   //临时数组的index指针
    int y_cursor = 0;      //指向ssy数组的index指针
    int dest = 0;          //指向原来的(ssz+ssy)的index指针,这个也是最终合并后保存数据的

    //经过gallop_right后,y[0]是小于ssz的所有元素的，可以先赋值
    z[dest++] = y[y_cursor++];   //赋值完后index指针++
    len_y --;
    
    //如果y只有一个元素
    if(len_y == 0){
        memcpy(&z[dest],ptem,z_size);
        return ;
    }
    //数组z中只剩下一个元素
    if(len_z == 1){
        memcpy(&z[dest],&y[y_cursor],len_y*sizeof(int));
        z[dest+len_y] = ptem[ptem_cursor];
        return ;
    }
    
    //连续性阈值
    int min_gallop = ms->min_gallop;
    while(1){
        int zCount = 0 ;    //序列z比y连续大的次数
        int yCount = 0 ;    //序列y比z连续大的次数
        do{
            if(y[y_cursor] < ptem[ptem_cursor] ){
                z[dest++] = y[y_cursor++];
                yCount ++;
                zCount = 0;
                len_y --;
                if(len_y == 0){
                    goto Last;
                }
            }else{
                z[dest++] = ptem[ptem_cursor++];
                zCount++;
                yCount = 0;
                len_z --;
                if(len_z == 1){
                    goto Last;
                }
            }
        }while((yCount | zCount) < min_gallop); //数组连续性差，继续做归并
        min_gallop++;

        /*
         执行到这里，猜测数据连续性较好
         先使用gallop_right查找y[b_cursor]在z的下标位置k,k前面的元素都会比y[y_cursor]小,则把k前面连续的元素copy到dest后即可，在追加放置y[y_cursor]；
         然后使用gallop_left查找temp[temp_cursor](实际是数组z[temp_cursor])在y的下标位置k，k前面的元素都会比temp[temp_cursor]小,则把k前面连续的元素copy到dest后即可，在追加放置temp[temp_cursor]；
        */
        do{
            //猜测数据连续性较好，减少阈值，使之，更容易使用连续copy方法提高性能
            min_gallop -= (min_gallop > 1);
            ms->min_gallop = min_gallop;
            zCount = gallop_right(y[y_cursor],&ptem[ptem_cursor],len_z,0);
            if(zCount > 0){
                memcpy(&z[dest],&ptem[ptem_cursor],zCount * sizeof(int));
                dest += zCount;
                ptem_cursor += zCount;
                len_z -= zCount;
                if(len_z == 1){
                    goto Last;
                }
            }
            z[dest++] = y[y_cursor];
            len_y --;
            if(len_y == 0){
                goto Last;
            }
            yCount = gallop_left(ptem[ptem_cursor],&y[y_cursor],len_y,0); 
            if(yCount != 0){
                memcpy(&z[dest],&y[y_cursor],yCount * sizeof(int));
                dest += yCount;
                y_cursor += yCount;
                len_y -= yCount;
                if(len_y == 0){
                    goto Last;
                } 
            }
            z[dest++] = ptem[ptem_cursor++];
            len_z--;
            if(len_z == 1){
                goto Last;
            }
        }while(zCount >= MIN_GALLOP || yCount >= MIN_GALLOP);  //数组连续性好，继续这样处理
        //连续性不好，增加阈值
        min_gallop++;
        ms->min_gallop = min_gallop;
    }
    Last:
         /*
        通过gallop后我们可以确定y[0]小于数组z中的所有元素，z[len-1]大于数组y中所有元素
        所以执行到这里存在两种情况：
            len_z=1,len_y>=1,剩下的y元素是最小的数值，拷贝到dest后，追加放置z[len-1]；
            len_y=0;len_z>=1,剩下的z元素都是大于y的连续元素，拷贝到目标数组dest后；
        */
        if(len_z == 1){
            memcpy(&z[dest],&y[y_cursor],len_y*sizeof(int));
            z[dest+len_y]=ptem[ptem_cursor];
        }else{
            memcpy(&z[dest],&ptem[ptem_cursor],len_z*sizeof(int));
        }
        free(ptem);
}


//ssz.len>ssy.len 则数组末尾位置开始合并,从大到小降序排序
void merge_high(MergeState* ms,sortSlice ssz,sortSlice ssy){
    int *y = ssy.pos;
    int *z = ssz.pos;
    int len_z = ssz.len;
    int len_y = ssy.len;
    int y_size = len_y * sizeof(int);
    //申请一个ssy.len的临时数组temp
    int *temp = (int*) malloc(y_size);
    //把数组ssy的数据拷贝到临时数组temp
    memcpy(temp,y,y_size);
    //临时数组下标指针
    int temp_cursor = len_y-1;
    //数组z的下标指针
    int z_cursor = len_z-1;
    //保存结果的下标指针,其首地址应该是ssz[ssz.len+ssz.len-1].pos，终点地址应该是ssz[0].pos,即数组末尾位置y[len-1]开始合并
    int dest = len_z + len_y-1;
    //通过gallop后我们可以确定z[len-1]大于数组y中的所有元素，可以直接把z[len-1]放置到下标dest;y[0]小于数组z中所有元素
    z[dest--] = z[z_cursor--];
    //放置后数组z的长度自动减小1
    --len_z;
    //如果数组z只有一个元素，那么y中所有元素都比z的小，把y序列元素放置到z[len-1]前即可
    if(len_z == 0){
        memcpy(z,temp,y_size);
        return;
    }
    //y数组只剩下一个元素的，那么这个元素y[0]比z中所有元素都小，所有把剩下的z元素拷贝到dest位置前，把y[0]放置在起始位置即可
    if(len_y == 1){
        memmove(z+1, z, len_z*sizeof(int));
        z[0] = temp[temp_cursor];
        return;
    }
    //连续性阈值
    int min_gallop = ms->min_gallop;
    while(1){
        int zcount = 0;   //序列z比序列y连续大的次数
        int ycount = 0;   //序列y比序列z连续大的次数
        //归并排序
        do{
            if(temp[temp_cursor] >= z[z_cursor]){
                z[dest--] = temp[temp_cursor--];
                ycount ++;
                zcount = 0;
                --len_y;
                //y[0]比z里所有的元素小，直接拷贝到数组头部
                if(len_y == 1){
                    goto Last;
                }
            }else{
                z[dest--] = z[z_cursor--];
                ycount = 0;
                zcount ++;
                --len_z;
                if(len_z == 0){
                    goto Last;
                }
            }
        }while((zcount|ycount)<min_gallop);   //数组连续性差，继续使用归并

        min_gallop ++;

        /*
         执行到这里，猜测数据连续性较好
        */
        do{
            //猜测数据连续性较好，减少阈值，使之，更容易使用连续copy方法提高性能
            min_gallop -= (min_gallop>1);
            ms->min_gallop = min_gallop;
            //查找temp[temp_cursor]在z数组的位置，那么z数组中此位置k后的所有元素都比temp[temp_cursor]大,则把k后面连续的元素copy到dest前即可，在dest-1放置temp[temp_cursor]；
            zcount = len_z-gallop_right(temp[temp_cursor],z,len_z,len_z-1);
            if(zcount > 0){
                dest -= zcount;
                z_cursor -= zcount;
                len_z  -= zcount;
                memmove(&z[dest+1], &z[z_cursor+1], zcount*sizeof(int));
                if(len_z == 0){
                    goto Last;
                }
            }
            z[dest--] = temp[temp_cursor--];
            len_y --;
            if(len_y  == 1){
                goto Last;
            }
             //查找z[z_cursor]在temp数组的位置k，那么temp数组中此位置k后的所有元素都比z[z_cursor]大,则把k后面连续的元素copy到dest前即可，在dest-1放置a[a_cursor]；
            ycount = len_y-gallop_left(z[z_cursor], temp, len_y, len_y-1);
            if(ycount > 0){
                dest -= ycount;
                temp_cursor -= ycount;
                len_y -= ycount;
                memcpy(&z[dest+1], &temp[temp_cursor+1], ycount*sizeof(int));
                if(len_y == 1){
                    goto Last;
                }
            }
            z[dest--] = z[z_cursor--];
            len_z --;
            if(len_z == 0){
                goto Last;
            }
        }while(zcount>=MIN_GALLOP || ycount>=MIN_GALLOP);
        //数据连续性不好，增加阈值
        min_gallop ++;
        ms->min_gallop = min_gallop;
    }
    Last:
        /*
        通过gallop后我们可以确定y[0]小于数组z中的所有元素，z[len-1]大于数组y中所有元素
        所以执行到这里存在两种情况：
            len_y=1,len_z>=1,剩下的z元素是最大的数值，放置到目标数组末尾即可,把剩下的数组y元素放在目标数据起始位置；
            len_z=0;len_y>=1,剩下的y元素都是小于z的连续元素，拷贝到目标数组dest前；
        */
        if(len_y == 1){
            memmove(&z[dest-(len_z-1)], &z[0], len_z*sizeof(int));
            z[0] = temp[temp_cursor];
        }else{
            memcpy(&z[dest-(len_y-1)], &temp[0], len_y*sizeof(int));
        }
        free(temp);
}


//合并位置为n的run栈：把n和n+1的run栈进行合并
void merge_at(MergeState* ms,int n){
    //假设位置n指向的是 (X+Y >= Z)&&（z < x）中的z序列
    //对序列y,z进行合并
    sortSlice ssz = ms->pending[n];
    sortSlice ssy = ms->pending[n+1];

    //1.更新合并之后的参数
    //1.1.更新长度
    ms->pending[n].len = ssz.len + ssy.len;
    //1.2.run栈的index往前移动一位。  疑问：为什么是这个判断条件
    if(n == ms->run_num - 3)  { ms->pending[n+1] = ms->pending[n+2]; }
    //1.3.更新run栈数量
    ms->run_num --;

    //2.开始合并操作：经过之前的操作后，y的长度是小于z的
    //2.1.找出y[0]在z序列中的位置，那么z[ky]前面的数据都比y[0]要来的小
    int pz = gallop_right(*ssy.pos,ssz.pos,ssz.len,0);
    //2.1找到之后直接z[ky]前面的数据不用改动，直接砍断即可
    ssz.pos = ssz.pos + pz;
    ssz.len = ssz.len - pz;
    if (ssz.len == 0) { return; }  //如果ssa已经排好，证明合并完成，直接返回
    //2.2.找出最后1个数据z[len-1]在序列y中的位置,找到后直接砍断
    int py = gallop_left(ssz.pos[ssz.len-1],ssy.pos,ssy.len,ssy.len-1);
    ssy.len = py;
    if(ssy.len == 0) { return; }
    
    //ssz.len <= ssy.len,则数组起始位置开始合并
    if(ssz.len <= ssy.len){
        merge_low(ms,ssz,ssy);
    }
    else if(ssz.len > ssy.len){
        merge_high(ms,ssz,ssy);
    }
}

/* 
run依次入栈后，最后一个run是在栈顶，记为X（run长度）,往下依次记为Y,Z  
    【NOTE:1）这个入栈顺序是Z-Y-X；2)栈顶index是最大的】,X的index是最大的
     这里的XYZ对应的参考代码的是CBA
run需要满足的条件：
    条件1）如果只有2个run栈，那么需要满足X < Y，
        如果不满足，那么直接合并这2个run栈
    条件2）对于栈顶的3个栈（可能有多个栈），需要满足 (X+Y < Z) && X < Y
        如果不满足其中一个:进行调整，把Y和 min(X,Z)进行合并，然后再判断是否需要接着合并
    如果A <= B+C,A和C中更小的和B合并;
    如果只有两个run:A和B，那么A<=B时，A和B合并  */
void merge_collapse(MergeState* ms){
    sortSlice* p = ms->pending;   //只是单纯想简写
    while (ms->run_num > 1){
        //先判断倒数第3个run栈（n=run_num - 2）的情形是否调整 [此时n就是前面定义的X]
        int n = ms->run_num - 2;

        //(n>1) && (p[n].len + p[n-1].len >= p[n-2].len) 这个是为了解决某个bug的，暂时不懂
        //对于(n > 0)此时n指向Y，但是对于(n>1)来说此时n指向X,这个不太一样，后面代码理解是以(n>0)情形来理解的 
        //对于(n > 0)此时n指向的是Y下标， 
        //（要求(X+Y < Z) && X < Y ）-- 此时情形包括时 【(X+Y >= Z) && X >= Y】 和 【(X+Y >= Z) && X < Y】
        if(((n > 0) && (p[n+1].len + p[n].len >= p[n-1].len))  ||  ((n>1) && (p[n].len + p[n-1].len >= p[n-2].len))){
            //针对x < z,合并X和Y,此时n指向y,  ；  针对z < x,合并Y和Z,此时执行n--,让其指向z,在合并zy
            if(p[n-1].len < p[n+1].len){       //这个是针对的(n > 0)的z < x， (n>1)好像不对？？？
                n--;  
            }
            merge_at(ms,n);    //这个参数n合并是把n和n+1进行合并，
        }
        //（要求(X+Y < Z) && X < Y ）-- 此时情形是【 (n <= 0) || (X+Y < Z) && X >= Y 】,(n <= 0)就是只有2个run栈
        else if (p[n+1].len >= p[n].len){ 
               merge_at(ms,n);
        }
        //（要求(X+Y < Z) && X < Y ）-- 此时情形是【(X+Y < Z) && X <Y 】
            else { break; }
        //截止到这，2个栈和2个以上栈的是否需要合并的情形已经囊括了
    }
    
}

//最后合并函数,经过merge_collapse函数操作后，剩下的run栈一定是满足【(X+Y < Z) && X < Y】这2个条件的
void merge_force_collapse(MergeState* ms){
    sortSlice* p = ms->pending;
    //最后剩下的run栈2个以上，要进行操作合并成1个
    while(ms->run_num > 1){
        int n = ms->run_num - 2;
        if( (n > 0) && (p[n-1].len < p[n+1].len) ) {
            n --;
        }
        merge_at(ms,n);
    }
}


//timsort排序
void tim_sort(int arr[],int len){
    //情形1：数组只有一个元素的情形：直接返回
    if(len < 2)  {  return; }
    
    //定义结构体变量ms以及初始化
    MergeState ms;    
    ms.run_num = 0;
    ms.min_gallop = MIN_GALLOP;

    //计算出minrun的值
    int  minrun = merge_compute_minrun(len);
    printf("minrun = %d\n\n",minrun);

    //情形2：数组长度小于minrun，直接二分插入排序即可
    if(len <= minrun){
        int init_offset = count_run(arr,0,len-1);
        binaryInsertSort(arr, 0, init_offset, len-1);
        return ;
    }

    //情形3：数组长度大于minrun
    int remain_len = len;
    int start = 0;
    int end = len - 1;
    int stack_index = 0;  //定义为入栈的下边
    //开始判断
    while(remain_len > 0){
        //3.1.先找出非严格升序或降序的片段
        int offset = count_run(arr,start,end);
        //比如前3个数是排序好的，那么offsetf == 2,run_len == 3;
        int run_len = offset + 1;
        //3.1.1.如果run长度小于minrun，太短，需要二分插入排序补长到minrun,形成一个run栈
        if(run_len < minrun){
            //如果后面数据很多，需要补足到minrun，如果后面没有这么多数据，可以把全部囊括
            int force_len = (remain_len <= minrun) ? remain_len : minrun ;
            binaryInsertSort(arr, start, (start + offset), (start + force_len -1));
            run_len = force_len;
        }  
        //3.2.创建后一个有序run序列后，把run入栈并更新参数
        ms.pending[ms.run_num].pos = &arr[start];
        ms.pending[ms.run_num].len = run_len;
        //入栈后打印入栈信息
        printf("stack[%d].len = %d ",stack_index++,run_len);
        printf("入栈数据：");
        printArray(&arr[start],run_len);
        printf("\n");
        ms.run_num ++;    
        //run入栈后判断开始合并run
        merge_collapse(&ms);
        //更新参数开始下一轮的循环判断
        start = start + run_len;
        remain_len = remain_len - run_len;
    }
    //经过循环调整run栈后，剩下的run再强制合并，直至剩下最后一个
    merge_force_collapse(&ms);

}


int main(){ 
    int len = 500;
    int arr[len];
    srand((unsigned)time(NULL));
    //随机生成长度为"len"的数组
    for(int i = 0; i < len; i++) {
        arr[i] = rand()%500;
    } 

    printf("排序前：");
    printArray(arr,len);
    printf("\n");

    tim_sort(arr,len);

    printf("\n");
    printf("排序后：");
    printArray(arr,len);
    printf("\n");
    
    return 0; 	
} 