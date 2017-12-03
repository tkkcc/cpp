//kkcckc AhoCorasickDoubleArrayTrie for SS
//20171030
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <list>

using namespace std;

class AC {
private:
    vector<vector<string>> output;
    vector<string> model;
    vector<char> ch;
    vector<long> next, fail, check, base, pos;
public:
    explicit AC() {
        pos.push_back(0);
        check.push_back(0);
        ch.push_back(0);
        fail.push_back(0);
    }

    explicit AC(const vector<string> &m) : AC() {
        model = m;
    }

    void trie() {
        long m = 0, n = 0;
        vector<vector<long>> tmp;
        //ch check
        sort(model.begin(), model.end());
        long num = 0;
        m = static_cast<long>(model.size());
        n = static_cast<long>(max_element(begin(model), end(model),
                                          [](string a, string b) { return a.size() < b.size(); })->size());
        tmp.resize(model.size());
        for (auto &i :tmp) i.resize(static_cast<unsigned long>(n), 0);
        for (long i = 0; i < n; ++i) {
            for (long j = 0; j < m; ++j) {
                if (model[j].size() > i) {
                    if (j > 0 && model[j - 1].size() > i && model[j][i] == model[j - 1][i]) {
                        tmp[j][i] = num;
                    } else {
                        tmp[j][i] = ++num;
                        ch.push_back(model[j][i]);
                        check.push_back(i > 0 ? tmp[j][i - 1] : 0);
                    }
                }
            }
        }
        //next base pos
        list<long> l;
        for (long i = 1; i < check.size(); ++i) {
            l.push_back(i);
            if (i < check.size() - 1 && check[i] != check[i + 1]) {
                bool f = true;
                long t = 1 - ch[l.front()];
                while (f) {
                    f = false;
                    for (auto &j:l) {
                        if (t + ch[j] > next.size())
                            next.resize(static_cast<unsigned long>(t + ch[j] + 1), 0);
                        while (next[t + ch[j]] != 0) {
                            t++;
                            f = true;
                        }
                    }
                }
                base.push_back(t - pos[check[i]]);
                for (auto &j:l) {
                    next[t + ch[j]] = j;
                    pos.push_back(t + ch[j]);
                }
                l.clear();
            }
        }
        //fail
        for (long i = 1; i < check.size(); ++i)
            fail.push_back(check[i] == 0 ? 0 : go(fail[check[i]], ch[i]));
        //output
        output.resize(check.size() + 1);
        for (auto i = 0; i < m; ++i) {
            long x = tmp[i][model[i].size() - 1];
            output[x].push_back(model[i]);
            if (fail[x] != x)
                for (const auto &j: output[fail[x]])
                    output[x].push_back(j);
        }

    }

    //match
    void find(string s) {
        long q = 0;
        for (long c = 0; c < s.size(); ++c) {
            q = go(q, s[c]);
            if (!output[q].empty()) {
                for (auto &j: output[q]) {
                    cout << 1 + c - long(j.size()) << ' ' << j << "  ";
                }
            }
        }
    }

    //goto
    long go(const long &i, const char &j) {
        long t = base[i] + pos[i] + j;
        t = next[t > 0 ? t : 0];
        if (i == check[t]) return t;
        else if (i == 0) return 0;
        else return go(fail[i], j);
    }

    const vector<long> &getNext() const { return next; }

    const vector<long> &getFail() const { return fail; }

    const vector<long> &getCheck() const { return check; }

    const vector<long> &getBase() const { return base; }
};

int main() {
    ifstream fin("1.txt");
    long num;
    fin >> num;
    string s;
    vector<string> model;
    for (long i = 0; i < num; ++i) {
        fin >> s;
        model.push_back(s);
    }
    AC ac(model);
    ac.trie();
    cout << "check\t";
    for (auto &i: ac.getCheck()) cout << i << ' ';
    cout << "\nbase\t";
    for (auto &i: ac.getBase()) cout << i << ' ';
    cout << "\nnext\t";
    auto next = ac.getNext();
    for (auto &i: next) cout << i << ' ';
    num = 0;
    bool f = false;
    for (auto &i: next) {
        if (i != 0) f = true;
        if (f && i==0) num++;
    }
    cout << "\nnext_usage\t"<<double(next.size()-num)/next.size();
    cout << "\nfail\t";
    for (auto &i: ac.getFail()) cout << i << ' ';
    cout << "\nresult\t";
    getline(fin, s);
    getline(fin, s);
    ac.find(s);
    return 0;
}