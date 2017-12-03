
#include "splaytree.h"
#include <iostream>
using namespace std;

void test() {
	const int length = 10;
	splaytree<int> a;
	int vector[10] = { 9,8,7,6,5,4,3,2,1,0 };
	for (int i = 0; i < length; i++)
		a.insert(vector[i]);
	cout << "1:insert 2:delete 3:search 4:print others:exit" << endl;

	while (1)	{
		int j, i;
		cin >> i;
		switch (i)		{
		case 1:
			//cout << "input key to insert:";
			cin >> j;
			a.insert(j);
			break;
		case 2:
			//cout << "input key to delete:";
			cin >> j;
			if (a.del(j))
				cout << "deleted\n";
			else
				cout << "not found\n";
			break;
		case 3:
			//cout << "input key to search:";
			cin >> j;
			if (a.search(j)->key == j) 
				cout<<"found\n";
			else 
				cout << "not found\n";
			break;
		case 4:
			a.print();
			break;
		default:
			return;
		}
	}
}

void main() {
	test();
}
