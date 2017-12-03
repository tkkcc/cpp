/*
https://github.com/julycoding/The-Art-Of-Programming-By-July/blob/master/ebook/zh/03.01.md
1）每个结点要么是红的，要么是黑的。
2）根结点是黑的。
3）每个叶结点（叶结点即指树尾端NIL指针或NULL结点）是黑的。
4）如果一个结点是红的，那么它的俩个儿子都是黑的。
5）对于任一结点而言，其到叶结点树尾端NIL指针的每一条路径都包含相同数目的黑结点。
*/
#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

#include <iostream>
#include <vector>

namespace red_black_tree {
	using namespace std;
	const int INF = 0x3f3f3f3f;
	enum COLOR { RED, BLACK };
	struct node {
		int k;
		node *p;
		node *l, *r;
		COLOR c;
		node() {}
		node(int k, node *p, node *l, node *r, COLOR c) :
			k(k), p(p), l(l), r(r), c(c) {}
		node& operator = (node& node) {
			this->k = node.k;
			this->p = node.p;
			this->l = node.l;
			this->r = node.r;
			this->c = node.c;
			return *this;
		}
		friend ostream& operator << (ostream& o, node*& a) {
			o << "<" << a->k << ",";
			if (a->c == RED) 
				return o << "RED" << "> ";
			return	o << "BLACK" << "> ";
		}
	};

	node NULL_NODE = { INF,NULL,NULL,NULL,BLACK };

	class Red_Black_Tree {
		node * root;
		int size;
		node * NIL;
		void inorder(node *x);
		void l_rotate(node *x);
		void r_rotate(node *x);
		void RB_Insert_FixUp(node *z);
		void RB_Delete_FixUp(node *z);
		void Transplant(node * u, node * v);
		node * minnode(node * root);
		node * maxnode(node * root);

	public:
		Red_Black_Tree() : size(0), NIL(&NULL_NODE), root(&NULL_NODE) {}// root NIL指向同一个节点
		void level_order();
		void insert(int k);
		void del(int k);
		void search(int k);
		void print();
		node *find(int k);
	};

	void Red_Black_Tree::search(int k) {
		node *p = root;
		while (p != NIL && p->k != k) {
			cout << p->k << "->";
			if (p->k > k)
				p = p->l;
			else
				p = p->r;
		}
		if (p == NIL)
			cout << "not found" << endl;
		else
			cout << p->k <<" found"<< endl;
	}

	void Red_Black_Tree::level_order() {
		if (root == NIL) {
			cerr << "not node" << endl;
			return;
		}
		cout << "level_order: ";
		vector<node*> q;
		vector<int> p;
		p.push_back(0);
		q.push_back(root);
		int tmp = -1;
		for (int i = 0; i < (int)q.size(); ++i) {
			if (tmp != p[i]) {
				tmp = p[i];
				cout << endl;
			}
			cout << q[i];
			if (q[i]->l != NIL) {
				q.push_back(q[i]->l);
				p.push_back(p[i] + 1);
			}
			if (q[i]->r != NIL) 
				q.push_back(q[i]->r);
				p.push_back(p[i] + 1);
		}
		cout << endl;
	}

	void Red_Black_Tree::inorder(node *x){
		if (x == NIL)
			return;
		inorder(x->l);
		cout << x;
		inorder(x->r);
	}

	void Red_Black_Tree::print() {
		cout << "preorder: " << endl;
		inorder(root);
		cout << endl;
	}


	void Red_Black_Tree::l_rotate(node *x) {
		if (x->r == NIL) return;
		node *y = x->r;
		x->r = y->l; 
		if (y->l != NIL) {
			y->l->p = x;
		}
		y->p = x->p; 
		if (x->p == NIL) {
			root = y;
		}
		else if (x == x->p->l) {
			x->p->l = y;
		}
		else {
			x->p->r = y;
		}
		y->l = x;    
		x->p = y;
	}

	void Red_Black_Tree::r_rotate(node *y) {
		if (y->l == NIL)
			return;
		node *x = y->l;
		y->l = x->r;
		if (x->r != nullptr) {
			x->r->p = y;
		}
		x->p = y->p;
		if (y->p == NIL) {
			root = x;
		}
		else if (y == y->p->l) {
			y->p->l = x;
		}
		else {
			y->p->r = x;
		}
		x->r = y;
		y->p = x;
	}

	void Red_Black_Tree::Transplant(node * u, node * v) {//v->u
		if (u->p == NIL) {
			root = v;
		}
		else if (u == u->p->l) {
			u->p->l = v;
		}
		else {
			u->p->r = v;
		}
		v->p = u->p;
	}

	node *Red_Black_Tree::find(int k) {
		node *p = root;
		while (p != NIL && p->k != k) {
			if (p->k > k)
				p = p->l;
			else
				p = p->r;
		}
		return p;
	}

	node *Red_Black_Tree::minnode(node *root) {
		node * p = root;
		while (p->l != NIL) {
			p = p->l;
		}
		return p;
	}

	node *Red_Black_Tree::maxnode(node *root) {
		node * p = root;
		while (p->r != NIL) {
			p = p->r;
		}
		return p;
	}

	void Red_Black_Tree::insert(int k) {
		node *z = new node(k, NIL, NIL, NIL, RED);
		node *y = NIL;
		node *x = root;
		while (x != NIL) {
			y = x;
			if (k < x->k)
				x = x->l;
			else
				x = x->r;
		}
		z->p = y;
		if (y == NIL) {
			root = z;
		}
		else if (z->k < y->k) {
			y->l = z;
		}
		else {
			y->r = z;
		}
		RB_Insert_FixUp(z);
	}

	void Red_Black_Tree::del(int k) {
		node *z = find(k);
		if (z == NIL) {
			cout << "not found " << endl;
			return;
		}
		node *y = z;
		COLOR y_original_color = y->c;
		node *x;
		if (z->l == NIL) {
			x = z->r;
			Transplant(z, z->r);
		}
		else if (z->r == NIL) {
			x = z->l;
			Transplant(z, z->l);
		}
		else {
			y = minnode(z->r);
			y_original_color = y->c;
			x = y->r;
			if (y->p == z) {
				x->p = y;
			}
			else {
				Transplant(y, y->r);
				y->r = z->r;
				y->r->p = y;
			}
			Transplant(z, y);
			y->l = z->l;
			y->l->p = y;
			y->c = z->c;
		}
		if (y_original_color == BLACK)
			RB_Delete_FixUp(x);
		delete z;
	}

	void Red_Black_Tree::RB_Insert_FixUp(node *z) {
		while (z->p->c == RED) {
			if (z->p == z->p->p->l) {
				node *y = z->p->p->r;
				//父红叔红 父黑叔黑祖红向祖
				if (y->c == RED) {
					z->p->c = BLACK;
					y->c = BLACK;
					z->p->p->c = RED;
					z = z->p->p;
				}
				else {
					//父红叔黑父右 向父左旋
					if (z == z->p->r) {
						z = z->p;
						l_rotate(z);
					}
					//父红叔黑父左 父黑祖红祖右旋
					z->p->c = BLACK;
					z->p->p->c = RED;
					r_rotate(z->p->p);
				}
			}
			else {
				node *y = z->p->p->l;
				if (y->c == RED) {
					z->p->c = BLACK;
					y->c = BLACK;
					z->p->p->c = RED;
					z = z->p->p;
				}
				else {
					if (z == z->p->l) {
						z = z->p;
						r_rotate(z);
					}
					z->p->c = BLACK;
					z->p->p->c = RED;
					l_rotate(z->p->p);
				}
			}
		}
		root->c = BLACK;
	}

	void Red_Black_Tree::RB_Delete_FixUp(node *x) {
		while (x != root && x->c == BLACK) {
			if (x == x->p->l) {
				node *w = x->p->r;
				//黑且兄红 父红兄黑
				if (w->c == RED) {
					w->c = BLACK;
					w->p->c = RED;
					r_rotate(w);
					w = x->p->r;
				}
				//黑且兄黑兄子全黑 兄红向父
				if (w->l->c == BLACK && w->r->c == BLACK) {
					w->c = RED;
					x = x->p;
				}
				else {
					//黑兄黑兄左红右黑 兄红兄左黑兄右旋
					if (w->r->c == BLACK) {
						w->l->c = BLACK;
						w->c = RED;
						r_rotate(w);
						w = x->p->r;
					}
					//黑兄黑兄右红 兄色=父色父黑兄右黑父左旋结束
					w->c = x->p->c;
					x->p->c = BLACK;
					w->r->c = BLACK;
					l_rotate(x->p);
					x = root;
				}
			}
			else {
				node *w = x->p->l;
				if (w->c == RED)
				{
					w->c = BLACK;
					w->p->c = RED;
					l_rotate(w);
					w = x->p->l;
				}

				if (w->l->c == BLACK && w->r->c == BLACK) {
					w->c = RED;
					x = x->p;
				}
				else {
					if (w->l->c == BLACK) {
						w->r->c = BLACK;
						w->c = RED;
						l_rotate(w);
						w = x->p->l;
					}
					w->c = x->p->c;
					x->p->c = BLACK;
					w->l->c = BLACK;
					r_rotate(x->p);
					x = root;
				}
			}
		}
		x->c = BLACK;
	}
}//namespace red_black_tree;
#endif // !RED_BLACK_TREE_H_
