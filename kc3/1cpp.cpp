/*实验3

by kkcckc
*/
#include<iostream>
#include<string>
#define maxnode 50//最大节点数
using namespace std;

typedef char treetype;
struct tn
{
	tn *l,*r;
	treetype m;
	bool ltag,rtag;
};
typedef tn *tree;

tree pre,head=NULL;//线索化二叉树全局量

void create (tree &t)
{
	char ch;
	cin>>ch;
	t = new tn;
	if (ch== '#' ) t=NULL;
	else 
	{
		t->m=ch;
		create(t->l);
		create(t->r);
	}
}

void create2 (tree &t)
{
	tree s[maxnode];
	int i,j;
	treetype ch;
	tree bt,p;
	cin>>i>>ch;
	while (i!=0 &&ch !=0)
	{
		p=new tn;
		p->m=ch;
		p->l=p->r=NULL;
		s[i]=p;
		if (i==1) t=p;
		else 
		{
			j=i/2;
			if (i%2==0) s[j]->l=p;
			else s[j]->r=p;
		}
		cin>>i>>ch;
	}
}

void preorder(tree &t)
{
	if (t)
	{
		cout<<t->m;
		preorder(t->l);
		preorder(t->r);
	}
}
void inorder(tree &t)
{
	if (t)
	{
		inorder(t->l);
		cout<<t->m;
		inorder(t->r);
	}
}

void postorder(tree &t)
{
	if (t)
	{
		postorder(t->l);
		postorder(t->r);
		cout<<t->m;
	}
}
void npreorder(tree t)
{
	tree s[maxnode];
	int top=-1;
	while (t!=NULL || top!=-1)
	{
		while (t !=NULL)
		{
			cout<<t->m;
			s[++top]=t;
			t=t->l;
		}
		if (top!=-1)
		{
			t=s[top--];
			t=t->r;
		}
	}
}

void ninorder(tree t)
{
	tree s[maxnode];
	int top=-1;
	while (t !=NULL || top!=-1)
	{
		while (t!=NULL)
		{
			s[++top]=t;
			t=t->l;
		}
		if (top!=-1)
		{
			t=s[top--];
			cout<<t->m;
			t=t->r;
		}
	}
}

void npostorder(tree t)
{
	tree s[maxnode];
	int flag[maxnode];
	int top=-1;
	while (t !=NULL || top!=-1)
	{
		while (t!=NULL)
		{
			s[++top]=t;
			flag[top]=1;
			t=t->l;
		}
		while (top!=-1 && flag[top]==2)
		{
			t=s[top--];cout<<t->m;
		}
		if (top!=-1)
		{
			flag[top]=2;
			t=s[top]->r;
		}
		if (top==-1) break;
	}
}

void lever(tree t)
{
	tree s[maxnode];
	int l,r=0;
	if (s[0]==NULL) return;
	s[0]=t;
	l=-1;
	while (++l<=r)
	{
		cout<<s[l]->m;
		if (s[l]->l) s[++r]=s[l]->l;
		if (s[l]->r) s[++r]=s[l]->r;
	}
}

void inorderth(tree t)
{
	if (t)
	{
		inorderth(t->l);
		if (t!=head)
		{
			t->ltag=(t->l)?true:false;
			t->rtag=(t->r)?true:false;
		}
		if (pre)
		{
			if (!pre->rtag && pre!=head) pre->r=t;
			if (!t->ltag) t->l=pre;
		}
		pre=t;
		if (t!=head) inorderth(t->r);

	}
}

tree prenext(tree p)
{
	tree q;
	if (p->ltag==true) q=p->l;
	else 
	{
		q=p;
		//if (q->r==head) return head;
		while ((!q->rtag) && (q->r!=head)) q=q->r;
		q=q->r;
	}
	return q;
}

tree innext(tree p)
{
	tree q;
	q=p->r;
	if (p->rtag)
		while (q->ltag)	
			q=q->l;
	return q;
}

tree postnext(tree p)
{
	tree q=p;
	while (q->rtag){q=q->r;}//最右节点（包括自己）
	q=q->r;
	if (q->l==p)//左子树根就是p q就是父节点
	{
		if (!q->rtag) return q;//没右子树,根就是后继
								//否则找右子树后序遍历的第一个节点
		q=q->r;
		while (q->ltag || q->rtag)
		{
			if (q->ltag) q=q->l;
			else q=q->r;
		}
		return q;
	}	
	q=q->l;						//p的后继必在左子树的最右分支中
	while (q->r != p){q=q->r;}
	return q;
}

void ungets(string &s,FILE *x)
{
	for (int i=s.length()-1;i>=0;i--)
	{
		ungetc(s[i],x);
	}
}

void main()
{
	tree t,temp;
	/*建树*/
	string s;
	getline(cin,s);
	bool f=s.find("#")==s.npos;
	ungets(s,stdin);
	if (f) create2(t);
	else create(t);

	/*递归非递归遍历*/
	cout<<"\n递归：\npreorder:\t";
	preorder(t);
	cout<<"\ninorder:\t";
	inorder(t);
	cout<<"\npostorder:\t";
	postorder(t);
	cout<<"\n非递归：\npreorder:\t";
	npreorder(t);
	cout<<"\ninorder:\t";
	ninorder(t);
	cout<<"\npostorder:\t";
	npostorder(t);
	cout<<"\n\n层序：\t\t";
	lever(t);

	/*线索化*/
	head=new tn;
	head->l=t;
	head->ltag=true;
	head->r=head;
	head->rtag=false;
	pre=head;
	inorderth(head);
	cout<<endl;

	/*线索树遍历*/
	cout<<"\n利用中序线索化二叉树遍历:\npreorder:\t";
	temp=head;
	while ((temp=prenext(temp))!=head) 
		cout<<temp->m;

	cout<<"\ninorder:\t";
	temp=head;
	do {temp=temp->l;} while (temp->ltag);//先找到最左节点
	do {cout<<temp->m;}while ((temp=innext(temp))!=head);

	cout<<"\npostorder:\t";
	temp=head;
	while (temp->ltag || temp->rtag)//找到后序第一个节点
	{
		if (temp->ltag) temp=temp->l;
		else temp=temp->r;
	}
	do {cout<<temp->m;}while ((temp=postnext(temp))!=head);

	getchar();
}
