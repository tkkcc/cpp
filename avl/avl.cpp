#include "avl.h"
#include<fstream>
#define ipath "f:\\desktop\\avl.in"
#define opath "f:\\desktop\\avl.out"
using namespace std;
void main()
{
	ios::sync_with_stdio(false);
	fstream ifile(ipath,ios::in);
	fstream ofile(opath,ios::out);
	if (!ifile || !ofile) {cout<<"文件不能打开";return;}
	cin.rdbuf(ifile.rdbuf());
	cout.rdbuf(ofile.rdbuf());

	int n,i;
	elementtype j;
	nn root=NULL;
	cin>>n;
	for (i=0;i<n;i++)
	{
		cin>>j;
		flag=0;
		cout<<"插入"<<j;
		root=insert(root,j);
		if (flag) continue;
		cout<<"\n先序：";
		preorder(root);
		cout<<"\n中序：";
		inorder(root);
		cout<<"\n树高："<<root->h;
		cout<<endl;
	}
	cin>>j;
	cout<<"\n查找"<<j<<"中..."<<endl;
	nn p=search(root,j);
	if (!p) cout<<"\n未找到"<<j;
	else 
	{
		cout<<"\n已找到 删除中...";
		root=del(root,p);
		cout<<"\n先序：";
		preorder(root);
		cout<<"\n中序：";
		inorder(root);
		cout<<"\n树高："<<root->h;
	}
	destroy(root);

	ifile.close();
	ofile.close();
}


