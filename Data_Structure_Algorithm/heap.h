#pragma once

template <typename T>
struct HNode {
public:
	T _element;	//�� ��.
	HNode<T> * p_Right; //�����ʳ��
	HNode<T> * p_Left; //���ʳ��.
	HNode<T> * p_Parent; //�θ���.

	HNode() : p_Right(nullptr), p_Left(nullptr), p_Parent(nullptr) {}
	HNode(T ele) : _element(ele), p_Right(nullptr), p_Left(nullptr), p_Parent(nullptr) {}
	HNode(T ele, HNode * right, HNode * left, HNode * parent) : _element(ele), p_Right(right), p_Left(left), p_Parent(parent) {}
};

template<typename T>
class heap {
public:
	heap();
	~heap();

	//���� : ���԰� ���ÿ� �����ؼ� �´� ��ġ�� ����.
	void Insert_Node(T t);
	
	//���� : ��Ʈ ��常 ���� : �ִ� or �ּ� ��.
	void Delete_Node();

	//�˻� : �ش� ���� ��尡 �ִ��� �˻�, ������ true, ������ false
	bool Search_Node(T t);

	//��� ���� ����Ʈ�� ����Ʈ�ٿ�
	void ShiftUp(HNode<T>* PreNode, HNode<T>* NewNode);
	void ShiftDown(HNode<T>* PreNode);

	void Search_Preorder() { Inner_Search_Preorder(Root); } //���� �˻�.
	void Search_Inorder() { Inner_Search_Inorder(Root); }//���� �˻�.
	void Search_Postorder() { Inner_Search_Postorder(Root); } //���� �˻�.
	

	HNode<T>* Find_Left_Most(HNode<T>* node);
	HNode<T>* Find_Right_Most(HNode<T>* node);
	//����
	bool Empty();
private:
	HNode<T> * Root;
	HNode<T> * Last;

	void Inner_Insert_Node(HNode<T>* PreNode,T t);

	void Inner_Search_Preorder(HNode<T>*& leaf); //���� �˻�.
	void Inner_Search_Inorder(HNode<T>*& leaf); //���� �˻�.
	void Inner_Search_Postorder(HNode<T>*& leaf); //���� �˻�.
};

template<typename T>
heap<T>::heap() : Root(nullptr) {}

template<typename T>
heap<T>::~heap() {
	delete Root;
}

//���� : ���԰� ���ÿ� �����ؼ� �´� ��ġ�� ����.
/*
���� �� ��ġ�� ����.
�θ�� �� �� ����
�˸��� ��ġ���� ��� ����.
*/
template<typename T>
void heap<T>::Insert_Node(T t) {

	Inner_Insert_Node(Root, t);
}
template<typename T>
void heap<T>::Inner_Insert_Node(HNode<T>* PreNode,T t) {
	if (PreNode == nullptr) { // Root �� ������
		HNode<T>* NewNode = new HNode<T>(t);
		Root = NewNode;
		Last = NewNode;
	}
	else if (PreNode->p_Parent == nullptr) { //Root���
		if (PreNode->p_Left == nullptr) { //������ ����ٸ�
			HNode<T>* NewNode = new HNode<T>(t, nullptr, nullptr, nullptr); //�θ�� root�� �ְ� �ڽ� ���� ����.
			PreNode->p_Left = NewNode; // Root�� ���ʿ� ����带
			Last = NewNode;
			ShiftUp(PreNode, NewNode); // ������ �θ𺸴� ũ�� swap
		}
		else if (PreNode->p_Right == nullptr) {//�������� ����ٸ�
			HNode<T>* NewNode = new HNode<T>(t, nullptr, nullptr, nullptr); //�θ�� root�� �ְ� �ڽ� ���� ����.
			PreNode->p_Right = NewNode; // Root�� �����ʿ� ����带
			Last = NewNode;
			ShiftUp(PreNode, NewNode);
		}
		else {//�� ��������
			Inner_Insert_Node(PreNode->p_Left,t);
		}
	}
	else { // Root�� �ƴ� �����.
		if (PreNode->p_Left == nullptr) { //������ ����ٸ�
			HNode<T>* NewNode = new HNode<T>(t, nullptr, nullptr, nullptr); //�θ�� root�� �ְ� �ڽ� ���� ����.
			PreNode->p_Left = NewNode; // Root�� ���ʿ� ����带
			//�� ���� ������ �θ𺸴� ũ�� swap false �϶����� �ݺ�. // ���� �ø�.
			Last = NewNode;
			ShiftUp(PreNode, NewNode);
		}
		else if (PreNode->p_Right == nullptr) {//�������� ����ٸ�
			HNode<T>* NewNode = new HNode<T>(t, nullptr, nullptr, nullptr); //�θ�� root�� �ְ� �ڽ� ���� ����.
			PreNode->p_Right = NewNode; // Root�� �����ʿ� ����带
			//�� ���� ������ �θ𺸴� ũ�� swap false �϶����� �ݺ�. // ���� �ø�.
			Last = NewNode;
			ShiftUp(PreNode, NewNode);
		}
		else {// �� �������� �θ��� ������ ���� ���� �����.
			if(PreNode->p_Parent->p_Right == PreNode){ //�θ��尡 ������ ����.
				if (PreNode->p_Parent->p_Parent != nullptr) { //�θ��尡 Root�� �ƴϸ�
					if (PreNode->p_Parent->p_Parent->p_Right == PreNode->p_Parent) {//���θ��尡 ������ ����.
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

//���� : ��Ʈ ��常 ���� : �ִ� or �ּ� ��.
template<typename T>
void heap<T>::Delete_Node() {
	if (Root != Last) {
		HNode<T>* tempNode;
		T temp;
		if (Root->p_Left == Last) {//��Ʈ ������ �������̸�
			tempNode = Root;
			temp = Root->_element;
			Root->_element = Last->_element;
			Last->_element = temp;
			Last = nullptr;
			Last = tempNode;
		}
		else if (Root->p_Right == Last) {//��Ʈ �������� �������̸�
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
		else { //�� ���� �ڽ��̸�
			temp = Root->_element;
			Root->_element = Last->_element;
			Last->_element = temp;
			tempNode = Last;
			//������������ ���� Ž���� ����.
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
//�˻� : �ش� ���� ��尡 �ִ��� �˻�, ������ true, ������ false
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

//���� �˻�.
template<typename T>
void heap<T>::Inner_Search_Inorder(HNode<T>*& leaf)
{
	if (leaf == nullptr) return;
	Inner_Search_Inorder(leaf->p_Left);
	cout << leaf->_element << " ";
	Inner_Search_Inorder(leaf->p_Right);
}

//���� �˻�.
template<typename T>
void heap<T>::Inner_Search_Postorder(HNode<T>*& leaf)
{
	if (leaf == nullptr) return;
	Inner_Search_Postorder(leaf->p_Left);
	Inner_Search_Postorder(leaf->p_Right);
	cout << leaf->_element << " ";
}

//����
template<typename T>
bool heap<T>::Empty() {
	if (Root == nullptr) {
		return true;
	}
	return fasle;
}