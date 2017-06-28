#include "SingleLink.h"
#include "CircularLink.h"
#include "DoubleLink.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "heap.h"
#include <iostream>
using namespace std;

/*
�Ϸ� ���
��ũ�� ����Ʈ, ���� ��ũ�� ����Ʈ ���� �Ϸ�
���� ��ũ�� ����Ʈ(���� �Ϸ�. ����߰��Ҷ� ������ ����������� �Ǿ���.)
����, ť ���� �Ϸ�.(����Ʈ ���.)
Ʈ�� ���� �Ϸ�(����Ž��Ʈ�� ���� �Ϸ�)

to do list
//�� ������. �������� ����. �����Ҷ� ���� �����ΰͰ���.
https://github.com/ewliang/Binary-Tree-Heap/tree/master/HeapAndSort ������
����Ʈ ���� �ؽñ��� ����. ��,  �׷���, �ؽ�
���� �˰��� ���� �ڷᱸ�� �̿��ؼ� �ذ��غ���.
*/

void main(){
	cout << "data structure and algorithm example" << endl;

	cout << "���� ��������." << endl;
	stack<int> Stack;
	for (int i = 0; i < 10; i++)
	{
		Stack.push(i*10);
	}
	cout << " ù��° ��� : " << Stack.top() << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i+1 << " ��° ��� : " << Stack.pop() << endl;
	}

	cout << "ť ��������." << endl;

	queue<int> Queue;
	for (int i = 0; i < 20; i++)
	{
		Queue.push(i * 10);
	}
	cout << " ù��° ��� : " << Queue.pop() << endl;

	cout << "ť ũ�� : " << Queue.size()<< endl;

	int size = Queue.size();

	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << " ��° ��� : " << Queue.pop() << endl;
	}

	cout << "���� Ʈ�� ��������." << endl;
	Tree<int> tree;

	tree.Insert_Node(90);
	tree.Insert_Node(30);
	tree.Insert_Node(20);
	tree.Insert_Node(60);
	tree.Insert_Node(70);
	tree.Insert_Node(50);
	
	cout << endl << "���� : ";
	tree.Search_Preorder();

	cout << endl << "���� : ";
	tree.Search_Inorder();

	cout << endl << "���� : ";
	tree.Search_Postorder();

	tree.Delete_Node(50);


	cout << endl << "���� : ";
	tree.Search_Preorder();

	cout << endl << "���� : ";
	tree.Search_Inorder();

	cout << endl << "���� : ";
	tree.Search_Postorder();


	cout << "30 �� �ִ��� �˻��մϴ�." << endl;

	if (tree.Search_Node(30) == true) {
		cout << "����" << endl;
	}
	else {
		cout << "����." << endl;
	}

	heap<int> Heap;
	for (int i = 0; i < 10; i++)
	{
		Heap.Insert_Node(10*i);
	}


	cout << endl << "���� : ";
	Heap.Search_Preorder();

	cout << endl << "���� : ";
	Heap.Search_Inorder();

	cout << endl << "���� : ";
	Heap.Search_Postorder();

	Heap.Delete_Node();
	Heap.Delete_Node();

	cout << endl << "���� : ";
	Heap.Search_Preorder();

	cout << endl << "���� : ";
	Heap.Search_Inorder();

	cout << endl << "���� : ";
	Heap.Search_Postorder();

	

}