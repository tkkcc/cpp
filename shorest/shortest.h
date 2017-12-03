#include<iostream>
#include<vector>

#define MAX 20
typedef int costtype;
using namespace std;
const int inf = 0x3f3f3f3f;
int n,m,p[MAX][MAX],t[MAX][MAX];
costtype a[MAX][MAX],d[MAX][MAX],dist[MAX];

void dijk(int A) {
	memset(p,-1,sizeof(p));
	memset(dist,0x3f,n*sizeof(costtype));
	bool vis[MAX]={false};
	dist[A] = 0;
	for(int i = 0; i < n; ++i) {
		int cur = -1;
		for(int j = 0; j < n; ++j) {
			if (vis[j]) continue;
			if (cur == -1 || dist[j] < dist[cur]) {
				cur = j;
			}
		}
		vis[cur] = true;
		for(int j = 0; j < n; ++j) {
			if (dist[cur] + a[cur][j] < dist[j]) {
				if (cur!=A) p[A][j]=cur;
				dist[j] = dist[cur] + a[cur][j];
			}
		}
	}

}
void floyd(){
	int i,j,k;
	for (i=0;i<n;++i)
		for (j=0;j<n;++j){
			d[i][j]=a[i][j];
			p[i][j]=-1;
		}
	for (k=0;k<n;++k)
		for (i=0;i<n;++i)
			for (j=0;j<n;++j)
				if (d[i][k]+d[k][j]<d[i][j]){
					d[i][j]=d[i][k]+d[k][j];
					p[i][j]=k;
				}
}
//¿É´ï¾ØÕó
void TransitiveClosure(){  
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){  
            if((i==j)||(a[i][j])<inf)
                t[i][j]=1;  
            else  
                t[i][j]=0; 
        }  
    for(int k=0;k<n;k++)  
        for(int i=0;i<n;i++)  
            for(int j=0;j<n;j++)  
                t[i][j]=t[i][j]||(t[i][k]&&t[k][j]);
}  
void printway(int x,int y){
	if (p[x][y]==-1) cout<<"->"<<y;
	else {
		printway(x,p[x][y]);
		printway(p[x][y],y);
	}
}
