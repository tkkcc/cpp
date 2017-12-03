#include <iostream>
#include <queue>
#include <string>
#define MAX 300
using namespace std;
int sum[MAX];//全局变量默认初始化
string ss[MAX];//同上
const string s1="aaaaabbbcccccdddefgggggggggghhhhiiiiiiiiiiiijkkllllmmnooooppppp";
const string s2="apple";
string ssr;
string sss;
const int k=5;
struct minheapnode{
	char data;			 
	unsigned freq;			 
	vector<minheapnode*> child; 
	minheapnode(char data, unsigned freq):data(data),freq(freq){
		child.resize(k,NULL);
	}
	minheapnode():data(0),freq(0){
		child.resize(k,NULL);
	}
};

struct compare{
	bool operator()(minheapnode* l, minheapnode* r){
		return (l->freq > r->freq);
	}
};

void print(minheapnode* root, string str){
	if (!root)
		return;
	if (root->data != 0){
		cout << root->data << ": " << str << "\n";
		ss[root->data]=str;
	}
	for (int i=0;i<k;++i){
		print(root->child[i],str+char(i+48));
	}
}

minheapnode* huffman(){
	priority_queue<minheapnode*, vector<minheapnode*>, compare> minheap;
	for (int i = 0; i < MAX; ++i){
		if (sum[i]){
			minheap.push(new minheapnode(i, sum[i]));
		}
	}
	int k0=(minheap.size()-1)%(k-1);
	if (k0){
		for (int i=0;i<k-1-k0;i++,minheap.push(new minheapnode));
	}
	while (minheap.size() != 1)	{
		minheapnode *top=new minheapnode();
		for (int i=0;i<k;++i){
			top->child[i]=minheap.top();
			top->freq+=top->child[i]->freq;
			minheap.pop();
		}
		minheap.push(top);
	}
	return minheap.top();
}

void  encode(){
	for (int i = 0; i < s2.size(); i++){
		ssr+=ss[s2[i]];
	}
}

void decode(minheapnode* root){
	minheapnode* p=root;
	for (int i=0;i<ssr.size();++i){
		p=p->child[ssr[i]-48];
		if (p->data) {
			sss+=p->data;
			p=root;
		}
	}
}
/*
void printtree(minheapnode* h){
	minheapnode* p;
	if (!h)
		return;
	cout<<"\n"<<h->data<<'\t';
	for (auto i:h->child)
		if (i){
			cout<<i->data;
		}
			
	for (auto i:h->child)
		printtree(i);
}*/

void main(){
	for (int i=0;i<s1.size();++i){
		sum[s1[i]]++;
	}
	minheapnode* root=huffman();
	//printtree(root);
	cout<<endl;
	print(root,"");
	encode();
	cout<<"encode: "<<ssr<<endl;
	decode(root);
	cout<<"decode: "<<sss<<endl;
	system("pause");
}
