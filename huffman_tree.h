#ifndef __HUFFMAN_TREE__
#define __HUFFMAN_TREE__

#include "stitch_algorithm.h"
#include <string.h>
#include <stdio.h>

typedef struct {
	int weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;
typedef char **HuffmanCode;

void Select(HuffmanTree HT,int n,int &s1,int &s2){
	s1 = 1;
	int i;
	while (HT[s1].parent && s1<n) s1++;
	for (i=s1+1;i<=n;++i){
		if (HT[i].parent == 0 && HT[i].weight < HT[s1].weight){
			s1 = i;
		}
	}
	for (i=1;i<=n;++i){
		if (HT[i].parent == 0 && i!=s1) break;
	}
	s2 = i;
	for (i=s2+1;i<=n;++i){
		if (HT[i].parent == 0 && i!=s1 && HT[i].weight < HT[s2].weight){
			s2 = i;
		}
	}
}

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n){
	//w存放n个字符的权值，构造哈夫曼树HT，并求出n个字符的哈夫曼编码HC 
	int i,j,m,s1,s2,start;
	char *cd; unsigned int c,f;
	
	if (n<=1) return;
	m = 2*n-1;
	HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
	
	for (i=1;i<=n;++i){
		HT[i].weight = w[i-1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i=n+1;i<=m;++i){
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}

	for (i=n+1;i<=m;++i){
		Select(HT,i-1,s1,s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	
	HC = (HuffmanCode)malloc((n+1)*sizeof(char*));
	cd = (char*)malloc(n*sizeof(char));
	cd[n-1]='\0';
	for (i=1;i<=n;++i){
		start = n-1;
		for (c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
			if (HT[f].lchild==c) cd[--start] = '0';
			else cd[--start] = '1';
		HC[i] = (char*)malloc((n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
}

#endif
