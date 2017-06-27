#pragma once
#include "SingleLink.h"
template<typename T>
class stack
{
public:
	stack();
	~stack();

	//����. push
	bool push(T t);
	//���. pop
	T pop();
	//���� �������� �ֱ�. top
	T top();
	//������� Ȯ��. empty
	bool empty();

	int size();
private:
	//�̱� ����Ʈ�� ������ ����.
	SingleLink<T> *list_stack;
};

template<typename T>
stack<T>::stack() : list_stack(nullptr){
	list_stack = new SingleLink<T>();
}

template<typename T>
stack<T>::~stack(){
	if (!empty())//������ ���������.
		delete list_stack;//��� ����~~
	else {
		while (!empty())//���� ����
		{
			pop();//ù��带 ��� �����
		}
		delete list_stack;//��� ����~
	}
}

//����. push
template<typename T>
bool stack<T>::push(T t){
	if (list_stack->insert_Head(t) == nullptr)
		return false;
	return true;
}

//���. pop
template<typename T>
T stack<T>::pop(){
	T result = 0;
	if (empty() == true)
		return 0;
	result = list_stack->get_head();
	list_stack->delete_Head();
	return result;
}

//���� �������� �ֱ�. top
template<typename T>
T stack<T>::top(){
	T result = 0;
	if (list_stack->get_Head() == nullptr)
		return 0;
	result = list_stack->get_head();
	return result;
}

//������� Ȯ��. empty
template<typename T>
bool stack<T>::empty(){
	if (list_stack->is_Empty())
		return true;
	return false;
}

template<typename T>
int stack<T>::size()
{
	return list_stack->Size();
}