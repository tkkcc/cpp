#include<strstream>
#include<iostream>
#include<fstream>
#include<time.h>
#include<map>
#include<string>
#include<vector>
#include<set>
#include <direct.h>
#include<random>
using namespace std;

class missingvalue {
public:
	typedef uniform_int_distribution<int> distribution;
	void input(ifstream &fin) {
		srand(unsigned(time(0)));
		if (!fin) {
			cerr << "can't open train file" << endl;
			return;
		}
		d = 0;
		tuplenum = 0;
		if (!getdimension(fin)) {
			cerr << "get deminsion error" << endl;
			return;
		}
		//vector<string> miss;
		set<string> *feaset = new set<string>[d + 1];
		s = new string[d + 1];
		fin.clear();
		fin.seekg(0, ios::beg);
		while (fin) {
			string line;
			getline(fin, line);
			if (line.size() > 1) {
				pretreatement(line);
				data.push_back(new string[d+1]);
				for (int i = 0; i <= d; ++i) {
					data[tuplenum][i] = s[i];
					feaset[i].insert(s[i]);
				}
				tuplenum++;
			}
		}
		//set->array
		fea = new string*[d + 1];
		size = new int[d + 1];
		for (int i = 0; i <= d; ++i) {
			size[i] = (int)feaset[i].size();
			fea[i] = new string[size[i]];
			int m = 0;
			for (auto j : feaset[i]) {
				fea[i][m++] = j;
			}
			feaset[i].clear();
		}
		delete[] feaset;
		delete[] s;
	}

	void miss(ofstream &fout, const double &k) {
		bool* is = new bool[(d + 1)*tuplenum]{ false };
		distribution dis(0, tuplenum * (d + 1) - 1);
		int i = 0;
		while (i < round(tuplenum * (d + 1) * k)) {
			int r = dis(generator);
			if (!is[r] && (r + 1) % (d + 1) != 0) {
				is[r] = true;
				i++;
			}
		}
		for (int i = 0; i < tuplenum; ++i) {
			for (int j = 0; j < d; ++j)
				if (!is[(i)*(d + 1) + j])
					fout << data[i][j] << ',';
				else
					fout << "?,";
			fout << data[i][d] << "\n";
		}
	}

	void inconsistence(ofstream &fout, const double &k) {
		bool* is = new bool[tuplenum] { false };
		distribution dis(0, tuplenum - 1);
		int i = 0;
		while (i < round(tuplenum * k)) {
			int r = dis(generator);
			if (!is[r]) {
				is[r] = true;
				i++;
			}
		}
		for (int i = 0; i < tuplenum; ++i) {
			for (int j = 0; j < d; ++j)
				fout << data[i][j] << ',';
			fout << data[i][d] << "\n";
			if (!is[i]) continue;
			for (int j = 0; j < d; ++j)
				fout << data[i][j] << ',';
			fout << random(d, data[i][d]) << "\n";
		}
	}
	void conflict(ofstream &fout, const double &k) {
		bool* is = new bool[tuplenum] { false };
		distribution dis(0, tuplenum - 1);
		distribution dis2(0, d - 1);
		int i = 0;
		while (i < round(tuplenum * k / 5)) {
			int r = dis(generator);
			if (!is[r]) {
				is[r] = true;
				i++;
			}
		}
		for (int i = 0; i < tuplenum; ++i) {
			for (int j = 0; j < d; ++j)
				fout << data[i][j] << ',';
			fout << data[i][d] << "\n";
			if (!is[i]) continue;
			for (int j = 0; j < 4; j++) {
				int r = dis2(generator);
				for (int k = 0; k < d; ++k) {
					if (k == r)
						fout << random(k, data[i][k]);
					else
						fout << data[i][k];
					fout << ",";
				}
				fout << data[i][d] << "\n";
			}

		}
	}

	void conflict_normal(ofstream &fout, const double &k, const double *p) {
		vector<vector<bool>> is(tuplenum, vector<bool>(d + 1, 1));
		distribution dis(0, tuplenum - 1);
		for (int i = 0; i < d; i++) {
			int num = 0;
			while (num < round(tuplenum * p[i] / 2)) {
				int r = dis(generator);
				if (is[r][i]) {
					is[r][i] = 0;
					num++;
				}
			}
		}

		for (int i = 0; i < tuplenum; ++i) {
			for (int j = 0; j < d; ++j)
				fout << data[i][j] << ',';
			fout << data[i][d] << "\n";
			for (int j = 0; j < d; j++){
				if (!is[i][j]) {
					for (int k = 0; k < d; k++)	{
						fout << ((k==j)?random(k,data[i][k]):data[i][k]) << ",";
					}
					fout << data[i][d] << "\n";
				}
			}
		}
	}

	void miss_normal(ofstream &fout, const double &k, const double *p) {
		vector<vector<bool>> is(tuplenum, vector<bool>(d + 1, 1));
		distribution dis(0, tuplenum - 1);
		for (int i = 0; i < d; i++) {
			int num = 0;
			while (num < round(tuplenum * p[i])) {
				int r = dis(generator);
				if (is[r][i]) {
					is[r][i] = 0;
					num++;
				}
			}
		}

		for (int i = 0; i < tuplenum; ++i) {
			for (int j = 0; j < d; ++j)
				if (is[i][j])
					fout << data[i][j] << ',';
				else
					fout << "?,";
			fout << data[i][d] << "\n";
		}
	}



	missingvalue() {
		generator.seed((unsigned)time(NULL));
	}
	~missingvalue() {}
private:
	default_random_engine generator;
	string **fea;
	int *size;
	ofstream fout;
	string *s;
	int  d, tuplenum;
	vector<string *> data;
	string random(const int &x, const string & s) {
		string c;
		if (size[x] < 2) {
			cerr << "this feature set size < 2!";
			system("pause");
			exit(0);
		}
		do {
			c = fea[x][rand() % size[x]];
		} while (c == s);
		return c;
	}

	bool isdivide(const char &ch) {
		//if (ch == ',' || ch == ';' || ch == '£¬' || ch == '£»' || ch == ' ')
		if (ch == ' ' )
			return true;
		return false;
	}

	bool getdimension(ifstream &fin) {
		string line;
		getline(fin, line);
		if (line.size() <= 1) return false;
		bool f = false;
		for (auto ch : line) {
			if (isdivide(ch)) {
				if (f) {
					f = false;
					d++;
				}
			}
			else
				f = true;
		}
		fin.seekg(0, ios::beg);
		return true;
	}

	void pretreatement(string &line) {
		for (auto i = line.begin(); i != line.end(); ++i) {
			if (isdivide(*i))
				*i = ' ';
		}
		int q = -1, p;
		for (int i = 0; i <= d; i++) {
			p = q + 1;
			while (line[p] == ' ') ++p;
			q = (int)line.find(' ', p);
			s[i] = line.substr(p, q - p);
		}
	}


};

string tostr(const int &a) {
	strstream ss;
	string s;
	ss << a;
	ss >> s;
	return s;
}

void dataprocess(const string &s, const string &ss) {
	missingvalue m;
	ifstream fin(ss + s + ".data");
	if (!fin) return;
	string dir = ss + s;
#if defined(_WIN32)
	_mkdir(dir.c_str());
#else
	mkdir(dir.c_str(), 0777);
#endif
	m.input(fin);
	for (int i = 10; i <= 50; i += 10) {
		ofstream f1(dir + "//" + tostr(i) + "%-miss" + ".data");
		ofstream f2(dir + "//" + tostr(i) + "%-incons" + ".data");
		ofstream f3(dir + "//" + tostr(i) + "%-conf" + ".data");
		m.miss(f1,i / 100.0);
		m.inconsistence(f2,i / 100.0);
		m.conflict(f3,i / 100.0);
		f1.close();
		f2.close();
		f3.close();
	}
	fin.close();
}

void dataprocess_normal(const string &s, const string &ss, const double p[][14]) {
	missingvalue m;
	ifstream fin(ss + s + ".data");
	if (!fin) return;
	string dir = ss + s + "_normal";
#if defined(_WIN32)
	_mkdir(dir.c_str());
#else
	mkdir(dir.c_str(), 0777);
#endif
	m.input(fin);
	for (int i = 10; i <= 30; i += 10) {
		ofstream f1(dir + "//" + tostr(i) + "%-miss" + ".data");
		ofstream f3(dir + "//" + tostr(i) + "%-conf" + ".data");
		m.miss_normal(f1, i / 100.0, p[i/10-1]);
		m.conflict_normal(f3, i / 100.0, p[i/10-1]);
		f1.close();
		f3.close();
	}
	fin.close();
}

void main() {
/*
	dataprocess("ecoli", "f:\\desktop\\");
	dataprocess("housing", "f:\\desktop\\");
	dataprocess("adult", "f:\\desktop\\");
	dataprocess_normal("housing", "f:\\desktop\\", 
		new double[3][14]{ {0.03,0.05,0.12, 0.15, 0.07,0.04,0.17,0.04,0.07,0.16,0.10,0.01,0.04},
		{ 0.13 ,0.37 ,0.10 ,0.18 ,0.20 ,0.15 ,0.18 ,0.19 ,0.14 ,0.19 ,0.05 ,0.00 ,0.25},
		{ 0.20 ,0.23 ,0.35 ,0.37 ,0.17 ,0.37 ,0.29 ,0.39 ,0.38 ,0.27 ,0.47 ,0.26 ,0.20} }
	);
	
	dataprocess_normal("ecoli", "f:\\desktop\\",
		new double[3][14]{ {0.34 ,0.22 ,0.19 ,0.04 ,0.10 ,0.08 ,0.20},
		{0.25 ,0.13 ,0.30 ,0.24 ,0.11 ,0.35 ,0.21 },
		{0.31 ,0.13 ,0.26 ,0.09 ,0.22 ,0.33 ,0.25} }
	);

	dataprocess_normal("adult", "f:\\desktop\\",
		new double[3][14]{ { 0.24 ,0.16 ,0.04 ,0.14 ,0.06 ,0.22 ,0.23 ,0.20 ,0.07 ,0.12 ,0.19 ,0.03 ,0.15 ,0.07},
		{0.28 ,0.16 ,0.23 ,0.31 ,0.06 ,0.26 ,0.24 ,0.29 ,0.23 ,0.16 ,0.32 ,0.13 ,0.29 ,0.33},
		{0.44 ,0.38 ,0.30 ,0.22 ,0.32 ,0.25 ,0.30 ,0.16 ,0.40 ,0.28 ,0.31 ,0.27 ,0.26 ,0.34 } }
	);*/
	dataprocess("servo", "f:\\desktop\\");
}
