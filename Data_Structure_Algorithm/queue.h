#pragma once
#include "SingleLink.h"
template<typename T>
class queue 
{
public:
	queue();
	~queue();

	//����
	bool push(T t);
	//���
	T pop();
	//������� Ȯ��.
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
	if (!empty())//������ ���������.
		delete list_queue;//��� ����~~
	else {
		while (!empty())//���� ����
		{
			pop();//��带 ��� �����
		}
		delete list_queue;//��� ����~
	}
}

//����
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

//���
template<typename T>
T queue<T>::pop(){
	if (empty() == true)
		return -999;
	T result = 0;
	result = list_queue->get_head();
	list_queue->delete_Head();
	return result;

}

//������� Ȯ��.
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