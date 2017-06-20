#include "SingleLink.h"
#include "CircularLink.h"
#include "DoubleLink.h"
#include <iostream>
using namespace std;

/*
to do list
리스트 부터 해시까지 구현.리스트(링크드 리스트, 더블 링크드 리스트), 스택, 큐, 힙, 트리, 그래프, 해시
각종 알고리즘 문제 자료구조 이용해서 해결해보기.
*/

/*
리스트 : 같은 속성의 객체를 이어놓은 것.
데이터 + 포인터 의 구조.
*/

void main(){
	cout << "data structure and algorithm example" << endl;

	DoubleLink<int> list;

	for (int i = 0; i < 10; i++){
		list.insert_Node(i, i);
	}

	cout << "list size : " << list.Size() << endl;

	list.insert_Head(100);
	list.insert_Last(200);

	DoubleLink<int>::pointer ptr = list.get_Head();
	while (ptr != nullptr)
	{
		cout << ptr->_element << endl;
		ptr = ptr->p_Next;
	}
}