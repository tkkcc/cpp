#include "sort.h"
void q(int n){
	cout<<"\nn="<<n<<endl;
	create(n);
	cout<<"�����������(Ĭ�����ǰ"<<good<<"����)��";
	print(a,n);
	//qs
	memcpy(b,a,sizeof(a));
	LARGE_INTEGER m_nFreq;  
    LARGE_INTEGER m_nBeginTime;  
    LARGE_INTEGER nEndTime;  
    QueryPerformanceFrequency(&m_nFreq); // ��ȡʱ������  
    QueryPerformanceCounter(&m_nBeginTime); // ��ȡʱ�Ӽ���  
    qs(b,0,n-1);
    QueryPerformanceCounter(&nEndTime);  
	cout<<"\n����(Ĭ�����ǰ"<<good<<"����)��";
	print(b,n);
    cout <<"\n����ʱ��:"<<(double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart << "ms";  
	//bubble
	memcpy(b,a,sizeof(a));
    QueryPerformanceCounter(&m_nBeginTime); // ��ȡʱ�Ӽ���  
    bubble(b,n);
    QueryPerformanceCounter(&nEndTime);  
	cout<<"\nð��(Ĭ�����ǰ"<<good<<"����)��";
	print(b,n);
    cout << "\nð��ʱ��:"<<(double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart << "ms\n"; 
}

void s(int n){
	int k=12;
	cout<<"\nn="<<n<<" ��"<<k<<endl;
	create(n);
	qs(a,0,n-1);
	LARGE_INTEGER m_nFreq;  
    LARGE_INTEGER m_nBeginTime;  
    LARGE_INTEGER nEndTime;  
    QueryPerformanceFrequency(&m_nFreq); // ��ȡʱ������  
    QueryPerformanceCounter(&m_nBeginTime); // ��ȡʱ�Ӽ���  
	binsearch(a,0,n-1,k);
    QueryPerformanceCounter(&nEndTime);  
    cout <<"\n�۰���ҵݹ�ʱ��:"<<(double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart << "ms\n";  
	QueryPerformanceCounter(&m_nBeginTime); // ��ȡʱ�Ӽ���  
	binsearch2(a,0,n-1,k);
    QueryPerformanceCounter(&nEndTime);  
    cout <<"\n�۰���ҷǵݹ�ʱ��:"<<(double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart << "ms\n";  
}

void main()
{
	int n;
	ios::sync_with_stdio(false);
	cout<<"����:";
	q(10);
	q(100);
	q(1000);
	q(10000);
	//q(100000);

	cout<<"\n����:";
	s(10);
	s(100);
	s(1000);
	s(10000);
	getchar();
	getchar();
	getchar();
}
