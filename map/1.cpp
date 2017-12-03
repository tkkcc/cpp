/*

实验题目：无向图存储结构的建立与搜索（遍历）
实验内容：
图的搜索（遍历）算法是图型结构相关算法的基础，本实验要求编写程序演示无向图三种典型存储结构的建立和（搜索）遍历过程。
实验要求：
1．分别实现无向图的邻接矩阵、邻接表和邻接多重表存储结构的建立算法，分析和比较各建立算法的时间复杂度以及存储结构的空间占用情况；
2．实现无向图的邻接矩阵、邻接表和邻接多重表三种存储结构的相互转换算法；
3．在上述三种存储结构上，分别实现无向图的深度优先搜索（递归和非递归)和广度优先搜索算法。并以适当的方式存储和显示相应的搜索结果（深度优先或广度优先生成森林（或生成树）、深度优先或广度优先序列和编号）；
4．分析搜索算法的时间复杂度；
5．以文件形式输入图的顶点和边，并显示相应的结果。要求顶点不少于10个，边不少于13个；
6．软件功能结构安排合理，界面友好，便于使用
----------------------------------------------------------------------------------------------
*/
#include<iostream>
#include<fstream>
#define max 40
#define ipath "f:\\desktop\\map.in"
#define opath "f:\\desktop\\map.out"
struct edgenode
{ 
	int vex;
	edgenode *next;
};
typedef edgenode *edge;
edge v[max]={NULL};

struct multiedgenode
{
	int flag,x1,x2;
	multiedgenode *next1,*next2;
};
typedef multiedgenode *multiedge;
multiedge vv[max]={NULL};

int n,m,a[max][max],b[max],s[max],top;
using namespace std;

void dfs_matrix_r(int x)
{
	int i;
	s[++top]=x;
	b[x]=1;
	for (i=0;i<n;i++)
	{
		if (a[x][i] && !b[i])
		{
			dfs_matrix_r(i);
		}
	}
}
void dfs_matrix_norecursion(int x)
{
	cout<<"\ndfs_matrix_norecursion:\n";
	int o,j;
	memset(b,-1,sizeof(b));
	for (j=0;j<n;j++)
	{
		if (b[j]!=-1) continue;
		memset(s,0,sizeof(s));
		s[0]=j;
		top=0;
		cout<<j<<' ';
		do
		{
			do
			{
				o=++b[s[top]];
				if (o==n) break;
				if (a[s[top]][o] && (b[o]==-1))
				{
					cout<<o<<' ';
					s[++top]=o;
					break;
				}
			}while (1);
			if (o==n) top--;
		}while (top!=-1);
		cout<<endl;
	}


}
void dfs_matrix_recursion(int x)
{
	cout<<"\ndfs_matrix_recursion:\n";
	int i,j;
	memset(b,0,sizeof(b));
	for (j=0;j<n;j++)
	{
		if (b[j]!=0) continue;
		top=-1;
		dfs_matrix_r(j);
		for (i=0;i<=top;i++)
		{
			cout<<s[i]<<' ';
		}
		cout<<endl;
	}
}
void bfs_matrix(int x)
{
	cout<<"\nbfs_matrix:\n";
	int l,r,i,j;
	memset(s,0,sizeof(s));
	for (j=0;j<n;j++)
	{
		if (s[j]) continue;
		l=r=0;
		b[0]=j;s[j]=1;
		do
		{
			for (i=0;i<n;i++)
			{
				if (a[b[l]][i] && !s[i])
				{
					b[++r]=i;
					s[i]=1;
				}
			}
			l++;
		}while (l<=r);
		for (i=0;i<=r;i++)
		{
			cout<<b[i]<<' ';
		}
		cout<<endl;
	}
}

void dfs_list_r(int x)
{
	edge p=v[x];
	s[++top]=x;
	b[x]=1;
	while((p=p->next)!=NULL)
	{
		if (!b[p->vex])
			dfs_list_r(p->vex);
	}
}
void dfs_list_norecursion(int x)
{
	cout<<"\ndfs_list_norecursion:\n";
	int i,o,j;
	edge e[max];
	for (i=0;i<n;i++) 
	{
		e[i]=v[i];
		v[i]->vex=0;
	}
	for (j=0;j<n;j++)
	{
		if (v[j]->vex) continue;
		v[j]->vex=1;
		memset(s,0,sizeof(s));
		s[0]=j;top=0;
		cout<<j<<' ';
		do
		{
			do
			{
				e[s[top]]=e[s[top]]->next;
				if (!e[s[top]]) break;
				o=e[s[top]]->vex;
				if (!v[o]->vex)
				{
					v[o]->vex=1;
					cout<<o<<' ';
					s[++top]=o;
					break;
				}
			}while (1);
			if (!e[s[top]]) top--;
		}while (top!=-1);
		cout<<endl;
	}


}
void dfs_list_recursion(int x)
{
	cout<<"\ndfs_list_recursion:\n";
	int i,j;
	memset(b,0,sizeof(b));
	for (j=0;j<n;j++)
	{
		if (b[j])continue;
		top=-1;
		dfs_list_r(j);
		for (i=0;i<=top;i++)
		{
			cout<<s[i]<<' ';
		}
		cout<<endl;
	}
}
void bfs_list(int x)
{
	cout<<"\nbfs_list:\n";
	edge p;
	int l,r,i,j;
	memset(s,0,sizeof(s));
	for (j=0;j<n;j++)
	{
		if (s[j]) continue;
		l=r=0;
		b[0]=j;s[j]=1;
		do
		{
			p=v[b[l]];
			while ((p=p->next)!=NULL)
			{
				if (!s[p->vex])
				{
					b[++r]=p->vex;
					s[p->vex]=1;
				}
			}
			l++;
		}while (l<=r);
		for (i=0;i<=r;i++)
		{
			cout<<b[i]<<' ';
		}
		cout<<endl;
	}
}

multiedge next(multiedge p,int i)
{
	if (p->x1==i) return p->next1;
	return p->next2;
}

int other(multiedge p,int i)
{
	if (p->x1==i) return p->x2;
	return p->x1;
}


void dfs_multilist_r(int x)
{
	multiedge p=vv[x]->next1;
	s[++top]=x;
	b[x]=1;
	while (p)
	{
		
		if (p->x1==x && !b[p->x2])
			dfs_multilist_r(p->x2);
		else if (p->x2==x && !b[p->x1])
			dfs_multilist_r(p->x1);
		p=next(p,x);
	}
}
void dfs_multilist_recursion(int x)
{
	int i,j;
	cout<<"\ndfs_multilist_recursion:\n";
	memset(b,0,sizeof(b));
	for (j=0;j<n;j++)
	{
		if (b[j])continue;
		top=-1;
		dfs_multilist_r(j);
		for (i=0;i<=top;i++)
		{
			cout<<s[i]<<' ';
		}
		cout<<endl;
	}
}

void dfs_multilist_norecursion(int x)
{
	cout<<"\ndfs_multilist_norecursion:\n";
	int i,o,j;
	memset(s,0,sizeof(s));
	multiedge e[max];
	for (i=0;i<n;i++) {e[i]=vv[i]->next1;vv[i]->x1=0;}
	for (j=0;j<n;j++)
	{
		if (vv[j]->x1) continue;
		s[0]=j;top=0;
		cout<<j<<' ';
		vv[j]->x1=1;
		if (!e[j]) {cout<<endl; continue;}
		do
		{
			do
			{
				o=other(e[s[top]],s[top]);//下个点
				if (!vv[o]->x1)//没走过
				{
					vv[o]->x1=1;//标记走过
					cout<<o<<' ';//输出
					s[++top]=o;
					break;
				}
			}while (e[s[top]]=next(e[s[top]],s[top]));
			if (!e[s[top]]) top--;
		}while (top!=-1);
		cout<<endl;
	}

}

void bfs_multilist(int x)
{
	cout<<"\nbfs_multilist:\n";
	multiedge p;
	int j,l,r=0,i;
	memset(s,0,sizeof(s));
	for (j=0;j<n;j++)
	{
		if (s[j])continue;
		l=r=0;
		b[0]=j;s[j]=1;
		do
		{
			p=vv[b[l]]->next1;
			if (p)
				do
				{
					i=other(p,b[l]);
					if (!s[i])
					{
						b[++r]=i;
						s[i]=1;
					}
				}while ((p=next(p,b[l]))!=NULL);
			l++;
		}while (l<=r);
		for (i=0;i<=r;i++)
		{
			cout<<b[i]<<' ';
		}
		cout<<endl;
	}
}

void input()
{
	int i,j,k;
	edge p;
	multiedge q;
	memset(a,0,sizeof(a));
	cin>>n>>m;
	for (i=0;i<n;i++){v[i]=new edgenode;v[i]->next=NULL;vv[i]=new multiedgenode;vv[i]->next1=NULL;}
	for (i=0;i<m;i++)
	{
		//martix
		cin>>j>>k;
		a[j][k]=a[k][j]=1;
		
		//list
		p=new edgenode;
		p->next=v[j]->next;
		p->vex=k;
		v[j]->next=p;
		p=new edgenode;
		p->next=v[k]->next;
		p->vex=j;
		v[k]->next=p;

		//multilist
		q=new multiedgenode;
		q->x1=j;q->x2=k;
		q->next1=vv[j]->next1;
		vv[j]->next1=q;
		q->next2=vv[k]->next1;
		vv[k]->next1=q;
	}
}
multiedge local(multiedge vx[],int x,int y)
{
	
	multiedge p=vx[x];
	if (!p) return NULL;
	p=p->next1;
	while (p!=NULL)
	{
		if (other(p,x)==y) break;
		p=next(p,x);
	}
	return p;
}
void search()
{
	int i,j;
	edge p;
	multiedge q;
	cout<<"1.\nadjacency matrix:\n";
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
		{
			cout<<a[i][j]<<'\t';
		}
		cout<<endl;
	}

	dfs_matrix_recursion(0);
	dfs_matrix_norecursion(0);
	bfs_matrix(0);

	cout<<"\n\n2.\nadjacency list:\n";
	for (i=0;i<n;i++)
	{
		p=v[i];
		
		cout<<i<<":\t";
		if (p==NULL) {cout<<endl;continue;}
		while ((p=p->next)!=NULL)
		{
			cout<<p->vex<<'\t';	
		}
		cout<<endl;
	}
	dfs_list_recursion(0);
	dfs_list_norecursion(0);
	bfs_list(0);

	cout<<"\n\n3.\nadjacency multilist:\n";
	for (i=0;i<n;i++)
	{
		q=vv[i]->next1;
		
		cout<<i<<":\t";
		if (q==NULL){cout<<endl;continue;}
		do 
		{
			cout<<'('<<q->x1<<','<<q->x2<<")\t";
			q=next(q,i);
		} while (q);
		cout<<endl;
	}
	dfs_multilist_recursion(0);
	dfs_multilist_norecursion(0);
	bfs_multilist(0);
}

void change()
{
	int i,j,k;
	edge p;
	multiedge q;
	multiedge vv1[max]={NULL};
	edge v1[max]={NULL};
	int a1[max][max];
	memset(a1,0,sizeof(a1));
	for (i=0;i<n;i++){v1[i]=new edgenode;v1[i]->next=NULL;vv1[i]=new multiedgenode;vv1[i]->next1=NULL;}
	cout<<"\n\nchange:\n";
	cout<<"1.matrix->list:\n";
	for (i=0;i<n;i++)
	{
		for (j=i+1;j<n;j++)
		{
			if (a[i][j])
			{
				if (!v1[i]) {v1[i]=new edgenode;v1[i]->next=NULL;}
				p=new edgenode;
				p->next=v1[i]->next;
				p->vex=j;
				v1[i]->next=p;
				if (!v1[j]) {v1[j]=new edgenode;v1[j]->next=NULL;}
				p=new edgenode;
				p->next=v1[j]->next;
				p->vex=i;
				v1[j]->next=p;
			}
		}
	}
	for (i=0;i<n;i++)
	{
		p=v1[i];
		cout<<i<<":\t";

		while ((p=p->next)!=NULL)
		{
			cout<<p->vex<<'\t';	
		}
		cout<<endl;
	}

	cout<<"\n2.list->multilist:\n";
	for (i=0;i<n;i++)
	{
		p=v1[i];

		while(p=p->next)
		{
			j=i;
			k=p->vex;
			if (local(vv1,j,k)) continue;
			if (!vv1[j]) {vv1[j]=new multiedgenode;vv1[j]->next1=NULL;}
			if (!vv1[k]) {vv1[k]=new multiedgenode;vv1[k]->next1=NULL;}
			q=new multiedgenode;
			q->x1=j;q->x2=k;
			q->next1=vv1[j]->next1;
			vv1[j]->next1=q;
			q->next2=vv1[k]->next1;
			vv1[k]->next1=q;
		}
	}

	for (i=0;i<n;i++)
	{
		q=vv1[i]->next1;
		
		cout<<i<<":\t";
		if (q==NULL) {cout<<endl;continue;}
		do 
		{
			cout<<'('<<q->x1<<','<<q->x2<<")\t";
			q=next(q,i);
		} while (q);
		cout<<endl;
	}

	cout<<"\n3.multilist->matrix:\n";
	for (i=0;i<n;i++)
	{
		q=vv1[i]->next1;
		if (!q) continue;
		while (q=next(q,i))
		{
			a1[q->x1][q->x2]=a1[q->x2][q->x1]=1;
		}
	}

	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
		{
			cout<<a1[i][j]<<'\t';
		}
		cout<<endl;
	}
}

void main()
{
	fstream ifile(ipath,ios::in);
	fstream ofile(opath,ios::out);
	if (!(ifile&&ofile)) {cout<<"can't open file!"; return;}
	cin.rdbuf(ifile.rdbuf());
	cout.rdbuf(ofile.rdbuf());

	input();

	search();

	change();

	ifile.close();
	ofile.close();
	//getchar();
}

