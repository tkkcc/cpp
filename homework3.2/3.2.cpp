/*
1.���ļ��ж�������һƪӢ���ı��ļ����ֱ�ͳ��Ӣ���ı��ļ��и��ַ������������źͿո�ʹ��Ƶ�ʣ�
2.�����ַ���ʹ��Ƶ�ʷֱ������������������ÿ���ַ��Ĺ��������룻
3.���ı��ļ����ù����������б��룬�洢��ѹ���ļ��������������ļ�����
4.��������������ļ���ѹ���ʣ�
5.�������������ļ�����Ϊ�ı��ļ�������ԭ�ļ����бȽϡ�
���¿��Բ�������˼�������˿����ʵ��ӷ�
6.�ܷ����öѽṹ���Ż��Ĺ����������㷨��
7.����1-5�ı��������ǻ����ַ���ѹ�������ǻ��ڵ��ʵ�ѹ��������������������۲��Ƚ�ѹ��Ч����
8.����1-5�ı����Ƕ����Ƶı��룬����K��Ĺ��������������������ʵ�֡�K���ơ��ı�������룬��������Ƶı����������бȽϡ�
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
	//cout<<"�������ı��ļ�����·�� '\'��'\\'\n";
	//cin>>sss;
	//fstream ifile(sss,ios::in);
	fstream ifile(ipath,ios::in);
	fstream mfile(mpath,ios::out);
	fstream ofile(opath,ios::out);
	if (!ifile.is_open() || !ofile.is_open() || !mfile.is_open()) {cout<<"file can't open";return;}
	cin.rdbuf(ifile.rdbuf());
	cout.rdbuf(ofile.rdbuf());

	//����
	cin>>noskipws;
	memset(ssr,0,sizeof(ssr));
	while (cin.peek()!=EOF)
	{
		cin>>ch;
		ssr[ch]++;
		w++;
	}
	//ÿ���ַ�����
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
	qs(forest,0,num);//����
	//����������
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
	//��hash��
	cout<<"�ַ����룺\n";
	preorder(root);

	//�ض� ����
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
	//��λ
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
	/*����*/
	cout<<"\n��code.txt����:"<<endl;
	mfile=fstream(mpath,ios::in);
	if (!mfile.is_open()) cout<<"binfile can't open!";
	//���ļ�ĩβ����λ��
	mfile.seekg(-1,ios::end);
	eend=mfile.tellg();//��¼���λ��
	mfile>>extra;
	//��
	mfile.seekg(0,ios::beg);
	p=root;m=8;z=0;
	for (z=0;z<eend;z++)
	{
		mfile>>ch1;
		if (z==eend-1) m=8-extra;//������ѭ������
		j=long(ch1);
		k=0x80;
		for (i=0;i<m;i++)
		{
			p=(!(j&k))?p->l:p->r;
			k>>=1;
			if (p->t!=0) {cout<<p->ch;p=root;}
		}
	}
	cout<<"\nѹ����:\t"<<y/w;
	mfile.close();
	ofile.close();
}
