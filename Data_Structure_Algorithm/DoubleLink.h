#pragma once
template <typename T>
class DNode {
public:
	T _element;
	DNode * p_Next; //�������
	DNode * p_Prev; //�������.

	DNode() {};
	DNode(T ele, DNode * next, DNode * prev) : _element(ele), p_Next(next), p_Prev(prev) {}
};

template <typename T>
class DoubleLink {
public:
	typedef DNode<T>*  pointer;
	DoubleLink();
	~DoubleLink();
	//����.
	DNode<T>* insert_Node(int index, T t);
	DNode<T>* insert_Head(T t);
	DNode<T>* insert_Last(T t);

	//����
	DNode<T>* delete_Node(int index);
	DNode<T>* delete_Head();
	DNode<T>* delete_Last();
	//ũ��
	int Size();
	//�������
	bool is_Empty();

	//�˻�
	T get_node(int index);
	T get_head();
	T get_last();

	DNode<T>* get_Head();
	DNode<T>* get_Last();
private:
	int node_count; // ���� ��ġ �±�.
	DNode<T> *p_head;

	DNode<T>* get_Node(int index);
};

template <typename T>
DoubleLink<T>::DoubleLink() :node_count(0), p_head(nullptr)
{
	p_head = new DNode<T>();
	p_head->p_Next = nullptr;
	p_head->p_Prev = nullptr;
}

template <typename T>
DoubleLink<T>::~DoubleLink(){
	//ù ������ ���������� ����.
	DNode<T>* pNode = p_head->p_Next;
	while (nullptr != pNode)
	{
		//���� ��带 �ӽ� ��忡 ����.
		DNode<T>* temp = pNode;
		pNode->p_Prev = p_head;//���� ��带 ����.
		pNode = pNode->p_Next; //���� ��带 ���� ����.
		delete temp; // �ӽó�� ����.
	}
}

template <typename T>
DNode<T>* DoubleLink<T>::insert_Node(int index, T t){
	DNode<T> * preNode = get_Node(index); //�ε����� ��带 ������.
	if (preNode) {//�����ϸ�.
		//��,����� ���� ����� ������� �����Ϳ� ����� ������� ������ �� �� ��� ����.
		DNode<T> * newNode = new DNode<T>(t, preNode->p_Next->p_Prev, preNode->p_Next);
		preNode->p_Next = newNode;  //����� ���� ��������Ϳ� �� ��� ����.
		preNode->p_Next->p_Prev = newNode; //����� ���� ��� ������� �����Ϳ� ����� ����.
		node_count++; // ��� ���� ����.
		return newNode; //����� ��ȯ.
	}
	return nullptr;
}

template <typename T>
DNode<T>* DoubleLink<T>::insert_Head(T t){
	return insert_Node(0,t);
}

template <typename T>
DNode<T>* DoubleLink<T>::insert_Last(T t){
	return insert_Node(node_count, t);
}

//����
template <typename T>
DNode<T>* DoubleLink<T>::delete_Node(int index){
	if (is_Empty())//�������.
		return nullptr;
	DNode<T>* ptrNode = get_Node(index); //�ε��� ��� ȣ��.
	DNode<T>* delNode = ptrNode->p_Next; //����� ���� ��带 ������ ���� ����.
	ptrNode->p_Next = delNode->p_Next; //����� ���� ��� �����͸� ��������� ������� �����ͷ�.
	delNode->p_Prev = ptrNode; //���� ����� ���� ��������͸� ����.
	node_count--;//��� ���� ����.
	delete delNode; //��� ����
	return ptrNode->p_Next; //���� ��� ��ȯ.
}

template <typename T>
DNode<T>* DoubleLink<T>::delete_Head(){
	return delete_Node(0);
}

template <typename T>
DNode<T>* DoubleLink<T>::delete_Last(){
	return delete_Node(node_count);
}

//ũ��
template <typename T>
int DoubleLink<T>::Size(){
	return node_count;
}

//�������
template <typename T>
bool DoubleLink<T>::is_Empty(){
	return node_count == 0;
}

template <typename T>
DNode<T>* DoubleLink<T>::get_Head(){
	return p_head->p_Next;
}

template <typename T>
DNode<T>* DoubleLink<T>::get_Last(){
	return get_Node(node_count);
}

template <typename T>
DNode<T>* DoubleLink<T>::get_Node(int index){
	if (index > node_count || index < 0) {
		return nullptr;
	}
	int temp = 0;
	DNode<T>* preNode = p_head;
	while (temp < index) {
		temp++;
		preNode = preNode->p_Next;
	}
	return preNode;
}