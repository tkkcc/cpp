#include <iostream>
#include <vector>
#include <map>
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
		g[m[y]]->next = new EdgeNode(g[m[x]]->adjvex, x, g[m[y]]->next);
	}
}

template <typename T>
T min(T x, T y) {
	if (x > y) return y;
	return x;
}

//bioconnected_judge
int counter, apcounter;
void dfs(int u) {
	static bool first = true;
	static int *dfn = new int[N + 1], *low = new int[N + 1], *parent = new int[N + 1];
	if (first) {
		first = false;
		memset(dfn, 0, (N + 1) * sizeof(int));
		memset(parent, 0, (N + 1) * sizeof(int));
		parent[u] = 0;
	}
	int children = 0;
	dfn[u] = low[u] = ++counter;
	for (auto p = g[u]->next; p; p = p->next) {
		int v = p->adjvex;
		if (!dfn[v]) {
			children++;
			parent[v] = u;
			dfs(v);
			low[u] = min(low[u], low[v]);
			if (!parent[u] && children > 1) {//根节点 对根节点u，若其有两棵或两棵以上的子树，则该根结点u为割点；
				apcounter++;
				cout << g[u]->data << ' ';
			}
			if (parent[u] && low[v] >= dfn[u]) {//非根节点 若其子树的节点均没有指向u的祖先节点的回边，说明删除u之后，根结点与u的子树的节点不再连通；则节点u为割点。
				apcounter++;
				cout << g[u]->data << ' ';
			}
		}
		else if (v != parent[u]) {//v已访问，则(u,v)为回边
			low[u] = min(low[u], dfn[v]);
		}
	}
}

void main() {
	input();
	cout << endl;
	dfs(1);//单从1深搜 有几个关节点
	if (counter < N)
		cout << "\nnot a biconnected graph";
	else if(apcounter == 0)
		cout << "\nis a biconnected graph";
	else if (apcounter)
		cout << "\narticulation point num: " << apcounter << "\nnot a biconnected graph";
	system("pause");
}
