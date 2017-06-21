#include "SingleLink.h"
#include "CircularLink.h"
#include "DoubleLink.h"
#include <iostream>
using namespace std;

/*
�Ϸ� ���
��ũ�� ����Ʈ, ���� ��ũ�� ����Ʈ ���� �Ϸ�
���� ��ũ�� ����Ʈ(�ϴ� ���� �Ϸ�. �ε��� 3���� ���� ���� �߻�.)

to do list
����Ʈ ���� �ؽñ��� ����.����, ť, ��, Ʈ��, �׷���, �ؽ�
���� �˰��� ���� �ڷᱸ�� �̿��ؼ� �ذ��غ���.
*/

/*
����Ʈ : ���� �Ӽ��� ��ü�� �̾���� ��.
������ + ������ �� ����.
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