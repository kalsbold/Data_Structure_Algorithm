#pragma once
template <typename T>
class DNode {
public:
	T _element;
	DNode<T> * p_Next; //�������
	DNode<T> * p_Prev; //�������.

	DNode() {}
	DNode(T ele, DNode * prev, DNode * next) : _element(ele), p_Next(next), p_Prev(prev) {}
};

template <typename T>
class DoubleLink {
public:
	typedef DNode<T>*  pointer;
	DoubleLink();
	~DoubleLink();
	//����. ��ġ�� ���� �ѱ�.
	DNode<T>* insert_Node(int index, T t);
	//���� �ѱ� // ù�Ӹ��� ����.
	DNode<T>* insert_Head(T t);
	//���� �ѱ� // ������ ����.
	DNode<T>* insert_Last(T t);

	//���� ��ġ �ѱ�.
	DNode<T>* delete_Node(int index);
	//ù �Ӹ� ����.
	DNode<T>* delete_Head();
	//���� ����.
	DNode<T>* delete_Last();

	//ũ��
	int Size();
	//�������
	bool is_Empty();

	//�˻�
	T get_node(int index) {
		DNode<T>* pN = get_Node(index);
		return pN->_element; }
	T get_head() { return p_head->p_Next->_element; }
	T get_last() { return p_head->p_Prev->_element; }

	DNode<T>* get_Head();
	DNode<T>* get_Last();
private:
	int node_count; // ��� ����.
	DNode<T> *p_head;

	DNode<T>* get_Node(int index);
};

template <typename T>
DoubleLink<T>::DoubleLink() :node_count(0), p_head(nullptr)
{
	p_head = new DNode<T>();

	p_head->p_Next = p_head;
	p_head->p_Prev = p_head;

}

template <typename T>
DoubleLink<T>::~DoubleLink(){

}

template <typename T>
DNode<T>* DoubleLink<T>::insert_Node(int index, T t){
	//�ε����� 0 �̸� ù�Ӹ��� ����.
	if (index == 0)
		return insert_Head(t);

	//�ش��ϴ� ��ġ�� ��带 ������.
	DNode<T> * preNode = get_Node(index); //�ε����� ��带 ������.
	if (preNode == nullptr)
		return nullptr;
	//��,����� ���� ��� �����Ϳ� ��� �� �� ��� ����.
	DNode<T> * newNode = new DNode<T>(t, preNode->p_Prev, preNode);
	preNode->p_Prev = newNode;  //����� ���� ��������Ϳ� �� ��� ����.
	preNode->p_Prev->p_Next = newNode; //����� ���� ��� ������� �����Ϳ� ����� ����.
	node_count++; // ��� ���� ����.
	return newNode; //����� ��ȯ.

}

template <typename T>
DNode<T>* DoubleLink<T>::insert_Head(T t){
	DNode<T> * newNode = new DNode<T>(t, p_head, p_head->p_Next);
	p_head->p_Next->p_Prev = newNode;
	p_head->p_Next = newNode;
	node_count++;
	return newNode;
	
}

template <typename T>
DNode<T>* DoubleLink<T>::insert_Last(T t){
	DNode<T> * newNode = new DNode<T>(t, p_head->p_Prev, p_head);
	p_head->p_Prev->p_Next = newNode;
	p_head->p_Prev = newNode;
	node_count++;
	return newNode;
}

//����
template <typename T>
DNode<T>* DoubleLink<T>::delete_Node(int index){
	if (index == 0) {
		return delete_Head();
	}
	if (index == node_count - 1) {
		return delete_Last();
	}
	if (index >= node_count)//�������.
		return nullptr;

	DNode<T>* ptrNode = get_Node(index); //�ε��� ��� ȣ��.
	
	ptrNode->p_Prev->p_Next = ptrNode->p_Next; //����� ���� ��� �����͸� ��������� ������� �����ͷ�.
	ptrNode->p_Next->p_Prev = ptrNode->p_Prev; //���� ����� ���� ��������͸� ����.
	
	DNode<T>* p_Temp = ptrNode->p_Prev; //����� ������带 ��ȯ�� ���� ����.
	

	delete ptrNode; //��� ����

	node_count--;//��� ���� ����.
	return p_Temp; //������� ��ȯ.
}

template <typename T>
DNode<T>* DoubleLink<T>::delete_Head(){
	if (is_Empty())//�������.
		return nullptr;
	DNode<T>* p_Node = p_head->p_Next;
	p_head->p_Next = p_Node->p_Next;
	p_Node->p_Next->p_Prev = p_head;
	delete p_Node;
	node_count--;
	return p_head->p_Next;

}

template <typename T>
DNode<T>* DoubleLink<T>::delete_Last(){
	if (is_Empty())//�������.
		return nullptr;
	DNode<T>* p_Node = p_head->p_Prev;
	p_head->p_Prev = p_Node->p_Prev;
	p_Node->p_Prev->p_Next = p_head;
	delete p_Node;
	node_count--;
	return p_head->p_Next;
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
	return p_head;
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
	if (index <= node_count/2)
	{
		temp = index;
		cout << "index : " << index << endl;
		DNode<T>* nextNode = p_head->p_Next;
		while (temp) {
			nextNode = nextNode->p_Next;
			temp--;
		}
		return nextNode;
	}
	else {
		temp = node_count - index - 1;
		cout << "index : " << index << endl;
		DNode<T>* preNode = p_head->p_Prev;
		while (temp) {
			preNode = preNode->p_Prev;
			temp--;
		}
		return preNode;
	}
}