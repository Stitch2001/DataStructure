#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "stitch_algorithm.h"

#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))

typedef struct{
	ElemType *elem;//存储空间分配的基地址 
	int length;//当前表长度 
}SSTable;

int Search_Seq(SSTable ST, KeyType key){
	int i;
	ST.elem[0].key = key;
	for (i=ST.length; ST.elem[i].key != key; --i);
	return i;
}

int Search_Bin(SSTable ST, KeyType key){
	//在有序表ST中二分查找key，要求已经从小到大排序好。 
	int low,high,mid;
	low = 1;high = ST.length;
	while(low<high){
		if (LT(key,ST.elem[low].key))//如果要找的位置比key还小 
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
