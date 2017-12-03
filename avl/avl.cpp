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
	if (!ifile || !ofile) {cout<<"�ļ����ܴ�";return;}
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
		cout<<"����"<<j;
		root=insert(root,j);
		if (flag) continue;
		cout<<"\n����";
		preorder(root);
		cout<<"\n����";
		inorder(root);
		cout<<"\n���ߣ�"<<root->h;
		cout<<endl;
	}
	cin>>j;
	cout<<"\n����"<<j<<"��..."<<endl;
	nn p=search(root,j);
	if (!p) cout<<"\nδ�ҵ�"<<j;
	else 
	{
		cout<<"\n���ҵ� ɾ����...";
		root=del(root,p);
		cout<<"\n����";
		preorder(root);
		cout<<"\n����";
		inorder(root);
		cout<<"\n���ߣ�"<<root->h;
	}
	destroy(root);

	ifile.close();
	ofile.close();
}


