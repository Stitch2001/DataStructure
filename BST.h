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

//�����������㷨 
Status Delete(BiTree &p)/*�Ӷ�����������ɾ��*p���*/
{
	//�Ӷ�����������ɾ�����p�����ؽ��������������
	BiTree q, s;
	if (!p->rchild) { // ����������ֻ���ؽ�����������
		q=p;p=p->lchild;free(q);
	} 
	else if (!p->lchild) { //����������ֻ���ؽ�����������
		q=p;p=p->rchild;free(q);
	}
	else { // ��������������
		q=p;s=p->lchild;
		while (s->rchild){ // ���ҵ���ͷ
			q=s;s=s->rchild;
		}
		p->data = s->data; 
		if (q != p) 
			q->rchild = s->lchild; //�ؽ�*q����������s����������
		else //sһ��ʼû�������������
			q->lchild = s->lchild; //�ؽ�*q��������
		free(s);
	}
	return TRUE;
}

Status DeleteBST(BiTree &T, ElemType key)/*������ɾ���ؼ���Ϊk�Ľ��*/
{
	//������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ��
	//��ɾ��������Ԫ�ؽ��p��������TRUE�����򷵻�FALSE
	if (!T)
		return FALSE;//�����ڹؼ��ֵ���key������Ԫ��
	else {
		if (EQ(key,T->data))//�ҵ��ؼ��ֵ���key������Ԫ�� 
			return Delete(T);
		else if (LT(key,T->data))
			return DeleteBST(T->lchild,key);
		else
			return DeleteBST(T->rchild,key);
	}
}

int isPrint = FALSE;
Status SearchBST1(BiTree T,ElemType key)/*�Էǵݹ鷽ʽ����Ӹ���㵽���ҵ��Ľ���·��*/
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
	if (!p){ //���Ҳ��ɹ�������Ϊ����������ʱp����ֵΪNull
		if (isPrint) printf("NULL\n");
		return FALSE;
	}
	else {
		if (isPrint) printf("%d\n",p->data);
		return TRUE;
	}
}

Status SearchBST2(BiTree T,ElemType key,BiTree f,BiTree &p)/*�Եݹ鷽ʽ����Ӹ���㵽���ҵ��Ľ���·��*/	
{
	//�������ú������ڸ�ָ��T��ָ�����������еݹ�ز�����ؼ��ֵ���
	// key������Ԫ�أ� �����ҳɹ�����ָ��pָ�������Ԫ�ؽ�㣬����
	// ��TRUE�� ����ָ��pָ�����·���Ϸ��ʵ����һ����㲢����
	// FALSE�� ָ��fָ��T��˫�ף����ʼ����ֵΪ������˫��NULL
	if (!T){ //���Ҳ��ɹ�������Ϊ����������ʱp����ֵΪNull
		if (isPrint) printf("NULL\n");
		p = f; //���Ҳ��ɹ�ʱpָ�����·���Ϸ��ʵ����һ����
		return FALSE;
	}
	else if (EQ(key,T->data)){ //���ҳɹ�
		if (isPrint) printf("%d\n",T->data);
		p = T; //Tֵ���ŵݹ�Ľ��̲��ϱ仯
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

Status InsertBST(BiTree &T,ElemType e)/*����*pΪ������BST�в���һ���ؼ���Ϊk�Ľ��*/
{
	BiTree p = T,s;
	if (!SearchBST2(T,e,NULL,p)){
		//���Ҳ��ɹ�
		s = (BiTree)malloc(sizeof(BiTNode)); 
		s->data = e;
		s->lchild = s->rchild = NULL;
		if (!p) //TΪ����
			T=s; //����sΪ�µĸ����
		else if (LT(e, p->data))
			p->lchild = s; //����sΪ����
		else
			p->rchild = s; //����sΪ�Һ���
		return TRUE;
	}
	else
		return FALSE; //�������йؼ�����ͬ�Ľ�㣬���ٲ���
}

void DispBST(BiTree T)	/*�����ű�ʾ���������������bt*/
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

BiTree CreateBST(ElemType A[],int n)/*������A�еĹؼ��ֽ���һ�ö���������*/
{
	BiTree T = NULL;
	isPrint = FALSE;//�رղ���ʱ����� 
	int i;
	for (i=0;i<n;i++){
		printf("��%d��������%d:",i+1,A[i]);
		InsertBST(T,A[i]);
		DispBST(T);
		printf("\n");
	}
	return T;
}

void JudgeBST(BiTree T, int &isBST)	/*�ж��Ƿ�ΪBST*/
{
	//����������ڵ�
	BiTree p = T;
	if (T->lchild){
		JudgeBST(T->lchild,isBST);
		if (p->data < T->lchild->data)
			isBST = FALSE;//���ڵ�����ӽڵ�С�������� 
	}
	if (T->rchild){
		JudgeBST(T->rchild,isBST);
		if (p->data > T->rchild->data)
			isBST = FALSE;//���ڵ���Һ��ӽڵ�󣬲����� 
	}
}

#endif 
