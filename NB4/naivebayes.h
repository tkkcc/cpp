//Author: kkcckc
//Naive Bayes Classify
#ifndef NAIVEBAYES_NAIVEBAYES_NAIVEBAYES_H_
#define NAIVEBAYES_NAIVEBAYES_NAIVEBAYES_H_
#include<cstdlib>
#include<cstdio> // 
#include<cmath> //abs 
#include<cstring> // for memset
#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<vector>
#include <thread>
#include <chrono>

namespace naivebayes {
	using namespace std;
	class NaiveBayes {
	public:
		struct gauss {
			double ave = 0, a2 = 0, num = 0;//u均值，a2方差
			vector<double> arr;
		};
		void train(ifstream &fin, const string &miss, int continu[] = NULL) {
			missingsign = miss;
			if (!fin) over("can't open train file");
			d = mmtop = 0;
			if (!getdimension(fin)) over("get deminsion error");
			con = new int[d + 1]();
			if (continu)
				memcpy(con, continu, (d + 1) * sizeof(int));
			s = new string[d + 1];
			mm = new map<string, int>[d + 1];
			ff = new map<int, gauss>[d];
			while (fin) {
				string line;
				getline(fin, line);
				if (line.size() <= 1) continue;
				pretreatement(line);
				add();
			}

			//连续型处理
			for (int i = 0; i < d; ++i) {
				if (!con[i]) continue;//连续才做
				for (int j = d; j <= d; ++j) {
					if (con[j]) continue;//对每个离散
					for (auto k : mm[j]) {
						auto q = &(ff[i][k.second]);
						if (!q) continue;
						double sum = 0, ave = 0;
						for (auto l : q->arr) {
							sum += l;
						}
						q->ave = ave = sum / q->num;
						sum = 0;
						for (auto l : q->arr) {
							sum += pow((l - ave), 2);
						}
						q->a2 = sum / q->num;
					}
				}
			}
		}

		void test(ifstream &fin, double ans[]) {
			if (!fin) over("can't open test file");
			if (!istrained()) over("not trained");
			map<string, int> dia, colsum, rowsum;
			while (fin) {
				string line;
				getline(fin, line);
				if (line.size() <= 1) continue;
				pretreatement(line);
				string maxstring = predict();
				if (s[d] == missingsign) continue;
				if (s[d] == maxstring) dia[s[d]]++;
				rowsum[s[d]]++;
				colsum[maxstring]++;
			}
			double P = 0, R = 0, F = 0;
			for (auto i : dia) {
				double p = (double)i.second / colsum[i.first], r = (double)i.second / rowsum[i.first];
				P += p; R += r; F += 2 * p * r / (p + r);
			}
			int num = dia.size();
			ans[0] = P / num; ans[1] = R / num; ans[2] = F / num;
		}

		NaiveBayes() {}
		~NaiveBayes() {
			delete[] s;
			delete[] mm;
			delete[] con;
			//delete ff[0];
			delete[] ff;
		}

	private:
		map<string, int> *mm;
		string missline, missingsign;
		string *s;
		int d, mmtop;
		int *con;
		map<int, int> count;
		map<int, map<int, int>> f;
		map<int, gauss> *ff;

		void over(const string &s) {
			cerr << s << endl;
			cin.get();
			exit(0);
		}

		bool istrained() {
			if (d == 0 || s == NULL)
				return false;
			return true;
		}

		bool isdivide(const char &ch) {
			if (ch == ',' || ch == ';' || ch == ' ')
				return true;
			return false;
		}

		string predict(int x = -1) {
			if (x == -1) x = d;//预测第x个，默认第d个即分类
			if (con[x]) {
				//连续型预测1
				return missingsign;
			}
			//离散型
			double k = 1, max, r;
			string maxstring;
			for (auto i = mm[x].begin(); i != mm[x].end(); ++i) {
				double t = count[i->second], p = log(t);
				for (int j = 0; j <= d; ++j) {
					if (j == x || s[j] == missingsign) continue;
					if (con[j]) {
						auto qq = &(ff[j][i->second]);
						if (!qq) {//// train 对该类全 miss，赋0，即不考虑了
							p += log(0);
							continue;
						}

						if (s[j] == missingsign) {
							p += log(qq->ave);
						}

						double q;
						if (abs(qq->a2) < 0.00000001)
							//方差为0,高斯分布退化为直线
							q = qq->ave;
						else
							q = exp(-pow(stod(s[j]) - qq->ave, 2) /
							(2 * qq->a2)) / sqrt(qq->a2);//sqrt(2pi)无需考虑
						p += log(q);
					}
					else {
						r = f[m(j, s[j])][m(x, i->first)];
						p += log(r + k) - log(t + k*mm[j].size());
					}
				}
				if (i == mm[x].begin() || p > max) {
					maxstring = i->first;
					max = p;
				}
			}
			return maxstring;
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

		int m(const int &i, const string &s) {
			return mm[i][s];
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

		void add() {
			bool flag = false;
			for (int i = 0; i <= d; i++) {
				if (!con[i] && mm[i].find(s[i]) == mm[i].end()) {
					mm[i][s[i]] = mmtop++;
				}
				//if (s[i] == missingsign) flag =true;//有连续型缺失 全不加入
			}
			if (flag) return;
			for (int i = 0; i <= d; i++) {
				if (s[i] == missingsign) continue;//连续型缺失 部分加入
				if (!con[i]) {
					count[m(i, s[i])]++;
					for (auto j = d; j <= d; ++j) {
						if (i == j || con[j] || s[j] == missingsign) continue;
						f[m(i, s[i])][m(j, s[j])]++;
					}
				}
				else {
					//连续
					for (int j = d; j <= d; ++j) {//start=0全预测
						if (i == j || con[j] || s[j] == missingsign) continue;
						if (ff[i].find(m(j, s[j])) == ff[i].end())
							ff[i].insert(pair<int, gauss>(m(j, s[j]), *(new gauss)));
						ff[i][m(j, s[j])].arr.push_back(stod(s[i]));
						ff[i][m(j, s[j])].num++;
					}
				}
			}
		}
	};
}
#endif //NAIVEBAYES_NAIVEBAYES_NAIVEBAYES_H_