#include <stdio.h>
#include <stdlib.h>

/*学习资料：b站up(哈哈哈哈栋)
一.定义规则：1）根节点和所有外部节点（空叶子结点）都是黑色
            2）根到外部节点的路径上没有2个红色
            3）所有根到外部结点的路径上，黑色结点个数相同
二.操作：1.插入：1）插入新节点的颜色判断？？？ 
                    1.1）策略1是插入的新节点及其孩子全部是黑色（规则1.2不破坏，规则3一定破坏）
                    1.2）策略2是插入的新节点是红色，孩子是黑色（规则1.3不破坏，规则2可能破坏）
                            如果父节点是红色，规则2会破坏，需要调整；
                            如果父节点是黑色，规则2不会破坏，不用调整   
                    1.3）综合考虑：插入新节点的策略是策略2
                    note：如果插入的节点是根节点，这种情况单独考虑，直接设置成黑色即可，这里主要讨论的是非根节点的情形
                2）选择策略2后，如果需要调整？？？怎么调整---不同失衡情形不同调整策略
                    2.1）失衡类型：LLr /LLb /LRr /LRb        /RLr /RLb /RRr /RRb
                        (插入节点的父节点pu是左/右孩子；插入的新结点u是父节点的左/右孩子；叔叔节点y颜色)
                        针对8种情形：前4和后4是对称的；  1.3（XXr型）只需变色调整；   2.4(XXb型)需要变色+左右旋调整
                    先定义几个标识，插入节点为u,父节点为pu,，爷爷节点为gu,叔叔结点为y  
                    2.2）1.3（XXr型）调整步骤：pu变黑色，y变黑色，gu变红色 ---gu变成新的u，在判断失衡类型调整
                    2.3）LLb调整：pu变黑色，gu变红色，对gu进行右旋
                    2.4）LRb调整：pu当成u，对u进行左旋，就变成了LLb型，在按照LLb型策略调整

*/

#define RED   1
#define BLACK 2
typedef  int KEY_TYPE;

//定义红黑树的结点的结构体
typedef struct _rbtree_node{
    unsigned char color;         //红色是1，黑色是2
    struct _rbtree_node* right;  //指向右孩子的指针
    struct _rbtree_node* left;   //指向左孩子的指针
    struct _rbtree_node* parent; //指向父母的指针
    KEY_TYPE key;                //保存的数据
    void* value;                 //这里用不到
}rbtree_node;

//定义一个结构体，保存外部节点和根结点的指针
typedef struct _rbtree{
    rbtree_node* root;  //指向根结点的指针
    rbtree_node* nil;   //指向外部（非空叶子结点）结点的指针
}rbtree;

//创建并初始化节点
rbtree_node* newNode(rbtree* T, KEY_TYPE key){
    rbtree_node* node = (rbtree_node*)malloc(sizeof(rbtree_node));
    node->color   = RED;
    node->key     = key;
    node->value   = NULL;
    node->left    = T->nil;
    node->right   = T->nil;
    node->parent  = T->nil;

    return node;
}

//定义左旋函数:T是根节点，
void leftRotate(rbtree* T,rbtree_node* root){
     rbtree_node* newroot = root->right;
     rbtree_node* T2 = newroot->left;
     root->right = T2;
     //修改父节点，谁的父节点改变了？T2，newroot,root
       //修改T2结点的父结点
     if(T2->parent != NULL){
        T2->parent = root;
     }
       //修改newroot的父节点
     newroot->parent = root->parent;
       //修改root的父节点
          //原来的root就是树根     这里为什么是这么判断
     if(root->parent == T->nil){               //T->nil就是NULL指针的意思
        T->root = newroot;
     }else if(root == root->parent->left){     //root是父节点的左子树情况
        root->parent->left = newroot;
     }else if(root == root->parent->right){    //root是父节点的右子树情况
        root->parent->right = newroot;
     }
     //旧根变成新根的左节点
     newroot->left = root;
     root->parent = newroot;
}

//定义右旋函数:T是根节点，
void rightRotate(rbtree* T,rbtree_node* root){
     rbtree_node* newroot = root->left;
     rbtree_node* T2 = newroot->right;
     root->left = T2;
     //修改父节点，谁的父节点改变了？T2，newroot,root
       //修改T2结点的父结点
     if(T2->parent != NULL){
        T2->parent = root;
     }
       //修改newroot的父节点
     newroot->parent = root->parent;
       //修改root的父节点
         //原来的root就是树根     这里为什么是这么判断
     if(root->parent == T->nil){               //T->nil就是NULL指针的意思
        T->root = newroot;
     }else if(root == root->parent->left){     //root是父节点的左子树情况
        root->parent->left = newroot;
     }else if(root == root->parent->right){    //root是父节点的右子树情况
        root->parent->right = newroot;
     }
     //旧根变成新根的右节点
     newroot->right = root;
     root->parent = newroot;
}

//失衡调整函数
void rbtree_insert_fixup(rbtree* T,rbtree_node* u){
    //1.只有父节点是红才需要调整
    while(u->parent->color == RED){
        //1.1父节点是祖父节点的左孩子情况：包括  LXX型  4种情况在内
        if(u->parent == u->parent->parent->left){
            //定义叔叔结点
            rbtree_node* y = u->parent->parent->right;
            //1.1.1在细分情况:  LXr型   都是只变色处理
            //（LXr型）调整步骤：pu变黑色，y变黑色，gu变红色 ---gu变成新的u，在判断失衡类型调整
            if(y->color == RED){
                u->parent->color = BLACK;
                y->color = BLACK;
                u->parent->parent->color = RED;

                u = u->parent->parent;    //这里为啥不用再递归修正?  已经递归了，下一轮判断的u就是新u了，
            }
            //1.1.2.LXb型
            else if(y->color == BLACK){
                //1.1.2.1.LRb情况：pu当成u，对u进行左旋，就变成了LLb型，在按照LLb型策略调整
                if(u == u->parent->right){
                    u = u->parent;
                    leftRotate(T,u);   
                }
                //1.1.2.2.到这就变成了LLb情况了，底下的LLb调整包括了LRb转变为LLb,和原来就是LLb情况
                //LLb情况 ：pu变黑色，gu变红色，对gu进行右旋
                    u->parent->color = BLACK;
                    u->parent->parent->color = RED;
                    rightRotate(T,u->parent->parent);   
            }
        }
        //1.2在考虑Rxx情况
        else if(u->parent == u->parent->parent->right){
            //定义叔叔结点
            rbtree_node* y = u->parent->parent->left;
            //在细分情况:  RXr型   都是只变色处理
            //（RXr型）调整步骤：pu变黑色，y变黑色，gu变红色 ---gu变成新的u，在判断失衡类型调整
            if(y->color == RED){
                u->parent->color = BLACK;
                y->color = BLACK;
                u->parent->parent->color = RED;

                u = u->parent->parent;     //这里为啥不用再递归修正?  已经递归了，下一轮判断的u就是新u了，
            }
            //RXb型
            else if(y->color == BLACK){
                //RLb情况：pu当成u，对u进行右旋，就变成了RRb型，在按照RRb型策略调整
                if(u == u->parent->left){
                    u = u->parent;
                    rightRotate(T,u);   
                }
                //到这就变成了RRb情况了，底下的RLb调整包括了RLb转变为RRb,和原来就是RRb情况
                //RRb情况 ：pu变黑色，gu变红色，对gu进行左旋
                    u->parent->color = BLACK;
                    u->parent->parent->color = RED;
                    leftRotate(T,u->parent->parent);   
            }
        }
    }
    T->root->color = BLACK;     //包括插入的节点是根节点的情况

}

//定义插入节点函数,z是需要插入的节点
void rbtree_insert(rbtree* T,rbtree_node* z){
    rbtree_node* y = T->nil;   //定义一个空指针，   
    rbtree_node* tem = T->root;

    //找出插入节点的位置
    while(tem != T->nil){        //tem != NULL  error;
        y = tem;                    //执行完之后y会指向插入结点的父节点
        if( z->key < tem->key )      { tem = tem->left; }        //往左边找
        else if(z->key > tem->key )  { tem = tem->right;}        //往右边找
        else if(z->key == tem->key)  { return;}                 //已经有一样的数据，不插入
    }

    //执行完这个循环，tem指向插入节点的位置，y指向插入节点的父节点
    z->parent = y;
    //插入y的左节点还是有节点
    if(y == T->nil)    { T->root = z; }        //如果空树情况，直接插入到树根为止
    else if(z->key > y->key)  {y->right = z;}  //z插入y的右孩子位置
    else if(z->key < y->key)  {y->left = z;}   //z插入y的左孩子位置

    //插入节点后判断是否进行调整
    rbtree_insert_fixup(T,z);

}


//先序遍历函数
void pre_traversal(rbtree* T,rbtree_node* node){
    if(node == T->nil) { return; }

    printf("key:%d  color:%d\n",node->key,node->color);
    pre_traversal(T,node->left);
    pre_traversal(T,node->right);
}

//中序遍历
void mid_traversal(rbtree* T,rbtree_node* node){
    if(node == T->nil) { return; }

    mid_traversal(T,node->left);
    printf("key:%d  color:%d\n",node->key,node->color);
    mid_traversal(T,node->right);
}

int main(){
    int array[6] = {10,50,60,62,65,70};
    rbtree* T = (rbtree*)malloc(sizeof(rbtree));

    //定义外部节点
    T->nil = (rbtree_node*)malloc(sizeof(rbtree_node));
    T->nil->color = BLACK;
    T->root = T->nil;

    //开始插入节点
    rbtree_node* node = T->nil;
    for(int i = 0; i < 6; i++){
        node = newNode(T,array[i]);
        rbtree_insert(T,node);
    }
    
    //打印结果
    printf("----------------中序遍历结果----------------\n");
    mid_traversal(T,T->root);
    printf("----------------先序遍历结果----------------\n");
    pre_traversal(T,T->root);
    printf("----------------end----------------\n");

    return 0;
}
