#ifndef SPLAYTREE_H_
#define SPLAYTREE_H_
#include <iostream>

template<typename T>
class splaytree {
	struct node {
		T key;
		node* l = NULL;
		node* r = NULL;
		node() {}
		node(T key) :key(key) {}
		node(T key, node *l, node *r) :key(key), l(l), r(r) {}
	};

	node* root = NULL;

	node* rroate(node* x) {
		node *y = x->l;
		x->l = y->r;
		y->r = x;
		return y;
	}

	node* lroate(node* x) {
		node* y = x->r;
		x->r = y->l;
		y->l = x;
		return y;
	}

	node *splay(T key, node *root) {
		if (!root) return NULL;
		node head, *l = &head, *r = &head;
		while (1) {
			if (key < root->key) {
				if (!root->l) break;
				if (key < root->l->key) {
					root = rroate(root);
					if (!root->l) break;
				}
				r = r->l = root;
				root = root->l;
				r->l = NULL;
			}
			else if (key > root->key) {
				if (!root->r) break;
				if (key > root->r->key) {
					root = lroate(root);
					if (!root->r) break;
				}
				l = l->r = root;
				root = root->r;
				l->r = NULL;
			}
			else
				break;
		}
		l->r = root->l;
		r->l = root->r;
		root->l = head.r;
		root->r = head.l;
		return root;
	}

	void print(node* root) {//preorder
		if (root) {
			if (!root->l && !root->r) return;
			std::cout << "key:" << root->key;
			if (root->l)
				std::cout << " l:" << root->l->key;
			if (root->r)
				std::cout << " r:" << root->r->key;
			std::cout << "\n";
			print(root->l);
			print(root->r);
		}
	}

public:
	void insert(T key) {
		if (!root) {
			root = new node(key);
			return;
		}
		root = splay(key, root);
		if (key < root->key) {
			node *p = new node(key, root->l, root);
			root->l = NULL;
			root = p;
		}
		else if (key > root->key) {
			node *p = new node(key, root, root->r);
			root->r = NULL;
			root = p;
		}
		return;
	}

	bool del(T key) {
		root = splay(key, root);
		if (!root || key != root->key) return 0;//¿ÕÊ÷»òÃ»ÕÒµ½
		node *t = root;
		if (!root->l) {
			root = root->r;
		}
		else {
			root = splay(key, root->l);
			root->r = t->r;
		}
		delete t;
		return 1;
	}

	node* search(T key) {
		return root = splay(key, root);
	}

	void print() {
		print(root);
	}
};
#endif SPLAYTREE_H_