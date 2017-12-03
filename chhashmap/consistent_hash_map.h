#ifndef Consistent_Hash_Map_H_
#define Consistent_Hash_Map_H_

#include"md5.h"
#include<iostream>
#include<map>
#include<set>
#include<strstream>

namespace chashmap {
	using namespace std;
	struct Hash_Map {
		struct datanode {
			string name;//原名
			string hash;//节点hash值 32位md5
			datanode(const string &name, const string &hash) :name(name), hash(hash) {}
			datanode() {}
			bool operator<(const datanode &b) const {
				return this->hash < b.hash;
			}
		};

		struct node {
			string name;//原名
			set<datanode> data;//数据区
			node(string name) :name(name) {}
			node() {}
		};

		typedef map<string, node> mm;

		void insert_node(const string& a, int b = 4) {
			if (Hashmap.find(a) != Hashmap.end()) {
				cout << "node exist" << endl;
				return;
			}
			int i = 1;
			for (; i <= b; ++i) {
				if (!insert_vnode(a + divide + tostr(i))) {
					cout << "insert node error\nyou make a MD5 collision" << endl;//MD5碰撞
					break;
				}
			}
			Hashmap[a] = i-1;
		}

		void search_node(const string &a) {
			if (Hashmap.find(a) == Hashmap.end())
				cout << "node not found" << endl;
			else
				cout << "node found" << endl;
		}

		void delete_node(const string &a) {
			if (Hashmap.size() == 0) {
				cout << "no node for delete" << endl;
				return;
			}
			if (Hashmap.find(a) == Hashmap.end()) {
				cout << "node not exist" << endl;
				return;
			}
			if (Hashmap.size() == 1) {
				datasize = 0;
				Hashmap.clear();
				hashmap.clear();
				cout << "node delete but data lost" << endl;
				return;
			}

			int b = Hashmap[a];
			for (int i = 1; i <= b; ++i) {
				string x = gethash(a + divide + tostr(i));
				auto p = hashmap.find(x);
				auto q = &(p->second.data);
				auto qq = &(next(p)->second.data);
				for (auto j : (*q)) {
					qq->insert(j);
				}
				hashmap.erase(p);
			}
			Hashmap.erase(a);
			cout << "node deleted" << endl;
		}

		void insert_data(const string &a, int b = 1) {//b控制是否有输出
			if (Hashmap.size() == 0) {
				cerr << "no node for data" << endl;
				return;
			}
			string hash = gethash(a);
			auto p = hashmap.upper_bound(hash);
			if (p == hashmap.end()) p = hashmap.begin();
			auto x = p->second.data.insert(datanode(a, hash));
			if (!x.second) {
				if (b) cout << "data exist" << endl;
			}
			else {
				if (b) cout << "data insert" << endl;
				datasize++;
			}
		}

		void search_data(const string &a) {
			string hash = gethash(a);
			auto p = hashmap.upper_bound(hash);
			if (p == hashmap.end()) p = hashmap.begin();
			auto y = &p->second.data;
			if (y->find(datanode(a, gethash(a))) == y->end())
				cerr << "data not found" << endl;
			else
				cerr << "data location: " << p->second.name << endl;
		}

		void delete_data(const string &a) {
			if (Hashmap.size() == 0) {
				cerr << "no node for data" << endl;
				return;
			}			
			string hash = gethash(a);
			auto p = hashmap.upper_bound(hash);
			if (p == hashmap.end()) p = hashmap.begin();
			auto x = p->second.data.erase(datanode(a, hash));
			if (x == 0) 
				cout << "data not found" << endl;
			else {
				cout << "data deleted" << endl;
				datasize--;
			}
		}

		void print(int a = 0) {
			cout << "datasize: " << datasize << "\nnodesize: "
				<< Hashmap.size() << "\nvnodesize: " << hashmap.size() << endl;
			for (auto i = hashmap.begin(); i != hashmap.end(); ++i) {
				auto x = i->second;
				if (a && x.data.size() == 0) continue;
				cout << x.name << ": ";
				for (auto j : x.data)
					cout << j.name << ' ';
				cout << endl;
			}
		}

		string tostr(const int &a) const {
			strstream ss;
			string s;
			ss << a;
			ss >> s;
			return s;
		}
	private:
		const string divide = "#";
		int datasize = 0;
		map<string, node> hashmap;
		map<string, int> Hashmap;
	
		string gethash(const string &s) {
			MD5 md5(s);
			return md5.md5();
		}

		mm::iterator next(const mm::iterator &a) {
			auto p = a;
			if (++p == hashmap.end()) p = hashmap.begin();
			return p;
		}

		bool insert_vnode(const string &a) {
			string hash = gethash(a);
			auto x = hashmap.insert(pair<string, node>(hash,node(a)));
			if (!x.second) {
				cerr << "insert vnode exist" << endl;
				return false;
			}
			if (hashmap.size() == 1) return true;//无需调整
			auto q = &(x.first->second.data), p = &(next(x.first)->second.data);
			hash = x.first->first;
			
			for (auto j = p->begin(); j != p->end();) {
				if (j->hash < hash) {
					q->insert(*j);
					p->erase(j++);
				}
				else
					j++;
			}
			return true;
		}
	};
} // chashmap
#endif // !Consistent_Hash_Map_H_
