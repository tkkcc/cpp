#include<map>
#include<iostream>
#define MAX 20
using namespace std;

typedef char vextype;
const int inf = 0x3f3f3f3f;
typedef int costtype;
struct edge {
	int begin, end;
	costtype cost;
	edge(int begin, int end, int cost) :begin(begin), end(end), cost(cost) {
	}
};

int n, m, p[MAX][MAX];
costtype dist[MAX];
edge **q;
map<vextype, int> mm;
vextype *_mm;

void createvex(vextype x) {
	static int i = 1;
	if (mm[x]) return;
	mm[x] = i;
	_mm[i] = x;
	++i;
}

void input() {
	vextype x, y;
	costtype z;
	cin >> n >> m;
	_mm = new vextype[n + 1];
	q = new edge*[m];
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> z;
		createvex(x); createvex(y);
		q[i] = new edge(mm[x],mm[y],z);
	}
}

bool bf(int A) {
	memset(p, -1, sizeof(p));
	memset(dist, 0x3f, sizeof(dist));
	dist[A] = 0;
	for (int i = 0; i < m; i++) 
		if (q[i]->begin == A)
			dist[q[i]->end] = q[i]->cost;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int u = q[j]->begin, v = q[j]->end, c = q[j]->cost;
			if (dist[v] > dist[u] + c) {
				dist[v] = dist[u] + c;
				if (u != A)
					p[A][v] = u;
				if (i == n-1) 
					return 0;
			}
		}
	}
	return 1;
}


void printway(int x, int y) {
	if (p[x][y] == -1) cout << "->" << _mm[y];
	else {
		printway(x, p[x][y]);
		printway(p[x][y], y);
	}
}

void test() {
	vextype x, y;
	cout << "input A,B: ";
	cin >> x >> y;
	if (bf(mm[x])) {
		cout << "bellman_ford: " << dist[mm[y]] << '\n' << x;
		printway(mm[x], mm[y]);
	}
	else
		cout << "Negative loop exist\n";
}
void main()
{
	input();
	test();
	system("pause");
}


