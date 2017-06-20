#pragma once
template <typename T>
class DNode {
public:
	T _element;
	DNode * p_Next; //다음노드
	DNode * p_Prev; //이전노드.

	DNode() {};
	DNode(T ele, DNode * next, DNode * prev) : _element(ele), p_Next(next), p_Prev(prev) {}
};

template <typename T>
class DoubleLink {
public:
	typedef DNode<T>*  pointer;
	DoubleLink();
	~DoubleLink();
	//삽입.
	DNode<T>* insert_Node(int index, T t);
	DNode<T>* insert_Head(T t);
	DNode<T>* insert_Last(T t);

	//삭제
	DNode<T>* delete_Node(int index);
	DNode<T>* delete_Head();
	DNode<T>* delete_Last();
	//크기
	int Size();
	//비었는지
	bool is_Empty();

	//검색
	T get_node(int index);
	T get_head();
	T get_last();

	DNode<T>* get_Head();
	DNode<T>* get_Last();
private:
	int node_count; // 꼬리 위치 태그.
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
	//첫 노드부터 순차적으로 삭제.
	DNode<T>* pNode = p_head->p_Next;
	while (nullptr != pNode)
	{
		//현재 노드를 임시 노드에 저장.
		DNode<T>* temp = pNode;
		pNode->p_Prev = p_head;//이전 노드를 헤드로.
		pNode = pNode->p_Next; //다음 노드를 지금 노드로.
		delete temp; // 임시노드 삭제.
	}
}

template <typename T>
DNode<T>* DoubleLink<T>::insert_Node(int index, T t){
	DNode<T> * preNode = get_Node(index); //인덱스의 노드를 가져옴.
	if (preNode) {//존재하면.
		//값,노드의 다음 노드의 이전노드 포인터와 노드의 다음노드 포인터 로 새 노드 생성.
		DNode<T> * newNode = new DNode<T>(t, preNode->p_Next->p_Prev, preNode->p_Next);
		preNode->p_Next = newNode;  //노드의 다음 노드포인터에 새 노드 저장.
		preNode->p_Next->p_Prev = newNode; //노드의 다음 노드 이전노드 포인터에 새노드 저장.
		node_count++; // 노드 숫자 증가.
		return newNode; //새노드 반환.
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

//삭제
template <typename T>
DNode<T>* DoubleLink<T>::delete_Node(int index){
	if (is_Empty())//비었으면.
		return nullptr;
	DNode<T>* ptrNode = get_Node(index); //인덱스 노드 호출.
	DNode<T>* delNode = ptrNode->p_Next; //노드의 다음 노드를 삭제할 노드로 저장.
	ptrNode->p_Next = delNode->p_Next; //노드의 다음 노드 포인터를 다음노드의 다음노드 포인터로.
	delNode->p_Prev = ptrNode; //삭제 노드의 이전 노드포인터를 노드로.
	node_count--;//노드 숫자 감소.
	delete delNode; //노드 삭제
	return ptrNode->p_Next; //다음 노드 반환.
}

template <typename T>
DNode<T>* DoubleLink<T>::delete_Head(){
	return delete_Node(0);
}

template <typename T>
DNode<T>* DoubleLink<T>::delete_Last(){
	return delete_Node(node_count);
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