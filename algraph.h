//邻接表存储图 

#ifndef __ALGRAPH_H__
#define __ALGRAPH_H__

typedef int ElemType;
#include "stitch_algorithm.h"
#include "queue.h"
#include "stack.h"

#define MAX_VERTEX_NUM 20
typedef struct ArcNode{//边结点 
	int adjvex;//邻接点域 
	struct ArcNode *nextarc;//指向下一个边结点的指针域 
}ArcNode;

typedef struct Vnode{//表头结点 
	VertexType vertex;
	ArcNode *firstarc;
}VNode; 

typedef struct{
	VNode adjlist[MAX_VERTEX_NUM];//结构体数组
	int vexnum,arcnum;//图的当前顶点数和弧数 
}ALGraph;

void CreateALGraph(ALGraph &G, int vex, int arc, VertexType *vtx_lst, int arc_lst[][2]){//建立无向图的邻接表存储 
	int i,j,k;
	ArcNode *s;
	G.vexnum = vex; G.arcnum = arc;//顶点数和边数 
	for (i=0;i<G.vexnum;i++){
		G.adjlist[i].vertex = vtx_lst[i];//存储顶点信息 
		G.adjlist[i].firstarc = NULL;
	}
	for (k=0;k<G.arcnum;k++){
		i = arc_lst[k][0];//存储边信息 
		j = arc_lst[k][1];//存储边信息 
		s = (ArcNode*)malloc(sizeof(ArcNode));
		s->adjvex = j;
		s->nextarc = G.adjlist[i].firstarc;
		G.adjlist[i].firstarc = s;
	}//在链表表头插入结点，从后向前建立链表 
}

bool visited[MAX_VERTEX_NUM];//访问标志数组
Status (*VisitFunc)(int v);//函数变量，指向函数的指针
int FirstAdjVex(ALGraph G, int v){
	if (G.adjlist[v].firstarc)
		return G.adjlist[v].firstarc->adjvex;
	else
		return -1;
} 
int NextAdjVex(ALGraph G, int v, int w){
	ArcNode *p = G.adjlist[v].firstarc;
	while (p->adjvex != w){
		if (p->nextarc) p = p->nextarc;
		else break;
	}
	if (p->nextarc)
		return p->nextarc->adjvex;
	else
		return -1;
}
void DFS(ALGraph G, int v){
	//从第v个顶点出发递归地深度优先遍历图G
	visited[v] = true;
	VisitFunc(v);//访问第v个顶点 
	for (int w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w)){
		if (!visited[w]){
			DFS(G,w);//对尚未访问的邻接顶点w递归调用DFS 
		}
	}
}
void DFSTraverse(ALGraph G, Status (*Visit)(int v)){
	VertexType v;
	VisitFunc = Visit;//使用全局变量使被调用函数DFS不必设函数指针参数
	for (v=0;v<G.vexnum;++v)
		visited[v] = false;//访问标志数组初始化 
	for (v=0;v<G.vexnum;++v)
		if (!visited[v])
			DFS(G,v);//对尚未访问的顶点调用DFS 
} 

void BFSTraverse(ALGraph G, Status (*Visit)(int v)){
	VertexType v,u,w;int s=0;
	SqQueue Q;
	Init_Queue(Q);
	VisitFunc = Visit;//使用全局变量使被调用函数DFS不必设函数指针参数
	for (v=0;v<G.vexnum;++v)
		visited[v] = false;//访问标志数组初始化 
	for (v=0;v<G.vexnum;++v)
		if (!visited[v]){
			visited[v] = true;
			Visit(v);
			In_Queue(Q,v);s++;
			while (!Empty_Queue(Q)){
				Out_Queue(Q,u);s--;
				for (w=FirstAdjVex(G,u);w>=0;w=NextAdjVex(G,u,w))
					if (!visited[w]){
						visited[w] = true;
						Visit(w);
						In_Queue(Q,w);s++;
					}
			}
		}
}

void DFSTraverseByStack(ALGraph G, Status (*Visit)(int v)){
	VertexType v,w;
	SqStack s;
	InitStack(s);
	for (v=0;v<G.vexnum;++v)
		visited[v] = false;//访问标志数组初始化 
	for (v=0;v<G.vexnum;++v)
		if (!visited[v]){
			visited[v] = true;
			Visit(v);//访问第v个顶点 
			do{
				for (w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w))
					if (!visited[w])
						break;
				if (w >= 0){
					Push(s,w);
					Visit(w);
					visited[w] = true;
					v = w;
				}
				else 
					Pop(s,v);
			} while (!EmptyStack(s));
		}
}

#endif
