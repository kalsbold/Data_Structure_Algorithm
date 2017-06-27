#pragma once
#include "SingleLink.h"
template<typename T>
class queue 
{
public:
	queue();
	~queue();

	//삽입
	bool push(T t);
	//출력
	T pop();
	//비었는지 확인.
	bool empty();

	int size();
private:
	SingleLink<T> *list_queue;
};


template<typename T>
queue<T>::queue() : list_queue(nullptr){
	list_queue = new SingleLink<T>();
}

template<typename T>
queue<T>::~queue(){
	if (!empty())//스택이 비어있으면.
		delete list_queue;//비면 삭제~~
	else {
		while (!empty())//빌때 까지
		{
			pop();//노드를 계속 지우고
		}
		delete list_queue;//비면 삭제~
	}
}

//삽입
template<typename T>
bool queue<T>::push(T t){
	if (empty() == true)
	{
		list_queue->insert_Head(t);
		return true;
	}
	list_queue->insert_Last(t);
	return true;
}

//출력
template<typename T>
T queue<T>::pop(){
	if (empty() == true)
		return -999;
	T result = 0;
	result = list_queue->get_head();
	list_queue->delete_Head();
	return result;

}

//비었는지 확인.
template<typename T>
bool queue<T>::empty(){
	if (list_queue->is_Empty())
		return true;
	return false;
}

template<typename T>
int queue<T>::size() {
	return list_queue->Size();
}