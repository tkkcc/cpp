//kkcckc 20171216 00:16 白盒测试 圈复杂度和基本路径
// c98 path没封装
#define SSTR(x) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#include <iostream>
#include <map>
#include <queue>
#include <cstdlib>
#include <sstream>

using namespace std;

//n1:F|N n2:T f:walkthrough f1:n->n1 walkthrough
struct node {
    node(int d) : d(d), n1(NULL), n2(NULL), f(false), f1(false), f2(false) {};

    node(int d, node *n1, node *n2) : d(d), n1(n1), n2(n2), f(false), f1(false), f2(false) {};
    int d;
    node *n1, *n2;
    bool f, f1, f2;
};

typedef vector<int> path;

struct path_compare {
    bool operator()(path a, path b) {
        if (a.size() == b.size()) {
            for (int i = 0; i < a.size(); ++i) {
                if (a[i] > b[i]) return true;
                else if (a[i] < b[i]) return false;
            }
        }
        return a.size() > b.size();

    }
};

priority_queue<path, vector<path>, path_compare> results;
map<int, node *> m;

path result;
int start;
//walk through num (before)
int wtn = 0, wtnb = 0;

void dfs(node *x) {
//    cout << result + SSTR(',' << x->d)<<endl;
    if (x->f || (x->n1 == NULL && x->n2 == NULL)) {
        if (wtn > wtnb) {
            wtnb = wtn;
//            result.push_back(x->d);
            path p(result);
            p.push_back(x->d);
            results.push(p);
        }
        return;
    }
    x->f = true;
    result.push_back(x->d);
    if (x->n1 != NULL) {
        if (!x->f1) {
            x->f1 = true;
            wtn++;
        }
        dfs(x->n1);
    }
    if (x->n2 != NULL) {
        if (!x->f2) {
            x->f2 = true;
            wtn++;
        }
        dfs(x->n2);
    }
    result.pop_back();
    x->f = false;
}

int main() {
    int CC = 0;
//    int start_basic;
//    cin >> start_basic;
//    start=start_basic;
    cin >> start;
    string s;
    while (cin >> s, s != "END" && s != "EXT") {
        unsigned long pos = s.find('-');
        int x = atoi(s.substr(0, pos).c_str());
        int y = atoi(s.substr(pos + 2).c_str());
        if (m.find(x) == m.end()) m[x] = new node(x);
        if (m.find(y) == m.end()) m[y] = new node(y);
        node *_x = m[x], *_y = m[y];
        if (*s.rbegin() == 'T') _x->n2 = _y;
        else _x->n1 = _y;
        if (_x->n1 != NULL && _x->n2 != NULL) CC++;
    }
    if (s == "EXT") {
        while (cin >> s, s != "END") {
            CC++;
            unsigned long pos = s.find(',');
            int x = atoi(s.substr(0, pos).c_str());
            int y = x * 10;
            node *_x = m[x];
            _x->d = y + 1;
//            if (x==start) start=y+1;
            if (*s.rbegin() == 'R') _x->n1 = new node(y + 2, _x->n1, _x->n2);
            else _x->n2 = new node(y + 2, _x->n1, _x->n2);
        }
    }
//    dfs(m[start_basic]);
    dfs(m[start]);
    cout << "CC=" << CC + 1 << endl;
    while (!results.empty()) {
        path p = results.top();
        cout << p[0];
        for (int i = 1; i < p.size(); ++i) {
            cout << ',' << p[i];
        }
        cout << endl;
        results.pop();
    }
    return 0;
}