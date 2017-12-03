#include<iostream>

using namespace std;

# define N 50

int flag = 0;
template<typename T>
struct node {
	T store_data;
	node* left;
	node* right;
	node(T initial_data, node* left, node* right) {
		store_data = initial_data;
		this->left = left;
		this->right = right;
	}//���캯����ʼ����ֵ
	node(node* left, node* right) {
		this->left = left;
		this->right = right;
	}//���ع��캯��
	node() {}
};

//�ඨ��
template<typename T>
class series;

template<typename T>
class splayTree;

//�ඨ��
template<typename T>
class splayTree {
private:
	node<T>* path[N];
	int height;
	T begin_data;
	T end_data;
	int root_position;//���ڵ��λ��
	//����·������λΪ·�����ȣ�����λ·����Ϣ(0Ϊ��1Ϊ��)
public:
	node<T> *Root;
	int data_amount;
	int mode;//ģʽ������Ϊ0Ϊ���У�����Ϊ������
private:
	template <class T>
	friend class series;
public:
	void insertNode(T insert_data);//����:��������ֵ
	//����һ���ڵ�

	void deleteNode(T delete_data);//���룺ɾ������ֵ
	//ɾ��һ���ڵ�

	node<T>* find(T find_data);//���룺��������ֵ �������Ӧ�ڵ㣨���ҳɹ�����գ�ʧ�ܣ�
	//���������Ƿ����

	splayTree(int opt) :Root(NULL), height(0), mode(opt), data_amount(0) {}
	splayTree() :Root(NULL), height(0), data_amount(0) {
		mode = 0;
	}
	//���캯��

	node<T>* getTree() {
		return Root;
	}
	//��������
private:
	int stretch(T x, node<T>*R);//���룺��չ����Ӧ���ݣ���չ�յ�
	//��չ

	 node<T>* searchNode(T search_data, node<T>* R);//���룺��������ֵ,������� �������Ӧ�ڵ㣨���ҳɹ������丸�ڵ㣨ʧ�ܣ�
	//���Ҳ���

	void display();
	//������ӡ����������

	node<T>* search(T target_data, int offsets);//����λ�ã�ƫ����
	//���ң����ڲ���ǰ������̻��߾���λ��
private:
	inline void leftRotate(node<T>* rotate_node, node<T>* father, int direction, node<T>*&R);//���룺��ת�ڵ㣬��ת�ڵ�ĸ��ڵ㸸�ڵ㵽�ڵ�ķ���0�󣩣�Ŀ����ڵ�
	//����

	inline void rightRotate(node<T>* rotate_node, node<T>* father, int direction, node<T>*&R);//���룺��ת�ڵ㣬��ת�ڵ�ĸ��ڵ㣬���ڵ㵽�ڵ�ķ���0�󣩣�Ŀ����ڵ�
	//����

	inline void getPath(node<T>* R, int depth, T target_data);//���룺��ǰ�ڵ㣬�ڵ���ȣ�Ŀ������
	//��ȡ·��

	void getRootPosition();
	//��ø��ڵ��λ��
};

template<typename T>
class series {
private:
	splayTree<T> test1;
	int data_size;
public:
	series() :data_size(0) {};
	//���캯��

	void deleteSection(T section_left, int data_size);//���룺������߽���ֵ��ɾ�����ݸ���
	//ɾ������

	void sumUp(T section_left, int data_size);//���룺������߽���ֵ��ɾ�����ݸ���
	//���������ݼӺ�

	void modifyData(T section_left, int data_size);//���룺������߽���ֵ��ɾ�����ݸ���
	//�޸�����������

	void reverseData(T section_left, int data_size);//���룺������߽���ֵ��ɾ�����ݸ���
	//�����������ݽ��з�ת

	T calculateMax();
	//�������������

	void insert(T insert_position);//�������λ��
	//����һ��������ָ��λ��

	void display() {
		test1.display();
	}
	//��ӡ��
private:
	node<T>* getSection(T section_left, T section_right);//���룺������߽���ֵ�������ұ߽���ֵ
	//��ȡ����
};

//����������
template<typename T>
void splayTree<T>::insertNode(T insert_data) {
	if (Root == NULL) {
		Root = new node<T>;
		Root->store_data = insert_data;
		Root->left = Root->right = NULL;
		begin_data = insert_data;
		end_data = insert_data;
		data_amount++;
	}//��ʼΪ�յ�ʱ��
	else {
		data_amount++;
		node<T>* temp_node;
		if (mode) {
			end_data = (end_data < insert_data) ? insert_data : end_data;
			begin_data = (begin_data > insert_data) ? insert_data : begin_data;
			//�������䷶Χ
			temp_node = searchNode(insert_data, Root);
			node<T>* right = NULL;
			if (temp_node->store_data == insert_data) {
				while ((temp_node->right != NULL) && temp_node->right->store_data == insert_data)
					temp_node = temp_node->right;
				right = temp_node->right;
			}
			node<T>* new_node = new node<T>(insert_data, NULL, right);
			if (path[height]->store_data <= insert_data)
				temp_node->right = new_node;
			else
				temp_node->left = new_node;
			//�����½ڵ�
		}
		else {
			end_data = insert_data;
			temp_node = Root;
			while (temp_node->right != NULL)
				temp_node = temp_node->right;
			node<T>* new_node = new node<T>(insert_data, NULL, NULL);
			temp_node->right = new_node;
		}
	}
	getRootPosition();
}

template<typename T>
node<T>* splayTree<T>::searchNode(T search_data,node<T>* R) {
	node<T>* temp = R, *result = R;
	height = 0;
	if (mode) {
		while (temp != NULL) {//ѭ����ֹ����
			path[height++] = temp;
			if ((temp->store_data) < search_data)
				temp = temp->right;
			else if ((temp->store_data) > search_data)
				temp = temp->left;
			else
				break;
			//�жϽڵ���ֵ���������Ĵ�С��ϵ���ڵ�����ת������������ת������
		}
		height--;
	}
	else {
		temp = search(search_data, 0);
		flag = 0;//�����ҵ��ı�־
		getPath(R, 0, temp->store_data);
	}
	return path[height];
	//�����ҵ���Ӧ�ڵ�ͷ��ط��򷵻��丸�ڵ�
}

template<typename T>
int splayTree<T>::stretch(T x,node<T>* R) {
	node<T>*p = searchNode(x,R);
	if (p == NULL) {//�����չ�����ݲ����ڣ����ӡ������Ϣ
		cout << "���ݲ����ڣ���Ч��չ��" << endl;
		return -1;
	}
	node<T>* father = NULL, *grandf = NULL, *ancestor = NULL;//���常�׽ڵ���游�ڵ�
	int fathertochild, grandftofather, ancestortograndf;//������������
	while (height >= 2) {
		father = path[--height];
		grandf = path[--height];
		fathertochild = (father->left == p) ? 0 : 1;
		grandftofather = (grandf->left == father) ? 0 : 1;
		if (height >= 1) {//�ж���ת�������Ƿ���Ҫ�ı���ڵ��ָ��
			ancestor = path[height - 1];
			ancestortograndf = (ancestor->left == grandf) ? 0 : 1;
		}
		else {
			ancestor = NULL;
			ancestortograndf = -1;
		}
		//��ֵ�����ڵ㣬�Լ���Ӧ����
		if (fathertochild == grandftofather) {
			if (grandftofather == 1) {
				leftRotate(grandf, ancestor, ancestortograndf,R);
				leftRotate(father, ancestor, fathertochild,R);//��ת���׷����ı�
			}//��һ��
			else {
				rightRotate(grandf, ancestor, ancestortograndf,R);
				rightRotate(father, ancestor, fathertochild,R);
			}//��һ��
		}//һ����
		else {
			if (grandftofather == 1) {
				rightRotate(father, grandf, grandftofather, R);//��ת���׷����ı�
				leftRotate(grandf, ancestor, ancestortograndf, R);
			}//��һ��
			else {
				leftRotate(father, grandf, grandftofather, R);
				rightRotate(grandf, ancestor, ancestortograndf, R);
			}//��һ��
		}
	}
	if (height == 1) {
		father = path[--height];
		fathertochild = (father->left == p) ? 0 : 1;
		if (fathertochild)
			leftRotate(father, grandf, -1,R);
		else
			rightRotate(father, grandf, -1,R);
	}//��·��������ڵ���ֻ����һ����ת
	return 0;
}

template<typename T>
inline void splayTree<T>::leftRotate(node<T>* rotate_node, node<T>* father, int direction, node<T>*&R) {
	node<T>* temp = Root, *temp_father = Root;
	int dir;
	if (R != Root){
		T x = R->store_data;
		while (temp->store_data == x) {
			temp_father = temp;
			temp = (temp->store_data > x) ? temp->left : temp->right;
		}
		dir = (temp_father->left == temp) ? 0 : 1;
	}//Ѱ��ڵ�ĸ��ڵ�
	node<T>* temp_node = rotate_node->right;
	rotate_node->right = temp_node->left;
	temp_node->left = rotate_node;
	//������ת
	if (direction == -1 || father == NULL) {
		if (R != Root) {
			if (dir)
				temp_father->right = temp_node;
			else
				temp_father->left = temp_node;
		}//��α���ڵ��������
		if (R == Root)
			Root = temp_node;
		R = temp_node;
	}
	else if (direction == 0)
		father->left = temp_node;
	else
		father->right = temp_node;
	//������ת�ڵ�
}

template<typename T>
inline void splayTree<T>::rightRotate(node<T>* rotate_node, node<T>* father, int direction, node<T>*&R) {
	int dir;
	node<T>* temp = Root, *temp_father = Root;
	if (R != Root){
		T x = R->store_data;
		while (temp->store_data == x) {
			temp_father = temp;
			temp = (temp->store_data > x) ? temp->left : temp->right;
		}
		dir = (temp_father->left == temp) ? 0 : 1;
	}//Ѱ��ڵ�ĸ��ڵ�
	node<T>* temp_node = rotate_node->left;
	rotate_node->left = temp_node->right;
	temp_node->right = rotate_node;
	//������ת
	if (direction == -1 || father == NULL) {
		if (R != Root) {
			if (dir)
				temp_father->right = temp_node;
			else
				temp_father->left = temp_node;
		}//��α���ڵ��������
		if (R == Root)
			Root = temp_node;
		R = temp_node;
	}
	else if (direction == 0)
		father->left = temp_node;
	else
		father->right = temp_node;
	//������ת�ڵ�
}

template<typename T>
void splayTree<T>::deleteNode(T delete_data) {
	if (stretch(delete_data,Root) == -1)
		cout << "���ݲ����ڣ��޷����ɾ��������" << endl;
	else {
		data_amount--;
		node<T>* temp_node;
		node<T>* temp_node_father;
		if (delete_data == begin_data)
			begin_data = search(begin_data, 1);
		if (delete_data == end_data)
			end_data = search(end_data, -1);
		if (Root->left != NULL) {
			temp_node = Root->left;
			temp_node_father = Root;
			while (temp_node->right != NULL) {
				temp_node_father = temp_node;
				temp_node = temp_node->right;
			}//ѡȡ�����������ҽڵ���Ϊ�µĸ��ڵ�
			node<T>* temp = temp_node->left;
			temp_node->left = (Root->left!=temp_node)?Root->left:NULL;
			temp_node->right = Root->right;
			temp_node_father->right = temp;
			//���µĸ��ڵ�������ȥ���������滻�ڵ�Ŀ�ȱ����
			delete(Root);
			Root = temp_node;
		}
		else {
			temp_node = Root->right;
			delete(Root);
			Root = temp_node;
		}//��������Ϊ�����������������滻
	}
	getRootPosition();
}

template<typename T>
node<T>* splayTree<T>::find(T find_data){
	node<T>* temp = searchNode(find_data,Root);
	if (temp->store == find_data)
		cout << "���ݴ���!" << endl;
	else
		cout << "���ݲ����ڣ�" << endl;
	return (temp->store == find_data) ? temp : NULL;
}

template<typename T>
void splayTree<T>::display() {
	node<T>* temp = Root;
	node<T>* S[N];
	int top = -1;
	while (top != -1 || temp != NULL) {
		while (temp != NULL) {
			S[++top] = temp;
			temp = temp->left;
		}
		if (top != -1) {
			temp = S[top--];
			cout << temp->store_data << " ";
			temp = temp->right;
		}
	}
	cout << endl;
	//�ǵݹ��������
}

template<typename T>
void splayTree<T>::getPath(node<T>* R,int depth,T target_data) {
	if (R == NULL||flag == 1)
		return;
	path[depth] = R;
	if (R->store_data == target_data) {
		height = depth;
		flag = 1;
		return;
	}
	getPath(R->left,depth+1, target_data);
	getPath(R->right,depth+1, target_data);
}

template<typename T>
node<T>* splayTree<T>::search(T target_data, int offsets) {
	if ((mode == 1 && ((target_data<begin_data) || target_data>end_data))||((mode == 0)&&
	((target_data == 0&&offsets == -1)||(target_data == data_amount&&offsets == 1))))
	//����������������ʱ����Խ�磬���в�������λ��ǰ����ĩβ�����
		return NULL;
	if (mode == 0)
		target_data = target_data-root_position+1;
	int count = 0;
	node<T>* temp = Root;
	node<T>* S[N];
	node<T>*container[N];//��ʱ������������ڵ�
	int top = -1,f = 0;
	while (top != -1 || temp != NULL) {
		while (temp != NULL) {
			S[++top] = temp;
			temp = temp->left;
		}
		if (top != -1) {
			temp = S[top--];
			count++;
			if (mode) {
				container[count - 1] = temp;
				//pay attention! �����޸���ʼλ�ã��˴�ҲӦ�޸�
				if (f) break;//��������������һ��
				if (temp->store_data == target_data) {
					if (offsets == 1) {
						f = 1;
						count--;
					}
					else
						break;
				}//�ж��Ƿ�Ҫ���һ�Σ������Ҫ���һ�Σ�
			}
			else {
				if (count == target_data - offsets)
					break;
			}
			temp = temp->right;
		}
	}
	count--;
	if (mode) {
		if ((count + offsets) >= 0 && (count + offsets) <= end_data)
			temp = container[count + offsets];
		else
			temp = NULL;
		//�ж��Ƿ�Խ��
	}
	return temp;
}

template<typename T>
void splayTree<T>::getRootPosition() {
	node<T>* temp = Root;
	node<T>* S[N];
	int top = -1, count = 0;
	while (top != -1 || temp != NULL) {
		while (temp != NULL) {
			S[++top] = temp;
			temp = temp->left;
		}
		if (top != -1) {
			temp = S[top--];
			count++;
			if (temp == Root)
				break;
			temp = temp->right;
		}
	}
	root_position = count;
}

//----------------------------------------------------------------------------------------------------splay Tree defination

template<typename T>
node<T>* series<T>::getSection(T section_left, T section_right) {
	node<T>* temp_node = test1.getTree();
	node<T>* temp;
	int left, right;
	int flag = 0;
	if (test1.mode) {
		left = test1.searchNode(section_left, temp_node)->store_data;
		int offsets = (left == section_left) ? -1 : 0;
		temp = test1.search(left, offsets);//�����µ�����ֵ���������˵���������splay tree��
		if (temp != NULL) {
			left = temp->store_data;
			test1.stretch(left, temp_node);//���������ǰ���Ƶ����ڵ�
		}
		else
			flag++;
		//��������߽��в���
		temp_node = (flag) ? test1.getTree() : test1.getTree()->right;
		//�ж���߽ڵ��Ƿ�Ϊ����߽�
		right = test1.searchNode(section_right, temp_node)->store_data;
		offsets = (right == section_right) ? 1 : 0;
		temp = test1.search(right, offsets);
		if (temp != NULL) {
			right = temp->store_data;//�����µ�����ֵ���������˵���������splay tree��
			test1.stretch(right, temp_node);//�����������Ƶ����ڵ��ұ�
		}
		else
			flag = (flag == 1) ? 2 : -1;
	}//���в���
	else {
		if (section_left > 1)
			test1.stretch(section_left - 1, temp_node);//���������ǰ���Ƶ����ڵ�
		else
			flag++;
		temp_node = (flag) ? test1.getTree() : test1.getTree()->right;
		if (section_right<test1.data_amount)
			test1.stretch(section_right + 1, temp_node);//�����������Ƶ����ڵ��ұ�
		else
			flag = (flag == 1) ? 2 : -1;
	}//�����������
	temp = test1.getTree();
	if (flag != 2) {//�Ƿ��������
		if (flag == 0)//�������Ҳ���
			temp_node = (temp->right)->left;
		else//����������ص�
			temp_node = (flag == 1) ? temp->left : temp->right;
	}
	return temp_node;
}

template<typename T>
void series<T>::deleteSection(T section_left, int data_size) {
	if (data_size <= 0) {
		cout << "�Ƿ����룡" << endl;
		return;
	}
	T section_right = section_left + data_size - 1;
	node<T>* temp_node = getSection(section_left, section_right);//��ȡ������ڵ�
	node<T>* temp = test1.getTree();//��ȡ�����ڵ�
	if (temp->left == temp_node)
		temp->left = NULL;
	else if (temp->right == temp_node)
		temp->right = NULL;
	else
		(temp->right)->left = NULL;
	delete temp_node;
	node<T>* p = temp;
	if (section_left == 0) {
		while (p->left != NULL)
			p = p->left;
		test1.begin_data = p->store_data;
	}
	if (section_right == test1.data_amount) {
		p = temp;
		while (p->right != NULL)
			p = p->right;
		test1.end_data = p->store_data;
	}
	//������β����
	test1.data_amount -= data_size;//�������ݸ���
	test1.getRootPosition();
	//�޸ĸ��ڵ�λ��
}

template<typename T>
void series<T>::sumUp(T section_left, int data_size) {
	if (data_size <= 0||data_size+section_left>test1.data_amount) {
		cout << "�Ƿ����룡" << endl;
		return;
	}
	T section_right = section_left + data_size - 1;
	node<T>* temp_node = getSection(section_left, section_right);//��ȡ������ڵ�
	node<T>* temp = temp_node;
	node<T>* S[N];
	int top = -1, count = 0;
	T result = 0;
	while (top != -1 || temp != NULL) {
		while (temp != NULL) {
			S[++top] = temp;
			temp = temp->left;
		}
		if (top != -1) {
			temp = S[top--];
			count++;
			if (count < data_size)
				cout << temp->store_data << " " << "+" << " ";
			else
				cout << temp->store_data << " " << "=";
			//�ж��Ƿ�Ϊ���һ��Ԫ��
			result += temp->store_data;
			temp = temp->right;
		}
	}//�������
	cout << " " << result << endl;
}

template<typename T>
void series<T>::modifyData(T section_left, int data_size) {
	if (data_size <= 0) {
		cout << "�Ƿ����룡" << endl;
		return;
	}
	T* new_data = new T[data_size];
	cout << "���������ݣ�" << endl;
	for (int i = 0; i < data_size; i++)
		cin >> new_data[i];
	T section_right = section_left + data_size - 1;
	node<T>* temp_node = getSection(section_left, section_right);//��ȡ������ڵ�
	node<T>* temp = temp_node;
	node<T>* S[N];
	int top = -1, count = 0;
	while (top != -1 || temp != NULL) {
		while (temp != NULL) {
			S[++top] = temp;
			temp = temp->left;
		}
		if (top != -1) {
			temp = S[top--];
			temp->store_data = new_data[count++];
			temp = temp->right;
		}
	}//�������
}

template<typename T>
void series<T>::reverseData(T section_left, int data_size) {
	if (data_size <= 0) {
		cout << "�Ƿ����룡" << endl;
		return;
	}
	T* new_data = new T[data_size];
	T section_right = section_left + data_size - 1;
	node<T>* temp_node = getSection(section_left, section_right);//��ȡ������ڵ�
	node<T>* temp = temp_node;
	node<T>* S[N];
	int top = -1, count = 0;
	while (top != -1 || temp != NULL) {
		while (temp != NULL) {
			S[++top] = temp;
			temp = temp->left;
		}
		if (top != -1) {
			temp = S[top--];
			count++;
			new_data[data_size - count] = temp->store_data;
			temp = temp->right;
		}
	}//��ȡԭ����
	temp = temp_node;
	count = 0;
	//���¸�ֵ
	while (top != -1 || temp != NULL) {
		while (temp != NULL) {
			S[++top] = temp;
			temp = temp->left;
		}
		if (top != -1) {
			temp = S[top--];
			temp->store_data = new_data[count++];
			temp = temp->right;
		}
	}//��ֵ
}

template<typename T>
T series<T>::calculateMax() {
	int data_size = test1.data_amount;
	T* series_data = new T[data_size];//���ڱ���������Ԫ��
	node<T>* temp = test1.getTree();//��ֵ���ڵ�
	node<T>* S[N];
	int top = -1, count = 0;
	while (top != -1 || temp != NULL) {
		while (temp != NULL) {
			S[++top] = temp;
			temp = temp->left;
		}
		if (top != -1) {
			temp = S[top--];
			series_data[count++] = temp->store_data;
			temp = temp->right;
		}
	}//��ȡԭ����
	T sum = 0;
	T max = sum;
	int series_begin = 1, series_end = 1;
	for (int i = 0; i < data_size; i++) {
		if (series_data[i] + sum <= series_data[i]) {
			sum = series_data[i];
			series_begin = i + 1;
		}

		else
			sum = series_data[i] + sum;
		if (max < sum) {
			max = sum;
			series_end = i + 1;
		}
	}
	cout << "���ֵΪ��" << series_begin << "��Ԫ�ص�" << series_end << "���Ϊ��" << max << endl;
	return max;
}

template<typename T>
void series<T>::insert(T insert_position) {
	if (insert_position < 0 || insert_position>test1.data_amount) {
		cout << "�Ƿ����룡" << endl;
		return;
	}
	int data_size;
	cout << "�������������ݸ�����" << endl;
	cin >> data_size;
	T insert_data;
	cout << "���������ݣ�" << endl;
	cin >> insert_data;
	node<T>* head = new node<T>(insert_data, NULL, NULL);
	node<T>* tail = head;
	for (int i = 1; i < data_size; i++) {
		cin >> insert_data;
		node<T>* new_node = new node<T>(insert_data, NULL, NULL);
		tail->right = new_node;
		tail = new_node;
	}//�������������������ݣ�
	if (insert_position == 0) {
		tail->right = test1.Root;
		test1.Root = head;
	}//case1:����λ���������׶�
	else {
		node<T>* temp = test1.getTree();
		node<T>* S[N];
		int top = -1, count = 0;
		while (top != -1 || temp != NULL) {
			while (temp != NULL) {
				S[++top] = temp;
				temp = temp->left;
			}
			if (top != -1) {
				temp = S[top--];
				count++;
				if (count == insert_position)
					break;
				temp = temp->right;
			}
		}//�������
		tail->right = temp->right;
		temp->right = head;
		//��������
	}//case:����λ�ò����׶�
	if (insert_position == 0||test1.data_amount == 0)
		test1.begin_data = head->store_data;
	if (insert_position == data_size || test1.data_amount == 0)
		test1.end_data = tail->store_data;
	//������β����
	test1.data_amount += data_size;//�������ݸ���
	test1.getRootPosition();
	//�޸ĸ��ڵ�λ��
}