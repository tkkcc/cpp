#include<iostream>
#include<map>
#define infinity 0x3f3f3f3f 
#define MAX 20
using namespace std;

typedef char vextype;
typedef int costtype;
struct vexnode {
	int vex;
	costtype cost;
	vexnode * next;
	vexnode(int vex, vexnode * next, costtype cost) :
		vex(vex), next(next), cost(cost) {
	}
	vexnode() :next(NULL) {
	}
};
int n, m, p[MAX][MAX];
costtype *dist;
map<vextype, int> mm;
vextype *_mm;
int *vis, *topo;
vexnode **g;
int top;
bool dfs(int u) {
	vis[u] = -1;//-1用来表示顶点u正在访问  
	for (auto p = g[u]->next; p; p = p->next) {
		int v = p->vex;
		if (vis[v] == -1)//有环
			return false;
		else if (vis[v] == 0) {
			dfs(v);
		}
	}
	vis[u] = 1;
	topo[top++] = u;
	return true;
}

bool toposort(int x) {
	topo = new int[n + 1];
	vis = new int[n + 1];
	memset(vis, 0, (n + 1) * sizeof(vis));
	if (!dfs(x)) {//只从源点排序
		cerr << "loop exist";
		return false;
	}
	//倒序
	for (int i = 0; i < top/2; i++) {
		int t = topo[i];
		topo[i] = topo[top - 1 - i];
		topo[top - 1 - i] = t;
	}
	return true;
}

void createvex(vextype x) {
	static int i = 1;
	if (mm[x]) return;
	mm[x] = i;
	_mm[i] = x;
	g[mm[x]] = new vexnode;
	++i;
}

void input() {
	vextype x, y;
	costtype z;
	cin >> n >> m;
	_mm = new vextype[n + 1];
	g = new vexnode*[n +  1];
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> z;
		createvex(x); createvex(y);
		g[mm[x]]->next = new vexnode(mm[y], g[mm[x]]->next, z);
	}
}

void printway(int x, int y) {
	if (p[x][y] == -1) cout << "->" << _mm[y];
	else {
		printway(x, p[x][y]);
		printway(p[x][y], y);
	}
}

void fpath(int x) {
	if (!toposort(x)) return;
	dist = new costtype[n+1];
	memset(dist, 0x3f, (n + 1) * sizeof(dist));
	dist[x] = 0;
	memset(p, -1, sizeof(p));
 	for (int j = 0; j < top; ++j) {
		int u = topo[j];
		for (auto q = g[u]->next; q; q = q->next) {
			int v = q->vex, c = q->cost;
			if (dist[v] > dist[u] + c) {
				dist[v] = dist[u] + c;
				if (u != x)
					p[x][v] = u;
			}
		}
	}
}

void test() {
	vextype x, y;
	cout << "input A,B: ";
	cin >> x >> y;
	fpath(mm[x]);
	cout << "distance: " << dist[mm[y]] << '\n' << x;
	printway(mm[x], mm[y]);
}

void main() {
	input();
	test();
	system("pause");
}