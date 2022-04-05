//—≠ª∑∂”¡–£®À≥–Ú¥Ê¥¢£© 
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "stitch_algorithm.h"

#define MAXQSIZE 100

typedef struct {
	ElemType *base;
	int front;
	int rear;
}SqQueue;

Status Init_Queue(SqQueue &Q){
	Q.base = (ElemType*) malloc(MAXQSIZE * sizeof(ElemType));
	if (!Q.base) exit(OVERFLOW);
	Q.front = Q.rear = 0;
	return OK;
}

int Empty_Queue(SqQueue Q){
	if (Q.front == Q.rear) return TRUE;
	else return FALSE;
}

Status In_Queue(SqQueue &Q, ElemType e){
	if ((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return OK;
}

Status Out_Queue(SqQueue &Q, ElemType &e){
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return OK; 
}

Status Front_Queue(SqQueue Q, ElemType &e){
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	return OK;
}

#endif
