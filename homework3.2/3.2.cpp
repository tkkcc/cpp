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
//#define binpath "f:\\desktop\\hfm.bin"
#define mpath "f:\\desktop\\code.txt"
#define opath "f:\\desktop\\hfm.out"
using namespace std;
typedef char treetype;

long num=-1;
string str="";

string hashtable[257]={""};
struct tn
{
	tn *l;
	tn *r;
	long m;
	char ch;
	long t;
};
typedef tn *tree;
void str2long (long &a,const string &s)
{
	stringstream stream(s);
	stream>>a;
}

void qs(tree v[],long left,long right)
{
	if (left<right)
	{
		tree key=v[left];
		long low=left;
		long high=right;
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
	char ch,ch1;
	long ssr[257],k,i,j,extra,m,eend,z;
	double y=0,w=0;
	tree forest[128];
	string sss,strtemp="";
	tree p,root;
	//cout<<"请输入文本文件绝对路径 '\'用'\\'\n";
	//cin>>sss;
	//fstream ifile(sss,ios::in);
	fstream ifile(ipath,ios::in);
	fstream mfile(mpath,ios::out);
	fstream ofile(opath,ios::out);
	if (!ifile.is_open() || !ofile.is_open() || !mfile.is_open()) {cout<<"file can't open";return;}
	cin.rdbuf(ifile.rdbuf());
	cout.rdbuf(ofile.rdbuf());

	//读入
	cin>>noskipws;
	memset(ssr,0,sizeof(ssr));
	while (cin.peek()!=EOF)
	{
		cin>>ch;
		ssr[ch]++;
		w++;
	}
	//每个字符建树
	for (i=0;i<257;i++)
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
	sss="";
	while (cin.peek()!=EOF)
	{
		cin>>ch;
		sss+=hashtable[ch];
		while (sss.length()>=8)
		{
			j=0;
			for (i=0;i<8;i++)
			{
				j=j*2+(sss[i]-48);
			}
			sss.replace(0,8,"");
			mfile<<char(j);
			y++;
		}
	}
	//补位
	extra=0;
	if (sss!="") 
	{
		extra=8-sss.length();
		sss.replace(sss.length(),0,extra,'0');
		j=0;
		for (i=0;i<8;i++)
		{
			j=j*2+(sss[i]-48);
		}
		mfile<<char(j);
		y++;
	}
	mfile<<extra;
	sss="";
	ifile.close();
	mfile.close();
	/*解密*/
	cout<<"\n由code.txt解密:"<<endl;
	mfile=fstream(mpath,ios::in);
	if (!mfile.is_open()) cout<<"binfile can't open!";
	//到文件末尾读补位数
	mfile.seekg(-1,ios::end);
	eend=mfile.tellg();//记录最后位置
	mfile>>extra;
	//解
	mfile.seekg(0,ios::beg);
	p=root;m=8;z=0;
	for (z=0;z<eend;z++)
	{
		mfile>>ch1;
		if (z==eend-1) m=8-extra;//最后减少循环次数
		j=long(ch1);
		k=0x80;
		for (i=0;i<m;i++)
		{
			p=(!(j&k))?p->l:p->r;
			k>>=1;
			if (p->t!=0) {cout<<p->ch;p=root;}
		}
	}
	cout<<"\n压缩率:\t"<<y/w;
	mfile.close();
	ofile.close();
}
