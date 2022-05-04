//�ڽӱ�洢ͼ 

#ifndef __ALGRAPH_H__
#define __ALGRAPH_H__

typedef int ElemType;
#include "stitch_algorithm.h"
#include "queue.h"
#include "stack.h"

#define MAX_VERTEX_NUM 20
typedef struct ArcNode{//�߽�� 
	int adjvex;//�ڽӵ��� 
	struct ArcNode *nextarc;//ָ����һ���߽���ָ���� 
}ArcNode;

typedef struct Vnode{//��ͷ��� 
	VertexType vertex;
	ArcNode *firstarc;
}VNode; 

typedef struct{
	VNode adjlist[MAX_VERTEX_NUM];//�ṹ������
	int vexnum,arcnum;//ͼ�ĵ�ǰ�������ͻ��� 
}ALGraph;

void CreateALGraph(ALGraph &G, int vex, int arc, VertexType *vtx_lst, int arc_lst[][2]){//��������ͼ���ڽӱ�洢 
	int i,j,k;
	ArcNode *s;
	G.vexnum = vex; G.arcnum = arc;//�������ͱ��� 
	for (i=0;i<G.vexnum;i++){
		G.adjlist[i].vertex = vtx_lst[i];//�洢������Ϣ 
		G.adjlist[i].firstarc = NULL;
	}
	for (k=0;k<G.arcnum;k++){
		i = arc_lst[k][0];//�洢����Ϣ 
		j = arc_lst[k][1];//�洢����Ϣ 
		s = (ArcNode*)malloc(sizeof(ArcNode));
		s->adjvex = j;
		s->nextarc = G.adjlist[i].firstarc;
		G.adjlist[i].firstarc = s;
	}//�������ͷ�����㣬�Ӻ���ǰ�������� 
}

bool visited[MAX_VERTEX_NUM];//���ʱ�־����
Status (*VisitFunc)(int v);//����������ָ������ָ��
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
	//�ӵ�v����������ݹ��������ȱ���ͼG
	visited[v] = true;
	VisitFunc(v);//���ʵ�v������ 
	for (int w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w)){
		if (!visited[w]){
			DFS(G,w);//����δ���ʵ��ڽӶ���w�ݹ����DFS 
		}
	}
}
void DFSTraverse(ALGraph G, Status (*Visit)(int v)){
	VertexType v;
	VisitFunc = Visit;//ʹ��ȫ�ֱ���ʹ�����ú���DFS�����躯��ָ�����
	for (v=0;v<G.vexnum;++v)
		visited[v] = false;//���ʱ�־�����ʼ�� 
	for (v=0;v<G.vexnum;++v)
		if (!visited[v])
			DFS(G,v);//����δ���ʵĶ������DFS 
} 

void BFSTraverse(ALGraph G, Status (*Visit)(int v)){
	VertexType v,u,w;int s=0;
	SqQueue Q;
	Init_Queue(Q);
	VisitFunc = Visit;//ʹ��ȫ�ֱ���ʹ�����ú���DFS�����躯��ָ�����
	for (v=0;v<G.vexnum;++v)
		visited[v] = false;//���ʱ�־�����ʼ�� 
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
		visited[v] = false;//���ʱ�־�����ʼ�� 
	for (v=0;v<G.vexnum;++v)
		if (!visited[v]){
			visited[v] = true;
			Visit(v);//���ʵ�v������ 
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
