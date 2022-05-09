#ifndef __MGRAPH_H__
#define __NGRAPH_H__

#include "stitch_algorithm.h"
#include <stdio.h>
 
#define MAX_VERTEX_NUM 20 //�����������ֵ 
#define INFINITY 10000

typedef char VertexType;

typedef struct{
	VertexType vexs[MAX_VERTEX_NUM]; 
	int adj[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum, arcnum;
}MGraph;

int LocateVex(MGraph Gn, VertexType v0){
	for (int i=0;i<MAX_VERTEX_NUM;i++){
		if (Gn.vexs[i] == v0){
			return i;
		}
	}
}

Status CreateUDN(MGraph &G){
	//����������G
	int i,j,k,v1,v2,w;
	printf("������������G�Ķ������ͱ�����");
	scanf("%d%d",&G.vexnum,&G.arcnum);
	printf("����������%d�������ֵ��",G.vexnum);
	for (i=0;i<G.vexnum;++i) {
		scanf(" %c",&G.vexs[i]);
	}
	for (i=0;i<G.vexnum;++i)
		for (j=0;j<G.vexnum;++j)
			G.adj[i][j]=0;//��ʼ���ڽӾ��� 
	printf("����������%d���ߵĶ���1������2��Ȩֵ��\n",G.arcnum);
	for (k=0;k<G.arcnum;++k){
		scanf(" %c %c%d",&v1,&v2,&w);
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G.adj[i][j] = w;
		G.adj[j][i] = w;//�öԳƱ� 
	}
	return OK; 
}

Status CreateDN(MGraph &G){
	//����������G
	int i,j,k,v1,v2,w;
	printf("������������G�Ķ������ͱ�����");
	scanf("%d%d",&G.vexnum,&G.arcnum);
	printf("����������%d�������ֵ��",G.vexnum);
	for (i=0;i<G.vexnum;++i) {
		scanf(" %c",&G.vexs[i]);
	}
	for (i=0;i<G.vexnum;++i)
		for (j=0;j<G.vexnum;++j)
			G.adj[i][j]=0;//��ʼ���ڽӾ��� 
	printf("����������%d�����Ļ�β����ͷ��Ȩֵ��\n",G.arcnum);
	for (k=0;k<G.arcnum;++k){
		scanf(" %c %c%d",&v1,&v2,&w);
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G.adj[i][j] = w;
	}
	return OK; 
}

/*Prim�㷨*/ 
typedef struct Closedge{
	VertexType adjvex;//�洢�ñ���������U�еĶ��� 
	int lowcost;//�ߵ�Ȩֵ 
} closedge[MAX_VERTEX_NUM];//closedge[i]��Ӧadjvex����V-U�еĶ���Vi֮��ı� 

int Mininum(closedge dge, MGraph G){
	int i,min;
	for (i=0;i<G.vexnum;i++)
		if (dge[i].lowcost != 0)//����Ӧ���㻹δ������U
			break;
	min = i;
	for (i=0;i<G.vexnum;i++){
		if (dge[i].lowcost > 0 && dge[i].lowcost < dge[min].lowcost){
			min = i;
		}
	}
	return min;
}

void Prim(MGraph Gn, VertexType v0){
	closedge dge;
	int i,j,k;
	k = LocateVex(Gn,v0);// ����v0�ڶ�������v[]�е����
	for (j=0;j<Gn.vexnum;j++){
		if (j!=k){//�ų�v0�������Ѿ��ڼ���U��
			dge[j].adjvex = v0;
			dge[j].lowcost = Gn.adj[k][j]; 
		}
	}//closedge�����ʼ��
	dge[k].lowcost = 0; //��ʼU={v0}
	printf("��С�����������ĸ�����Ϊ��\n");
	for (i=1;i<Gn.vexnum;i++){//ѡ������vex_num-1������
		k = Mininum(dge,Gn);//��Ȩֵ��С�ıߣ�kֵΪ�߶�Ӧ��U-V�ж������
		printf("<%c-%c>\n",dge[k].adjvex,Gn.vexs[k]);//dge[k].adjvex�ñ�U�ж��㣬Gn.vexs[k]�ñ�V-U�ж���
		dge[k].lowcost = 0;//����vk��U
		for (j=0;j<Gn.vexnum;j++){//�¶�����U������ѡ����С��
			if (Gn.adj[k][j]<dge[j].lowcost){
				dge[j].lowcost = Gn.adj[k][j];
				dge[j].adjvex = Gn.vexs[k];
			} 
		}
	}
}
/*Prim�㷨*/ 

/*Dijkstra�㷨*/
typedef int Patharc[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];

void Dijkstra(MGraph G, VertexType V0, Patharc &P, ShortPathTable &D){
	//��Dijkstra�㷨��������G��V0���㵽���ඥ��v�����·��P[v]�����Ȩ����D[v]��
	//final[v]ΪTRUE���ҽ���v��S�����Ѿ���ô�v0��v�����·����
	int i,v,w,k=0,min,v0=LocateVex(G,V0);
	int final[MAX_VERTEX_NUM];//final[w]=TRUE��ʾ��ö���v0��vw�����·��
	for (v=0;v<G.vexnum;v++){
		final[v]=FALSE;//ȫ�������ʼ��Ϊδ֪���·��״̬
		D[v]=G.adj[v0][v];//����v0�������ߵĶ������Ȩֵ
		if (D[v]==0) D[v]=INFINITY;
		for (w=0;w<G.vexnum;++w) P[v][w] = FALSE;//��ʼ��·������PΪFALSE
		if (D[v]<INFINITY) {
			P[v][v0] = TRUE; P[v][v]=TRUE;
		}
	}
	D[v0] = 0;//v0��v0·��Ϊ0
	final[v0] = TRUE;//v0��v0����Ҫ��·��
	/* ��ʼ��ѭ����ÿ�����v0��ĳ��v��������·�� */
	for (i=1;i<G.vexnum;i++){
		min=INFINITY;//��ǰ��֪��v0������������
		for (w=0;w<G.vexnum;w++){//Ѱ����v0����Ķ���
			if (!final[w] && D[w]<min){
				v = w;
				min = D[w];
			}
		}
		final[v] = TRUE;//��Ŀǰ�ҵ�������Ķ�����Ϊ1 
		for (w=0;w<G.vexnum;w++){//������ǰ���·��������
			/* �������v�����·������������·���ĳ��ȶ̵Ļ� */
			if (!final[w] && (min+G.adj[v][w]<D[w]) && G.adj[v][w]!=0){
				/* ˵���ҵ��˸��̵�·�����޸�D[w]��P[w] */
				D[w] = min + G.adj[v][w];
				for (int j=0;j<G.vexnum;j++) P[w][j] = P[v][j];
				P[w][w]=TRUE;
			}
		}
	}
}

#endif 
