/*

��������Cʵ�֣��ӳ���qi��qo��qp�û��ʵ�֣�incp��Cʵ�֡�C�ɷ���ASM��n��
�ֱ��ύ C.CPP��ASM.ASM��������
*/

#include <stdio.h>
#include <conio.h>

//�����ⲿ����Ķ������������

extern "C"	int qo(char* chrr,int *pii,char *buff);
extern "C"	int qi(int eeax,int *pii,char *buff);
extern "C"	int qp(int poo,int pii,char *buff);
extern "C"  int pi,po,n;
extern "C"  char chr;
extern "C"	char buf[16];

//Ϊ�ⲿ�����ṩ�Ķ������������
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
	printf("��ѡ��ESC �˳���- �Ӷ�����ȡԪ����ʾ +��ӡ��ǰ���У�0-9A-Z������У�����������\n");
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
			else printf("��ȡ��Ԫ��Ϊ��%c\n",chr);
			break;
		default:
			if ((ch>='0' && ch<='9')||(ch>='A' && ch<='Z'))
				if (!qi(ch,&pi,buf)) printf(" FULL!\n");
		}
		ch=_getche();
	}
	return 0;
}