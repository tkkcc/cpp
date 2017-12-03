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
			if (e<p->l->e) {p=ll(p); cout<<" ��������";}
			else {p=lr(p); cout<<" ��������";}
		}
	}
	else if (e>p->e){
		p->r=insert(p->r,e);
		if (H(p->r)-H(p->l) == 2){
			if (e<p->r->e) {p=rl(p); cout<<" ��������";}
			else {p=rr(p); cout<<" ��������";}
		}
	}
	else {cout<<" ���ʧ��!��ͬ�ڵ������"<<endl;flag=1;}
	p->h=MAX(H(p->l),H(p->r))+1;
	return p;
}
//ɾ�ڵ�k
nn del(nn p,nn k)
{
	if (!p || !k) return NULL;
	if (k->e<p->e){
		p->l=del(p->l,k);//ɾ���ٵ�ƽ��
		if (H(p->r)-H(p->l) == 2){
			nn q=p->r;
			if (H(q->l)>H(q->r)) {p=rl(p); cout<<" ��������";}
			else {p=rr(p); cout<<" ��������";}
		}
	}
	else if (k->e>p->e)	{
		p->r=del(p->r,k);
		if (H(p->r)-H(p->l) == -2){
			nn q=p->l;
			if (H(q->r)>H(q->l)) {p=lr(p); cout<<" ��������";}
			else {p=ll(p); cout<<" ��������";}
		}
	}
	else // p->e=k->e Ҫɾp
	{
		if ((p->l) && (p->r))//���ҷǿ�
		{
			if (H(p->l)>H(p->r))//���
			{
				nn q=searchmax(p->l);//����������� ���������������ҽڵ�
				p->e=q->e;//��Ϊ���ֵ
				p->l=del(p->l,q);//�ٰ����ڵ�ɾ��
			}
			else
			{
				nn q=searchmin(p->r);//����������С ����������������ڵ�
				p->e=q->e;//��Ϊ��Сֵ
				p->r=del(p->r,q);//�ٰ���С�ڵ�ɾ��		
			}
		}
		else //������һ���ջ�ȫ�� ֱ��Ų��ȥ
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