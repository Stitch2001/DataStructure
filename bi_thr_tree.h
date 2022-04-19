#ifndef __BI_THR_TREE__
#define __BI_THR_TREE__

#include "stitch_algorithm.h"

typedef enum PointerTag{Link,Thread};
typedef struct BiThrNode{
	ElemType data;
	struct BiThrNode *lchild,*rchild;
	PointerTag LTag,RTag;
} BiThrNode, *BiThrTree;

Status InitThrBiTree(BiThrTree &T){
	T = NULL;
}

void DestroyThrBiTree(BiThrTree &T){
	if (T == NULL) return;
	if (T->LTag == Link) DestroyThrBiTree(T->lchild);
	if (T->RTag == Link) DestroyThrBiTree(T->rchild);
	free(T);
}

Status CreateBiThrTree(BiThrTree &T, char* str){
	static int i=0;
	char ch = str[i++];
	if (ch=='.') T=NULL;
	else {
		if (!(T = (BiThrNode*) malloc(sizeof(BiThrNode))))
			exit(OVERFLOW);
		T->data = ch;
		CreateBiThrTree(T->lchild,str);
		CreateBiThrTree(T->rchild,str);
	}
	return OK;
}

BiThrTree pre;

void PreThreading(BiThrTree p){
	if (p){
		if (!p->lchild) {
			p->LTag = Thread; p->lchild = pre;
		}
		if (!pre->rchild){
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		if (p->LTag != Thread)
			PreThreading(p->lchild);
		if (p->RTag != Thread)
			PreThreading(p->rchild);
	}
}

Status PreOrderThreading(BiThrTree &Thrt, BiThrTree T){
	if (!(Thrt = (BiThrTree) malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
	Thrt->data = '#';
	Thrt->LTag = Link; Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T) Thrt->lchild = Thrt;
	else {
		Thrt->lchild = T;
		pre = Thrt;
		PreThreading(T);
		pre->rchild = Thrt;pre->RTag = Thread;
		Thrt->rchild = pre;
	}
	return OK;
}

void InThreading(BiThrTree p){
	if (p){
		InThreading(p->lchild);
		if (!p->lchild) {
			p->LTag = Thread; p->lchild = pre;
		}
		if (!pre->rchild){
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}

Status InOrderThreading(BiThrTree &Thrt, BiThrTree T){
	if (!(Thrt = (BiThrTree) malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
	Thrt->LTag = Link; Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T) Thrt->lchild = Thrt;
	else {
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T);
		pre->rchild = Thrt;pre->RTag = Thread;
		Thrt->rchild = pre;
	}
	return OK;
}

Status Visit(ElemType e){
	printf("%c ",e);//默认e为char类型 
	return OK;
}

Status InOrderTraverse_Thr(BiThrTree T,Status(*Visit)(ElemType e)){
	BiThrTree p = T->lchild;
	while (p != T){
		while (p->LTag == Link) p = p->lchild;
		if (!Visit(p->data)) return ERROR;
		while (p->RTag == Thread && p->rchild != T){
			p = p->rchild; Visit(p->data);
		}
		p = p->rchild;
	}
	return OK;
}

Status PreOrderTraverse_Thr(BiThrTree T,Status(*Visit)(ElemType e)){
	if (T){
		if (!T->data) return ERROR;
		if (T->data != '#') Visit(T->data);
		if (T->LTag == Link)
			PreOrderTraverse_Thr(T->lchild,Visit);
		if (T->RTag == Link)
			PreOrderTraverse_Thr(T->rchild,Visit);
	}
	return OK;
}

#endif
