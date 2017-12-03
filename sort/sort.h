#include<iostream>
//#include<cstdio>
#include<ctime>
#include <windows.h> 
#include<time.h>
#include<stdio.h>
#define MAX 10001
#define MAX_RANGE 10001
#define MIN(a,b) a<b?a:b
#define good 8
using namespace std;
typedef int typee;
typee a[MAX],b[MAX];
double random(double start,double end){
	return start+(end-start)*rand()/(RAND_MAX+1.0);
}
void print(typee a[],int n){
	int x=MIN(good,n);
	for (int i=0;i<x;i++){
		cout<<a[i]<<' ';
	}
}

void create(int n){
	bool f[MAX_RANGE+1]={false};
	srand(unsigned(time(0)));
	/*
	for (int i=0;i <n;i++){
		a[i]=int (random(-MAX_RANGE,MAX_RANGE));
		int f=0;
		for (int j=0;j<i;j++){
			if (a[i]==a[j]) {
				i--;f=1;
				break;
			}
		}
	}*/
	for (int i=0;i <n;i++){
		a[i]=int (random(0,MAX_RANGE));
		if (!f[a[i]]){
			f[a[i]]=true;
			//cout<<i;
			continue;
		}
		i--;
	}
}


void swap(typee b[],int i,int j)
{
	typee t=b[i];
	b[i]=b[j];
	b[j]=t;
}

void qs(typee a[],int l,int r){
	if (l>=r) return;
	typee t=a[l];
	int i=l,j=r;
	while (i<j){
		while (i<j && a[j]>=t) j--;
		a[i]=a[j];
		while (i<j && a[i]<=t) i++;
		a[j]=a[i];
	}
	a[i]=t;
	qs(a,l,i-1);
	qs(a,i+1,r);
}

/*
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
*/
void bubble(typee a[],int n){
	int i,j,f=1;
	while (f){
		f=0;
		for (i=0;i<n-1;i++){
			if (a[i]>a[i+1]) {
				swap(a,i,i+1);
				f=1;
			}
		}
	}
}

void binsearch(typee a[], int i,int j,int x){
	if (i>j) {cout<<"找不到";return;}
	int m=(i+j)/2;
	if (a[m]==x) {cout<<x<<"找到了";}
	else if (a[m]<x) {cout<<m<<"->";binsearch(a,m+1,j,x);}
	else {cout<<m<<"->";binsearch(a,i,m-1,x);}
}

void binsearch2(typee a[], int l,int r,int x){
	int i=l,j=r,m;
	while (i<=j){
		m=(i+j)/2;
		if (a[m]==x) {cout<<x<<"找到了";return;}
		else if (a[m]<x) {cout<<m<<"->";i=m+1;}
		else {cout<<m<<"->";j=m-1;}
	}
	cout<<"找不到";
	return;
}




