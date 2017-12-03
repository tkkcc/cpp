#include "headings.h"

template<typename T>
void display(node<T>* R) {
	if (R == NULL)
		return;
	display(R->left);
	cout << R->store_data << " ";
	display(R->right);
}

int main()
{
	series<int> test2;
	int x,y,opt;
	while (1) {
		cout << "选择操作：" << endl;
		cout << "插入一串数据（1）：" << endl;
		cout << "删除一串数据（2）：" << endl;
		cout << "修改一串数据（3）：" << endl;
		cout << "求某一段数据的和（4）：" << endl;
		cout << "求数列中最大连续子列（5）：" << endl;
		cout << "操作前数列中的数据为：";
		test2.display();
		cin >> opt;
		switch (opt) {
		case 1:
			cout << "请输入选择插入位置：" << endl;
			cin >> x;
			test2.insert(x);
			break;
		case 2:
			cout << "请输入删除位置和删除数据个数：" << endl;
			cin >> x>>y;
			test2.deleteSection(x, y);
			break;
		case 3:
			cout << "请输入修改位置和修改数据个数：" << endl;
			cin >> x>> y;
			test2.modifyData(x, y);
			break;
		case 4:
			cout << "请输入计算起始位置和参与计算数据个数：" << endl;
			cin >> x>>y;
			test2.sumUp(x,y);
			break;
		case 5:
			test2.calculateMax();
			break;
		default:
			cout << "非法输入！" << endl;
		}
		cout << "操作后数列中的数据为：";
		test2.display();
		system("pause");
		system("cls");
	}
}