#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#define SWAP(a,b) a^=b^=a^=b
#define OUTNUM 0
#define NUM 10000000
#define MAXRANGE 10000000
using namespace std;
int a[NUM], b[NUM];

void arraycpy(int a[], int b[], int n) {
	for (int i = 0; i < n; ++i) {
		b[i] = a[i];
	}
}

//shellsort ����ֻ�����
void ss(int a[], int l, int r) {
	int n = r - l + 1;
	for (int gap = n / 2; gap > 0; gap /= 2)
		for (int i = l + gap; i <= r; ++i)
			for (int j = i - gap; j >= l && a[j] > a[j + gap]; j -= gap)
				SWAP(a[j], a[j + gap]);
}

void qs(int a[], int left, int right) {//��ͨ����
	if (left >= right) return;
	int l = left, r = right;
	int k = a[l];//ȡ����
	while (l < r) {
		while (r > l && a[r] >= k) {
			r--;
		}
		a[l] = a[r];
		while (r > l && a[l] <= k) {
			l++;
		}
		a[r] = a[l];
	}
	a[l] = k;
	qs(a, left, l - 1);
	qs(a, l + 1, right);
}

void qs2(int a[], int left, int right) {//�Ż����� ����ȡ�С����š��ظ�Ԫ�ش���
	if (left >= right) return;
	//Ԫ�ظ���<9 ������
	int l = left, r = right;
	int m = l + ((r - l) / 2);
	if (a[r] > a[m] && a[l] < a[m])
		SWAP(a[m], a[l]);
	else if (a[m] > a[r] && a[l] < a[r])
		SWAP(a[r], a[l]);
	if (right - left < 2000) {
		ss(a, left, right);
		return;
	}
	int k = a[l];//ȡ����
	while (l < r) {
		while (r > l && a[r] >= k) {
			r--;
		}
		a[l] = a[r];
		while (r > l && a[l] <= k) {
			l++;
		}
		a[r] = a[l];
	}
	a[l] = k;
	qs2(a, left, l - 1);
	qs2(a, l + 1, right);
}

void qs3(int a[], int left, int right) {
	if (right <= left) return;
	//if (right - left < 10) {
	//	ss(a, left, right);
	//	return;
	//}
	int l = left, r = right, samel = left, samer = right;
	//����ȡ�� mid������a[l]
	int m = l + ((r - l) / 2);
	if (a[r] > a[m] && a[l] < a[m])
		SWAP(a[m], a[l]);
	else if (a[m] > a[r] && a[l] < a[r])
		SWAP(a[r], a[l]);
	int k = a[l];
	while (l < r) {
		while (r > l && a[r] >= k) {
			if (a[r] == k) {
				SWAP(a[r], a[samer]);
				samer--;
			}
			r--;
		}
		a[l] = a[r];
		while (r > l && a[l] <= k) {
			if (a[l] == k) {
				SWAP(a[l], a[samel]);
				samel++;
			}			
			l++;
		}
		a[r] = a[l];
	}
	a[l] = k;
	int i = left, j = l-1;
	while (i < samel && a[j] != k) {
		SWAP(a[i],a[j]);
		i++; j--;
	}
	i = right; j = l + 1;
	while (i > samer && a[j] != k) {
		SWAP(a[i], a[j]);
		i--; j++;
	}
	qs3(a, left, l - (samel-left) - 1);
	qs3(a, l +(right-samer) + 1, right);
}

//radix_sort
const int radix = 100;//����
int whichbucket(int n, int i) {
	return (int)(n / pow(radix, i)) % radix;
}
void rs(int* a, int n) {
	int *bucket = new int[n], *count = new int[n];
	for (int i = 0; i < 4; ++i) {//����100^4��С
		memset(count, 0, sizeof(int)*radix);//radix��Ͱ
		for (int j = 0; j < n; ++j) {
			count[whichbucket(a[j], i)]++;//��Ͱ����
		}
		for (int j = 1; j < radix; ++j) {//�ۼ�
			count[j] += count[j - 1];
		}
		for (int j = n-1; j >= 0; --j) {//�ռ�
			int k = whichbucket(a[j], i);
			bucket[--count[k]] = a[j];//�±�0��ʼ->ǰ��--
		}
		memcpy(a, bucket, sizeof(int)*n);
	}
	delete[] bucket;
	delete[] count;
}

const static int radix2 = 1024;
static int p[] = { 0,10,20 };//���2^30
int whichbucket2(int n, int i) {//2. ��2Ϊ�ף�����λ���� ���������ƣ�ȡģ����
	return n >> p[i] & (radix2 - 1);// (n/2^p[i]) % radix2
}
void rs2(int* a, int n) {
	int *bucket = new int[n], count[radix2];//1. count��̬����
	for (int i = 0; i < 3; ++i) {//���2^30
		memset(count, 0, sizeof(int)*radix2);
		for (int j = 0; j < n; ++j) {
			count[whichbucket2(a[j], i)]++;
		}
		for (int j = 1; j < radix2; ++j) {
			count[j] += count[j - 1];
		}
		for (int j = n - 1; j >= 0; --j) {
			int k = whichbucket2(a[j], i);
			bucket[--count[k]] = a[j];
		}
		memcpy(a, bucket, sizeof(int)*n);
	}
	delete[] bucket;
}

//countingsort��������û�ظ�
void cs(int* a, int n , int k) {//n���������Ϊk
	int *count = new int[k] { 0 }, *bucket = new int[n];
	for (int j = 0; j < n; ++j) {
		count[a[j]]++;
	}
	for (int j = 1; j <= k; ++j) {
		count[j] += count[j - 1];
	}
	for (int j = 0; j < n; ++j) {
		bucket[--count[a[j]]] = a[j];
	}
	memcpy(a, bucket, sizeof(int)*n);
	delete[] bucket;//��֪��delete[] bucket,count; ��
	delete[] count;
}

void cs2(int* a, int n, int k) {//���ۼ���
	int *count = new int[k] { 0 };
	int t = 0;
	for (int j = 0; j < n; ++j) {
		count[a[j]]++;
	}
	for (int j = 0; j <= k; ++j) {
		for (int i = 0; i < count[j]; ++i) {
			a[t++] = j;
		}
	}
	delete[] count;
}

void test() {
	//ios_base::sync_with_stdio(false);
	//ifstream fin("f:\\desktop\\testData_0_9999999.csv");
	ifstream fin("f:\\desktop\\1000data.txt");
	string s;
	getline(fin, s);
	for (int i = 0; i < NUM; ++i) {
		fin >> b[i];
	}
	fin.close();

	clock_t start, end;
	ofstream fout0("f:\\desktop\\ss_out.txt");
	ofstream fout1("f:\\desktop\\qs_out1.txt");
	ofstream fout2("f:\\desktop\\qs_out2.txt");
	ofstream fout3("f:\\desktop\\rs_out1.txt");
	ofstream fout4("f:\\desktop\\rs_out2.txt");
	ofstream fout5("f:\\desktop\\cs_out1.txt");
	ofstream fout6("f:\\desktop\\cs_out2.txt");
	ofstream fout7("f:\\desktop\\stl_out.txt");

	for (int i = 1; i <= 30; ++i) {
		int N = NUM / 30 * i;
		N = 10000000;
		cout << "\ndata size: " << N << endl;
		//stlsort
		arraycpy(b, a, N);
		start = clock();
		sort(a, a + N);
		end = clock();
		cout << "stlsort: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "ms\n";
		if (N == OUTNUM) {
			for (int i = 0; i < N; ++i) {
				fout7 << a[i] << endl;
			}
		}
		//ϣ��
		//arraycpy(b, a, N);
		//start = clock();
		//ss(a, 0, N - 1);
		//end = clock();
		//cout << "shellsort: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "ms\n";
		//if (N == OUTNUM) {
		//	for (int i = 0; i < N; ++i) {
		//		fout0 << a[i] << endl;
		//	}
		//}
		//��ͨ����
		arraycpy(b, a, N);
		start = clock();
		qs(a, 0, N - 1);
		end = clock();
		cout << "normal quicksort: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "ms\n";
		if (N == OUTNUM) {
			for (int i = 0; i < N; ++i) {
				fout1 << a[i] << endl;
			}
		}
		//�Ż�����
		arraycpy(b, a, N);
		start = clock();
		qs3(a, 0, N - 1);
		end = clock();
		cout << "optimized quicksort: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "ms\n";
		if (N == OUTNUM) {
			for (int i = 0; i < N; ++i) {
				fout2 << a[i] << endl;
			}
		}
		//arraycpy(b, a, N);
		//start = clock();
		//qs3(a, 0, N - 1);
		//end = clock();
		//cout << "mof quicksort: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "ms\n";
		//if (N == OUTNUM) {
		//	for (int i = 0; i < N; ++i) {
		//		fout2 << a[i] << endl;
		//	}
		//}
		//��ͨ����
		arraycpy(b, a, N);
		start = clock();
		rs(a, N);
		end = clock();
		cout << "normal radixsort: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "ms\n";
		if (N == OUTNUM) {
			for (int i = 0; i < N; ++i) {
				fout3 << a[i] << endl;
			}
		}
		//�Ż�����
		arraycpy(b, a, N);
		start = clock();
		rs2(a, N);
		end = clock();
		cout << "optimized radixsort: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "ms\n";
		if (N == OUTNUM) {
			for (int i = 0; i < N; ++i) {
				fout4 << a[i] << endl;
			}
		}
		//��ͨ����
		arraycpy(b, a, N);
		start = clock();
		cs(a, N, MAXRANGE);
		end = clock();
		cout << "normal countingsort: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "ms\n";
		if (N == OUTNUM) {
			for (int i = 0; i < N; ++i) {
				fout5 << a[i] << endl;
			}
		}
		//�Ż�����
		arraycpy(b, a, N);
		start = clock();
		cs2(a, N, MAXRANGE);
		end = clock();
		cout << "optimized countingsort: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "ms\n";
		if (N == OUTNUM) {
			for (int i = 0; i < N; ++i) {
				fout6 << a[i] << endl;
			}
		}
	}
	fout7.close();
	fout0.close();
	fout1.close();
	fout2.close();
	fout3.close();
	fout4.close();
	fout5.close();
	fout6.close();
}

void main() {
	test();
	system("pause");
}
