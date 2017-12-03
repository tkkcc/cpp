#include"Consistent_Hash_Map.h"
#include<iostream>
#include<string>
#include<time.h>
using namespace std;
void main() {
	int a;
	string b;
	chashmap::Hash_Map h;
	cout << "11:insert node 12:search node 13:delete node \
\n21:insert data 22:search data 23:delete data \
\n111:insert node with vnode num 211:insert random data\
\n41:print 42:printall -1:exit\n";
	
	for (;;) {
		if (cin >> a, a == -1) break;
		switch (a) {
		case 11:
			cin >> b;
			h.insert_node(b);
			break;
		case 12:
			cin >> b;
			h.search_node(b);
			break;
		case 13:
			cin >> b;
			h.delete_node(b);
			break;
		case 21:
			cin >> b;
			h.insert_data(b);
			break;
		case 22:
			cin >> b;
			h.search_data(b);
			break;
		case 23:
			cin >> b;
			h.delete_data(b);
			break;
		case 41:
			h.print(1);
			break;
		case 42:
			h.print();
			break;
		case 111:
			cin >> b >> a;
			h.insert_node(b, a);
			break;
		case 211:
			cin >> a;
			//srand(time(NULL));
			for (int i = 0; i < a; ++i) {
				h.insert_data(h.tostr(rand() % 200), 0);
			}
			break;
		default:
			break;
		}
	}
	system("pause");
}