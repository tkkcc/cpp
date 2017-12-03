/*

主程序用C实现，子程序qi、qo、qp用汇编实现，incp用C实现。C可访问ASM的n。
分别提交 C.CPP与ASM.ASM两个程序。
*/

#include <stdio.h>
#include <conio.h>

//调用外部程序的东东在这儿声明

extern "C"	int qo(char* chrr,int *pii,char *buff);
extern "C"	int qi(int eeax,int *pii,char *buff);
extern "C"	int qp(int poo,int pii,char *buff);
extern "C"  int pi,po,n;
extern "C"  char chr;
extern "C"	char buf[16];

//为外部程序提供的东东在这儿声明
extern "C"
{
	
	char ch;
	void incp(int *poo);
}
void incp(int *poo)
{
	(*poo)++;
	*poo = (*poo) % 16;
}


int main()
{
	//char ch;
	printf("请选择：ESC 退出；- 从队列提取元素显示 +打印当前队列；0-9A-Z进入队列，其他抛弃。\n");
	ch=_getche();
	while (ch != 0x1B)
	{
		switch (ch)
		{
		case '+':
			qp(po,pi,buf);
			break;
		case '-':
			if (!qo(&chr,&po,buf)) printf(" EMPTY!\n");
			else printf("提取的元素为：%c\n",chr);
			break;
		default:
			if ((ch>='0' && ch<='9')||(ch>='A' && ch<='Z'))
				if (!qi(ch,&pi,buf)) printf(" FULL!\n");
		}
		ch=_getche();
	}
	return 0;
}
