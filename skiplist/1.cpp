#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define n 10
#define maxlevel 4
struct node{
	double key;
	struct node *next[1];
};

struct skiplist{
	int level;
	node *head;
};

node* createnode(int level,double key)
{
	node *ns=(node *)malloc(sizeof(node)+level*sizeof(node*));  
	ns->key=key;  
	return ns;  
}

skiplist* create()
{
	skiplist *a=(skiplist *)malloc(sizeof(skiplist));  
	a->level=0;  
	a->head=createnode(maxlevel-1,0);  
	for(int i=0;i<maxlevel;i++){  
		a->head->next[i]=NULL;  
	}
	return a;
}
  
int randomlevel(){ //∑i*2^i 趋向于2 
	int k=1;
	while (rand()%2 && k<maxlevel)
		k++;  
	return k;  
}

int insert(skiplist *a,double key){
	node *tmp[maxlevel];
	node *p=a->head, *q=NULL;
	int k=a->level-1;
	for(int i=k; i >= 0; i--){
		while((q=p->next[i])&&(q->key<key)){
			p=q;
		}
		tmp[i]=p;//记录每行比key小的最大值位置
	}
	if(q&&q->key==key){//重复不插
		return 0;
	}
	k=randomlevel();
	if(k>(a->level)){//高行头插key的预处理
		for(int i=a->level; i < k; i++){
			tmp[i] = a->head;
		}
		a->level=k;
	}
	q=createnode(k,key);//建一列 k个元素 
	for(int i=0;i<k;i++){
		q->next[i]=tmp[i]->next[i];//每行插入
		tmp[i]->next[i]=q;
	}
	return 1;
}
  
int search(skiplist *a,double key){
	node *p=a->head,*q;
	int k=a->level;
	for(int i=k-1; i >= 0; i--){
		while((q=p->next[i])&&(q->key<=key)){
			printf("%d,%.1f->",i,q->key);
			if(q->key == key){
				printf("found");
				return 1;
			}
			p=q;
		}
	}
	printf("notfonund");
	return NULL;
}

int deletekey(skiplist *a,double key){
	node *tmp[maxlevel];
	node *p,*q=NULL;
	p=a->head;
	int k=a->level;
	for(int i=k-1; i >= 0; i--){
		while((q=p->next[i])&&(q->key<key)){
			p=q;
		}
		tmp[i]=p;
	}
	if(q&&q->key==key)
	{
		for(int i=0;i<k;i++){  
			if(tmp[i]->next[i]==q){  
				tmp[i]->next[i]=q->next[i];  
			}
		} 
		free(q);
		for(int i=k-1;i>=0;i--){  
			if(a->head->next[i]==NULL){//改行为空 减行数  
				a->level--;  
			}  
		}  
		return 1;
	}
	else
		return 0;//notfound
}

void print(skiplist *a){
	printf("\n");
	node *p,*q=NULL;
	int k=a->level-1;
	for(int i=k; i >= 0; i--){
		p=a->head;
		if (q=p->next[i])
			printf("%.1f",q->key);
		else 
			continue;
		p=q;
		while(q=p->next[i]){
			printf("-%.1f",q->key);
			p=q;
		}
		printf("\n");
	}
}

void main()
{
	srand(time(NULL));
	skiplist *a=create();
	for(int i=1;i<=n;i++) insert(a,i);
	print(a);
	int y;
	float x;
	while (printf("\n1.insert 2.search 3.delete\n"),scanf("%d",&y),y){
		
		if (y==1){
			scanf("%f",&x);
			printf("\ninsert %f: ",x);
			insert(a,x);
			print(a);
		}
		else if (y==2){
			scanf("%f",&x);
			printf("\nsearch %f: ",x);
			search(a,x);
		}
		else if (y==3){
			scanf("%f",&x);

			printf("\ndelete %f: ",x);if (deletekey(a,x)) print(a);else printf("notfound"); 

		}
		
	}

	/*
	printf("search 5.5: ");
	search(a,5.5);
	printf("\n\ninsert 5.5: ");
	insert(a,5.5);
	print(a);
	printf("\nsearch 5.5: ");
	search(a,5.5);
	printf("\ndelete 5: ");if (deletekey(a,5)) print(a);else printf("notfound"); 
	printf("\ndelete 11: ");if (deletekey(a,11)) print(a);else printf("notfound"); 
	printf("\ninsert 3: ");if (insert(a,3)) print(a);else printf("failed"); 
	printf("\ninsert 6: ");if (insert(a,6)) print(a);else printf("failed"); 
	printf("\nsearch 6: ");search(a,6); 
	printf("\nsearch 5: ");search(a,5);*/
	/*
	deletekey(a,8);
	print(a); 
	deletekey(a,1);
	print(a); 
	deletekey(a,3);
	print(a); 
	*/
	system("pause");
}


