#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
using namespace std;
typedef char datatype;
class treenode{
public:
	datatype key;
	vector<treenode*> child;
	treenode(){
		child.assign(2,NULL);
	}
	~treenode(){}
};
map<datatype,treenode*> m;
ifstream sss("2.txt");
void preorder(treenode *h){
	if (!h) return;
	if (h->key!=0) cout<<h->key;
	for (int i=0;i<(int)h->child.size();i++){
		preorder(h->child[i]);	
	}
}

void Fpreorder(treenode* h){
	if (!h) 
		return;
	for (int i=0;i<(int)h->child.size();i++){
		preorder(h->child[i]);
		cout<<endl;
	}
}

void Tlevelorder(treenode* h){
	if (!h) 
		return;
	treenode* b[1000];
	treenode *p;
	int l=0,r=0;
	b[0]=h;
	while (l<=r){
		p=b[l];
		for (int i=0;i<(int)p->child.size();++i){
			if (p->child[i])
				b[++r]=p->child[i];
		}
		l++;
	}
	for (int i=1;i<=r;i++){
		cout<<b[i]->key;
	}

}

void T2BT(treenode* h){
	if (!h) return;
	for (int i=0;i<(int)h->child.size();i++){
		if (!h->child[i]) continue;
		T2BT(h->child[i]);
		//h->child[i]->child.resize(2,NULL);//É¾
		if (i!=h->child.size()-1)//Á¬
			h->child[i]->child[1]=h->child[i+1];
	}
	h->child.resize(2);//É¾
	h->child[1]=NULL;
}

void BT2T(treenode *h){
	if (!h) return;
	treenode *p=h->child[0];
	h->child.resize(1,NULL);//É¾
	if (!h->child[0]) return;
	while (p=p->child[1]){
		h->child.push_back(p);//Á¬
	}
	if (h->child.size()==1) h->child.resize(2,NULL);
	for (int i=0;i<(int)h->child.size();i++){
		BT2T(h->child[i]);
	}
}

void mapinsert(char ch){
	if (m.find(ch)==m.end()){
		m[ch]=new treenode;
		m[ch]->key=ch;
	}
}

void Tin(){
	//treenode *h=NULL;
	string s="";
	while (cin>>s,s!= "#"){
		mapinsert(s[0]);
		//if (!h) h=m[s[0]];
		m[s[0]]->child.resize(0);
		for (int i=1;i<(int)s.size();i++){
			mapinsert(s[i]);
			m[s[0]]->child.push_back(m[s[i]]);
		}
		if (m[s[0]]->child.size()<3) {
			m[s[0]]->child.resize(2,NULL);
		}
	}
	//return h;
}

treenode* Fin(){
	int n;
	treenode *h=new treenode;
	h->key=0;
	string s="";
	cin>>n>>s;
	h->child.resize(0);
	for (int i=0;i<n;i++){
		mapinsert(s[i]);
		h->child.push_back(m[s[i]]);
	}
	Tin();
	if (n==0) 
		return NULL;
	if (n==1) h->child.resize(2,NULL);
	return h;
}

void main(){
	cin.rdbuf(sss.rdbuf());
	treenode *a=Fin();
	//cout<<"\nForest preorder:\n";
	//Fpreorder(a);
	//Fpreorder2(a);
	T2BT(a);
	cout<<"\nBT preorder: ";
	preorder(a);

	BT2T(a);
	cout<<"\n\nTlevelorder: ";
	Tlevelorder(a);
	system("pause");
}
