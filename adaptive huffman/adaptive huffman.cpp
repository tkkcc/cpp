#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>
#include <cstdlib>
#define NUM 300
#define NYT 256
#define COM 257//普通节点
using namespace std;

struct node{
	int d,w,p,l,r;
	string s;
	void nodee(int d,int w,int p,int l,int r,string s){
		this->d=d;
		this->w=w;
		this->p=p;
		this->l=l;
		this->r=r;
		this->s=s;
	}
	node():d(0),w(0),p(-1),l(-1),r(-1),s(""){}
	node(int d,int w,int p,int l,int r,string s):
		d(d),w(w),p(p),l(l),r(r),s(s){}
	~node(){}
};

void restring(const int x,node* a[],const string s){//改变孩子的string
	if (x==-1) return;
	a[x]->s=s;
	restring(a[x]->l,a,s+'0');
	restring(a[x]->r,a,s+'1');
}
template<typename T>
void swapp(T &a, T &b) {
	T t=a;a=b;b=t;
}
void swap(int x,int y,int where[],node* a[]){
	string s;
	swapp(a[x]->d,a[y]->d);
	swapp(a[x]->l,a[y]->l);
	swapp(a[x]->r,a[y]->r);
	if (a[x]->l!=-1) a[a[x]->l]->p=x;
	if (a[x]->r!=-1) a[a[x]->r]->p=x;
	if (a[y]->l!=-1) a[a[y]->l]->p=y;
	if (a[y]->r!=-1) a[a[y]->r]->p=y;
	restring(x,a,a[x]->s);
	restring(y,a,a[y]->s);
	where[a[x]->d]=x;	
	where[a[y]->d]=y;
}

void oneplus(int t,int where[],node *a[]){
	if (t==-1)
		return;
	int max=t;
	if (a[t]->w!=0){//等于0不需要找
		for (int i=NYT;i>t;i--){
			if (a[i]->w==a[t]->w){
				max=i;
				break;
			}
		}
		if (max!=t && a[t]->p!=max)
			swap(t,max,where,a);
		t=max;
	}
	a[t]->w++;
	oneplus(a[t]->p,where,a);
}

string encode(){
	char ch;
	int where[NUM],t;
	memset(where,-1,sizeof(where));
	where[NYT]=NYT;//256=NYT,初始放在末尾
	node *a[NUM];
	a[NYT]=new node(NYT,0,-1,-1,-1,"");
	string s;
	while (cin>>ch){
		if (where[ch]==-1){
			bitset<sizeof(char)*8> bs(ch);
			t=where[NYT];
			s+=a[t]->s+bs.to_string();
			a[t-2]=new node(NYT,0,t,-1,-1,a[t]->s+'0');
			a[t-1]=new node(ch,1,t,-1,-1,a[t]->s+'1');
			a[t]->nodee(COM,0,a[t]->p,t-2,t-1,a[t]->s);
			where[ch]=t-1;where[NYT]=t-2;
			oneplus(t,where,a);
		}
		else{
			s+=a[where[ch]]->s;
			oneplus(where[ch],where,a);
		}
	}
	return s;
}

string decode(){
	char ch;
	int p;
	int where[NUM];
	memset(where,-1,sizeof(where));
	where[NYT]=NYT;
	node *a[NUM];
	a[NYT]=new node(NYT,0,-1,-1,-1,"");
	string s;
	//string ss((istreambuf_iterator<char>(cin)),istreambuf_iterator<char>());
	//怎么忽略/0？
	string ss;
	int length=cin.seekg(0,ios::end).tellg();
	cin.seekg(0,ios::beg);
	for(int i=0;i<length;i++){
		cin>>ch;
		ss+=ch;
	}
	/*
	int length=cin.seekg(0,ios::end).tellg();
	cin.seekg(0,ios::beg);    
	char* buffer = new char[length];   
	cin.read(buffer,length);
	string ss(buffer);
	*/
	int y=0;
	string ssr(8*ss.size(),0);
	for (auto i:ss){
		p=(i+256)%256;
		for (int j=0;j<8;j++){
			ssr[y+7-j]=p%2+48;
			p/=2;
		}
		y+=8;
	}
	ssr.erase(ssr.end()-(*(ss.end()-1))-8,ssr.end());

	y=0;
	for(;;){
		p=NYT;		
		if(ssr.size()-y<10){
			y=y;
		}
		if (y==ssr.size()) break;
		while(a[p]->d==COM){
			ch=ssr[y++];
			p=ch=='0'?a[p]->l:a[p]->r;
		}
		if(a[p]->d==NYT){
			int a=0;
			for(int i=0;i<8;i++){
				a=a*2+ssr[y++]-48;
			}
			ch=a;
		}
		else
			ch=a[p]->d;
		s+=ch;
		if (where[ch]==-1){
			int t=where[NYT];
			a[t-2]=new node(NYT,0,t,-1,-1,a[t]->s+'0');
			a[t-1]=new node(ch,1,t,-1,-1,a[t]->s+'1');
			a[t]->nodee(COM,0,a[t]->p,t-2,t-1,a[t]->s);
			where[ch]=t-1;where[NYT]=t-2;
			oneplus(t,where,a);
		}
		else{
			oneplus(where[ch],where,a);
		}
	}
	return s;
}

string compress(string s){
	string ss;
	int x=0,y=0;
	for (auto i:s){
		x=x*2+i-48;
		y++;
		if (y==8){
			ss+=x;
			x=y=0;
		}
	}
	for (int i=0;i<8-y;i++) x=x*2;
	ss+=x;
	return ss.append(1,8-y);
}

void main(){
	cin>>noskipws;
	fstream f1("1.txt",ios::in),f2("2.txt",ios::out|ios::binary);
	cin.rdbuf(f1.rdbuf());
	f2<<compress(encode());
	double rate=((double)f2.tellp()/(double)f1.tellg());
	f1.close();f2.close();
	f2.open("2.txt",ios::in|ios::binary);
	cin.rdbuf(f2.rdbuf());
	f1.open("3.txt",ios::out);
	f1<<"rate: "<<rate<<endl<<decode();
	f1.close();f2.close();
}
