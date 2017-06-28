#pragma once

template <typename T>
struct HNode {
public:
	T _element;	//실 값.
	HNode<T> * p_Right; //오른쪽노드
	HNode<T> * p_Left; //왼쪽노드.
	HNode<T> * p_Parent; //부모노드.

	HNode() : p_Right(nullptr), p_Left(nullptr), p_Parent(nullptr) {}
	HNode(T ele) : _element(ele), p_Right(nullptr), p_Left(nullptr), p_Parent(nullptr) {}
	HNode(T ele, HNode * right, HNode * left, HNode * parent) : _element(ele), p_Right(right), p_Left(left), p_Parent(parent) {}
};

template<typename T>
class heap {
public:
	heap();
	~heap();

	//삽입 : 삽입과 동시에 정렬해서 맞는 위치에 저장.
	void Insert_Node(T t);
	
	//삭제 : 루트 노드만 삭제 : 최대 or 최소 값.
	void Delete_Node();

	//검색 : 해당 값의 노드가 있는지 검색, 있으면 true, 없으면 false
	bool Search_Node(T t);

	//노드 정렬 시프트업 시프트다운
	void ShiftUp(HNode<T>* PreNode, HNode<T>* NewNode);
	void ShiftDown(HNode<T>* PreNode);

	void Search_Preorder() { Inner_Search_Preorder(Root); } //전위 검색.
	void Search_Inorder() { Inner_Search_Inorder(Root); }//중위 검색.
	void Search_Postorder() { Inner_Search_Postorder(Root); } //후위 검색.
	

	HNode<T>* Find_Left_Most(HNode<T>* node);
	HNode<T>* Find_Right_Most(HNode<T>* node);
	//상태
	bool Empty();
private:
	HNode<T> * Root;
	HNode<T> * Last;

	void Inner_Insert_Node(HNode<T>* PreNode,T t);

	void Inner_Search_Preorder(HNode<T>*& leaf); //전위 검색.
	void Inner_Search_Inorder(HNode<T>*& leaf); //중위 검색.
	void Inner_Search_Postorder(HNode<T>*& leaf); //후위 검색.
};

template<typename T>
heap<T>::heap() : Root(nullptr) {}

template<typename T>
heap<T>::~heap() {
	delete Root;
}

//삽입 : 삽입과 동시에 정렬해서 맞는 위치에 저장.
/*
가장 끝 위치에 저장.
부모와 비교 후 정렬
알맞은 위치까지 계속 정렬.
*/
template<typename T>
void heap<T>::Insert_Node(T t) {

	Inner_Insert_Node(Root, t);
}
template<typename T>
void heap<T>::Inner_Insert_Node(HNode<T>* PreNode,T t) {
	if (PreNode == nullptr) { // Root 가 없으면
		HNode<T>* NewNode = new HNode<T>(t);
		Root = NewNode;
		Last = NewNode;
	}
	else if (PreNode->p_Parent == nullptr) { //Root라면
		if (PreNode->p_Left == nullptr) { //왼쪽이 비었다면
			HNode<T>* NewNode = new HNode<T>(t, nullptr, nullptr, nullptr); //부모로 root를 주고 자식 없이 생성.
			PreNode->p_Left = NewNode; // Root의 왼쪽에 새노드를
			Last = NewNode;
			ShiftUp(PreNode, NewNode); // 새값이 부모보다 크면 swap
		}
		else if (PreNode->p_Right == nullptr) {//오른쪽이 비었다면
			HNode<T>* NewNode = new HNode<T>(t, nullptr, nullptr, nullptr); //부모로 root를 주고 자식 없이 생성.
			PreNode->p_Right = NewNode; // Root의 오른쪽에 새노드를
			Last = NewNode;
			ShiftUp(PreNode, NewNode);
		}
		else {//다 차있으면
			Inner_Insert_Node(PreNode->p_Left,t);
		}
	}
	else { // Root가 아닌 노드라면.
		if (PreNode->p_Left == nullptr) { //왼쪽이 비었다면
			HNode<T>* NewNode = new HNode<T>(t, nullptr, nullptr, nullptr); //부모로 root를 주고 자식 없이 생성.
			PreNode->p_Left = NewNode; // Root의 왼쪽에 새노드를
			//값 비교후 새값이 부모보다 크면 swap false 일때까지 반복. // 위로 올림.
			Last = NewNode;
			ShiftUp(PreNode, NewNode);
		}
		else if (PreNode->p_Right == nullptr) {//오른쪽이 비었다면
			HNode<T>* NewNode = new HNode<T>(t, nullptr, nullptr, nullptr); //부모로 root를 주고 자식 없이 생성.
			PreNode->p_Right = NewNode; // Root의 오른쪽에 새노드를
			//값 비교후 새값이 부모보다 크면 swap false 일때까지 반복. // 위로 올림.
			Last = NewNode;
			ShiftUp(PreNode, NewNode);
		}
		else {// 다 차있으면 부모의 오른쪽 노드로 가서 재시작.
			if(PreNode->p_Parent->p_Right == PreNode){ //부모노드가 오른쪽 노드면.
				if (PreNode->p_Parent->p_Parent != nullptr) { //부모노드가 Root가 아니면
					if (PreNode->p_Parent->p_Parent->p_Right == PreNode->p_Parent) {//조부모노드가 오른쪽 노드면.
						Inner_Insert_Node(Find_Left_Most(Root),t);
					}
					else {
						Inner_Insert_Node(PreNode->p_Parent->p_Parent->p_Right->p_Left, t);
					}
				}
				else if (PreNode->p_Parent->p_Parent == nullptr) {
					Inner_Insert_Node(Find_Left_Most(Root), t);
				}
			}
			else if (PreNode->p_Parent->p_Right != PreNode) {
				Inner_Insert_Node(PreNode->p_Parent->p_Right, t);
			}
		}
	}
}

template<typename T>
void heap<T>::ShiftUp(HNode<T>* PreNode, HNode<T>* NewNode) {
	if (NewNode->_element > PreNode->_element) {
		T temp = PreNode->_element;
		PreNode->_element = NewNode->_element;
		NewNode->_element = temp;
	}
	if (PreNode->p_Parent != nullptr) {
		ShiftUp(PreNode->p_Parent, PreNode);
	}
}

template<typename T>
HNode<T>* heap<T>::Find_Left_Most(HNode<T>* node)
{
	while (node->p_Left) {
		node = node->p_Left;
	}
	return node;
}

template<typename T>
HNode<T>* heap<T>::Find_Right_Most(HNode<T>* node)
{
	while (node->p_Right) {
		node = node->p_Right;
	}
	return node;
}

template<typename T>
void heap<T>::ShiftDown(HNode<T>* PreNode) {
	T temp;
	if (PreNode->p_Left == nullptr) {
		return;
	}
	else {
		if (PreNode->p_Right != nullptr) {
			if (PreNode->p_Left->_element > PreNode->p_Right->_element) {
				if (PreNode->p_Left->_element > PreNode->_element) {
					temp = PreNode->p_Left->_element;
					PreNode->p_Left->_element = PreNode->_element;
					PreNode->_element = temp;
					ShiftDown(PreNode->p_Left);
				}
			}
			else {
				if (PreNode->p_Right->_element > PreNode->_element) {
					temp = PreNode->p_Right->_element;
					PreNode->p_Right->_element = PreNode->_element;
					PreNode->_element = temp;
					ShiftDown(PreNode->p_Right);
				}
			}
		}
		else {
			if (PreNode->p_Left->_element > PreNode->p_Right->_element) {
				if (PreNode->p_Left->_element > PreNode->_element) {
					temp = PreNode->p_Left->_element;
					PreNode->p_Left->_element = PreNode->_element;
					PreNode->_element = temp;
					ShiftDown(PreNode->p_Left);
				}
			}
		}
	}
}

//삭제 : 루트 노드만 삭제 : 최대 or 최소 값.
template<typename T>
void heap<T>::Delete_Node() {
	if (Root != Last) {
		HNode<T>* tempNode;
		T temp;
		if (Root->p_Left == Last) {//루트 왼쪽이 마지막이면
			tempNode = Root;
			temp = Root->_element;
			Root->_element = Last->_element;
			Last->_element = temp;
			Last = nullptr;
			Last = tempNode;
		}
		else if (Root->p_Right == Last) {//루트 오른쪽이 마지막이면
			tempNode = Root->p_Left;
			temp = Root->_element;
			Root->_element = Last->_element;
			Last->_element = temp;
			Last = nullptr;
			Last = tempNode;
			if (Root->p_Left->_element > Root->_element) {
				temp = Root->p_Left->_element;
				Root->p_Left->_element = Root->_element;
				Root->_element = temp;
			}
		}
		else { //그 밑의 자식이면
			temp = Root->_element;
			Root->_element = Last->_element;
			Last->_element = temp;
			tempNode = Last;
			//마지막노드부터 위로 탐색해 들어간다.
			if (Last->p_Parent->p_Left == Last) {
				if (Last->p_Parent->p_Parent->p_Left != Last->p_Parent) {
					tempNode = Last->p_Parent->p_Parent->p_Left->p_Right;
				}
				else {
					if (Last->p_Parent->p_Parent != Root) {
						if (Last->p_Parent->p_Parent->p_Left != Last->p_Parent->p_Parent) {
							tempNode = Last->p_Parent->p_Parent->p_Parent->p_Left->p_Right->p_Right;
						}
						else {
							tempNode = Find_Right_Most(Root);
						}
					}
					else {
						tempNode = Last->p_Parent->p_Parent->p_Left->p_Right;
					}
				}
			}
			else if(Last->p_Parent->p_Right == Last){
				tempNode = Last->p_Parent->p_Left;
			}
			Last = nullptr;
			Last = tempNode;

			ShiftDown(Root);
		}
	}
	else {
		delete Root;
		delete Last;
	}
}
//검색 : 해당 값의 노드가 있는지 검색, 있으면 true, 없으면 false
template<typename T>
bool heap<T>::Search_Node(T t) {
	HNode<T>* node = Root;

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

template<typename T>
void heap<T>::Inner_Search_Preorder(HNode<T>*& leaf)
{
	if (leaf == nullptr) return;
	cout << leaf->_element << " ";
	Inner_Search_Preorder(leaf->p_Left);
	Inner_Search_Preorder(leaf->p_Right);
}

//중위 검색.
template<typename T>
void heap<T>::Inner_Search_Inorder(HNode<T>*& leaf)
{
	if (leaf == nullptr) return;
	Inner_Search_Inorder(leaf->p_Left);
	cout << leaf->_element << " ";
	Inner_Search_Inorder(leaf->p_Right);
}

//후위 검색.
template<typename T>
void heap<T>::Inner_Search_Postorder(HNode<T>*& leaf)
{
	if (leaf == nullptr) return;
	Inner_Search_Postorder(leaf->p_Left);
	Inner_Search_Postorder(leaf->p_Right);
	cout << leaf->_element << " ";
}

//상태
template<typename T>
bool heap<T>::Empty() {
	if (Root == nullptr) {
		return true;
	}
	return fasle;
}