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
	}//构造函数初始化数值
	node(node* left, node* right) {
		this->left = left;
		this->right = right;
	}//重载构造函数
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
	int root_position;//根节点的位置
	//保存路径，首位为路径长度，其余位路径信息(0为左，1为右)
public:
	int data_amount;
	int mode;//模式，若果为0为数列，否则为有序数
public:
	void insertNode(T insert_data);//输入:插入数据值
	//插入一个节点
	void deleteNode(T delete_data);//输入：删除数据值
	//删除一个节点
	node<T>* find(T find_data);///输入：查找数据值 输出：对应节点（查找成功）或空（失败）
	//查找数据是否存在
	splayTree(int opt):Root(NULL),height(0),mode(opt), data_amount(0){}
	//构造函数
	int stretch(T x, node<T>*R);//输入：伸展处对应数据，伸展终点
	//伸展
	node<T>* getTree() {
		return Root;
	}
	//返回树根
	node<T>* searchNode(T search_data, node<T>* R);//输入：查找数据值,查找起点 输出：对应节点（查找成功）或其父节点（失败）
	//查找操作
	void display();
	//将树打印出来（中序）
	node<T>* splayTree<T>::search(T target_data, int offsets);//查找位置，偏移量
	//查找，用于查找前驱，后继或者具体位置
private:
	inline void leftRotate(node<T>* rotate_node, node<T>* father, int direction, node<T>*&R);//输入：旋转节点，旋转节点的父节点父节点到节点的方向（0左），目标根节点
	//左旋
	inline void rightRotate(node<T>* rotate_node, node<T>* father, int direction, node<T>*&R);//输入：旋转节点，旋转节点的父节点，父节点到节点的方向（0左），目标根节点
	//右旋
	inline void getPath(node<T>* R,int depth, T target_data);//输入：当前节点，节点深度，目标数据
	//获取路径
	void getRootPosition();
	//获得根节点的位置
};

//函数定义区
template<typename T>
void splayTree<T>::insertNode(T insert_data) {
	if (Root == NULL) {
		Root = new node<T>;
		Root->store_data = insert_data;
		Root->left = Root->right = NULL;
		begin_data = insert_data;
		end_data = insert_data;
	}//初始为空的时候
	else {
		data_amount++;
		node<T>* temp_node;
		if (mode) {
			end_data = (end_data < insert_data) ? insert_data : end_data;
			begin_data = (begin_data > insert_data) ? insert_data : begin_data;
			//更新区间范围
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
			//链接新节点
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
		while (temp != NULL) {//循环终止条件
			path[height++] = temp;
			if ((temp->store_data) < search_data)
				temp = temp->right;
			else if ((temp->store_data) > search_data)
				temp = temp->left;
			else
				break;
			//判断节点数值与搜索数的大小关系，节点数大，转左子树，否则转右子树
		}
		height--;
	}
	else {
		temp = search(search_data, 0);
		flag = 0;//用于找到的标志
		getPath(R, 0, temp->store_data);
	}
	return path[height];
	//若查找到对应节点就返回否则返回其父节点
}

template<typename T>
int splayTree<T>::stretch(T x,node<T>* R) {
	node<T>*p = searchNode(x,R);
	if (p == NULL) {//如果伸展的数据不存在，则打印错误信息
		cout << "数据不存在，无效伸展！" << endl;
		return -1;
	}
	node<T>* father = NULL, *grandf = NULL, *ancestor = NULL;//定义父亲节点和祖父节点
	int fathertochild, grandftofather, ancestortograndf;//定义三个方向
	while (height >= 2) {
		father = path[--height];
		grandf = path[--height];
		fathertochild = (father->left == p) ? 0 : 1;
		grandftofather = (grandf->left == father) ? 0 : 1;
		if (height >= 1) {//判断旋转过程中是否需要改变根节点的指向
			ancestor = path[height - 1];
			ancestortograndf = (ancestor->left == grandf) ? 0 : 1;
		}
		else {
			ancestor = NULL;
			ancestortograndf = -1;
		}
		//赋值三个节点，以及对应方向
		if (fathertochild == grandftofather) {
			if (grandftofather == 1) {
				leftRotate(grandf, ancestor, ancestortograndf,R);
				leftRotate(father, ancestor, fathertochild,R);//旋转后父亲发生改变
			}//右一字
			else {
				rightRotate(grandf, ancestor, ancestortograndf,R);
				rightRotate(father, ancestor, fathertochild,R);
			}//左一字
		}//一字型
		else {
			if (grandftofather == 1) {
				rightRotate(father, grandf, grandftofather, R);//旋转后父亲发生改变
				leftRotate(grandf, ancestor, ancestortograndf, R);
			}//右一字
			else {
				leftRotate(father, grandf, grandftofather, R);
				rightRotate(grandf, ancestor, ancestortograndf, R);
			}//左一字
		}
	}
	if (height == 1) {
		father = path[--height];
		fathertochild = (father->left == p) ? 0 : 1;
		if (fathertochild)
			leftRotate(father, grandf, -1,R);
		else
			rightRotate(father, grandf, -1,R);
	}//若路径到达根节点则只进行一次旋转
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
	}//寻求节点的父节点
	node<T>* temp_node = rotate_node->right;
	rotate_node->right = temp_node->left;
	temp_node->left = rotate_node;
	//进行旋转
	if (direction == -1 || father == NULL) {
		if (R != Root) {
			if (dir)
				temp_father->right = temp_node;
			else
				temp_father->left = temp_node;
		}//将伪根节点进行连接
		if (R == Root)
			Root = temp_node;
		R = temp_node;
	}
	else if (direction == 0)
		father->left = temp_node;
	else
		father->right = temp_node;
	//链接旋转节点
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
	}//寻求节点的父节点
	node<T>* temp_node = rotate_node->left;
	rotate_node->left = temp_node->right;
	temp_node->right = rotate_node;
	//进行旋转
	if (direction == -1 || father == NULL) {
		if (R != Root) {
			if (dir)
				temp_father->right = temp_node;
			else
				temp_father->left = temp_node;
		}//将伪根节点进行连接
		if (R == Root)
			Root = temp_node;
		R = temp_node;
	}
	else if (direction == 0)
		father->left = temp_node;
	else
		father->right = temp_node;
	//链接旋转节点
}

template<typename T>
void splayTree<T>::deleteNode(T delete_data) {
	if (stretch(delete_data,Root) == -1)
		cout << "数据不存在，无法完成删除操作！" << endl;
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
			}//选取左子树的最右节点作为新的根节点
			node<T>* temp = temp_node->left;
			temp_node->left = (Root->left!=temp_node)?Root->left:NULL;
			temp_node->right = Root->right;
			temp_node_father->right = temp;
			//将新的根节点链接上去，并处理替换节点的空缺问题
			delete(Root);
			Root = temp_node;
		}
		else {
			temp_node = Root->right;
			delete(Root);
			Root = temp_node;
		}//若左子树为空则用右子树进行替换
	}
	getRootPosition();
}

template<typename T>
node<T>* splayTree<T>::find(T find_data){
	node<T>* temp = searchNode(find_data,Root);
	if (temp->store == find_data)
		cout << "数据存在!" << endl;
	else
		cout << "数据不存在！" << endl;
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
	//非递归中序遍历
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
	//跳出条件：有序数时不能越界，数列不能在首位读前驱，末尾读后继
		return NULL;
	if (mode == 0)
		target_data = target_data-root_position+1;
	int count = 0;
	node<T>* temp = Root;
	node<T>* S[N];
	node<T>*container[N];//临时保存中序遍历节点
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
				//pay attention! 如需修改起始位置，此处也应修改
				if (f) break;//如果读后继则需多读一次
				if (temp->store_data == target_data) {
					if (offsets == 1) {
						f = 1;
						count--;
					}
					else
						break;
				}//判断是否要多读一次（后继需要多读一次）
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
		//判断是否越界
	}
	return temp;
}

template<typename T>
void splayTree<T>::getRootPosition() {
	node<T>* temp = Root;
	node<T>* S[N];
	node<T>*container[N];//临时保存中序遍历节点
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