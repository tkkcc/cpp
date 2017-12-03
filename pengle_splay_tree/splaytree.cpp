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
		cout << "ѡ�������" << endl;
		cout << "����һ�����ݣ�1����" << endl;
		cout << "ɾ��һ�����ݣ�2����" << endl;
		cout << "�޸�һ�����ݣ�3����" << endl;
		cout << "��ĳһ�����ݵĺͣ�4����" << endl;
		cout << "������������������У�5����" << endl;
		cout << "����ǰ�����е�����Ϊ��";
		test2.display();
		cin >> opt;
		switch (opt) {
		case 1:
			cout << "������ѡ�����λ�ã�" << endl;
			cin >> x;
			test2.insert(x);
			break;
		case 2:
			cout << "������ɾ��λ�ú�ɾ�����ݸ�����" << endl;
			cin >> x>>y;
			test2.deleteSection(x, y);
			break;
		case 3:
			cout << "�������޸�λ�ú��޸����ݸ�����" << endl;
			cin >> x>> y;
			test2.modifyData(x, y);
			break;
		case 4:
			cout << "�����������ʼλ�úͲ���������ݸ�����" << endl;
			cin >> x>>y;
			test2.sumUp(x,y);
			break;
		case 5:
			test2.calculateMax();
			break;
		default:
			cout << "�Ƿ����룡" << endl;
		}
		cout << "�����������е�����Ϊ��";
		test2.display();
		system("pause");
		system("cls");
	}
}