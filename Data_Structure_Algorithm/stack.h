#pragma once
#include "SingleLink.h"
template<typename T>
class stack
{
public:
	stack();
	~stack();

	//삽입. push
	bool push(T t);
	//출력. pop
	T pop();
	//가장 윗데이터 주기. top
	T top();
	//비었는지 확인. empty
	bool empty();

	int size();
private:
	//싱글 리스트로 스택을 구현.
	SingleLink<T> *list_stack;
};

template<typename T>
stack<T>::stack() : list_stack(nullptr){
	list_stack = new SingleLink<T>();
}

template<typename T>
stack<T>::~stack(){
	if (!empty())//스택이 비어있으면.
		delete list_stack;//비면 삭제~~
	else {
		while (!empty())//빌때 까지
		{
			pop();//첫노드를 계속 지우고
		}
		delete list_stack;//비면 삭제~
	}
}

//삽입. push
template<typename T>
bool stack<T>::push(T t){
	if (list_stack->insert_Head(t) == nullptr)
		return false;
	return true;
}

//출력. pop
template<typename T>
T stack<T>::pop(){
	T result = 0;
	if (empty() == true)
		return 0;
	result = list_stack->get_head();
	list_stack->delete_Head();
	return result;
}

//가장 윗데이터 주기. top
template<typename T>
T stack<T>::top(){
	T result = 0;
	if (list_stack->get_Head() == nullptr)
		return 0;
	result = list_stack->get_head();
	return result;
}

//비었는지 확인. empty
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