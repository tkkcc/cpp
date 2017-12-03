
#include <iostream>
//#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#define IPATH "f:\\desktop\\in.txt"
#define OPATH "f:\\desktop\\out.txt"
using namespace std;

const double mi=0.0001;

struct mult{
	double coef;
	int exp;
	struct mult * next;
};

struct mult_divide{
	mult *quotient;
	mult *remainder;
};


void hint()
{
	cout<<"输入两个多项式 要求降次 一行输一个\
		  \n例如:\n1 4 -2 3 3 2 1 1 -11 0\n1 1 0 5\n表示多项式： X^4-2X^3+3X^2+X-11 和 X\n";
}

void make(mult *(&head))//创建头指针
{
	head = new mult;
	head->next=NULL;
}
void del(mult *h)//删除链表
{

	if (!h) return;
	mult *p=h,*q=h;
	while ((p=p->next) != NULL)
	{
		delete(q);
		q=p;
	}
	delete(q);
}
mult *attach (mult *d,double c,int e)//新增结点
{
	mult *x= new mult;
	x->coef = c;
	x->exp = e;
	x->next=NULL;
	d->next =x;
	return x;
}
void del0(mult *h)	//去0
{
	mult *p=h->next,*q=h;
	while (p != NULL)
	{
		if (abs(p->coef)<mi)
		{
			q->next=p->next;
			delete p;
			p=q->next;
		}
		else {q=p;p=p->next;}
	}
}

void sort_combine(mult *h)//冒泡降幂 合并同类项
{
	int flag=1;
	mult *p=h->next,*q=h->next,*r=h;
	if (!(h->next)) return;
	if (!(h->next->next)) return;
	while (flag)
	{
		flag=0;
		mult *p=h->next->next,*q=h->next,*r=h;
		while ((p) !=NULL)
		{
			if (q->exp < p->exp)
			{
				r->next=p;
				q->next=p->next;
				p->next=q;
				flag=1;
			}
			r=r->next;
			q=r->next;
			p=q->next;
		}
	}
	p=h->next;
	while (p)
	{
		while ((p->next)!=NULL &&(p->exp==p->next->exp))
		{
			q=p->next;
			p->coef+=q->coef;
			p->next=q->next;
			delete(q);
		}
		p=p->next;
	}
}

void output_exp(double x,int i)
{
	if (!i) ;//首位不输正号
	else if (x>0) cout<<'+';
	cout<<x;
}
void output_coef(double l,int i)
{

	if (i)//非首位
	{
		if (l==1) cout<<'+';
		else if (l==-1) cout<<'-';
		else  output_exp(l,i);
	}

	else//首位处理
	{
		if (l==1) ;
		else if (l==-1) cout<<'-';
		else if (l>0) cout<<l;
		else { output_exp(l,i);}
	}
}
void output (mult *head)
{
	//cout.precision(15);//小数精度
	int i=0;
	del0(head);
	mult *p=head->next;
	if ((p == NULL)) cout<<0;
	else 
	{
		do
		{
			if (abs(p->coef)<mi) ;//系数为0
			else if (p->exp == 1)//1次幂
				{output_coef(p->coef,i);cout<<"X";}
			else if (p->exp == 0)// 0次幂
				 output_exp(p->coef,i);
			else
				{output_coef(p->coef,i);cout<<"X^"<<p->exp;}
			p=p->next;
			i++;
		}while (p != NULL);
	}
	cout<<endl;
}

void input (mult *head,FILE *fp)
{
	double c;
	int e;
	char ch;
	mult *p=head;
	do
	{
		fscanf_s(fp,"%lf%d",&c,&e);
		p=attach(p,c,e);
		while ((ch=fgetc(fp))==' ') ;
		if (ch=='\n') break;
		ungetc(ch,fp);
	}while (!feof(fp));
	sort_combine(head);
	del0(head);
}

mult *add(mult *head1,mult *head2)//加到head3
{
	mult *head3;
	make(head3);
	mult *p1=head1->next,*p2=head2->next,*p=head3;
	while(p1 != NULL && p2 != NULL)
	{
		if (p1->exp > p2->exp) {p=attach(p,p1->coef,p1->exp);p1=p1->next;continue;}
		if (p1->exp < p2->exp) {p=attach(p,p2->coef,p2->exp);p2=p2->next;continue;}
		if (p1->coef+p2->coef != 0)
			p=attach(p,p1->coef+p2->coef,p1->exp);
		p1=p1->next;p2=p2->next;
		//output(p);
	}
	while(p1 != NULL)
	{
		p=attach(p,p1->coef,p1->exp);
		p1=p1->next;
	}
	while(p2 != NULL)
	{
		p=attach(p,p2->coef,p2->exp);
		p2=p2->next;
	}
	return head3;
}

void subtract2(mult *head2,mult *head1)//减到head1 去0
{
	 mult *p1=head1->next,*p2=head2->next,*p2_above=head2;
	 mult *t=NULL;
	 while ((p1 != NULL) && (p2 != NULL))
	 {
		 if (p1->exp > p2->exp) 
		 {
			 p2_above=p2;
			 t=new mult;
			 t->exp=p2->exp;t->coef=p2->coef;t->next=p2->next;//p2前插p1
			 p2->exp=p1->exp;p2->coef=-p1->coef;p2->next=t;
			 p1=p1->next;
			 continue;
		 }
		 if (p1->exp == p2->exp) 
		 {
			 p2->coef-=p1->coef;
			 p2_above=p2;
			 p1=p1->next;
			 p2=p2->next;
			 continue;
		 }
		 p2_above=p2;
		 p2=p2->next;
	 }
	 p2=p2_above;
	 while (p1 != NULL)
	 {
		 p2=attach(p2,-p1->coef,p1->exp);
		 p1=p1->next;
	 }
	 del0(head2);
}
/*
void add2(mult *head1,mult *head2)//加到head2 0节点不去除
{
	 mult *p1=head1->next,*p2=head2->next,*p2_above=head2;
	 mult *t=NULL;
	 while ((p1 != NULL) && (p2 != NULL))
	 {
		 if (p1->exp > p2->exp) 
		 {
			 p2_above=p2;
			 t=new mult;
			 t->exp=p2->exp;t->coef=p2->coef;t->next=p2->next;//p2前插p1
			 p2->exp=p1->exp;p2->coef=p1->coef;p2->next=t;
			 p1=p1->next;
			 
			 continue;
		 }
		 if (p1->exp == p2->exp) 
		 {
			 p2->coef+=p1->coef;
			 p2_above=p2;
			 p1=p1->next;
			 p2=p2->next;
			 continue;
		 }
		 p2_above=p2;
		 p2=p2->next;
	 }
	 p2=p2_above;
	 while (p1 != NULL)
	 {
		 p2=attach(p2,p1->coef,p1->exp);
		 p1=p1->next;
	 }
}
*/
mult *subtract(mult *head1,mult *head2)//head1减数，head2被减数
{
	mult *head3=new mult;
	make (head3);
	mult *p1=head1->next,*p2=head2->next,*p=head3;
	while(p1 != NULL && p2 != NULL)
	{
		if (p1->exp > p2->exp) {p=attach(p,p1->coef,p1->exp);p1=p1->next;continue;}
		if (p1->exp < p2->exp) {p=attach(p,-p2->coef,p2->exp);p2=p2->next;continue;}
		if (p1->coef-p2->coef != 0)
			p=attach(p,p1->coef-p2->coef,p1->exp);
		p1=p1->next;p2=p2->next;
	}
	while(p1 != NULL)
	{
		p=attach(p,p1->coef,p1->exp);
		p1=p1->next;
	}
	while(p2 != NULL)
	{
		p=attach(p,-p2->coef,p2->exp);
		p2=p2->next;
	}
	return head3;
}
mult *multiply(mult *head1,mult *head2)//alone add to head2
{
	mult *head3,*t,*p_above;//head3：和 t：中间量
	make (head3);
	mult *p1=head1,*p2,*p=head3;
	double c;int e;
	while((p1= p1->next)!= NULL)
	{
		p2=head2;p=head3->next;p_above=head3;
		while ((p2=p2->next) !=NULL)
		{
			c=(p2->coef)*(p1->coef);e=(p2->exp)+(p1->exp);
			while((p!=NULL)&&(p->exp > e)) {p_above=p;p=p->next;}
			if (p == NULL)
			{
				p=p_above;
				do 
				{
					c=(p2->coef)*(p1->coef);e=(p2->exp)+(p1->exp);
					p=attach(p,c,e);
				}while ((p2=p2->next)!=NULL);
				break;
			}
			if (p->exp < e)
			{
				t=new mult;
				t->exp=p->exp;t->coef=p->coef;t->next=p->next;//前插
				p->exp=e;p->coef=c;p->next=t;
				p_above=p;
				p=p->next;
			}
			if (p->exp == e)
			{
				p->exp=e;p->coef+=c;
				p_above=p;
				p=p->next;
			}
		}
	}
	return head3;
}
/*
mult *multiply2(mult *head1,mult *head2)//add to head2
{
	mult *head3,*t,*temp=NULL;//head3：和 t：中间量
	make (head3);make(t);
	mult *p1=head1,*p2,*p=head3,*pt=t;
	double c;int e;
	while((p1= p1->next)!= NULL)
	{
		p2=head2;pt=t;
		while ((p2=p2->next) !=NULL)
		{
			c=(p2->coef)*(p1->coef);e=(p2->exp)+(p1->exp);
			pt=attach(pt,c,e);
		}
			
			//temp=head3;
			//head3=add(t,head3);
			//del(temp);
			add2(t,head3);
			del(t->next);
	}
	delete(t);
	return head3;
}
*/
mult_divide *divide(mult *head1,mult *head2)//head1/head2
{
	mult *head3,*head4; //head1/head2 head3:配项 head4=head3*head2 head1=head1-head4
	make(head3);make(head4);
	mult_divide *ans=new mult_divide;
	make(ans->quotient);make(ans->remainder);//余数
	mult *p1=head1->next,*p2=head2->next,*p4=head4,*ans_quo=ans->quotient;
	double c;int e;
	while((p1 != NULL) && (p1->exp >= p2->exp))
	{
		c=p1->coef/p2->coef;e=p1->exp-p2->exp;
		attach(head3,c,e);											//配项	
		ans_quo=attach(ans_quo,c,e);								//配项加到商里
		head4=multiply(head3,head2);								//配项*除数
		//temp=subtract(head1,head4);									//被除数-配项*除数
		//del(head1);													//差作为被除数
		//head1=temp;
		subtract2(head1,head4);
		p1=head1->next;
		del(head4);
	}
	ans->remainder=head1;
	del(head3);
	return (ans);

}
void all_output(mult *head1,mult *head2)
{

	mult_divide *answer;
	cout<<"多项式四则\n";
	cout<<"   ";output(head1);cout<<"+  ";output(head2);cout<<"=  ";output(add(head1,head2));cout<<'\n';
	cout<<"   ";output(head1);cout<<"-  ";output(head2);cout<<"=  ";output(subtract(head1,head2));cout<<'\n';
	cout<<"   ";output(head1);cout<<"*  ";output(head2);cout<<"=  ";output(multiply(head1,head2));cout<<'\n';
	if (!(head2->next)) cout<<"除数为0,无意义";
	else 
	{
		cout<<"   ";output(head1);cout<<"/  ";output(head2);cout<<"=  ";
		answer=divide(head1,head2);
		output(answer->quotient);
		cout<<"余 ";
		output(answer->remainder);
	}

}

void compute(mult *h,double x)
{
	mult *p=h,*q;
	double y=0;
	int i,ex,min_exp=0;
	output(h);
	cout<<"在X="<<x<<"处的值为："<<"\n";
	while ((p=p->next) != NULL) min_exp=p->exp;
	if (min_exp<0)
	{
		p=h;
		while ((p=p->next) != NULL) p->exp-=min_exp;
	}
	p=h;
	while ((p=p->next)!=NULL)
	{
		y+=p->coef;
		q=p->next;
		if (q) ex=q->exp;
		else ex=0;
		for (i=0;i<(p->exp-ex);i++) y*=x;
	}
			
		
	if (min_exp<0)for (i=0;i<-min_exp;i++) y/=x;
	cout<<y<<endl;
}
