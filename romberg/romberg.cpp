#include<iostream>
#include<algorithm>
using namespace std;
double f(double x){
	return pow(x,2)*exp(x);
}
void main(){
	int m=2;
	double a,b,n,e;
	//cin>>a>>b>>n>>e;
	cout.setf(ios_base::fixed);
	cout.precision(10);
	a=0;b=1;n=100;e=pow(10,-6);
	double h=(b-a)/(double)n;
	double t1=.5*h*(f(a)+f(b)),t2,s1,s2,r1,r2,c1,c2,tmp;
	t2=s1=s2=r1=r2=c1=c2=tmp=0;
	cout<<t1<<endl;
	for (int i=2;i<=n;i++){
		int ii=pow(2,i-1);
		tmp=0;
		for (int k=1;k<=ii;k++){
			tmp+=f(a+(k-.5)*h);
		}
		t2=0.5*t1+0.5*h*tmp;
		cout<<t2<<'\t';
		s2=1.0/3*(4*t2-t1);
		cout<<s2<<'\t';
		if (m>2){
			c2=1.0/15*(16*s2-s1);
			cout<<c2<<'\t';
		}
		if (m>3){
			r2=1.0/63*(64*c2-c1);
			cout<<r2<<'\t';
		}
		if (m>4){
			if(abs(r2-r1)<e) break;
		}
		r1=r2;c1=c2;s1=s2;t1=t2;h=h/2;m++;
		cout<<endl;
	}
	system("pause");
}