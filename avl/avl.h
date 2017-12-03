#include<iostream>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define H(p) ((p==NULL)?-1:((nn)(p))->h)
using namespace std;
typedef int elementtype;
typedef struct node *nn;
int flag=0;
struct node
{
	int h;
	elementtype e;
	nn l,r;
};
//travel
void preorder(nn p)
{
	if (!p) return;
	cout<<p->e<<' ';
	preorder(p->l);
	preorder(p->r);
}
void inorder(nn p)
{
	if (!p) return;
	inorder(p->l);
	cout<<p->e<<' ';
	inorder(p->r);
}
void postorder(nn p)
{
	if (!p) return;
	postorder(p->l);
	postorder(p->r);
	cout<<p->e<<' ';
}
//search
nn search(nn p,elementtype e)
{
	while (p && p->e!=e) {cout<<p->e<<"->";p=(e<p->e)?p->l:p->r;}
	if (p) cout<<p->e;
	return p;
}
nn searchmax(nn p)
{
	if (p) while (p->r) p=p->r;
	return p;
}
nn searchmin(nn p)
{
	if (p) while (p->l) p=p->l;
	return p;
}
//rotation
nn ll(nn p)
{
	nn q=p->l;
	p->l=q->r;
	q->r=p;
	p->h=MAX(H(p->l),H(p->r))+1;
	q->h=MAX(H(p->l),p->h)+1;
	return q;
}
nn rr(nn p)
{
	
	nn q=p->r;
	p->r=q->l;
	q->l=p;
	p->h=MAX(H(p->l),H(p->r))+1;
	q->h=MAX(H(p->r),p->h)+1;
	return q;
}
nn lr(nn p)
{
	p->l=rr(p->l);
	return (ll(p));
}
nn rl(nn p)
{
	p->r=ll(p->r);
	return (rr(p));
}
//create
nn create(elementtype e,nn l,nn r)
{
	nn p;
	try {p=new node;}
	catch(bad_alloc &memExp) {cerr<<memExp.what()<<endl;}
	p->e=e;
	p->h=0;
	p->l=l;
	p->r=r;
	return p;
}
//insert
nn insert(nn p,elementtype e)
{
	if (!p)	p =create(e,NULL,NULL);
	else if (e<p->e) {
		p->l=insert(p->l,e);
		if (H(p->l)-H(p->r) == 2){
			if (e<p->l->e) {p=ll(p); cout<<" 调了左左";}
			else {p=lr(p); cout<<" 调了左右";}
		}
	}
	else if (e>p->e){
		p->r=insert(p->r,e);
		if (H(p->r)-H(p->l) == 2){
			if (e<p->r->e) {p=rl(p); cout<<" 调了右左";}
			else {p=rr(p); cout<<" 调了右右";}
		}
	}
	else {cout<<" 添加失败!相同节点已添加"<<endl;flag=1;}
	p->h=MAX(H(p->l),H(p->r))+1;
	return p;
}
//删节点k
nn del(nn p,nn k)
{
	if (!p || !k) return NULL;
	if (k->e<p->e){
		p->l=del(p->l,k);//删完再调平衡
		if (H(p->r)-H(p->l) == 2){
			nn q=p->r;
			if (H(q->l)>H(q->r)) {p=rl(p); cout<<" 调了右左";}
			else {p=rr(p); cout<<" 调了右右";}
		}
	}
	else if (k->e>p->e)	{
		p->r=del(p->r,k);
		if (H(p->r)-H(p->l) == -2){
			nn q=p->l;
			if (H(q->r)>H(q->l)) {p=lr(p); cout<<" 调了左右";}
			else {p=ll(p); cout<<" 调了左左";}
		}
	}
	else // p->e=k->e 要删p
	{
		if ((p->l) && (p->r))//左右非空
		{
			if (H(p->l)>H(p->r))//左大
			{
				nn q=searchmax(p->l);//找左子树最大 就是左子树的最右节点
				p->e=q->e;//赋为最大值
				p->l=del(p->l,q);//再把最大节点删掉
			}
			else
			{
				nn q=searchmin(p->r);//找右子树最小 就是右子树的最左节点
				p->e=q->e;//赋为最小值
				p->r=del(p->r,q);//再把最小节点删掉		
			}
		}
		else //左右有一个空或全空 直接挪上去
		{
			nn q=p;
			p=p->l?p->l:p->r;
			delete(q);
		}
	}
	return p;
}
//destroy
void destroy(nn p)
{
	if (!p) return;
	if (p->l) destroy(p->l);
	if (p->r) destroy (p->r);
	delete(p);
}