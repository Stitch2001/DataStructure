#ifndef __STACK_H__
#define __STACK_H__

#include "stitch_algorithm.h"

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct{
	ElemType *base;
	ElemType *top;
	int stacksize;
} SqStack;

//在本模型中，top指针指向的是栈顶之上的空元素 

Status InitStack(SqStack &S){
	S.base = (ElemType*) malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status EmptyStack(SqStack S){
	if (S.top == S.base) return TRUE;
	else return FALSE;
}

Status GetTop(SqStack S, ElemType &e){
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
}

Status Push(SqStack &S, ElemType e){
	if (S.top - S.base >= S.stacksize){
		S.base = (ElemType*) realloc(S.base, (S.stacksize+STACKINCREMENT) * sizeof(ElemType));
		if (!S.base) exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack &S, ElemType &e){
	if (S.top == S.base) return ERROR;
	e = *--S.top; 
	return OK;
}

#endif
