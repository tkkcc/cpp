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

template<typename T>
class splayTree {
private:
	node<T> *Root;
	node<T>* path[N];
	int height;
	T begin_data;
	T end_data;
	int root_position;//���ڵ��λ��
	//����·������λΪ·�����ȣ�����λ·����Ϣ(0Ϊ��1Ϊ��)
public:
	int data_amount;
	int mode;//ģʽ������Ϊ0Ϊ���У�����Ϊ������
public:
	void insertNode(T insert_data);//����:��������ֵ
	//����һ���ڵ�
	void deleteNode(T delete_data);//���룺ɾ������ֵ
	//ɾ��һ���ڵ�
	node<T>* find(T find_data);///���룺��������ֵ �������Ӧ�ڵ㣨���ҳɹ�����գ�ʧ�ܣ�
	//���������Ƿ����
	splayTree(int opt):Root(NULL),height(0),mode(opt), data_amount(0){}
	//���캯��
	int stretch(T x, node<T>*R);//���룺��չ����Ӧ���ݣ���չ�յ�
	//��չ
	node<T>* getTree() {
		return Root;
	}
	//��������
	node<T>* searchNode(T search_data, node<T>* R);//���룺��������ֵ,������� �������Ӧ�ڵ㣨���ҳɹ������丸�ڵ㣨ʧ�ܣ�
	//���Ҳ���
	void display();
	//������ӡ����������
	node<T>* splayTree<T>::search(T target_data, int offsets);//����λ�ã�ƫ����
	//���ң����ڲ���ǰ������̻��߾���λ��
private:
	inline void leftRotate(node<T>* rotate_node, node<T>* father, int direction, node<T>*&R);//���룺��ת�ڵ㣬��ת�ڵ�ĸ��ڵ㸸�ڵ㵽�ڵ�ķ���0�󣩣�Ŀ����ڵ�
	//����
	inline void rightRotate(node<T>* rotate_node, node<T>* father, int direction, node<T>*&R);//���룺��ת�ڵ㣬��ת�ڵ�ĸ��ڵ㣬���ڵ㵽�ڵ�ķ���0�󣩣�Ŀ����ڵ�
	//����
	inline void getPath(node<T>* R,int depth, T target_data);//���룺��ǰ�ڵ㣬�ڵ���ȣ�Ŀ������
	//��ȡ·��
	void getRootPosition();
	//��ø��ڵ��λ��
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
	if ((mode == 1 && (target_data<begin_data) || target_data>end_data)||(mode == 0)&&
	((target_data == begin_data&&offsets == -1)||(target_data == end_data&&offsets == 1)))
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
	node<T>*container[N];//��ʱ������������ڵ�
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