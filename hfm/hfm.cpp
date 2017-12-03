/*
1.从文件中读入任意一篇英文文本文件，分别统计英文文本文件中各字符（包括标点符号和空格）使用频率；
2.根据字符的使用频率分别构造哈夫曼树，并给出每个字符的哈夫曼编码；
3.将文本文件利用哈夫曼树进行编码，存储成压缩文件（哈夫曼编码文件）；
4.计算哈夫曼编码文件的压缩率；
5.将哈夫曼编码文件译码为文本文件，并与原文件进行比较。
以下可以不做，供思考，做了可以适当加分
6.能否利用堆结构，优化的哈夫曼编码算法。
7.上述1-5的编码译码是基于字符的压缩，考虑基于单词的压缩，完成上述工作，讨论并比较压缩效果。
8.上述1-5的编码是二进制的编码，采用K叉的哈夫曼树完成上述工作，实现“K进制”的编码和译码，并与二进制的编码和译码进行比较。
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define ipath "f:\\desktop\\hfm.in"
#define binpath "f:\\desktop\\hfm.bin"
#define opath "f:\\desktop\\hfm.out"
using namespace std;
typedef char treetype;

int num=-1;
string str="";

string hashtable[128]={""};
struct tn
{
	tn *l;
	tn *r;
	int m;
	char ch;
	int t;
};
typedef tn *tree;
void str2int (int &a,const string &s)
{
	stringstream stream(s);
	stream>>a;
}

void qs(tree v[],int left,int right)
{
	if (left<right)
	{
		tree key=v[left];
		int low=left;
		int high=right;
		while (low<high)
		{
			while (low<high && v[high]->t >= key->t) high--;
			v[low]=v[high];
			while (low<high && v[low]->t <= key->t) low++;
			v[high]=v[low];			
		}
		v[low]=key;
		qs(v,left,low-1);
		qs(v,low+1,right);
	}
}
void preorder(tree o)
{
	if (o==NULL) return;
	if (o->t!=0) 
	{
		cout<<o->ch<<' '<<str<<endl;
		hashtable[o->ch]=str;
	}
	str+="0";
	preorder(o->l);
	str[str.length()-1]='1';
	preorder(o->r);
	str.erase(str.length()-1);
}

void main()
{
	char ch;
	int ssr[128],i,j;
	tree forest[128];
	string sss,strtemp="";
	tree p,root;

	fstream ifile(ipath,ios::in);
	fstream binfile(binpath,ios::binary|ios::out);
	fstream ofile(opath,ios::out);
	if (!ifile.is_open() || !ofile.is_open() || !binfile.is_open()) {cout<<"file can't open";return;}
	cin.rdbuf(ifile.rdbuf());
	cout.rdbuf(ofile.rdbuf());

	//读入
	cin>>noskipws;
	memset(ssr,0,sizeof(ssr));
	while (cin.peek()!=EOF)
	{
		cin>>ch;
		ssr[ch]++;
	}
	//ssr[ch]--;
	//每个字符建树
	for (i=0;i<128;i++)
	{
		if (ssr[i]>0)
		{
			forest[++num]=new tn;
			forest[num]->ch=i;
			forest[num]->t=ssr[i];
			forest[num]->m=0;
			forest[num]->l=forest[num]->r=NULL;
		}
	}
	qs(forest,0,num);//快排

	//建哈夫曼树
	
	for (i=0;i<num;i++)
	{
		p=new tn;
		p->m=forest[i]->t+forest[i+1]->t+forest[i]->m+forest[i+1]->m;
		p->l=forest[i];
		p->r=forest[i+1];
		p->t=0;
		forest[i+1]=p;
		p->t=p->m;
		for (j=i+1;j<num;j++)
		{
			if (forest[j]->t<=forest[j+1]->t) break;
			p=forest[j];forest[j]=forest[j+1];forest[j+1]=p;
		}
		forest[j]->t=0;
	}
	root=forest[num];
	//打hash表
	cout<<"字符编码：\n";
	preorder(root);

	//重读 加密
	ifile.seekg(0,ios::beg);
	cin.rdbuf(ifile.rdbuf());
	while (cin.peek()!=EOF)
	{
		cin>>ch;
		sss+=hashtable[ch];
	}
	binfile.write(&sss[0],sss.length());
	cout<<"二进制加密结果：\n"<<sss<<endl;

	sss="";
	/*
	cout<<"字符加密：\n";
	while (sss.length()>0)
	{
		strtemp=sss.substr(0,8);
		if (strtemp.length()<8) for (;strtemp.length()<8;)	strtemp+='0';
		str2int(j,strtemp);
		ch=j;
		cout<<ch;
		sss+=ch;
		sss.erase(0,8);
	}
	*/
	ifile.close();
	binfile.close();
	/*解密*/
	cout<<"\n由hfm.bin解密:\n"<<endl;
	binfile=fstream(binpath,ios::binary|ios::in);
	if (!binfile.is_open()) cout<<"binfile can't open!";
	p=root;
	while (!binfile.eof())
	{
		binfile.read(&ch,1);
		if (ch=='0') p=p->l;
		else if (ch=='1') p=p->r;
		else {cout<<"hfm.bin wrong format";return;}
		if (p->t!=0) {cout<<p->ch;p=root;}
	}
	binfile.close();
	ofile.close();
}
