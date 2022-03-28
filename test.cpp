typedef int ElemType;

#include "sequence_list.h"
#include <stdio.h>

SqList La, Lb;
int sqListsCount = 0;

int main(){
	//��������ʼ��˳���Ӳ���룩 
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
	printf("˳�������ϣ�����Ϊ��\n");
	printf("La: ");
	for (ElemType* p=La.elem;p<La.elem+La.length;p++)
		printf("%d ",*p);
	printf("\nLb: ");
	for (ElemType* p=Lb.elem;p<Lb.elem+Lb.length;p++)
		printf("%d ",*p);
	printf("\n");
	//��˳����в�������
	printf("\n������˳���La�в���1��Ԫ�ء�\n");
	while (1){
		int locate, value;
		printf("������λ�ã�");scanf("%d",&locate);
		printf("������ֵ��");scanf("%d",&value);
		if (ListInsert_Sq(La,locate,value)==OK){
			printf("����ɹ���\n");
			printf("La: ");
			for (ElemType* p=La.elem;p<La.elem+La.length;p++)
				printf("%d ",*p);
			printf("\n");
			break;
		}
		else
			printf("����ʧ�ܣ������ԡ�\n");
	} 
	printf("\n������˳���La�в���1��Ԫ�ء�\n");
	while (1){
		int value,locate;
		printf("������ֵ��");scanf("%d",&value);
		locate = LocateElem_Sq(La,value,compare);
		if (locate){
			printf("���ҳɹ���λ��Ϊ��%d\n",locate);
			break;
		}
		else
			printf("����ʧ�ܣ������ԡ�\n");
	} 
	printf("\n������˳���La��ɾ��1��Ԫ�ء�\n");
	while (1){
		int value,locate;
		printf("������λ�ã�");scanf("%d",&locate);
		if (ListDelete_Sq(La,locate,value) == OK){
			printf("ɾ���ɹ�����ɾ����ֵΪ��%d\n",value);
			printf("La: ");
			for (ElemType* p=La.elem;p<La.elem+La.length;p++)
				printf("%d ",*p);
			printf("\n");
			break;
		}
		else
			printf("ɾ��ʧ�ܣ������ԡ�\n");
	} 
	printf("\n���ںϲ�La��Lb����˳���\n");
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
	printf("�µ�˳���Ϊ��\n");
	printf("Lc: ");
	for (ElemType* p=Lc.elem;p<Lc.elem+Lc.length;p++)
		printf("%d ",*p);
	printf("\n");
	return 0;
}
