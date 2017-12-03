#include<iostream>
#include<map>
#include<algorithm>
#include<queue>

using namespace std;
typedef char vextype;
typedef int costtype;
const costtype infinity=0x3f3f3f3f;
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

struct edge {
	int begin, end;
	costtype cost;
	edge(int begin, int end, int cost) :begin(begin), end(end), cost(cost) {
	}
};

struct compare {
	bool operator()(const edge* l, const edge* r) {
		return (l->cost > r->cost);
	}
};

int n, m;
typedef priority_queue<edge*, vector<edge*>, compare> edgequeue;
edgequeue q;// edge
vexnode **g;//顶点表

map<vextype, int> mm;
vextype *_mm;
int *parent;

ostream & operator<<(ostream &o, edge* &e) {
	o << "<" << _mm[e->begin] << "," << _mm[e->end] << ">" << ' ' << e->cost;
	return o;
}

void Prim() {
	costtype *lowcost = new costtype[n + 1], min, sum = 0;;
	int *closset = new int[n + 1], k;
	memset(lowcost, 0x3f, (n+1)*sizeof(costtype));
	for (int i = 1; i < n + 1; ++i) 
		closset[i] = 1;

	for (auto p = g[1]->next; p; p = p->next)
		lowcost[p->vex] = p->cost;
	for (int i = 2; i <= n; ++i) {
		min = lowcost[i];
		k = i;
		for (int j = 2; j <=n; j++) {
			if (lowcost[j] < min) {
				min = lowcost[j];
				k = j;
			}
		}
		sum += min;
		cout << "<" << _mm[closset[k]] << "," <<  _mm[k] << "> " << min << endl;
		lowcost[k] = infinity+1;
		for (auto p = g[k]->next; p; p = p->next) {
			int v = p->vex;
			if (p->cost < lowcost[v] && lowcost[v] <=infinity) {
				lowcost[v] = p->cost;
				closset[v] = k;
			}
		}
	}
	cout << "total: " << sum << endl;
}

int Find(int x) {
	if (x != parent[x]) {
		parent[x] = Find(parent[x]);//并查集 压缩路径
	}
	return parent[x];
}

void Kruskal() {
	costtype sum = 0;
	parent = new int[n + 1];
	for (int i = 1; i <= n; ++i) {
		parent[i] = i;
	}
	for (int i = 0; i < m; ++i) {
		edge* e = q.top();
		q.pop();
		int bnf = Find(e->begin), edf = Find(e->end);
		if (bnf != edf) {
			parent[bnf] = edf;
			cout << e << endl;
			sum += e->cost;
		}
	}
	cout << "total: " << sum << endl;

}

void createvex(vextype x) {
	static int i=1;
	if (mm[x]) return;
	mm[x] = i;
	_mm[i] = x;
	g[i] = new vexnode;
	++i;
}

void input() {
	vextype x, y;
	costtype z;
	cin >> n >> m;
	_mm = new vextype[n+1];
	g = new vexnode*[n];
	for (int i = 0; i < m; i++){
		cin >> x >> y >> z;
		//edge
		createvex(x); createvex(y);
		q.push(new edge(mm[x], mm[y], z));
		//adjvex
		g[mm[x]]->next = new vexnode(mm[y], g[mm[x]]->next, z);
		g[mm[y]]->next = new vexnode(mm[x], g[mm[y]]->next, z);
	}
}

void main() {
	input();
	cout <<"Kruskal:\n";
	Kruskal();
	cout << "Prim:\n";
	Prim();
	system("pause");
}