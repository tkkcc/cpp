#include<iostream>
#include<cmath>
using namespace std;
double f(double x,double y){
	return 1/x*(y*y+y);
}
void main(){
	double a=1,b=3,alpha=-2;
	double k1,k2,k3,k4,x0,y0,h;
	int N[]={5,10,20};
	for (int i=0;i<3;i++){
		cout<<N[i]<<":\n";
		x0=a,y0=alpha,h=(b-a)/N[i];
	//	cout<<h<<endl;
		for (int j=1;j<=N[i];j++){
			k1=h*f(x0,y0);
			k2=h*f(x0+h/2,y0+k1/2);
			k3=h*f(x0+h/2,y0+k2/2);
			k4=h*f(x0+h,y0+k3);
			x0=x0+h;
			y0=y0+(k1+2*k2+2*k3+k4)/6;
			cout<<x0<<' '<<y0<<endl;s
		}
	}


	system("pause");
}