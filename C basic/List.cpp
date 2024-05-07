#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

//ͷ���+β��㶯̬����װ�ɺ����Ļ�ֻ��Ҫ����ͷָ�븳ֵ����������ͷָ�뼴�� 


typedef struct node{
	int date;
	struct node* pNext;
}NODE,*PNODE;  

//�������� 
PNODE creat_list(void);              //��������--β������ʽ 
void traverse_list(PNODE pHEAD);     //���� 
bool is_empty(PNODE pHead);         //�ж��Ƿ������ 
int length_list(PNODE pHead);       //�ж�������
void select_sort_list(PNODE pHead) ;    //����ѡ������ 
bool insert_list(PNODE ,int ,int ) ;   //�������
bool delete_list(PNODE pHead,int pos,int* val ); 
 
 

int main(void){
	
	PNODE pHead=NULL;
	pHead=creat_list();
	traverse_list(pHead);

    {               //�ж��Ƿ������ 
		if(is_empty(pHead))
		printf("�����ǿ�\n");
	else
	   printf("������\n");  }
	
	
	int len=length_list(pHead);
	printf("������Ϊ%d\n",len);
	
//	select_sort_list( pHead);
//	traverse_list(pHead);
	
	insert_list( pHead,3,33 );
	printf("����һ�����ݺ������������£�\n");
	traverse_list(pHead);
	
	int val;
	if(delete_list(pHead,4,&val )){
		printf("ɾ���ɹ���ɾ����Ԫ���ǣ�%d\n",val);
	}else{
		printf("ɾ��ʧ��\n"); 
	}
	printf("ɾ��һ�����ݺ������������£�\n");
	traverse_list(pHead);

	
	return 0;
} 


PNODE creat_list(void)
{
	int i,val,len;
	
    PNODE pHead=(PNODE)malloc(sizeof(NODE));  
    if(pHead==NULL){        //����ռ�ʧ�ܼ�� 
    	printf("����ʧ��,������ֹ");
		exit(-1);    
	}
	
	PNODE pTail=pHead;
    pTail->pNext=NULL;                            //��ʼerror��ԭ��  pTail=NULL
    
    printf("����ڵ������len=");
    scanf("%d",&len);
    
    for(i=0;i<len;i++){
    	printf("�����%d���������:",i+1);
    	scanf("%d",&val);
    	
    	PNODE pNew=(PNODE)malloc(sizeof(NODE) ); // �¼���Ľ������Ϊpnew,��������ݼ��뵽������ 
                	if(pNew==NULL){        //����ռ�ʧ�ܼ�� 
    				printf("����ʧ��,������ֹ");
					exit(-1);    
									}
	
		pNew->date =val;                //�������ɹ� 
		pTail->pNext=pNew;                      //errorʧ���� why 	
		pNew->pNext=NULL;
		pTail=pNew;                    //���������������Ϊ ptail;Ҳ��֤ptailָ��յ�ַ 
	
	}
    return pHead; 
}

void traverse_list(PNODE pHead)      //�������� 
{   
	PNODE p = pHead->pNext;
	while(p != NULL){
		printf("%d  ",p->date );
		p=p->pNext;
	
	}
	printf("\n");

}



bool is_empty(PNODE pHead){    //�ж��Ƿ�� 
	if(pHead->pNext ==NULL)
	    return true;
	else
	    return false;
	
}

int length_list(PNODE pHead)   //����������
{
	int len=0;
	PNODE p = pHead->pNext;
	while(p!= NULL){
		len++;
		p=p->pNext;
	}
	
	return len;
}

	
 void select_sort_list(PNODE pHead)        //����ѡ������ 
 {
 	 PNODE turn=pHead->pNext ;       //���������ͳ�ʼ�ڵ�
 	 PNODE move=turn->pNext; //�ӵڶ�����ʼ�ƶ��� 
	 PNODE max=turn;          // 
	
	 while(turn->pNext  != NULL) {    //��ѭ���������� ��ΪʲôҪָ�� turn->pNext������Ϊ����ʵ�ʲ���Ҫ��ô�� 
	 
	  while(move  != NULL) {        //��ѭ���ҳ����������λ��    
	  //Ϊʲô��ѭ��move->pnext !=0??  move�Ǹ���ַ��move->pnextָ������¸����ĵ�ַ 
	  	 	if(move->date > max->date ){
	  	 		max=move;               //max��¼�ľ�������㣬�����ǽṹ�� 
			   }	                 //�жϴ�С 
			move=move->pNext;         
	  }                              //�����ҳ�һ�������ֵ�� 
	  
	   //�ҳ����ֵ��ʼ���� 
	 	 if(max != turn)           //���һ��ʼ�������ֵ����ô���ý��� 
	 	 {
	 	 	NODE tem;
	 	 	tem.date  = turn->date ;
	 	 	turn->date = max->date ;
	 	 	max->date  = tem.date ;    // ���ݽ��� 
			   
		  }
	  //�����������һ���ж� 
		 turn=turn->pNext ;
		 move=turn->pNext;    //move����turn��һ����㣻����turn�Ѿ����¸�ֵ�ˣ� 
		 max=turn; 
	 }
 	
 }


//������� �� ��posλ�ò���valֵ 
bool insert_list(PNODE pHead,int pos,int val ) 
{
	int i=0;
	PNODE p=pHead; 
	//�ж��Ƿ���Բ���ڵ�
	if(pos<0)
	return false;
	
	while(i<pos-1 && p!=NULL){   //Ѱ�ҵ�i-1�����   i-1����p 
		i++;
		p=p->pNext; 
	} 
	
	if(p==NULL)    //δ�ҵ�i-1��λ�� 
	return false; 
	
	//�жϺ���Կ�ʼ���� 
	PNODE PNew=(PNODE)malloc(sizeof(NODE));
   				if (PNew==NULL){
					printf("�����ڴ�ʧ��\n");
					exit(-1);
								}
							
	PNew->date =val;
	PNew->pNext=p->pNext ;
	p->pNext =PNew;
	
	return true; 	
}  


//����ɾ��posλ�ý�� 
bool delete_list(PNODE pHead,int pos,int* val ) 
{
	int i=0;
	PNODE p=pHead; 
	
	if(pos<0)
	return false;
	
	while(i<pos-1 && p->pNext != NULL){     //�ҳ�ɾ����POSλ�õ�ǰһ�����λ�� ��POSǰһ��λ��Ϊp; 
		i++;
		p=p->pNext; 
	} 
	
	if(p->pNext == NULL)    //δ�ҵ�i-1��λ�� 
	return false; 
	
	//�жϺ���Կ�ʼɾ��
	PNODE q=p->pNext ;
	*val=q->date;  //���᷵��ɾ���ڵ��ֵ 
	
	p->pNext =p->pNext->pNext ;
	free(q);
	q=NULL;
	
	return true; 	
}

