#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define LL long long
#define seq tr[tr[root].ch[1]].ch[0]
#define INF (1<<29)
using namespace std;
const int N = 510000;
struct node {
	int ch[2], fa, size, v, ll, rr, mm, tt; bool rev, lz;
};
int n, m, w[N];
struct Splay {
	node tr[N]; int tot, tot2, root, s[N];
	void update(int x) { int l = tr[x].ch[0], r = tr[x].ch[1]; tr[x].size = tr[l].size + tr[r].size + 1; tr[x].tt = tr[l].tt + tr[r].tt + tr[x].v; tr[x].ll = max(tr[l].ll, tr[l].tt + tr[x].v + max(0, tr[r].ll)); tr[x].rr = max(tr[r].rr, tr[r].tt + tr[x].v + max(0, tr[l].rr)); tr[x].mm = max(max(tr[l].mm, tr[r].mm), tr[x].v + max(0, tr[l].rr) + max(0, tr[r].ll)); }
	void zig(int x) { int y = tr[x].fa; tr[y].ch[0] = tr[x].ch[1]; if (tr[x].ch[1])tr[tr[x].ch[1]].fa = y; tr[x].ch[1] = y; tr[x].fa = tr[y].fa; tr[y].fa = x; if (tr[x].fa) { if (tr[tr[x].fa].ch[0] == y) tr[tr[x].fa].ch[0] = x; else tr[tr[x].fa].ch[1] = x; }update(y); }
	void zag(int x) { int y = tr[x].fa; tr[y].ch[1] = tr[x].ch[0]; if (tr[x].ch[0])tr[tr[x].ch[0]].fa = y; tr[x].ch[0] = y; tr[x].fa = tr[y].fa; tr[y].fa = x; if (tr[x].fa) { if (tr[tr[x].fa].ch[0] == y) tr[tr[x].fa].ch[0] = x; else tr[tr[x].fa].ch[1] = x; }update(y); }
	void splay(int x, int target) { while (tr[x].fa != target) { int y = tr[x].fa; if (tr[y].fa == target) { tr[y].ch[0] == x ? zig(x) : zag(x); } else { if (tr[tr[y].fa].ch[0] == y) { if (tr[y].ch[0] == x) { zig(y); zig(x); } else { zag(x); zig(x); } } else { if (tr[y].ch[1] == x) { zag(y); zag(x); } else { zig(x); zag(x); } } } }update(x); if (!target) root = x; }
	void downlab(int x) { int l = tr[x].ch[0], r = tr[x].ch[1], ww = tr[x].v; if (tr[x].lz) { if (l) { down(l, ww); }if (r) { down(r, ww); }tr[x].lz = 0; }if (tr[x].rev) { if (l) { rever(l); }if (r) { rever(r); }tr[x].rev = 0; } }
	void search(int x, int target) {
		int y = root; while (1) {
			downlab(y); if (x == tr[tr[y].ch[0]].size + 1) break; if (x <= tr[tr[y].ch[0]].size) { y = tr[y].ch[0]; }
			else {
				x -= (tr[tr[y].ch[0]].size + 1);
				y = tr[y].ch[1];
			}
		}splay(y, target);
	}
	void newnode(int &x, int pnt, int val) {
		x = tot2 ? s[tot2--] : ++tot; tr[x].v = tr[x].tt = tr[x].ll = tr[x].mm = tr[x].rr = val;
		tr[x].rev = tr[x].lz = tr[x].ch[0] = tr[x].ch[1] = 0;
		tr[x].fa = pnt; tr[x].size = 1;
	}
	void init(int n) {
		tr[0].mm = tr[0].ll = tr[0].rr = -INF;
		newnode(root, 0, 0);
		newnode(tr[root].ch[1], root, 0);
		build(seq, tr[root].ch[1], 1, n);
		update(tr[root].ch[1]);
		update(root);
	}
	void build(int &x, int pnt, int l, int r) {
		if (l > r) return;
		int mid = (l + r) >> 1; newnode(x, pnt, w[mid]);
		build(tr[x].ch[0], x, l, mid - 1);
		build(tr[x].ch[1], x, mid + 1, r);
		update(x);
	}
	void insert(int pos, int num) {
		search(pos, 0); search(pos + 1, root);
		build(seq, tr[root].ch[1], 1, num);
		update(tr[root].ch[1]);
		update(root);
	}
	void eraser(int x) {
		if (!x) return; s[++tot2] = x;
		eraser(tr[x].ch[0]); eraser(tr[x].ch[1]);
	}
	void del(int l, int r) {
		search(l, 0); search(r + 2, root);
		eraser(seq);
		tr[tr[tr[root].ch[1]].ch[0]].fa = 0; tr[tr[root].ch[1]].ch[0] = 0;
		update(tr[root].ch[1]); update(root);
	}
	void down(int x, int c) {
		if (!x) return; tr[x].lz = 1; tr[x].v = c;
		tr[x].tt = c*tr[x].size; tr[x].mm = tr[x].ll = tr[x].rr = c > 0 ? tr[x].tt : c;
	}
	void change(int l, int r, int c) {
		search(l, 0); search(r + 2, root); down(seq, c);
		update(tr[root].ch[1]); update(root);
	}
	void rever(int x) {
		if (!x) return; swap(tr[x].ch[0], tr[x].ch[1]);
		tr[x].rev ^= 1; swap(tr[x].ll, tr[x].rr);
	}
	void turn(int l, int r) {
		search(l, 0); search(r + 2, root);
		rever(seq);
	}
	void print(int x) {
		printf("Instructions of x:%d %d %d %d %d %d %d %d %d\n", tr[x].ch[0], tr[x].ch[1], tr[x].fa, tr[x].ll, tr[x].rr, tr[x].mm, tr[x].tt, tr[x].size, tr[x].v);
	}
	void Ask_Max(int sum) {
		search(1, 0); search(sum + 2, root); update(seq);
		printf("%d\n", max(tr[seq].mm, max(tr[seq].ll, tr[seq].rr)));
	}
	void Ask_Sum(int l, int r) {
		search(l, 0); search(r + 2, root);
		printf("%d\n", tr[seq].tt);
	}
}Tree;
char s[20];
int read() {
	char ch = getchar(); int f = 1, x = 0;
	while (ch > '9' || ch < '0') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch <= '9'&&ch >= '0') { x = x * 10 + ch - '0'; ch = getchar(); }
	return f*x;
}
int main() {
	freopen("seq2005.in", "r", stdin);
	freopen("seq2005.out", "w", stdout);
	n = read(); m = read();
	for (int i = 1; i <= n; i++) w[i] = read(); Tree.init(n);
	for (int i = 1, be, Q, W; i <= m; i++) {
		scanf("%s", s + 1);
		if (s[1] == 'I') { be = read(); Q = read(); n += Q; for (int j = 1; j <= Q; j++) w[j] = read(); Tree.insert(be + 1, Q); }
		if (s[1] == 'D') { be = read(); Q = read(); n -= Q; Tree.del(be, be + Q - 1); }
		if (s[1] == 'M'&&s[3] == 'K') { be = read(); Q = read(); W = read(); Tree.change(be, be + Q - 1, W); }
		if (s[1] == 'M'&&s[3] == 'X') { Tree.Ask_Max(n); }
		if (s[1] == 'G') { be = read(); Q = read(); Tree.Ask_Sum(be, be + Q - 1); }
		if (s[1] == 'R') { be = read(); Q = read(); Tree.turn(be, be + Q - 1); }
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}