typedef int ElemType;

#include "sequence_list.h"
#include <stdio.h>

SqList La, Lb;
int sqListsCount = 0;

int main(){
	//建立及初始化顺序表（硬编码） 
	int a[10]={1,2,2,3,4,6,7,8,8,9};
	int b[15]={2,3,4,5,5,7,9,10,11,12,13,13,15,15,16};
	InitList_Sq(La);
	InitList_Sq(Lb);
	for (int i=0;i<10;i++){
		ListInsert_Sq(La,i+1,a[i]);
	}
	for (int i=0;i<15;i++){
		ListInsert_Sq(Lb,i+1,b[i]);
	}
	printf("顺序表建立完毕，内容为：\n");
	printf("La: ");
	for (ElemType* p=La.elem;p<La.elem+La.length;p++)
		printf("%d ",*p);
	printf("\nLb: ");
	for (ElemType* p=Lb.elem;p<Lb.elem+Lb.length;p++)
		printf("%d ",*p);
	printf("\n");
	//向顺序表中插入数据
	printf("\n现在向顺序表La中插入1个元素。\n");
	while (1){
		int locate, value;
		printf("请输入位置：");scanf("%d",&locate);
		printf("请输入值：");scanf("%d",&value);
		if (ListInsert_Sq(La,locate,value)==OK){
			printf("插入成功！\n");
			printf("La: ");
			for (ElemType* p=La.elem;p<La.elem+La.length;p++)
				printf("%d ",*p);
			printf("\n");
			break;
		}
		else
			printf("插入失败，请重试。\n");
	} 
	printf("\n现在向顺序表La中查找1个元素。\n");
	while (1){
		int value,locate;
		printf("请输入值：");scanf("%d",&value);
		locate = LocateElem_Sq(La,value,compare);
		if (locate){
			printf("查找成功！位置为：%d\n",locate);
			break;
		}
		else
			printf("查找失败，请重试。\n");
	} 
	printf("\n现在向顺序表La中删除1个元素。\n");
	while (1){
		int value,locate;
		printf("请输入位置：");scanf("%d",&locate);
		if (ListDelete_Sq(La,locate,value) == OK){
			printf("删除成功！被删除的值为：%d\n",value);
			printf("La: ");
			for (ElemType* p=La.elem;p<La.elem+La.length;p++)
				printf("%d ",*p);
			printf("\n");
			break;
		}
		else
			printf("删除失败，请重试。\n");
	} 
	printf("\n现在合并La和Lb两个顺序表\n");
	printf("La: ");
	for (ElemType* p=La.elem;p<La.elem+La.length;p++)
		printf("%d ",*p);
	printf("\n");
	printf("Lb: ");
	for (ElemType* p=Lb.elem;p<Lb.elem+Lb.length;p++)
		printf("%d ",*p);
	printf("\n");
	SqList Lc;
	MergeList_Sq(La, Lb, Lc);
	printf("新的顺序表为：\n");
	printf("Lc: ");
	for (ElemType* p=Lc.elem;p<Lc.elem+Lc.length;p++)
		printf("%d ",*p);
	printf("\n");
	return 0;
}
