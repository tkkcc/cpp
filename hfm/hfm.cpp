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

	//����
	cin>>noskipws;
	memset(ssr,0,sizeof(ssr));
	while (cin.peek()!=EOF)
	{
		cin>>ch;
		ssr[ch]++;
	}
	//ssr[ch]--;
	//ÿ���ַ�����
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
	while (cin.peek()!=EOF)
	{
		cin>>ch;
		sss+=hashtable[ch];
	}
	binfile.write(&sss[0],sss.length());
	cout<<"�����Ƽ��ܽ����\n"<<sss<<endl;

	sss="";
	/*
	cout<<"�ַ����ܣ�\n";
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
	/*����*/
	cout<<"\n��hfm.bin����:\n"<<endl;
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
