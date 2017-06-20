#pragma once


template <typename T>
class CircularLink {
public:
	typedef Node<T>*  pointer;
	CircularLink();
	~CircularLink();

	//����.
	Node<T>* insert_Node(int index, T t);
	Node<T>* insert_Head(T t);
	Node<T>* insert_Last(T t);

	//����
	Node<T>* delete_Node(int index);
	Node<T>* delete_Head();
	Node<T>* delete_Last();
	//ũ��
	int Size();
	//�������
	bool is_Empty();

	//�˻�
	T get_node(int index);
	T get_head();
	T get_last();

	Node<T>* get_Head();
	Node<T>* get_Last();
private:
	int node_count;// ���� ��ġ �±�.
	Node<T> *p_head;

	Node<T>* get_Node(int index);
};

template <typename T>
CircularLink<T>::CircularLink()
	:node_count(0), p_head(nullptr)
{
	p_head = new Node<T>();
	p_head->p_Next = nullptr;
}

template <typename T>
CircularLink<T>::~CircularLink(){
	Node<T>* pNode = p_head->p_Next;
	while (nullptr != pNode)
	{
		Node<T>* temp = pNode;
		pNode = pNode->p_Next;
		delete temp;
	}
}

//����.
template <typename T>
Node<T>* CircularLink<T>::insert_Node(int index, T t){
	Node<T> * preNode = get_Node(index);
	//�Էµ� ���� ��尡 ������
	if (preNode) {
		Node<T> * newNode = new Node<T>(t, preNode->p_Next);
		preNode->p_Next = newNode;
		node_count++;
		return newNode;
	}
	//������.
	else {
		Node<T> * newNode = new Node<T>(t, p_head->p_Next);
		p_head->p_Next = newNode;
		newNode->p_Next = p_head;
		node_count++;
		return newNode;
	}
	return nullptr;
}

template <typename T>
Node<T>* CircularLink<T>::insert_Head(T t){
	return insert_Node(0, t);
}

template <typename T>
Node<T>* CircularLink<T>::insert_Last(T t){
	return insert_Node(node_count, t);
}

//����
template <typename T>
Node<T>* CircularLink<T>::delete_Node(int index){
	if (is_Empty())
		return nullptr;
	Node<T>* ptrNode = get_Node(index);
	Node<T>* delNode = ptrNode->p_Next;
	ptrNode->p_Next = delNode->p_Next;
	node_count--;
	delete delNode;
	return ptrNode->p_Next;
}

template <typename T>
Node<T>* CircularLink<T>::delete_Head() {
	return delete_Node(0);
}

template <typename T>
Node<T>* CircularLink<T>::delete_Last(){
	return delete_Node(node_count);
}

//ũ��
template <typename T>
int CircularLink<T>::Size(){
	return node_count;
}

//�������
template <typename T>
bool CircularLink<T>::is_Empty(){
	return node_count == 0;
}

template <typename T>
Node<T>* CircularLink<T>::get_Head(){
	return p_head->p_Next;
}

template <typename T>
Node<T>* CircularLink<T>::get_Last(){
	return get_Node(node_count);
}

template <typename T>
Node<T>* CircularLink<T>::get_Node(int index){
	if (index > node_count || index < 0) {
		return nullptr;
	}
	int temp = 0;
	Node<T>* preNode = p_head;
	while (temp < index) {
		temp++;
		preNode = preNode->p_Next;
	}
	return preNode;
}