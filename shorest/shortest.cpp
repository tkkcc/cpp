#include "shortest.h"
#include<fstream>
#include<iomanip>
#define ipath "f:\\desktop\\shortest.in"
#define opath "f:\\desktop\\shortest.out"
using namespace std;
void main()
{
	int i,j,k,x;
	ios::sync_with_stdio(false);
	streambuf *inbackup=cin.rdbuf();
	//streambuf *outbackup=cout.rdbuf();
	fstream ifile(ipath,ios::in);
	//fstream ofile(opath,ios::out);
	//if (!ifile || !ofile) {cout<<"文件不能打开";return;}
	if (!ifile) {cout<<"文件不能打开";return;}
	cin.rdbuf(ifile.rdbuf());
	//cout.rdbuf(ofile.rdbuf());
	cout.setf(ios::right);
	cin>>n>>m;
	memset(a,0x3f,sizeof(a));
	for (i=0;i<m;++i)
	{
		cin>>j>>k>>x;
		a[j][k]=x;
		a[i][i]=0;
	}
	//∞
	floyd();
	cout<<"floyd shorest distance:\n";
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			if (d[i][j]==inf)cout<<setw(3)<<"∞";
			else cout<<setw(3)<<d[i][j];
		}
		cout<<endl;
	}
	cout<<"floyd shorest way matrix:\n";
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			cout<<setw(4)<<p[i][j];
		}
		cout<<endl;
	}
	cout<<"floyd shorest way:\n";
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			if (d[i][j] == inf || i==j) continue;
			cout<<i<<"->"<<j<<':'<<right<<setw(3)<<d[i][j]<<setw(3)<<i;
			printway(i,j);
			cout<<endl;
		}
	}

	//可达矩阵
	TransitiveClosure();
	cout<<"\nTransitiveClosure\n";
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			cout<<setw(3)<<t[i][j];
		}
		cout<<endl;
	}
	ifile.close();
	//dijkstra
	//cout.rdbuf(outbackup);
	cin.rdbuf(inbackup);
	do {
		cout<<"1.输入顶点A，求A到其他各点最短路径\n2.输入顶点A、B，求AB最短路径\n3.输入顶点A，求其他各点到A的最短路径\n4.结束\n";
		cin>>k;
		if (k==1 || k==2 || k==3) {
			cin>>i;
			//cout.rdbuf(ofile.rdbuf());
			dijk(i);
			if (k==1) {
				cout<<"\ndijkstra shorest distance form "<<i<<":\n";
				for (j=0;j<n;j++){
					if (dist[j] == inf || j==i) continue;
					cout<<i<<"->"<<j<<':'<<right<<setw(3)<<dist[j]<<setw(3)<<i;
					printway(i,j);
					cout<<endl;
				}
			}
			else if (k==2){
				cin>>j;
				cout<<"\nshorest distance form "<<i<<" to "<<j<<":\n";
				if (dist[j] == inf || j==i) {cout<<"NONE\n";continue;}
				cout<<i<<"->"<<j<<':'<<right<<setw(3)<<dist[j]<<setw(3)<<i;
				printway(i,j);
				cout<<endl;
			}
			else {
				floyd();
				j=i;
				cout<<"floyd shorest way to "<<j<<":\n";
				for (i=0;i<n;i++){	
					if (d[i][j] == inf || i==j) continue;
						cout<<i<<"->"<<j<<':'<<right<<setw(3)<<d[i][j]<<setw(3)<<i;
						printway(i,j);
						cout<<endl;
					}
				}
			}
		else if (k==4){
			return;
		}
		else cout<<"输入有误！\n";
	}while (1);
}


