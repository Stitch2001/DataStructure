#ifndef __BST_H__
#define __BST_H__

#include "stitch_algorithm.h"
#include <stdio.h>

#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))

typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

//二叉排序树算法 
Status Delete(BiTree &p)/*从二叉排序树中删除*p结点*/
{
	//从二叉排序树中删除结点p，并重接它的左或右子树
	BiTree q, s;
	if (!p->rchild) { // 右子树空则只需重接它的左子树
		q=p;p=p->lchild;free(q);
	} 
	else if (!p->lchild) { //左子树空则只需重接它的右子树
		q=p;p=p->rchild;free(q);
	}
	else { // 左右子树均不空
		q=p;s=p->lchild;
		while (s->rchild){ // 向右到尽头
			q=s;s=s->rchild;
		}
		p->data = s->data; 
		if (q != p) 
			q->rchild = s->lchild; //重接*q的右子树，s可能有左孩子
		else //s一开始没有右子树的情况
			q->lchild = s->lchild; //重接*q的左子树
		free(s);
	}
	return TRUE;
}

Status DeleteBST(BiTree &T, ElemType key)/*在树中删除关键字为k的结点*/
{
	//若二叉排序树T中存在关键字等于key的数据元素时，
	//则删除该数据元素结点p，并返回TRUE；否则返回FALSE
	if (!T)
		return FALSE;//不存在关键字等于key的数据元素
	else {
		if (EQ(key,T->data))//找到关键字等于key的数据元素 
			return Delete(T);
		else if (LT(key,T->data))
			return DeleteBST(T->lchild,key);
		else
			return DeleteBST(T->rchild,key);
	}
}

int isPrint = FALSE;
Status SearchBST1(BiTree T,ElemType key)/*以非递归方式输出从根结点到查找到的结点的路径*/
{
	BiTree p = T;
	while (!EQ(key,p->data) && p){
		if (isPrint) printf("%d->",p->data);
		if (LT(key,p->data)){
			p = p->lchild;
		}
		else {
			p = p->rchild;
		}
	}
	if (!p){ //查找不成功，或树为空树，空树时p返回值为Null
		if (isPrint) printf("NULL\n");
		return FALSE;
	}
	else {
		if (isPrint) printf("%d\n",p->data);
		return TRUE;
	}
}

Status SearchBST2(BiTree T,ElemType key,BiTree f,BiTree &p)/*以递归方式输出从根结点到查找到的结点的路径*/	
{
	//（被调用函数）在根指针T所指二叉排序树中递归地查找其关键字等于
	// key的数据元素， 若查找成功，则指针p指向该数据元素结点，并返
	// 回TRUE， 否则指针p指向查找路径上访问的最后一个结点并返回
	// FALSE， 指针f指向T的双亲，其初始调用值为根结点的双亲NULL
	if (!T){ //查找不成功，或树为空树，空树时p返回值为Null
		if (isPrint) printf("NULL\n");
		p = f; //查找不成功时p指向查找路径上访问的最后一个点
		return FALSE;
	}
	else if (EQ(key,T->data)){ //查找成功
		if (isPrint) printf("%d\n",T->data);
		p = T; //T值随着递归的进程不断变化
		return TRUE;
	}
	else if (LT(key,T->data)){
		if (isPrint) printf("%d->",T->data);
		return SearchBST2(T->lchild,key,T,p);
	}
	else{
		if (isPrint) printf("%d->",T->data);
		return SearchBST2(T->rchild,key,T,p);
	}
}

Status InsertBST(BiTree &T,ElemType e)/*在以*p为根结点的BST中插入一个关键字为k的结点*/
{
	BiTree p = T,s;
	if (!SearchBST2(T,e,NULL,p)){
		//查找不成功
		s = (BiTree)malloc(sizeof(BiTNode)); 
		s->data = e;
		s->lchild = s->rchild = NULL;
		if (!p) //T为空树
			T=s; //插入s为新的根结点
		else if (LT(e, p->data))
			p->lchild = s; //插入s为左孩子
		else
			p->rchild = s; //插入s为右孩子
		return TRUE;
	}
	else
		return FALSE; //树中已有关键字相同的结点，不再插入
}

void DispBST(BiTree T)	/*以括号表示法输出二叉排序树bt*/
{
	printf("%d",T->data);
	if (T->lchild || T->rchild){
    	printf("(");
		if (T->lchild){
	        DispBST(T->lchild);
	    }
	    if (T->rchild){
		    printf(",");
	        DispBST(T->rchild);
	    }
	    printf(")");
	}
}

BiTree CreateBST(ElemType A[],int n)/*由数组A中的关键字建立一棵二叉排序树*/
{
	BiTree T = NULL;
	isPrint = FALSE;//关闭查找时的输出 
	int i;
	for (i=0;i<n;i++){
		printf("第%d步，插入%d:",i+1,A[i]);
		InsertBST(T,A[i]);
		DispBST(T);
		printf("\n");
	}
	return T;
}

void JudgeBST(BiTree T, int &isBST)	/*判断是否为BST*/
{
	//后序遍历各节点
	BiTree p = T;
	if (T->lchild){
		JudgeBST(T->lchild,isBST);
		if (p->data < T->lchild->data)
			isBST = FALSE;//根节点比左孩子节点小，不满足 
	}
	if (T->rchild){
		JudgeBST(T->rchild,isBST);
		if (p->data > T->rchild->data)
			isBST = FALSE;//根节点比右孩子节点大，不满足 
	}
}

#endif 
