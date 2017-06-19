#include "SingleLink.h"
#include <iostream>
using namespace std;

/*
to do list
����Ʈ ���� �ؽñ��� ����.����Ʈ(��ũ�� ����Ʈ, ���� ��ũ�� ����Ʈ), ����, ť, ��, Ʈ��, �׷���, �ؽ�
���� �˰��� ���� �ڷᱸ�� �̿��ؼ� �ذ��غ���.
*/

/*
����Ʈ : ���� �Ӽ��� ��ü�� �̾���� ��.
������ + ������ �� ����.
*/

void main(){
	cout << "data structure and algorithm example" << endl;

	SingleLink<int> list;

	for (int i = 0; i < 10; i++){
		list.insert_Node(i, i);
	}

	cout << "list size : " << list.Size() << endl;

	list.insert_Head(100);
	list.insert_Last(200);

	SingleLink<int>::pointer ptr = list.get_Head();
	while (ptr != nullptr)
	{
		cout << ptr->_element << endl;
		ptr = ptr->p_Next;
	}
}