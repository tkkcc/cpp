#include<iostream>
#include<map>
#include<vector>
using namespace std;
typedef char EdgeData;
class EdgeNode {
public:
	int adjvex;
	EdgeData data;
	EdgeNode * next;
	EdgeNode(int adjvex, EdgeData data, EdgeNode * next) :
		adjvex(adjvex), data(data), next(next) {
	}
	EdgeNode() :next(NULL) {
	}
};

typedef vector<EdgeNode*> graph;
map<EdgeData, int> m;
graph g;
int N;

void createnode(EdgeData x) {
	if (m[x]) return;
	g.push_back(new EdgeNode(++N, x, NULL));
	m[x] = N;
}

void input() {//input graph
	int n;
	EdgeData x, y;
	g.push_back(NULL);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> x >> y;
		createnode(x);
		createnode(y);
		g[m[x]]->next = new EdgeNode(g[m[y]]->adjvex, y, g[m[x]]->next);
	}
}

//tarjan
int *dfn, *low, *s, top, counter, sum;
bool *ins;

void dfs(int u) {
	int v;
	dfn[u] = low[u] = ++counter;//序号
	s[++top] = u; 
	ins[u] = true;//加入堆栈
	for (auto i = g[u]->next; i; i = i->next) {
		v = i->adjvex;
		if (!dfn[v]) {
			dfs(v);
			low[v] < low[u] ? low[u] = low[v]:0;
		}
		else if (ins[v] && dfn[v] < low[u])//能回退到更前
			low[u] = dfn[v];
	}
	if (dfn[u] == low[u]) {
		cout << endl;
		sum++;
		do {
			v = s[top--];
			ins[v] = false;
			cout << g[v]->data << ' ';
		} while (v != u);
	}
}

void solve() {
	s = new int[N+1];
	dfn = new int[N+1];
	low = new int[N+1];
	ins = new bool[N+1];
	memset(dfn, 0, (N+1)*sizeof(int));
	memset(ins, 0, (N+1)*sizeof(bool));
	for (int i = 1; i <= N; i++)
		if (!dfn[i])
			dfs(i);
	cout << "\ntotal: " << sum;
}

void main() {
	input();
	solve();
	system("pause");
}