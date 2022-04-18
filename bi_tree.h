#ifndef __BI_TREE_H__
#define __BI_TREE_H__

#include "stitch_algorithm.h"

typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
typedef BiTree SElemType;

#include "stack.h"
#include <stdio.h>

Status InitBiTree(BiTree &T){
	T = NULL;
}

void DestroyBiTree(BiTree &T){
	if (T == NULL) return;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	free(T);
}

Status CreateBiTree(BiTree &T, char* str){
	static int i=0;
	char ch = str[i++];
	if (ch=='.') T=NULL;
	else {
		if (!(T = (BiTNode*) malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data = ch;
		CreateBiTree(T->lchild,str);
		CreateBiTree(T->rchild,str);
	}
	return OK;
}

Status Visit(ElemType e){
	printf("%c ",e);//默认e为char类型 
	return OK;
}

Status FindNode(BiTree T, ElemType e){
	if (T){
		if (T->data != e){
			if (!FindNode(T->lchild,e))
				if (!FindNode(T->rchild,e)) return ERROR;
				else return OK;
			else return OK; 
		}
		else return OK;
	} else return ERROR;
}

int BiTHeight(BiTree T){
	if (T){
		int m = BiTHeight(T->lchild);
		int n = BiTHeight(T->rchild);
		return (m>n)?(m+1):(n+1);
	}
	else return 0;
}

Status PreOrderTraverse(BiTree T, Status (*Visit)(ElemType e)){
	if (T){
		if (Visit(T->data))
			if (PreOrderTraverse(T->lchild,Visit))
				if (PreOrderTraverse(T->rchild,Visit)) return OK;
		return ERROR;
	} else return OK;
}

Status InOrderTraverse(BiTree T, Status (*Visit)(ElemType e)){
	SqStack S;
	BiTree p;
	InitStack(S);
	p = T;
	while (p||!EmptyStack(S)){
		if (p){
			Push(S,p);
			p = p->lchild;
		}
		else {
			Pop(S,p);
			if (!Visit(p->data))
				return ERROR;
			p = p->rchild;
		}
	}
	return OK;
}

Status PostOrderTraverse(BiTree T, Status (*Visit)(ElemType e)){
	if (T){
		if (PostOrderTraverse(T->lchild,Visit))
			if (PostOrderTraverse(T->rchild,Visit))
				if (Visit(T->data)) return OK;
	return ERROR;
	} else return OK;
}

#endif
