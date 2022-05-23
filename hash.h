#ifndef __HASH_H__
#define __HASH_H__

#include "stitch_algorithm.h"
#include <stdio.h>

typedef struct{
	int key;
	int c;
}ElemType;

typedef struct{
	ElemType *elem;//����Ԫ�ش洢����ַ 
	int count;//��ǰ����Ԫ�ظ��� 
	int sizeindex;
}HashTable;

#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1

int Hash(HKeyType K);

int collision(int p, int &c, int size){
	return (p+1)%size;
}

Status SearchHash(HashTable H, HKeyType K, int &p, int &c){
	// �ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ�أ�
	// �����ҳɹ�����pָʾ��������Ԫ���ڱ���λ�ã�������SUCCESS��
	// ������pָʾ����λ�ã�������UNSUCCESS,
	// c���ԼƳ�ͻ���������ֵ����
	p = Hash(K);//��ù�ϣ��ַ
	while ((H.elem[p].key != NULL) && K != H.elem[p].key){
		p = collision(p,++c,H.count);
	} 
	if (K == H.elem[p].key)
		return SUCCESS;
	else
		return UNSUCCESS;
}

Status InsertHash(HashTable &H, ElemType e){
	//���Ҳ��ɹ�ʱ��������Ԫ��e�����Ŷ�ַ��ϣ��H��
	int p,c=0;
	if (SearchHash(H,e.key,p,e.c)){
		//����������e����ͬ�ؼ��ֵ�Ԫ�� 
			return DUPLICATE;
	}
	else {
		H.elem[p] = e;
		++H.count;
		return OK;
	}
}

HashTable CreateHashTable(int A[],int n){
	//������A�н�����ϣ�� 
	int i;
	HashTable table;
	table.elem = (ElemType*) calloc(n,sizeof(ElemType));
	table.count = 0;
	for (i=0;i<n;++i){
		ElemType e;
		e.key = A[i];
		InsertHash(table,e);
	}
	return table;
}

Status DeleteKey(HashTable &H, HKeyType K){
	int p,c=0;
	if (SearchHash(H,K,p,c)){
		H.elem[p].key = NULL;
		H.elem[p].c = 0;
		H.count--;
	}
	else return ERROR;
}

#endif
