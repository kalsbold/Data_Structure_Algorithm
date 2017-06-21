#include "SingleLink.h"
#include "CircularLink.h"
#include "DoubleLink.h"
#include <iostream>
using namespace std;

/*
완료 목록
링크드 리스트, 원형 링크드 리스트 구현 완료
더블 링크드 리스트(일단 구현 완료. 인덱스 3에서 삭제 오류 발생.)

to do list
리스트 부터 해시까지 구현.스택, 큐, 힙, 트리, 그래프, 해시
각종 알고리즘 문제 자료구조 이용해서 해결해보기.
*/

/*
리스트 : 같은 속성의 객체를 이어놓은 것.
데이터 + 포인터 의 구조.
*/

void main(){
	cout << "data structure and algorithm example" << endl;

	DoubleLink<int> list;

	for (int i = 0; i < 13; i++){
		list.insert_Node(0, i*10);
		cout << "index "<<i<<" element : " << list.get_node(i) << endl;
	}

	cout << "list size : " << list.Size() << endl;

	for (int i = 0; i < list.Size(); i++)
	{
		cout << "index " << i << " element : " << list.get_node(i) << endl;
	}

	list.insert_Head(100);
	list.insert_Last(200);
	list.insert_Node(4,50);
	list.insert_Node(4, 40);
	list.insert_Node(4, 30);
	list.insert_Node(4, 20);
	list.insert_Node(4, 10);

	cout << "list size : " << list.Size() << endl;
	for (int i = 0; i < list.Size(); i++)
	{
		cout << "index " << i << " element : " << list.get_node(i) << endl;
	}

	cout << "list size : " << list.Size() << endl;
	list.delete_Head();
	list.delete_Last();
	list.delete_Node(3);

	for (int i = 0; i < list.Size(); i++)
	{
		cout << "index "<<i<<" element : " << list.get_node(i) << endl;
	}


	DoubleLink<int>::pointer ptr = list.get_Head();
	ptr = ptr->p_Next;
	while (ptr != list.get_Head())
	{
		cout << ptr->_element << endl;
		ptr = ptr->p_Next;
	}
}