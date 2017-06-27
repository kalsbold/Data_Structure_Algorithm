#pragma once


template <typename T>
class Node {
public:
	T _element;
	Node * p_Next;

	Node() {};
	Node(T ele, Node * next) : _element(ele), p_Next(next) {}
};


template <typename T>
class SingleLink
{
public:
	typedef Node<T>*  pointer;
	SingleLink();
	~SingleLink();
	//삽입.
	Node<T>* insert_Node(int index, T t);
	Node<T>* insert_Head(T t);
	Node<T>* insert_Last(T t);

	//삭제
	Node<T>* delete_Node(int index);
	Node<T>* delete_Head();
	Node<T>* delete_Last();
	//크기
	int Size();
	//비었는지
	bool is_Empty();

	//검색
	T get_node(int index);
	T get_head();
	T get_last();

	Node<T>* get_Head();
	Node<T>* get_Last();
private:
	int node_count;// 꼬리 위치 태그.
	Node<T> *p_head;

	Node<T>* get_Node(int index);
};


template <typename T>
SingleLink<T>::SingleLink()
	:node_count(0), p_head(nullptr)
{
	p_head = new Node<T>();
	p_head->p_Next = nullptr;
}

template <typename T>
SingleLink<T>::~SingleLink() {
	Node<T>* pNode = p_head->p_Next;
	while (nullptr != pNode)
	{
		Node<T>* temp = pNode;
		pNode = pNode->p_Next;
		delete temp;
	}
}

template <typename T>
Node<T>* SingleLink<T>::insert_Node(int index, T t) {
	Node<T> * preNode = get_Node(index);
	if (preNode) {
		Node<T> * newNode = new Node<T>(t, preNode->p_Next);
		preNode->p_Next = newNode;
		node_count++;
		return newNode;
	}
	return nullptr;
}

template <typename T>
Node<T>* SingleLink<T>::insert_Head(T t) {
	return insert_Node(0, t);
}

template <typename T>
Node<T>* SingleLink<T>::insert_Last(T t) {
	return insert_Node(node_count, t);
}

template <typename T>
Node<T>* SingleLink<T>::delete_Node(int index) {
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
Node<T>* SingleLink<T>::delete_Head() {
	return delete_Node(0);
}

template <typename T>
Node<T>* SingleLink<T>::delete_Last() {
	return delete_Node(node_count);
}

template <typename T>
int SingleLink<T>::Size() {
	return node_count;
}

template <typename T>
bool SingleLink<T>::is_Empty() {
	return node_count == 0;
}

template <typename T>
Node<T>* SingleLink<T>::get_Node(int index) {
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

template <typename T>
Node<T>* SingleLink<T>::get_Head() {
	return p_head->p_Next;
}

template <typename T>
Node<T>* SingleLink<T>::get_Last() {
	return get_Node(node_count);
}

template <typename T>
T SingleLink<T>::get_node(int index) {
	return get_Node(index)->_element;
}

template <typename T>
T SingleLink<T>::get_head() {
	return get_Head()->_element;
}

template <typename T>
T SingleLink<T>::get_last() {
	return get_Last()->_element;
}