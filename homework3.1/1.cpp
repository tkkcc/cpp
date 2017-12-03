/*作业3.1
by kkcckc
*/
#include<iostream>
#include<string>

using namespace std;

typedef char treetype;
struct tn
{
	tn *l,*r;
	treetype m;
};

string s1,s2,s3;

typedef tn *tree;

void findpreorder(string s2,string s3,tree &t)
{
	int pos,len=s2.length();
	if (len==0) {t=NULL;return;}
	t=new tn;
	if (len==1) {t->m=s3.back();t->l=t->r=NULL;return;}
	t->m=s3.back();
	pos=s2.find(s3.back());
	findpreorder(s2.substr(0,pos),s3.substr(0,pos),t->l);
	findpreorder(s2.substr(pos+1,len-pos-1),s3.substr(pos,len-pos-1),t->r);
}
void findpostorder(string s1,string s2,tree &t)
{
	int pos,len=s2.length();
	if (len==0) {t=NULL;return;}
	t=new tn;
	if (len==1) {t->m=s1[0];t->l=t->r=NULL;return;}
	t->m=s1[0];
	pos=s2.find(s1[0]);
	findpostorder(s1.substr(1,pos),s2.substr(0,pos),t->l);
	findpostorder(s1.substr(pos+1,len-pos-1),s2.substr(pos+1,len-pos-1),t->r);
}
void inorder(tree t)
{
	if (t==NULL) return;
	cout<<t->m;
	inorder(t->l);
	inorder(t->r);
}
void postorder(tree t)
{
	if (t==NULL) return;
	postorder(t->l);
	postorder(t->r);
	cout<<t->m;
}
void main()
{
	tree t;
	//getline(cin,s1);
	cin>>s1>>s2>>s3;
	//getline(cin,s2);
	//getline(cin,s3);
	if (s2=="#") cout<<"不能唯一确定二叉树";
	else if (s1=="#") 
	{
		findpreorder(s2,s3,t);
		cout<<"preorder:";
		inorder(t);
	}
	else if (s3=="#")
	{
		findpostorder(s1,s2,t);
		cout<<"postorder:";
		postorder(t);
	}
	else cout<<"输入有误！";getchar();getchar();
}
