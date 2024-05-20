#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


//代码来源：https://www.jianshu.com/p/f80306282c7c

//函数声明
void printArray(char msg[],int arr[],int len);
void binary_insert(int a[],int low ,int high,int end);
int merge_compute_minrun(int n);
void binary_insert(int a[],int low ,int high,int end);
int merge_compute_minrun(int n);
int count_run(int a[],int low,int high);
void reverse_range(int a[],int low,int high);
int gallop_left(int key,int *a,int len,int offset);
int gallop_right(int key,int *a,int len,int offset);
void merge_lo(struct MergeState *ms,struct sortslice ssa,struct sortslice ssb);
void merge_hi(struct MergeState *ms,struct sortslice ssa,struct sortslice ssb);
void merge_collapse(struct MergeState *ms);
void merge_force_collapse(struct MergeState *ms);

//最大栈大小
#define MAX_MERGE_PENDING 85
//判断数据顺序连续性的阈值
#define MIN_GALLOP 7
// 参与序列合并的最短长度
#define MIN_RUN_BOUND 64

//打印数组
void printArray(char msg[],int arr[],int len){
    printf("%s:",msg);
    for (int i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

//已排序的run
struct sortslice
{
    int *pos;
    int len;
};
//保存run栈状态
struct MergeState
{
    int n;              //run栈的个数
    int min_gallop;
    struct sortslice pending[MAX_MERGE_PENDING];
};
//二分插入排序
void binary_insert(int a[],int low ,int high,int end){
    for(int i=high+1;i<=end;i++){
        int left=low;
        int right=i-1;
        int temp=a[i];
        if(temp>=a[right]){
            continue;
        }
        while(left<=right){
            int mid = (left+right)/2;
            if(temp<a[mid]){
                right=mid-1;
            }else{
                left=mid+1;
            }
        }
        for(int j=i-1;j>=left;j--){
            a[j+1]=a[j];
        }
        a[left]=temp;
    }
}
//算出minrun,MIN_RUN_BOUND=64,minrun:[32,63]
int merge_compute_minrun(int n){
    int r=0;
    while(n>=MIN_RUN_BOUND){
        r|=n&1;
        n>>=1;
    }
    return n+r;
}
/*
count_run() returns the # of elements in the next run.  A run is either
"ascending", which means non-decreasing:

    a0 <= a1 <= a2 <= ...

or "descending", which means strictly decreasing:

    a0 > a1 > a2 > ...
通过非严格升序或者严格降序截取run块
low：截取的开始下标位置
high：截取的结束下标位置
*/
int count_run(int a[],int low,int high){
    //数组只存在一个元素的情况，当作是一个已排序好的数组;
    if(low==high){
        return 0;
    }
    int run_hi=low;
    if(a[low]<=a[low+1]){
        //非严格升序
        while(run_hi<high&&a[run_hi]<=a[run_hi+1]){
            run_hi++;
        }
    }else{
        //严格降序
        while(run_hi<high&&a[run_hi]>a[run_hi+1]){
            run_hi++;
        }
        //转为升序
        reverse_range(a,low,run_hi);
    }
    //返回下标偏移值
    return run_hi-low;
}
//反转数组
void reverse_range(int a[],int low,int high){
    while(low<high){
        int t=a[low];
        a[low++]=a[high];
        a[high--]=t;
    }
}
//合并指定位置i的run
void merge_at(struct MergeState *ms,int i){
    //序列a
    struct sortslice ssa=ms->pending[i];
    //序列b
    struct sortslice ssb=ms->pending[i+1];
    //合并a和b的run长度
    ms->pending[i].len=ssa.len+ssb.len;
    //如果i位置是序列a<=b+c，a<c 中的a 则合并a和b，c位置前移
    if(i==ms->n-3){
        ms->pending[i+1]=ms->pending[i+2];
    }
    --ms->n;
    //找到b[0]在序列a中的位置ka，那么a中ka前的元素都小等于b[0],ka后的元素都大于b[0]
    int ka = gallop_right(*ssb.pos, ssa.pos, ssa.len, 0);
    ssa.pos+=ka;
    ssa.len-=ka;
    if(ssa.len==0){
        return;
    }
    //找到a[len-1]在序列b中的位置kb,那么b中kb前的元素都小于a[len-1],kb后的元素都大等于a[len-1]
    int kb = gallop_left(ssa.pos[ssa.len-1], ssb.pos, ssb.len, ssb.len-1);
    ssb.len=kb;
    if(ssb.len==0){
        return;
    }
    if(ssa.len<=ssb.len){
        //a.len<b.len 则数组起始位置开始合并
        merge_lo(ms,ssa,ssb);
    }else{
        //a.len>b.len 则数组末尾位置开始合并
        merge_hi(ms,ssa,ssb);
    }

}
/*
在一个序列中，将一个指定的key，查找它应当插入的位置；如果序列中存在与key相同的值(一个或者多个)，那返回这些值中最左边的位置，保持原有数组相同元素顺序。
用于key所在的数组在数组*a前面；
查找的规则：先使用跳跃式模糊查找确定大概位置区间： fn(x)=fn(x-1)*2+1,x>=1，其中fn(1)=1；在用二分法查找精确定位：a[fn(x-1)]<key<a[fn(x)]
key：指定要查找的数值
*a：在数组a中查找key的位置
len：数组a长度
offset：数组a中的偏移值，表示从offset开始查找
*/
int gallop_left(int key,int *a,int len,int offset){
    int lastofs=0;
    int ofs=1;
    //跳跃式模糊查找确定大概位置
    //key大于a[offset]所在值，那么key位置肯定大于offset
    if(key>*(a+offset)){
        //相对与offset最大偏移值，实际位置为offset+ofs,ofs<=maxofs
        const int maxofs=len-offset;
        while(ofs<maxofs && key > *(a+offset+ofs)){
            lastofs=ofs;
            ofs=(ofs<<1)+1;
            if(ofs<=0){
                ofs=maxofs;
            }
        }
        if(ofs>maxofs){
            ofs=maxofs;
        }
        lastofs+=offset;
        ofs+=offset;
    }else{
         //key小于于a[offset]所在值，那么key位置肯定小于offset,所以下标要前移ofs
          //相对与offset最大偏移值，实际位置为offset-ofs,ofs<=maxofs
        const int maxofs=offset+1;
        while(ofs<maxofs && key <= *(a+offset-ofs)){
            lastofs=ofs;
            ofs=(ofs<<1)+1;
            if(ofs<=0){
                ofs=maxofs;
            }
        }
        if(ofs>maxofs){
            ofs=maxofs;
        }
        //转换数据确保lastofs<ofs,并且key位于区间[lastofs,ofs]
        int k=lastofs;
        lastofs=offset-ofs;
        ofs=offset-k;
    }
    ++lastofs;
    //二分法查找精确定位位置:[lastofs,ofs]
    while(lastofs<ofs){
        int m = lastofs+((ofs-lastofs)>>1);
        if(key>a[m]){
            lastofs=m+1;
        }else{
            ofs=m;
        }
    }
    return ofs;
}

/*
在一个序列中，将一个指定的key，查找它应当插入的位置；如果序列中存在与key相同的值(一个或者多个)，那返回这些值中最右边的位置，保持原有数组相同元素顺序。
用于key所在的数组在数组*a后面；
查找的规则：先使用跳跃式模糊查找确定大概位置区间： fn(x)=fn(x-1)*2+1,x>=1，其中fn(1)=1；在用二分法查找精确定位：a[fn(x-1)]<key<a[fn(x)]
key：指定要查找的数值
*a：在数组a中查找key的位置
len：数组a长度
offset：数组a中的偏移值，表示从offset开始查找
*/
int gallop_right(int key,int *a,int len,int offset){
//ssa.len<=ssb.len //ssa和ssb是连续的数组
    int lastofs=0;
    int ofs=1;
     //key小于于a[offset]所在值，那么key位置肯定小于offset,所以下标要前移ofs
    if(key<*(a+offset)){
        //相对于offset最大偏移值，实际位置为offset-ofs,ofs<=maxofs
        const int maxofs=offset+1;
        while(ofs<maxofs && key<*(a+offset-ofs)){
            lastofs=ofs;
            ofs=(ofs<<1)+1;
            if(ofs<=0){ //int overflow
                ofs=maxofs;
            }
        }
        if(ofs>maxofs){
            ofs=maxofs;
        }
        //转换数据确保lastofs<ofs,并且key位于区间[lastofs,ofs]
        int k=lastofs;
        lastofs=offset-ofs;
        ofs=offset-k;
    }else{
        //key大于a[offset]所在值，那么key位置肯定大于offset
        //相对与offset最大偏移值，实际位置为offset+ofs,ofs<=maxofs
        const int maxofs=len-offset;
        while(ofs<maxofs && key>=*(a+offset+ofs)){
            lastofs=ofs;
            ofs=(ofs<<1)+1;
            if(ofs<=0){ //int overflow
                ofs=maxofs;
            }
        }
        if(ofs>maxofs){
            ofs=maxofs;
        }
        lastofs+=offset;
        ofs+=offset;
    }
    ++lastofs;
    //二分法查找精确定位位置:[lastofs,ofs]
    while(lastofs<ofs){
        int m=lastofs+((ofs-lastofs)>>1);
        if(key<a[m]){
            ofs=m;
        }else{
            lastofs=m+1;
        }
    }
    return ofs;
}
/*
ssa.len<=ssb.len 则数组起始位置开始合并,从小到大升序排序
*/
void merge_lo(struct MergeState *ms,struct sortslice ssa,struct sortslice ssb){
    int *a = ssa.pos;
    int *b = ssb.pos;
    int len_a=ssa.len;
    int len_b=ssb.len;
    int a_size=len_a * sizeof(int);
    //申请一个ssa.len的临时数组temp
    int *temp=(int*) malloc(a_size);
    //把数组ssa的数据拷贝到临时数组temp
    memcpy(temp,a,a_size);
    //临时数组下标指针
    int temp_cursor=0;
    //数组b的下标指针
    int b_cursor=0;
    //保存结果的下标指针,其首地址应该是ssa.pos，终点地址应该是ssa[ssa.len+ssb.len-1].pos,即数组起始位置0开始合并
    int dest=0;
    //通过gallop后我们可以确定b[0]小于数组a中的所有元素，可以直接把b[0]放置到下标0;a[len-1]大于数组b中所有元素
    a[dest++]=b[b_cursor++];
    //放置后数组b的长度自动减小1
    --len_b;
    //如果数组b只有一个元素，那么a中所有元素都比b的大，把a序列元素放置到b[0]后即可
    if(len_b==0){
        memcpy(&a[dest],temp,a_size);
        return;
    }
    //a数组只剩下一个元素的，那么这个元素a[len-1]比b中所有元素都大，所有把剩下的b元素拷贝到dest位置后，把a[len-1]放置在末尾即可
    if(len_a==1){
        memcpy(&a[dest],&b[b_cursor],len_b*sizeof(int));
        a[dest+len_b]=temp[temp_cursor];
        return;
    }
    //连续性阈值
    int min_gallop=ms->min_gallop;
    while(1){
        int acount=0;//序列a比序列b连续大的次数
        int bcount=0;//序列b比序列a连续大的次数
        //归并排序
        do{
            if(b[b_cursor]<temp[temp_cursor]){
                a[dest++]=b[b_cursor++];
                ++bcount;
                acount=0;
                --len_b;
                if(len_b==0){
                    goto Last;
                }
            }else{
                a[dest++]=temp[temp_cursor++];
                acount++;
                bcount=0;
                --len_a;
                if(len_a==1){
                    goto Last;
                }
            }
        }while((acount|bcount)<min_gallop);//数组连续性差，继续使用归并

        ++min_gallop;

        /*
         执行到这里，猜测数据连续性较好
         先使用gallop_right查找b[b_cursor]在a的下标位置k,k前面的元素都会比b[b_cursor]小,则把k前面连续的元素copy到dest后即可，在追加放置b[b_cursor]；
         然后使用gallop_left查找temp[temp_cursor](实际是数组a[temp_cursor])在b的下标位置k，k前面的元素都会比temp[temp_cursor]小,则把k前面连续的元素copy到dest后即可，在追加放置temp[temp_cursor]；
        */
        do{
            //猜测数据连续性较好，减少阈值，使之，更容易使用连续copy方法提高性能
            min_gallop-=(min_gallop>1);
            ms->min_gallop=min_gallop;
            acount = gallop_right(b[b_cursor],&temp[temp_cursor],len_a,0);
            if(acount>0){
                memcpy(&a[dest],&temp[temp_cursor],acount*sizeof(int));
                dest+=acount;
                temp_cursor+=acount;
                len_a-=acount;
                if(len_a==1){
                    goto Last;
                }
            }
            a[dest++]=b[b_cursor++];
            --len_b;
            if(len_b==0){
                goto Last;
            }
            bcount=gallop_left(temp[temp_cursor],&b[b_cursor],len_b,0);
            if(bcount!=0){
                memcpy(&a[dest],&b[b_cursor],bcount*sizeof(int));
                dest+=bcount;
                b_cursor+=bcount;
                len_b-=bcount;
                if(len_b==0){
                    goto Last;
                }
            }
            a[dest++]=temp[temp_cursor++];
            --len_a;
            if(len_a==1){
                goto Last;
            }
        }while(acount>=MIN_GALLOP || bcount>=MIN_GALLOP);//数组连续性好，继续这样处理
        //数据连续性不好，增加阈值
        ++min_gallop;
        ms->min_gallop=min_gallop;
    }
    Last:
        /*
        通过gallop后我们可以确定b[0]小于数组a中的所有元素，a[len-1]大于数组b中所有元素
        所以执行到这里存在两种情况：
            len_a=1,len_b>=1,剩下的b元素是最小的数值，拷贝到dest后，追加放置a[len-1]；
            len_b=0;len_a>=1,剩下的a元素都是大于b的连续元素，拷贝到目标数组dest后；
        */
        if(len_a==1){
            memcpy(&a[dest],&b[b_cursor],len_b*sizeof(int));
            a[dest+len_b]=temp[temp_cursor];
        }else{
            memcpy(&a[dest],&temp[temp_cursor],len_a*sizeof(int));
        }
        free(temp);
}
/*
ssa.len>ssb.len 则数组末尾位置开始合并,从大到小降序排序
*/
void merge_hi(struct MergeState *ms,struct sortslice ssa,struct sortslice ssb){
    int *a = ssa.pos;
    int *b = ssb.pos;
    int len_a=ssa.len;
    int len_b=ssb.len;
    int b_size=len_b * sizeof(int);
    //申请一个ssb.len的临时数组temp
    int *temp=(int*) malloc(b_size);
    //把数组ssb的数据拷贝到临时数组temp
    memcpy(temp,b,b_size);
    //临时数组下标指针
    int temp_cursor=len_b-1;
    //数组a的下标指针
    int a_cursor=len_a-1;
    //保存结果的下标指针,其首地址应该是ssa[ssa.len+ssb.len-1].pos，终点地址应该是ssa[0].pos,即数组末尾位置b[len-1]开始合并
    int dest=len_a+len_b-1;
    //通过gallop后我们可以确定a[len-1]大于数组b中的所有元素，可以直接把a[len-1]放置到下标dest;b[0]小于数组a中所有元素
    a[dest--]=a[a_cursor--];
    //放置后数组a的长度自动减小1
    --len_a;
    //如果数组a只有一个元素，那么b中所有元素都比a的小，把b序列元素放置到a[len-1]前即可
    if(len_a==0){
        memcpy(a,temp,b_size);
        return;
    }
    //b数组只剩下一个元素的，那么这个元素b[0]比a中所有元素都小，所有把剩下的a元素拷贝到dest位置前，把b[0]放置在起始位置即可
    if(len_b==1){
        memmove(a+1,a,len_a*sizeof(int));
        a[0]=temp[temp_cursor];
        return;
    }
    //连续性阈值
    int min_gallop=ms->min_gallop;
    while(1){
        int acount=0;//序列a比序列b连续大的次数
        int bcount=0;//序列b比序列a连续大的次数
        //归并排序
        do{
            if(temp[temp_cursor]>=a[a_cursor]){
                a[dest--]=temp[temp_cursor--];
                bcount++;
                acount=0;
                --len_b;
                //b[0]比a里所有的元素小，直接拷贝到数组头部
                if(len_b==1){
                    goto Last;
                }
            }else{
                a[dest--]=a[a_cursor--];
                bcount=0;
                acount++;
                --len_a;
                if(len_a==0){
                    goto Last;
                }
            }
        }while((acount|bcount)<min_gallop);//数组连续性差，继续使用归并

        ++min_gallop;

        /*
         执行到这里，猜测数据连续性较好
        */
        do{
            //猜测数据连续性较好，减少阈值，使之，更容易使用连续copy方法提高性能
            min_gallop-=(min_gallop>1);
            ms->min_gallop=min_gallop;
            //查找temp[temp_cursor]在a数组的位置，那么a数组中此位置k后的所有元素都比temp[temp_cursor]大,则把k后面连续的元素copy到dest前即可，在dest-1放置temp[temp_cursor]；
            acount=len_a-gallop_right(temp[temp_cursor],a,len_a,len_a-1);
            if(acount>0){
                dest-=acount;
                a_cursor-=acount;
                len_a-=acount;
                memmove(&a[dest+1],&a[a_cursor+1],acount*sizeof(int));
                if(len_a==0){
                    goto Last;
                }
            }
            a[dest--]=temp[temp_cursor--];
            --len_b;
            if(len_b==1){
                goto Last;
            }
             //查找a[a_cursor]在temp数组的位置k，那么temp数组中此位置k后的所有元素都比a[a_cursor]大,则把k后面连续的元素copy到dest前即可，在dest-1放置a[a_cursor]；
            bcount=len_b-gallop_left(a[a_cursor],temp,len_b,len_b-1);
            if(bcount>0){
                dest-=bcount;
                temp_cursor-=bcount;
                len_b-=bcount;
                memcpy(&a[dest+1],&temp[temp_cursor+1],bcount*sizeof(int));
                if(len_b==1){
                    goto Last;
                }
            }
            a[dest--]=a[a_cursor--];
            --len_a;
            if(len_a==0){
                goto Last;
            }
        }while(acount>=MIN_GALLOP || bcount>=MIN_GALLOP);
        //数据连续性不好，增加阈值
        ++min_gallop;
        ms->min_gallop=min_gallop;
    }
    Last:
        /*
        通过gallop后我们可以确定b[0]小于数组a中的所有元素，a[len-1]大于数组b中所有元素
        所以执行到这里存在两种情况：
            len_b=1,len_a>=1,剩下的a元素是最大的数值，放置到目标数组末尾即可,把剩下的数组b元素放在目标数据起始位置；
            len_a=0;len_b>=1,剩下的b元素都是小于a的连续元素，拷贝到目标数组dest前；
        */
        if(len_b==1){
            memmove(&a[dest-(len_a-1)],&a[0],len_a*sizeof(int));
            a[0]=temp[temp_cursor];
        }else{
            memcpy(&a[dest-(len_b-1)],&temp[0],len_b*sizeof(int));
        }
        free(temp);
}
/*
合并run使之满足：  A > B+C ；B > C
如果A <= B+C,A和C中更小的和B合并;
如果只有两个run:A和B，那么A<=B时，A和B合并
*/
void merge_collapse(struct MergeState *ms){
    struct sortslice *p=ms->pending;
    while(ms->n>1){
        int n=ms->n-2;
        //如果A <= B+C,A和C中更小的和B合并;
        if((n>0 && p[n-1].len <= p[n].len + p[n+1].len) ||
           //解决timsort的bug
           (n>1 && p[n-2].len <= p[n-1].len + p[n].len)){
               if(p[n-1].len < p[n+1].len){
                --n;
               }
               merge_at(ms,n);
           }else if(p[n].len<=p[n+1].len){ //那么A<=B时，A和B合并
               merge_at(ms,n);
           }else{
               break;
           }
    }
}
//最后合并栈中所有run
void merge_force_collapse(struct MergeState *ms){
    struct sortslice *p=ms->pending;
    while(ms->n>1){
        int n=ms->n-2;
        if(n>0&&p[n-1].len<p[n+1].len){
            --n;
        }
        merge_at(ms,n);
    }
}
//timsort入口
void tim_sort(int a[],int len){
    if(len<2){
        return;
    }
    int remain_len=len;
    struct MergeState ms;
    ms.n=0;
    ms.min_gallop=MIN_GALLOP;
    //算出minrun
    int minrun = merge_compute_minrun(len);
    printf("minrun:%d\n\n",minrun);
    //长度小于minrun直接用二分插入排序
    if(len<=minrun){
        //偏移值,offset+1就是实际长度
        int init_offset=count_run(a,0,len-1);
        binary_insert(a,0,init_offset,len-1);
        return;
    }
    int low=0,high=len-1,no=0;
    while(remain_len>0){
        //找出非严格升序或者严格降序的run
        int offset=count_run(a,low,high);
        int runlen=offset+1;
        //如果run长度小于minrun使用二分插入排序使run的长度等于minrun
        if(runlen<minrun){
            int force=remain_len<=minrun?remain_len:minrun;
            binary_insert(a,low,low+offset,low+force-1);
            runlen=force;
        }
        //run入栈
        ms.pending[ms.n].pos=&a[low];
        ms.pending[ms.n].len=runlen;
        //打印栈
        printf("stack[%d].len=%d ",no++,runlen);
        printArray("栈内容",&a[low],runlen);
        printf("\n");
        ms.n++;
        //合并run
        merge_collapse(&ms);
        low+=runlen;
        remain_len-=runlen;
    }
    //合并剩下的run，直至剩下最后一个
    merge_force_collapse(&ms);
}

int main()
{
    int len=256;
    int arr[len];
    srand((unsigned)time(NULL));
    //随机生成长度为"len"的数组
    for(int i=0;i<len;i++){
        arr[i]=rand()%256;
    }
    printArray("未排序前",arr,len);
    printf("\n");
    tim_sort(arr,len);
    printf("\n");
    printArray("在排序后",arr,len);
    //防止windows下控制台窗口闪退
    // int s;
    // scanf("%d",&s);
    return 0;
}
