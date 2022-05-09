#ifndef __MGRAPH_H__
#define __NGRAPH_H__

#include "stitch_algorithm.h"
#include <stdio.h>
 
#define MAX_VERTEX_NUM 20 //顶点数的最大值 
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
	//构造无向网G
	int i,j,k,v1,v2,w;
	printf("请输入无向网G的顶点数和边数：");
	scanf("%d%d",&G.vexnum,&G.arcnum);
	printf("请依次输入%d个顶点的值：",G.vexnum);
	for (i=0;i<G.vexnum;++i) {
		scanf(" %c",&G.vexs[i]);
	}
	for (i=0;i<G.vexnum;++i)
		for (j=0;j<G.vexnum;++j)
			G.adj[i][j]=0;//初始化邻接矩阵 
	printf("请依次输入%d条边的顶点1、顶点2、权值：\n",G.arcnum);
	for (k=0;k<G.arcnum;++k){
		scanf(" %c %c%d",&v1,&v2,&w);
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G.adj[i][j] = w;
		G.adj[j][i] = w;//置对称边 
	}
	return OK; 
}

Status CreateDN(MGraph &G){
	//构造有向网G
	int i,j,k,v1,v2,w;
	printf("请输入有向网G的顶点数和边数：");
	scanf("%d%d",&G.vexnum,&G.arcnum);
	printf("请依次输入%d个顶点的值：",G.vexnum);
	for (i=0;i<G.vexnum;++i) {
		scanf(" %c",&G.vexs[i]);
	}
	for (i=0;i<G.vexnum;++i)
		for (j=0;j<G.vexnum;++j)
			G.adj[i][j]=0;//初始化邻接矩阵 
	printf("请依次输入%d条弧的弧尾、弧头、权值：\n",G.arcnum);
	for (k=0;k<G.arcnum;++k){
		scanf(" %c %c%d",&v1,&v2,&w);
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G.adj[i][j] = w;
	}
	return OK; 
}

/*Prim算法*/ 
typedef struct Closedge{
	VertexType adjvex;//存储该边依附的在U中的顶点 
	int lowcost;//边的权值 
} closedge[MAX_VERTEX_NUM];//closedge[i]对应adjvex与在V-U中的顶点Vi之间的边 

int Mininum(closedge dge, MGraph G){
	int i,min;
	for (i=0;i<G.vexnum;i++)
		if (dge[i].lowcost != 0)//所对应顶点还未进集合U
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
	k = LocateVex(Gn,v0);// 查找v0在顶点向量v[]中的序号
	for (j=0;j<Gn.vexnum;j++){
		if (j!=k){//排除v0，因其已经在集合U中
			dge[j].adjvex = v0;
			dge[j].lowcost = Gn.adj[k][j]; 
		}
	}//closedge数组初始化
	dge[k].lowcost = 0; //初始U={v0}
	printf("最小代价生成树的各条边为：\n");
	for (i=1;i<Gn.vexnum;i++){//选择其余vex_num-1个顶点
		k = Mininum(dge,Gn);//求权值最小的边，k值为边对应的U-V中顶点序号
		printf("<%c-%c>\n",dge[k].adjvex,Gn.vexs[k]);//dge[k].adjvex该边U中顶点，Gn.vexs[k]该边V-U中顶点
		dge[k].lowcost = 0;//顶点vk入U
		for (j=0;j<Gn.vexnum;j++){//新顶点入U后重新选择最小边
			if (Gn.adj[k][j]<dge[j].lowcost){
				dge[j].lowcost = Gn.adj[k][j];
				dge[j].adjvex = Gn.vexs[k];
			} 
		}
	}
}
/*Prim算法*/ 

/*Dijkstra算法*/
typedef int Patharc[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];

void Dijkstra(MGraph G, VertexType V0, Patharc &P, ShortPathTable &D){
	//用Dijkstra算法求有向网G的V0顶点到其余顶点v的最短路径P[v]及其带权长度D[v]。
	//final[v]为TRUE当且仅当v∈S，即已经求得从v0到v的最短路径。
	int i,v,w,k=0,min,v0=LocateVex(G,V0);
	int final[MAX_VERTEX_NUM];//final[w]=TRUE表示求得顶点v0至vw的最短路径
	for (v=0;v<G.vexnum;v++){
		final[v]=FALSE;//全部顶点初始化为未知最短路径状态
		D[v]=G.adj[v0][v];//将与v0点有连线的顶点加上权值
		if (D[v]==0) D[v]=INFINITY;
		for (w=0;w<G.vexnum;++w) P[v][w] = FALSE;//初始化路径数组P为FALSE
		if (D[v]<INFINITY) {
			P[v][v0] = TRUE; P[v][v]=TRUE;
		}
	}
	D[v0] = 0;//v0至v0路径为0
	final[v0] = TRUE;//v0至v0不需要求路径
	/* 开始主循环，每次求得v0到某个v顶点的最短路径 */
	for (i=1;i<G.vexnum;i++){
		min=INFINITY;//当前所知离v0顶点的最近距离
		for (w=0;w<G.vexnum;w++){//寻找离v0最近的顶点
			if (!final[w] && D[w]<min){
				v = w;
				min = D[w];
			}
		}
		final[v] = TRUE;//将目前找到的最近的顶点置为1 
		for (w=0;w<G.vexnum;w++){//修正当前最短路径及距离
			/* 如果经过v顶点的路径比现在这条路径的长度短的话 */
			if (!final[w] && (min+G.adj[v][w]<D[w]) && G.adj[v][w]!=0){
				/* 说明找到了更短的路径，修改D[w]和P[w] */
				D[w] = min + G.adj[v][w];
				for (int j=0;j<G.vexnum;j++) P[w][j] = P[v][j];
				P[w][w]=TRUE;
			}
		}
	}
}

#endif 
