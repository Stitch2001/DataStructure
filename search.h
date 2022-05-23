#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "stitch_algorithm.h"

#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))

typedef struct{
	ElemType *elem;//�洢�ռ����Ļ���ַ 
	int length;//��ǰ���� 
}SSTable;

int Search_Seq(SSTable ST, KeyType key){
	int i;
	ST.elem[0].key = key;
	for (i=ST.length; ST.elem[i].key != key; --i);
	return i;
}

int Search_Bin(SSTable ST, KeyType key){
	//�������ST�ж��ֲ���key��Ҫ���Ѿ���С��������á� 
	int low,high,mid;
	low = 1;high = ST.length;
	while(low<high){
		if (LT(key,ST.elem[low].key))//���Ҫ�ҵ�λ�ñ�key��С 
			return low;
		mid = (low+high)/2;
		if (EQ(key,ST.elem[mid].key))
			return mid;
		else if (LT(key,ST.elem[mid].key))
			high = mid;
		else
			low = mid;
		if (high-low == 1 && !EQ(key,ST.elem[low].key))
			return high;
	} 
} 
#endif
