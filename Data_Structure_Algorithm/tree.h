#pragma once
template <typename T>
struct TNode {
public:
	T _element;	//�� ��.
	TNode<T> * p_Right; //�����ʳ��
	TNode<T> * p_Left; //���ʳ��.

	TNode() : p_Right(nullptr), p_Left(nullptr) {}
	TNode(T ele) : _element(ele), p_Right(nullptr), p_Left(nullptr) {}
	TNode(T ele, TNode * right, TNode * left) : _element(ele), p_Right(right), p_Left(left) {}
};

//����Ʈ��
//���� ����Ʈ��
//��ȭ ����Ʈ�� ��� ��尡 �����ִ� Ʈ��. ���̰� k��� ����� ���� 2k-1��.
//���� ����Ʈ�� ��ȭ ����Ʈ���� Ư���� ���. ��ȭ ����Ʈ������ 2k-1���� �ƴ� n���� ���. 
//���⿡���� ��������Ʈ���� �����Ͽ� ��ȭ ����Ʈ������ ������ ����.

template<typename T>
class Tree {
public:
	Tree();
	~Tree();
	//���� ����, ������ ����.������ ������ ����-> ����������.
	bool Insert_Node(T t);//������ ��带 ���ϴ� ������ ����.
	

	//���� ���ϴ� ��� ����. �˻��� ���� ����. ��ü ������ ���� ���� ��ȸ ����
	bool Delete_Node(T t); //���ϴ� ��� ����
	void Replace_Node(TNode<T>*& replaced, TNode<T>*& newnode); //��� ��ü.
	void Delete_Tree(); //Ʈ�� ��ü ����. ���� ��ȸ �ϸ� ���� ����.
	TNode<T>*& Find_Left_Most(TNode<T>*& node);

	//�˻� ����, ����, ���� ��ȸ �˻�. 
	void Search_Preorder() { Inner_Search_Preorder(Root); } //���� �˻�.
	void Search_Inorder() { Inner_Search_Inorder(Root); }//���� �˻�.
	void Search_Postorder() { Inner_Search_Postorder(Root); } //���� �˻�.
	
	bool Search_Node(T t);

	//���� ����ִ���
	bool Empty();
private:
	TNode<T> * Root;
	
	void Inner_Search_Preorder(TNode<T>*& leaf); //���� �˻�.
	void Inner_Search_Inorder(TNode<T>*& leaf); //���� �˻�.
	void Inner_Search_Postorder(TNode<T>*& leaf); //���� �˻�.

	bool Inner_Insert_Node(TNode<T>*& node,T t);//��Ʈ�� ����.
	bool Inner_Delete_Node(TNode<T>*& node, T t);
};

template<typename T>
Tree<T>::Tree() : Root(nullptr)
{}

template<typename T>
Tree<T>::~Tree()
{
	delete Root;
}

//���� ����, ������ ����.������ �Է� ���� ���� ����� �����Ϳ� ���ؼ� ����-> ����������.
//������ ��带 ���ϴ� ������ ����.
template<typename T>
bool Tree<T>::Insert_Node(T t){
	return Inner_Insert_Node(Root, t);
}

//��Ʈ�� ����.
template<typename T>
bool Tree<T>::Inner_Insert_Node(TNode<T>*& node, T t) 
{
	if (node == nullptr) {
		node = new TNode<T>(t);//��尡 ������ ������.~
		return true;
	}
	else if (node->_element < t) {//����� ������ ������
		return Inner_Insert_Node(node->p_Left, t); //����
	}
	else if (node->_element > t) {//ũ��
		return Inner_Insert_Node(node->p_Right, t);//������
	}

	return false;
}


//���� ���ϴ� ��� ����. �˻��� ���� ����. ��ü ������ ���� ���� ��ȸ ����
//���ϴ� ��� ����
template<typename T>
bool Tree<T>::Delete_Node(T t){
	return Inner_Delete_Node(Root,t);
}

template<typename T>
bool Tree<T>::Inner_Delete_Node(TNode<T>*& node,T t) {
	if (node->_element == t) {
		if (node->p_Left == nullptr &&node->p_Right == nullptr){
			delete node;
			node = nullptr;
		}
		else if (node->p_Left != nullptr && node->p_Right != nullptr) {
			Replace_Node(node, Find_Left_Most(node->p_Right));
		}
		else if(node->p_Left != nullptr && node->p_Right == nullptr){
			Replace_Node(node,node->p_Left);
		}
		else if (node->p_Left == nullptr && node->p_Right != nullptr) {
			Replace_Node(node,node->p_Right);
		}
		return true;
	}
	else if (node->_element > t) {
		return Inner_Delete_Node(node->p_Right,t);
	}
	else {
		return Inner_Delete_Node(node->p_Left, t);
	}
	return false;
}

//��� ��ü
template<typename T>
void Tree<T>::Replace_Node(TNode<T>*& replaced, TNode<T>*& newnode) {
	if (replaced == nullptr || newnode == nullptr) {
		return;
	}

	if (replaced->p_Left != nullptr && replaced->p_Right != nullptr) {
		newnode->p_Left = replaced->p_Left;
		if (replaced->p_Right != newnode) {
			newnode->p_Right = replaced->p_Right;
		}
	}

	TNode<T>* temp = replaced;
	replaced = newnode;
	delete temp;

	return;
}

template<typename T>
TNode<T>*& Tree<T>::Find_Left_Most(TNode<T>*& node)
{
	while (node->p_Left) {
		node = node->p_Left;
	}

	return node;
}

//Ʈ�� ��ü ����. ���� ��ȸ �ϸ� ���� ����.
template<typename T>
void Tree<T>::Delete_Tree(){}

//�˻� ����, ����, ���� ��ȸ �˻�. 
//���� �˻�.
template<typename T>
void Tree<T>::Inner_Search_Preorder(TNode<T>*& leaf)
{
	if (leaf == nullptr) return;
	cout << leaf->_element << " ";
	Inner_Search_Preorder(leaf->p_Left);
	Inner_Search_Preorder(leaf->p_Right);
}

//���� �˻�.
template<typename T>
void Tree<T>::Inner_Search_Inorder(TNode<T>*& leaf)
{
	if (leaf == nullptr) return;
	Inner_Search_Inorder(leaf->p_Left);
	cout << leaf->_element << " ";
	Inner_Search_Inorder(leaf->p_Right);
}

//���� �˻�.
template<typename T>
void Tree<T>::Inner_Search_Postorder(TNode<T>*& leaf)
{
	if (leaf == nullptr) return;
	Inner_Search_Postorder(leaf->p_Left);
	Inner_Search_Postorder(leaf->p_Right);
	cout << leaf->_element << " ";
}

template<typename T>
bool Tree<T>::Search_Node(T t) {
	TNode<T>* node = Root;

	while (node)
	{
		if (node->_element == t) {
			return true;
		}
		else if (node->_element > t) {
			node = node->p_Right;
		}
		else {
			node = node->p_Left;
		}
	}
	return false;
}

//���� ũ��, ����ִ���
template<typename T>
bool Tree<T>::Empty(){
	if (Root == nullptr)
		return false;
	return true;
}