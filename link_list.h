#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

#include "stitch_algorithm.h"

typedef struct Lnode{
	ElemType data;
	struct Lnode *next;
} LNode, *LinkList;

LinkList CreateList_L(){
	LinkList p,H;
	int i;
	H = (LinkList) malloc(sizeof(LNode));
	H->next = NULL;
	return H;
}

Status GetElem_L(LinkList L, int i, ElemType &e){
	LinkList p;
	p = L->next;
	int j=1;
	while (p && j<i){
		p = p->next;
		++j;
	}
	if (!p || j>i)
		return ERROR;
	e = p->data;
	return OK;
}

Status ListInsert_L(LinkList &L, int i, ElemType e){
	LinkList p,s;
	p = L;
	int j=0;
	while (p && j < i-1){
		p = p->next;
		++j;
	}
	if (!p || j > i-1)
		return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

Status ListDelete_L(LinkList &L, int i, ElemType &e){
	LinkList p,q;
	p=L;
	int j=0;
	while (p->next && j<i-1){
		p = p->next;
		++j;
	}
	if (!(p->next) && j < i-1){
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i-1)
		return ERROR;
	q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return OK;
}

int ListDeleteByValue_L(LinkList &H, ElemType x){
	LNode *p, *q=H;
	int count=0;
	while (q->next){
		p = q->next;
		if (p->data == x){
			q->next = p->next;
			free(p);
			++count;
		}
		else q=p;
	}
	return count;
}

#endif
