#if defined(_WIN32)
#define pd "\\"
#define mkdir(aaa) {string t = "md " + aaa; system(t.c_str());}
#define rmdir(aaa) {string t = "rd /s /q " + aaa; system(t.c_str());}
//#elif defined(__linux__)
#else 
#define pd "/"
#define mkdir(aaa) {string t = "mkdir -p " + aaa; system(t.c_str());}
#define rmdir(aaa) {string t = "rm -Rf " + aaa; system(t.c_str());}
#define rmdir(aaa) {string t = "rm -Rf " + aaa; system(t.c_str());}
#endif

#include "naivebayes.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <random>

using namespace std;
//default_random_engine gen(time(NULL));
default_random_engine gen(time(0));
ofstream fout;
void over(const string &s = "can't open file") {
	cerr << s << endl;
	cin.get();
	exit(0);
}

void t(const string &s1, const string &s2, int a[], double ans[][4], int m) {
	clock_t start, end;
	for (int i = 10; i <= m; i += 10) {
		ifstream ftrain(s1 + pd + to_string(i) + "%-" + s2 + "7.data");
		ifstream ftest(s1 + +pd + to_string(i) + "%-" + s2 + "3.data");
		if (!ftrain || !ftest) over("testfile wrong");
		start = clock();
		naivebayes::NaiveBayes nb;
		nb.train(ftrain, "?", a);
		nb.test(ftest, ans[i / 10 - 1]);
		end = clock();
		ans[i / 10 - 1][3] = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
		ftrain.close();
		ftest.close();
	}
}

void split(const string &s2, const string &s3, int m) {
	string dir73 = s2 + "73";
	string dir = s2;
	for (int i = 10; i <= m; i += 10) {
		ifstream fin(dir + pd + to_string(i) + "%-" + s3 + ".data");
		ofstream fout1(dir73 + pd + to_string(i) + "%-" + s3 + "7.data");
		ofstream fout2(dir73 + pd + to_string(i) + "%-" + s3 + "3.data");
		if (!fin || !fout1 || !fout2) over("split wrong");
		vector<string> v;
		string s;
		while (fin) {
			getline(fin, s);
			if (s.size() <= 1) continue;
			v.push_back(s);
		}
		int tuplenum = (int)v.size();
		bool *is = new bool[tuplenum]();
		uniform_int_distribution<int> dis(0, tuplenum - 1);
		for (int i = 0; i < round(tuplenum*0.3); ++i) {
			int r = dis(gen);
			if (!is[r])
				is[r] = 1;
			else
				--i;
		}
		for (int i = 0; i < tuplenum; i++) {
			if (!is[i])
				fout1 << v[i] << "\n";
			else
				fout2 << v[i] << "\n";
		}
		fin.close();
		fout1.close();
		fout2.close();
	}
}

void tt(const string &s1, const string &s, int m, int con[]) {
	double ans[5][4], tmp[5][4];
	memset(ans, 0, sizeof(ans));
	mkdir(s1 + "73")
	int times = 10;
	for (int i = 0; i < times; ++i) {
		split(s1, s, m);
		t(s1 + "73", s, con, tmp, m);
		for (int j = 0; j < m / 10; ++j)
			for (int k = 0; k < 4; ++k)
				ans[j][k] += tmp[j][k] / times;
	}
	fout << "\"NB_" << s1 << "\"\n";
	if (m == 50) fout << "\"uniform\","; else fout << "\"normal\",";
	for (int i = 10; i <= m; i += 10)
		fout << "\"" << to_string(i) + "%-" + s << "\",";
	fout << "\n";
	for (int j = 0; j < 4; ++j) {
		if (j == 0) fout << "\"P\","; else if (j == 1) fout << "\"R\",";
		else if (j == 2) fout << "\"F1\","; else fout << "\"time(ms)\",";
		for (int i = 0; i < m / 10; i += 1)
			fout << "\"" << ans[i][j] << "\",";
		fout << "\n";
	}
	fout << "\n";
	rmdir(s1 + "73")
}

void ttt(const string &s, int con[]) {
	fout.open("NB_" + s + ".csv");
	if (!fout) over("can't open out.csv");
	//cout.rdbuf(fout.rdbuf());
	//fout << "\"1.P 2.R 3.F1 4.time(ms)\"\n";
	tt(s, "miss", 50, con);
	tt(s, "incons", 50, con);
	tt(s, "conf", 
		50, con);
	tt(s + "_normal", "miss", 30, con);
	tt(s + "_normal", "conf", 30, con);
	fout.close();
}

int main() {
	//int a[37]; for (int i = 0; i < 37; ++i) a[i] = 1;
	//ttt("ecoli", new int[8] { 1, 1, 1, 1, 1, 1, 1, 0 });
	//ttt("adult", new int[15]{ 1,0,1,0,1,0,0,0,0,0,1,1,1,0,0});
	//ttt("car", new int[7]());
	//ttt("chess", new int[37]());
	cin.get();
	this_thread::sleep_for(chrono::milliseconds(3000));
	cin.get();

	ttt("iris",new int[5] {1,1,1,1,0});
	cerr << "ok";
	//cin.get();
	return 0;
}

