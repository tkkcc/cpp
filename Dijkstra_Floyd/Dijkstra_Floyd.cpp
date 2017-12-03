#include<vector>
#include<map>
#include<iostream>
using namespace std;
#define MAX 20
typedef int costtype;
typedef char vextype;
const int inf = 0x3f3f3f3f;
typedef char vextype;
typedef int costtype;
int n, m, p[MAX][MAX], t[MAX][MAX];
costtype a[MAX][MAX], d[MAX][MAX], dist[MAX];

map<vextype, int> mm;
vextype *_mm;

void createvex(vextype x) {
	static int i = 1;
	if (mm[x]) return;
	mm[x] = i;
	_mm[i] = x;
	//g[i] = new vexnode;
	++i;
}

void input() {
	vextype x, y;
	costtype z;
	cin >> n >> m;
	_mm = new vextype[n + 1];
	memset(a, 0x3f, sizeof(a));
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> z;
		//edge
		createvex(x); createvex(y);
		a[mm[x]][mm[y]] = a[mm[y]][mm[x]] = z;

	}
}

void dijk(int A) {
	memset(p, -1, sizeof(p));
	memset(dist, 0x3f, sizeof(dist));
	bool vis[MAX] = { false };
	dist[A] = 0;
	for (int i = 1; i <= n; ++i) {
		int cur = -1;
		for (int j = 1; j <= n; ++j) {
			if (vis[j]) continue;
			if (cur == -1 || dist[j] < dist[cur]) {
				cur = j;
			}
		}
		vis[cur] = true;
		for (int j = 1; j <= n; ++j) {
			if (dist[cur] + a[cur][j] < dist[j]) {
				dist[j] = dist[cur] + a[cur][j];
				if (cur != A) 
					p[A][j] = cur;
			}
		}
	}
}
void floyd() {
	int i, j, k;
	for (i = 1; i<=n; ++i)
		for (j = 1; j<=n; ++j) {
			d[i][j] = a[i][j];
			p[i][j] = -1;
		}
	for (k = 1; k<=n; ++k)
		for (i = 1; i<=n; ++i)
			for (j = 1; j<=n; ++j)
				if (d[i][k] + d[k][j]<d[i][j]) {
					d[i][j] = d[i][k] + d[k][j];
					p[i][j] = k;
				}
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
	floyd();
	cout << "Floyd: " << d[mm[x]][mm[y]] << '\n' << x;
	printway(mm[x], mm[y]);

	//dijkstra
	dijk(mm[x]);
	cout << "\ndijkstra: " << dist[mm[y]] << "\n" << x;
	printway(mm[x], mm[y]);
}
void main()
{
	input();
	test();
	system("pause");
}


