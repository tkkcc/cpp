#include "sort.h"
void q(int n){
	cout<<"\nn="<<n<<endl;
	create(n);
	cout<<"随机整型数组(默认输出前"<<good<<"个数)：";
	print(a,n);
	//qs
	memcpy(b,a,sizeof(a));
	LARGE_INTEGER m_nFreq;  
    LARGE_INTEGER m_nBeginTime;  
    LARGE_INTEGER nEndTime;  
    QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期  
    QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数  
    qs(b,0,n-1);
    QueryPerformanceCounter(&nEndTime);  
	cout<<"\n快排(默认输出前"<<good<<"个数)：";
	print(b,n);
    cout <<"\n快排时间:"<<(double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart << "ms";  
	//bubble
	memcpy(b,a,sizeof(a));
    QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数  
    bubble(b,n);
    QueryPerformanceCounter(&nEndTime);  
	cout<<"\n冒泡(默认输出前"<<good<<"个数)：";
	print(b,n);
    cout << "\n冒泡时间:"<<(double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart << "ms\n"; 
}

void s(int n){
	int k=12;
	cout<<"\nn="<<n<<" 找"<<k<<endl;
	create(n);
	qs(a,0,n-1);
	LARGE_INTEGER m_nFreq;  
    LARGE_INTEGER m_nBeginTime;  
    LARGE_INTEGER nEndTime;  
    QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期  
    QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数  
	binsearch(a,0,n-1,k);
    QueryPerformanceCounter(&nEndTime);  
    cout <<"\n折半查找递归时间:"<<(double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart << "ms\n";  
	QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数  
	binsearch2(a,0,n-1,k);
    QueryPerformanceCounter(&nEndTime);  
    cout <<"\n折半查找非递归时间:"<<(double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart << "ms\n";  
}

void main()
{
	int n;
	ios::sync_with_stdio(false);
	cout<<"排序:";
	q(10);
	q(100);
	q(1000);
	q(10000);
	//q(100000);

	cout<<"\n查找:";
	s(10);
	s(100);
	s(1000);
	s(10000);
	getchar();
	getchar();
	getchar();
}
