#include <stdio.h>
#include <stdlib.h>

/*学习资料: Abdul_Bari && b站up:Tyrantlucifer
https://www.bilibili.com/video/BV1CU4y1G72e/?spm_id_from=333.788.recommend_more_video.-1&vd_source=017cc0a5f238638bc0ba4f55c269f5e8
https://www.bilibili.com/video/BV1W64y1z7jh?p=37
二叉搜索树--改进--AVL树    <--->   m叉搜索树--改进--B_Tree（m叉AVL树）---再改进--B+Tree树 (用于数据库DBMS,用于多级索引)*/

//操作有：插入节点，查找节点，删除节点

/*b树特点：1.术语，关键字key数量x,阶数m(m叉树，就是子节点的个数，参考二叉树),两者关系【向上取整（m/2）-1】 <= x <= m-1
          2.叶子结点都在同一层    3.父母亲至少有2子女    
操作：
1）插入操作：key数量>= m,要进行分裂操作--中间劈开，中间的关键字插入到父节点中，劈开的左右两边作为父节点的的两个孩子
2）查找：
3）删除：情形1：删除的key在非叶子结点：先把这个key的左孩子的最大值替换上去，然后按照叶子结点的删除流程
        情形2：删除的key在叶子结点
              2.1)叶子结点个数> 最小值，直接删除
              2.2）叶子结点个数==最小值：先去（找父母）借，借不到就合并
                怎么借：找父母借，借完后父母父母在从最边边的子结点借，如果借完子节点还可以满足最小值要求，可以借，
                                                     如果借完子节点不满足最小值，那么整个流程不能借，考虑合并
                怎么合并：（一般需要合并情况是，要删除的结点已经是最小值，兄弟结点也是最小值），
                    从父母节点拉一个key下来，和这个剩下的key一起合并到兄弟结点，父母节点在判断是否需要借/合并
*/

typedef struct Node{
    int level;                   //阶数m
    int keyNum;                  //关键字数量
    int childNum;                //孩子个数 
    int* keys;                   //关键字数组
    struct Node** children;      //孩子数组
    struct Node* parent;         //父母指针
}Node;

//初始化
Node* initNode(int level){
    Node* node   = (Node*)malloc(sizeof(Node));
    node->level  = level;
    node->keyNum = 0;
    node->childNum  = 0;
    node->keys      = (int*)malloc(sizeof(int) * (level+1));
    node->children  = (Node**)malloc(sizeof(Node*) * level);
    node->parent    = NULL;

    int i;
    for(i=0; i<level;i++){
        node->keys[i] = 0;
        node->children[i] = NULL;
    }
    node->keys[i] = 0;   //keys最后一个赋值，循环没有赋值到
    return node;
}

//找出在keys数组中插入data的位置index
int findSuiteIndex(Node* node, int data){
    int index;
    for(index=1; index <= node->keyNum; index++){
        if(data < node->keys[index])  { break; }
    }
    return index;
}

//插入时只能插入到叶子结点，所以需要找叶子结点
Node* findSuiteLeafNode(Node* root,int data){
    if(root->childNum == 0)  { return root; }    //只有根节点情况，直接插入
    else{
        int index = findSuiteIndex(root,data);
        return findSuiteLeafNode(root->children[index-1],data);
    }
}


//插入函数，
//参数说明：node是需要插入data的某个结点，root是整个Btree的根节点，因为插入数据过程可能改变BTree的根节点
void addData(Node* node,int data,Node** root){
    //找到插入合适位置
    int index = findSuiteIndex(node,data);
    //找到合适位置，keys数组中后面的key往后往后移动一位，然后插入key,keynum+1
    for(int i = node->keyNum; i >= index; i--){
        node->keys[i+1] = node->keys[i];
    }
    node->keys[index] = data;
    node->keyNum ++;
    //插入数据后判断是否分裂
    if(node->keyNum == node->level){
        //1.判断哪个keys[index]插入key
        int mid = (node->level)/2 + (node->level) % 2;
        //2.分裂
        //2.1找到index后左右劈开，生成左右孩子
        Node* Lchild = initNode(node->level);
        Node* Rchild = initNode(node->level);
        //2.2把分裂前数据赋值给到新孩子
        //2.2.1赋值keys数组给左右孩子
        for(int i=1; i<mid; i++){    //keys[0]是空的，key数据是从key[1]开始保存的
            Lchild->keys[i] = node->keys[i];
            Lchild->keyNum ++;
            /*   循环内可用递归实现
            addData(Lchild,node->keys[i],root);  */
        }
        for(int i = mid+1, j=1; i <= node->keyNum; i++ ){
            Rchild->keys[j] = node->keys[i];
            j++;
            Rchild->keyNum ++;
            /*   循环内可用递归实现
            addData(Rchild,node->keys[i],root);  */
        }
        //2.2.2把原来的孩子结点也需要一并给到新的孩子LChild结点
        for(int i = 0; i < mid;i++){
            //3.2.1先全部复制给过去
            Lchild->children[i] = node->children[i];
            //3.2.2更新孩子结点的父节点为LChild
            if(node->children[i] != NULL){
                node->children[i]->parent = Lchild;
                Lchild->childNum ++;
            }
        }
        //2.2.3把原来的孩子结点也需要一并给到新的孩子RChild结点
        for(int i = mid ,j=0; i < node->childNum; i++){
            //2.2.3.1先全部复制给过去
            Rchild->children[j] = node->children[i];
            j++;
            //2.2.3.2更新孩子结点的父节点为RChild
            if(node->children[i] != NULL){
                node->children[i]->parent = Rchild;
                Rchild->childNum ++;
            }
        }
        //3.完成分裂后，处理key[mid]升到父节点情况，   需要考虑到父节点里面的每个参数是否更新
        //3.1 node节点没有父节点情况
        if(node->parent == NULL){
            Node* newParent = initNode(node->level);
            addData(newParent,node->keys[mid],root);
            newParent->children[0] = Lchild;
            newParent->children[1] = Rchild;
            newParent->childNum = 2;
            Lchild->parent = newParent;
            Rchild->parent = newParent;
            *root = newParent;
        }
        //3.2node节点原本有父节点情况
        else{
            //3.2.1找到在父节点中插入的合适位置index,btree特点这里肯定是在后面插入数据的，所以不用再判断keys[index]后面的是否需要移动一位
            int index = findSuiteIndex(node->parent,node->keys[mid]);
            Lchild->parent = node->parent;
            Rchild->parent = node->parent;
            node->parent->children[index-1] = Lchild;
            //在childdren[]指向Rchild之前，需要先判断本事是否已有指针，如果有需要往后移动一位
            if(node->parent->children[index] != NULL ){
                for(int i = (node->parent->childNum)-1; i >= index; i--){
                    node->parent->children[i+1] = node->parent->children[i];
                }
            }
            node->parent->children[index] = Rchild;
            node->parent->childNum ++;                        //不用加2，因为本来指向node的childnum没有了
            addData(node->parent,node->keys[mid],root);       //root是二级指针，本身就是指向根节点的
          
        }
    }
}

//封装插入函数
void insert(Node** root ,int data){
    Node* node = findSuiteLeafNode(*root,data);
    addData(node,data,root);
}

//查找和删除待写

//打印函数
void printTree(Node* root){
    if(root != NULL){
        //打印根节点数据
        for(int i=1; i<=root->keyNum; i++){
            printf("%d ",root->keys[i]);
        }
        printf("\n");
        //打印根节点的孩子结点里面的数据
        for(int i=0; i<root->childNum; i++){
            printTree(root->children[i]);
        }    
    }   
}

int main(){
    Node* root = initNode(5);
    insert(&root,1);
    insert(&root,2);
    insert(&root,3);
    insert(&root,4);
    insert(&root,5);
    insert(&root,6);
    insert(&root,7);
    insert(&root,8);
    insert(&root,9);
    insert(&root,10);
    insert(&root,11);
    insert(&root,12);
    insert(&root,13);
    insert(&root,14);
    insert(&root,15);

    printTree(root);


    return 0;
}