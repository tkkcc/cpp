/*
	多项式四则
	2016.10.19 by kkcckc
*/
#include "multi.h"

void main()
{
	int flag;
	double x;
	mult *head1,*head2;
	//hint();
	FILE *fp=NULL;
	if ((fp=fopen(IPATH,"r"))<0) {cout<<"无法打开输入文件";exit(0);};
	ofstream fpp(OPATH,ios::out);
	if (!fpp) exit(0);
	streambuf *oldbuf = cout.rdbuf(fpp.rdbuf());


	fscanf(fp,"%d",&flag);
	if (!flag) 
	{
		make (head1);
		input (head1,fp);
		fscanf(fp,"%lf",&x);
		compute(head1,x);
	}
	else
	{
		make (head1);make(head2);
		input(head1,fp);input(head2,fp);
		all_output(head1,head2);
	}
	fclose(fp);
	cout.rdbuf(oldbuf);
	fpp.close();
}

