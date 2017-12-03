/*
 ��С��
 ����λ��������˳�
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int heap[MAX];
int n;
void init(){
	heap[0]=0;//0�Ŵ�Ԫ�ظ���
	n=0;
}

void print(){
	for (int i = 1; i <=heap[0]; i++)
		printf("%d ",heap[i]);
	printf("\n");
}

void pop(int x,int y){//��x�������Ƶ�y��
	int w=x,tmp=heap[x];
	while (w>y && heap[w>>1]>tmp){
		heap[w]=heap[w>>1];
		w>>=1;
	}
	heap[w]=tmp;
}

void push(int x,int y){//��x��ѹ��y��
	int tmp=heap[x],i,j;
	for (i=x;(i<<1)<=y;i=j){
		j=i<<1;
		if (j != y && heap[j+1]<heap[j]){
			j++;
		}
		if (tmp>heap[j]){
			heap[i]=heap[j];
		}else break;
	}
	heap[i]=tmp;
}

void insert(int x){
	heap[++heap[0]]=x;
	pop(heap[0],1);
}

int popmin(){//pop��СԪ��
	int min=heap[1];
	heap[1]=heap[heap[0]--];
	push(1,heap[0]);
	return min;
}

int change(int x,int y){
	int i,j;
	for (int k = 1; k <=heap[0]; k++){
		if (heap[k]==x){
			heap[k]=y;
			if (y>x){
				push(k,heap[0]);
				print();
				return 1;
			}
			else{	
				pop(k,1);
				print();
				return 1;
			}
		}
	}
	return 0;
}

void input(){
	int x;
	init();
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		scanf("%d",&x);
		insert(x);
	} 
}

void main(){
	int i,j,x,sum=0;
	//�ϲ�����
    input();
 	for (int i=1;i<n;i++){
		x=0;
		x+=popmin()+popmin();
		insert(x);
		sum+=x;
	}
	printf("%d\n\n",sum);

	//�ı����ȼ�
	input();
	//int i=4,j=0;
	scanf("%d%d",&i,&j);
	printf("�ı����ȼ�Ԫ��%dΪ���ȼ�%d��\n",i,j);
	print();
	change(i,j);
	system("pause");
}
