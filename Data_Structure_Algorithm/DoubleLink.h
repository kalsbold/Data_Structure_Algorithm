#pragma once
template <typename T>
class DNode {
public:
	T _element;
	DNode<T> * p_Next; //다음노드
	DNode<T> * p_Prev; //이전노드.

	DNode() {}
	DNode(T ele, DNode * prev, DNode * next) : _element(ele), p_Next(next), p_Prev(prev) {}
};

template <typename T>
class DoubleLink {
public:
	typedef DNode<T>*  pointer;
	DoubleLink();
	~DoubleLink();
	//삽입. 위치와 값을 넘김.
	DNode<T>* insert_Node(int index, T t);
	//값을 넘김 // 첫머리에 삽입.
	DNode<T>* insert_Head(T t);
	//값을 넘김 // 꼬리에 삽입.
	DNode<T>* insert_Last(T t);

	//삭제 위치 넘김.
	DNode<T>* delete_Node(int index);
	//첫 머리 삭제.
	DNode<T>* delete_Head();
	//꼬리 삭제.
	DNode<T>* delete_Last();

	//크기
	int Size();
	//비었는지
	bool is_Empty();

	//검색
	T get_node(int index) {
		DNode<T>* pN = get_Node(index);
		return pN->_element; }
	T get_head() { return p_head->p_Next->_element; }
	T get_last() { return p_head->p_Prev->_element; }

	DNode<T>* get_Head();
	DNode<T>* get_Last();
private:
	int node_count; // 노드 숫자.
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
	//인덱스가 0 이면 첫머리에 삽입.
	if (index == 0)
		return insert_Head(t);

	//해당하는 위치의 노드를 가져옴.
	DNode<T> * preNode = get_Node(index); //인덱스의 노드를 가져옴.
	if (preNode == nullptr)
		return nullptr;
	//값,노드의 다음 노드 포인터와 노드 로 새 노드 생성.
	DNode<T> * newNode = new DNode<T>(t, preNode->p_Prev, preNode);
	preNode->p_Prev = newNode;  //노드의 다음 노드포인터에 새 노드 저장.
	preNode->p_Prev->p_Next = newNode; //노드의 다음 노드 이전노드 포인터에 새노드 저장.
	node_count++; // 노드 숫자 증가.
	return newNode; //새노드 반환.

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

//삭제
template <typename T>
DNode<T>* DoubleLink<T>::delete_Node(int index){
	if (index == 0) {
		return delete_Head();
	}
	if (index == node_count - 1) {
		return delete_Last();
	}
	if (index >= node_count)//비었으면.
		return nullptr;

	DNode<T>* ptrNode = get_Node(index); //인덱스 노드 호출.
	
	ptrNode->p_Prev->p_Next = ptrNode->p_Next; //노드의 다음 노드 포인터를 다음노드의 다음노드 포인터로.
	ptrNode->p_Next->p_Prev = ptrNode->p_Prev; //삭제 노드의 이전 노드포인터를 노드로.
	
	DNode<T>* p_Temp = ptrNode->p_Prev; //노드의 이전노드를 반환할 노드로 저장.
	

	delete ptrNode; //노드 삭제

	node_count--;//노드 숫자 감소.
	return p_Temp; //이전노드 반환.
}

template <typename T>
DNode<T>* DoubleLink<T>::delete_Head(){
	if (is_Empty())//비었으면.
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
	if (is_Empty())//비었으면.
		return nullptr;
	DNode<T>* p_Node = p_head->p_Prev;
	p_head->p_Prev = p_Node->p_Prev;
	p_Node->p_Prev->p_Next = p_head;
	delete p_Node;
	node_count--;
	return p_head->p_Next;
}

//크기
template <typename T>
int DoubleLink<T>::Size(){
	return node_count;
}

//비었는지
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