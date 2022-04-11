#ifndef __SPARSE_MATRIX_H__
#define __SPARSE_MATRIX_H__

#include "stitch_algorithm.h"

#define MAXSIZE 12500
typedef struct {
	int i,j;
	ElemType e;
} Triple;
typedef struct{
	Triple data[MAXSIZE+1];
	int mu,nu,tu;
} TSMatrix;

Status CreateSMatrix(TSMatrix &M, ElemType *A, int x, int y){
	M.mu = x; M.nu = y; M.tu = 0;
	for (int i=0;i<x;i++){
		for (int j=0;j<y;j++){
			if (A[i*y+j]){
				M.tu++;
				if (M.tu>MAXSIZE) return OVERFLOW;
				M.data[M.tu].e = A[i*y+j];
				M.data[M.tu].i = i+1;
				M.data[M.tu].j = j+1;
			}
		}
	}
	return OK;
}

Status DestroySMatrix(TSMatrix &M){
	M.mu = 0; M.nu = 0; M.tu = 0;
	return OK;
}

Status PrintSMatrix(TSMatrix M){
	printf("稀疏矩阵对应的三元组表为：\n");
	printf("%d行%d列%d个非零元素。\n",M.mu,M.nu,M.tu);
	printf("行  列  元素值\n");
	for (int i=1;i<=M.tu;i++){
		printf("%2d  %2d  %6d\n",M.data[i].i,M.data[i].j,M.data[i].e);
	}
	return OK;
}

Status AddSMatrix(TSMatrix M,TSMatrix N,TSMatrix &Q){
	if (M.mu != N.mu || M.nu != N.nu) return ERROR;
	Q.mu=0;Q.nu=0;Q.tu=0;
	int m_idx=1,n_idx=1;
	while (m_idx<=M.tu||n_idx<=N.tu){
		if (M.data[m_idx].i == N.data[n_idx].i && M.data[m_idx].j == N.data[n_idx].j){
			Q.tu++;
			Q.data[Q.tu].i = M.data[m_idx].i;
			Q.data[Q.tu].j = M.data[m_idx].j;
			Q.data[Q.tu].e = M.data[m_idx++].e + N.data[n_idx++].e;
		}
		else if (M.data[m_idx].i == N.data[n_idx].i && M.data[m_idx].j < N.data[n_idx].j
					|| M.data[m_idx].i < N.data[n_idx].i){
			Q.tu++;
			Q.data[Q.tu].i = M.data[m_idx].i;
			Q.data[Q.tu].j = M.data[m_idx].j;
			Q.data[Q.tu].e = M.data[m_idx++].e;
		}
		else{
			Q.tu++;
			Q.data[Q.tu].i = N.data[n_idx].i;
			Q.data[Q.tu].j = N.data[n_idx].j;
			Q.data[Q.tu].e = N.data[n_idx++].e;
		}
		if (M.data[m_idx].i > Q.mu) Q.mu = M.data[m_idx].i;
		if (M.data[m_idx].j > Q.nu) Q.nu = M.data[m_idx].j;
		if (N.data[n_idx].i > Q.mu) Q.mu = N.data[n_idx].i;
		if (N.data[n_idx].j > Q.nu) Q.nu = N.data[n_idx].j;
	}
	if (m_idx>M.tu && n_idx<=N.tu){
		for (;n_idx<=N.tu;n_idx++){
			Q.data[++Q.tu].e = N.data[n_idx].e;
		}
	}
	else if (n_idx>N.tu && m_idx<=M.tu){
		for (;m_idx<=M.tu;m_idx++){
			Q.data[++Q.tu].e = M.data[m_idx].e;
		}
	}
	return OK;
}

Status TransposeSMatrix(TSMatrix M,TSMatrix &T){
	T.mu = M.nu; T.nu=M.mu; T.tu = M.tu;
	int *num = (int*)malloc((M.nu+1) * sizeof(int));
	int *cpot = (int*)malloc((M.nu+1) * sizeof(int));
	if (T.tu){
		for (int col=1;col<=M.nu;++col) num[col]=0;
		for (int t=1;t<=M.tu;++t) ++num[M.data[t].j];
		cpot[1]=1;
		for (int col=2;col<=M.nu;++col) cpot[col]=cpot[col-1]+num[col-1];
		for (int p=1;p<=M.tu;++p){
			int col = M.data[p].j;
			int q = cpot[col];
			T.data[q].i = M.data[p].j;
			T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e;
			++cpot[col];
		}
	}
	return OK;
}

#endif
