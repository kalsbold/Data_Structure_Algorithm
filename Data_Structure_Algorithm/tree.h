#pragma once
template <typename T>
struct TNode {
public:
	T _element;	//실 값.
	TNode<T> * p_Right; //오른쪽노드
	TNode<T> * p_Left; //왼쪽노드.

	TNode() : p_Right(nullptr), p_Left(nullptr) {}
	TNode(T ele) : _element(ele), p_Right(nullptr), p_Left(nullptr) {}
	TNode(T ele, TNode * right, TNode * left) : _element(ele), p_Right(right), p_Left(left) {}
};

//이진트리
//편향 이진트리
//포화 이진트리 모든 노드가 꽉차있는 트리. 깊이가 k라면 노드의 수는 2k-1개.
//완전 이진트리 포화 이진트리의 특별한 경우. 포화 이진트리에서 2k-1개가 아닌 n개인 경우. 
//여기에서는 완전이진트리를 구현하여 포화 이진트리까지 감당할 예정.

template<typename T>
class Tree {
public:
	Tree();
	~Tree();
	//삽입 왼쪽, 오른쪽 삽입.순서는 무조건 왼쪽-> 오른쪽으로.
	bool Insert_Node(T t);//임의의 노드를 최하단 리프에 삽입.
	

	//삭제 원하는 노드 삭제. 검색을 통해 삭제. 전체 삭제를 위한 후위 순회 삭제
	bool Delete_Node(T t); //원하는 노드 삭제
	void Replace_Node(TNode<T>*& replaced, TNode<T>*& newnode); //노드 교체.
	void Delete_Tree(); //트리 전체 삭제. 후위 순회 하며 순차 삭제.
	TNode<T>*& Find_Left_Most(TNode<T>*& node);

	//검색 전위, 중위, 후위 순회 검색. 
	void Search_Preorder() { Inner_Search_Preorder(Root); } //전위 검색.
	void Search_Inorder() { Inner_Search_Inorder(Root); }//중위 검색.
	void Search_Postorder() { Inner_Search_Postorder(Root); } //후위 검색.
	
	bool Search_Node(T t);

	//상태 비어있는지
	bool Empty();
private:
	TNode<T> * Root;
	
	void Inner_Search_Preorder(TNode<T>*& leaf); //전위 검색.
	void Inner_Search_Inorder(TNode<T>*& leaf); //중위 검색.
	void Inner_Search_Postorder(TNode<T>*& leaf); //후위 검색.

	bool Inner_Insert_Node(TNode<T>*& node,T t);//루트에 삽입.
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

//삽입 왼쪽, 오른쪽 삽입.순서는 입력 값이 현재 노드의 데이터와 비교해서 왼쪽-> 오른쪽으로.
//임의의 노드를 최하단 리프에 삽입.
template<typename T>
bool Tree<T>::Insert_Node(T t){
	return Inner_Insert_Node(Root, t);
}

//루트에 삽입.
template<typename T>
bool Tree<T>::Inner_Insert_Node(TNode<T>*& node, T t) 
{
	if (node == nullptr) {
		node = new TNode<T>(t);//노드가 없으면 생성함.~
		return true;
	}
	else if (node->_element < t) {//현노드 값보다 작으면
		return Inner_Insert_Node(node->p_Left, t); //왼쪽
	}
	else if (node->_element > t) {//크면
		return Inner_Insert_Node(node->p_Right, t);//오른쪽
	}

	return false;
}


//삭제 원하는 노드 삭제. 검색을 통해 삭제. 전체 삭제를 위한 후위 순회 삭제
//원하는 노드 삭제
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

//노드 교체
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

//트리 전체 삭제. 후위 순회 하며 순차 삭제.
template<typename T>
void Tree<T>::Delete_Tree(){}

//검색 전위, 중위, 후위 순회 검색. 
//전위 검색.
template<typename T>
void Tree<T>::Inner_Search_Preorder(TNode<T>*& leaf)
{
	if (leaf == nullptr) return;
	cout << leaf->_element << " ";
	Inner_Search_Preorder(leaf->p_Left);
	Inner_Search_Preorder(leaf->p_Right);
}

//중위 검색.
template<typename T>
void Tree<T>::Inner_Search_Inorder(TNode<T>*& leaf)
{
	if (leaf == nullptr) return;
	Inner_Search_Inorder(leaf->p_Left);
	cout << leaf->_element << " ";
	Inner_Search_Inorder(leaf->p_Right);
}

//후위 검색.
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

//상태 크기, 비어있는지
template<typename T>
bool Tree<T>::Empty(){
	if (Root == nullptr)
		return false;
	return true;
}