#include <iostream>
#include <string>
using namespace std;
enum tag{link,thread};
class node{
public:
	char data;
	node* l;
	node* r;
	tag lflag,rflag;
	node():l(NULL),r(NULL),lflag(link),rflag(link){};
	node(char data,node* l,node* r,tag x,tag y):data(data),l(l),r(r),lflag(x),rflag(y){};
	~node(){};
};
string s;
node* head;

void rmthread(node* &a){//a->b
	if (!a)
		return;
	//b=new node(a->data,a->lflag==thread?NULL:a->l,a->rflag==thread?NULL:a->r,link,link);
	if (a->lflag==thread){
		a->lflag=link;
		a->l=NULL;
	}
	if (a->rflag==thread){
		a->rflag=link;
		a->r=NULL;
	}
	rmthread(a->l);
	rmthread(a->r);
}

void create(node* &h){
	static int i=0;
	char ch=s[i++];
	if ('#' == ch)
		h = NULL;
	else{
		h = new node(ch,NULL,NULL,link,link);
		create(h->l);      
		create(h->r);   
	}
}

void print(node* h){
	if (!h) return;
	cout<<h->data;
	print(h->l);
	print(h->r);
}

void postthread(node* &p){
	static node* pre=NULL;
	if (!p)
		return;
	postthread(p->l);
	postthread(p->r);
	if (!p->l){
		p->lflag=thread;
		p->l=pre;
	}
	if (pre && !pre->r){
		pre->rflag=thread;
		pre->r=p;
	}
	pre=p;
}

void prethread(node* &p){
	static node* pre=NULL;
	if (!p)
		return;
	if (!p->l){
		p->lflag=thread;
		p->l=pre;
	}
	if (pre && !pre->r){
		pre->rflag=thread;
		pre->r=p;
	}
	pre=p;	
	if (p->lflag==link)
		prethread(p->l);
	if (p->rflag==link)
		prethread(p->r);
}

void postorder(node* h){
	if (!h)
		return;
	string s;
	node *p=h;
	while (p!=NULL){
		s+=p->data;
		if (p->rflag==link)
			p=p->r;
		else
			p=p->l;
	}
//	cout<<s.size();
	for (auto i=s.rbegin();i!=s.rend();i++)
		cout<<*i;
}
int i=0;
void preorder(node* h){
	if (!h)
		return;
	cout<<h->data;
	i++;
	if (h->lflag==link)
		preorder(h->l);
	else
		preorder(h->r);
}

void main(){
	//s="FBA##DC##E##G#IH###";
	s="AB#CD###E#FGH##K###";
	create(head);
	cout<<"preorder:\t";
	print(head);
	postthread(head);
	cout<<"\npostorder by postthread:\t";
	postorder(head);
	cout<<"\npreorder by prethread:\t";
	rmthread(head);
	prethread(head);
	preorder(head);
	//cout<<i<<endl;
	cout<<endl;
	system("pause");
}