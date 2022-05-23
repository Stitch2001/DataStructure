#ifndef __HASH_H__
#define __HASH_H__

#include "stitch_algorithm.h"
#include <stdio.h>

typedef struct{
	int key;
	int c;
}ElemType;

typedef struct{
	ElemType *elem;//数组元素存储基地址 
	int count;//当前数据元素个数 
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
	// 在开放定址哈希表H中查找关键码为K的元素，
	// 若查找成功，以p指示待查数据元素在表中位置，并返回SUCCESS；
	// 否则，以p指示插入位置，并返回UNSUCCESS,
	// c用以计冲突次数，其初值置零
	p = Hash(K);//求得哈希地址
	while ((H.elem[p].key != NULL) && K != H.elem[p].key){
		p = collision(p,++c,H.count);
	} 
	if (K == H.elem[p].key)
		return SUCCESS;
	else
		return UNSUCCESS;
}

Status InsertHash(HashTable &H, ElemType e){
	//查找不成功时插入数据元素e到开放定址哈希表H中
	int p,c=0;
	if (SearchHash(H,e.key,p,e.c)){
		//表中已有与e有相同关键字的元素 
			return DUPLICATE;
	}
	else {
		H.elem[p] = e;
		++H.count;
		return OK;
	}
}

HashTable CreateHashTable(int A[],int n){
	//从数组A中建立哈希表 
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
