#include<iostream>
//#include<cstdio>
#include<ctime>

#define MAX 16
#define MAX_RANGE 0x3f3f3f3f
#define MIN(a,b) a<b?a:b
using namespace std;
typedef int typee;
typee a[MAX],b[MAX];
double random(double start,double end){
	return start+(end-start)*rand()/(RAND_MAX+1.0);
}
void print(typee a[],int n){
	int x=MIN(100,n);
	for (int i=0;i<n;i++){
		cout<<a[i]<<endl;
	}
}

void create(){
	cout<<"随机整型数组：\n";
	srand(unsigned(time(0)));
	for (int i;i <MAX-1;i++){
		a[i]=int (random(-MAX_RANGE,MAX_RANGE));
		cout<<a[i];
	}
}

void swap(typee i,typee j)
{
	typee t=a[i];
	a[i]=a[j];
	a[j]=t;
}

void qs(typee a[],int l,int r){
	typee t=a[l];
	int i=l,j=r;
	while (i<j){
		while (i<j && a[j]>=t) j--;
		a[i]=a[j];
		while (i<j && a[i]<=t) i++;
		a[j]=a[i];
	}
	a[l]=t;
	qs(a,l,i-1);
	qs(a,i+1,r);
}

void choice(typee a[],int n){
	int i,j,max;
	for (i=n-1;i>0;i--){
		max=0;
		for (j=0;j<i;j++){
			if (a[j]>a[max]) max=j;
		}
		swap(max,i);
	}
}
void bubble(typee a[],int n){
	int i,j,f=1;
	while (f){
		f=0;
		for (i=0;i<n-1;i++){
			if (a[i]>a[i+1]) {
				swap(i,j);
				f=1;
			}
		}
	}
}




