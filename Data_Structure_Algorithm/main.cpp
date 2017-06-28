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
완료 목록
링크드 리스트, 원형 링크드 리스트 구현 완료
더블 링크드 리스트(구현 완료. 노드추가할때 포인터 순서지켜줘야 되었음.)
스택, 큐 구현 완료.(리스트 사용.)
트리 구현 완료(이진탐색트리 구현 완료)

to do list
//힙 구현중. 삭제에서 문제. 삽입할때 생긴 문제인것같음.
https://github.com/ewliang/Binary-Tree-Heap/tree/master/HeapAndSort 참고중
리스트 부터 해시까지 구현. 힙,  그래프, 해시
각종 알고리즘 문제 자료구조 이용해서 해결해보기.
*/

void main(){
	cout << "data structure and algorithm example" << endl;

	cout << "스택 돌려보기." << endl;
	stack<int> Stack;
	for (int i = 0; i < 10; i++)
	{
		Stack.push(i*10);
	}
	cout << " 첫번째 요소 : " << Stack.top() << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i+1 << " 번째 요소 : " << Stack.pop() << endl;
	}

	cout << "큐 돌려보기." << endl;

	queue<int> Queue;
	for (int i = 0; i < 20; i++)
	{
		Queue.push(i * 10);
	}
	cout << " 첫번째 요소 : " << Queue.pop() << endl;

	cout << "큐 크기 : " << Queue.size()<< endl;

	int size = Queue.size();

	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << " 번째 요소 : " << Queue.pop() << endl;
	}

	cout << "이진 트리 돌려보기." << endl;
	Tree<int> tree;

	tree.Insert_Node(90);
	tree.Insert_Node(30);
	tree.Insert_Node(20);
	tree.Insert_Node(60);
	tree.Insert_Node(70);
	tree.Insert_Node(50);
	
	cout << endl << "전위 : ";
	tree.Search_Preorder();

	cout << endl << "중위 : ";
	tree.Search_Inorder();

	cout << endl << "후위 : ";
	tree.Search_Postorder();

	tree.Delete_Node(50);


	cout << endl << "전위 : ";
	tree.Search_Preorder();

	cout << endl << "중위 : ";
	tree.Search_Inorder();

	cout << endl << "후위 : ";
	tree.Search_Postorder();


	cout << "30 이 있는지 검색합니다." << endl;

	if (tree.Search_Node(30) == true) {
		cout << "존재" << endl;
	}
	else {
		cout << "없음." << endl;
	}

	heap<int> Heap;
	for (int i = 0; i < 10; i++)
	{
		Heap.Insert_Node(10*i);
	}


	cout << endl << "전위 : ";
	Heap.Search_Preorder();

	cout << endl << "중위 : ";
	Heap.Search_Inorder();

	cout << endl << "후위 : ";
	Heap.Search_Postorder();

	Heap.Delete_Node();
	Heap.Delete_Node();

	cout << endl << "전위 : ";
	Heap.Search_Preorder();

	cout << endl << "중위 : ";
	Heap.Search_Inorder();

	cout << endl << "후위 : ";
	Heap.Search_Postorder();

	

}