#include<iostream>
#include<fstream>
#include <map>
#include<string>
using namespace std;

struct Hash_Map {
	typedef long long datatype;
	struct node {
		datatype data = 0;
		node *next = NULL;
		node(datatype data, node *next) :data(data), next(next) {}
		node() {}
	};

	long long search(const long long &a) {
		long long i = a % capicity;
		node *q = &hashmap[i];
		for (auto p = q->next; p; q = p, p = p->next) {
			if (p->data == a) {
				return i;
			}
		}
		return -1;
	}

	void del(const long long &a) {
		node *q = &hashmap[a % capicity];
		for (auto p = q->next; p; q = p, p = p->next) {
			if (p->data == a) {
				q->next = p->next;
				delete(p);
				mapsize--;
				hashmap[a % capicity].data--;
				cout << "deleted" << endl;
				return;
			}
		}
		cerr << "not found" << endl;
	}

	void insert(const long long &a) {
		long long d = search(a);
		if (d != -1) {
			cerr << "exist" << endl;
			return;
		}
		d = a % capicity;
		hashmap[d].data++;
		hashmap[d].next = new node(a, hashmap[d].next);
		if (++mapsize > loadfactor*capicity) 
			rehash();
	}

	void print() {
		for (long long i = 0; i < capicity; ++i) {
			cout << i << ":";
			for (auto p = hashmap[i].next; p; p = p->next) {
				cout << p->data << ' '  ;
			}
			cout << endl;
		}
		cout << endl;
	}

	void print2() {
		map<long long, long long> m;
		for (long long i = 0; i < capicity; ++i) {
			if (hashmap[i].data == 0) cout << '1';
			m[hashmap[i].data]++;
			//cout << i << ":" << hashmap[i].data<<endl;
			//for (auto p = hashmap[i].next; p; p = p->next) {
			//	cout << p->data << ' ';
			//}
			//cout << endl;
		}
		//long long sum = 0;
		//for (auto j : m) {
			//cout << j.first << ":" << j.second << endl;
			//sum += j.second;
		//}
		//cout << sum << ' ' << capicity << endl;
		cout << m[0] << endl << capicity;
		cout << "\n0rate: "<<(double) m[0] / capicity;
		cout << endl;
	}

	void rehash() {
		long long top = 0;
		node **hashmap_tmp = new node*[mapsize];
		node *newhashmap = new node[2 * capicity];
		for (long long i = 0; i < capicity; ++i) {
			for (auto p = hashmap[i].next; p; p = p->next)
				hashmap_tmp[top++] = p;
		}
		capicity *= 2;
		for (long long i = 0; i < mapsize; ++i) {
			node *p = hashmap_tmp[i];
			long long j = p->data % capicity;
			p->next = newhashmap[j].next;
			newhashmap[j].next = p;
			newhashmap[j].data++;
		}
		delete[] hashmap;
		hashmap = newhashmap;
	}

	Hash_Map() {
		hashmap = new node[capicity];
	}

private:
	node *hashmap;
	long long mapsize = 0;
	long long capicity = 3;
	double loadfactor = 3;
};
void test() {
	Hash_Map h;
	ifstream fin("f:\\desktop\\testData_0_9999999.csv");
	long long n, a, b;
	//fin.getline();
	string str;
	getline(fin, str);

	for (long long i = 0; i < 10000000; ++i) {
		fin >> a;
		h.insert(a);
	}

	fin.close();
	h.print2();
}


void main() {
	test();
	system("pause");
	/*
	Hash_Map h;
	long long a;
	cout << "1:insert 2:search 3:delete 4:print -1:exit\n";
	for (;;) {
		if (cin >> a, a == -1) break;
		switch (a) {
		case 1:
			cin >> a;
			h.insert(a);
			break;
		case 2:
			cin >> a;
			if (h.search(a) != -1)
				cout << "found" << endl;
			else
				cout << "not found" << endl;
			break;
		case 3:
			cin >> a;
			h.del(a);
			break;
		case 4:
			cout <<"size:"<< h.size() << endl;
			h.print();
			break;
		default:
			break;
		}
	}*/
}