#include<iostream>
#include<vector>
#include "RBTree.h"
#include "BTree.h"
#include "AVLTree.h"
#include "funcTime.h"
#include "Random.h"


// AVL ������
void avlTreeTest(std::vector<int>& add_list, std::vector<int>& search_list, std::vector<int>& delete_list) {
	AVLTree<int> avl;
	static FuncTime ft;
	ft.funcStart();

	// ����
	for (int i = 0; i < add_list.size(); i++) {
		avl.add(add_list[i]);
	}

	ft.funcEnd();
	double t1 = ft.funcRunTime();

	ft.funcStart();

	// ����
	for (int i = 0; i < search_list.size(); i++) {
		avl.search(search_list[i]);
	}

	ft.funcEnd();
	double t2 = ft.funcRunTime();

	ft.funcStart();

	// ɾ��
	for (int i = 0; i < delete_list.size(); i++) {
		avl.erase(delete_list[i]);
	}

	ft.funcEnd();
	double t3 = ft.funcRunTime();

	std::cout << t1 << "," << t2 << "," << t3 << ",";
}

// B-������
void bTreeTest(std::vector<int>& add_list, std::vector<int>& search_list, std::vector<int>& delete_list) {
	BTree<int> b(512);
	static FuncTime ft;
	ft.funcStart();

	// ����
	for (int i = 0; i < add_list.size(); i++) {
		b.add(add_list[i]);
	}

	ft.funcEnd();
	double t1 = ft.funcRunTime();

	ft.funcStart();

	// ����
	for (int i = 0; i < search_list.size(); i++) {
		b.search(search_list[i]);
	}

	ft.funcEnd();
	double t2 = ft.funcRunTime();

	ft.funcStart();

	// ɾ��
	for (int i = 0; i < delete_list.size(); i++) {
		b.erase(delete_list[i]);
	}

	ft.funcEnd();
	double t3 = ft.funcRunTime();

	std::cout << t1 << "," << t2 << "," << t3 << ",";
}

// ���������
void rbTreeTest(std::vector<int>& add_list, std::vector<int>& search_list, std::vector<int>& delete_list) {
	RedBlack<int> rb;
	
	static FuncTime ft;
	ft.funcStart();

	// ����
	for (int i = 0; i < add_list.size(); i++) {
		rb.add(add_list[i]);
	}

	ft.funcEnd();
	double t1 = ft.funcRunTime();

	ft.funcStart();

	// ����
	for (int i = 0; i < search_list.size(); i++) {
		rb.search(search_list[i]);
	}

	ft.funcEnd();
	double t2 = ft.funcRunTime();
	
	ft.funcStart();

	// ɾ��
	for (int i = 0; i < delete_list.size(); i++) {
		rb.erase(delete_list[i]);
	}

	ft.funcEnd();
	double t3 = ft.funcRunTime();

	std::cout << t1 << "," << t2 << "," << t3 << " ";
}

void test() {
	std::cout << "1.������˳�����N������, �������1000����, ����ͬ˳��ɾ��\n";

	for (int N = 10000; N <= 500000; N += 10000) {
	    Random r(N);
	    std::vector<int> add_list = r.getIncreaseRandomList();
	    std::vector<int> search_list = r.getRandomSearchList();

	    // avl ��
	    avlTreeTest(add_list, search_list, add_list);
	    // B- ��
	    bTreeTest(add_list, search_list, add_list);
		// �����
	    rbTreeTest(add_list, search_list, add_list);
		
		std::cout << "\n";
	}

	std::cout << "2.������˳�����N������, �������1000����, ���෴˳��ɾ��\n";

	for (int N = 10000; N <= 500000; N += 10000) {
		Random r(N);
		std::vector<int> add_list = r.getIncreaseRandomList();
		std::vector<int> search_list = r.getRandomSearchList();
		std::vector<int> delete_list = r.getDecreaseRandomList();

		// avl ��
		avlTreeTest(add_list, search_list, delete_list);
		// B- ��
		bTreeTest(add_list, search_list, delete_list);
		// �����
		rbTreeTest(add_list, search_list, delete_list);

		std::cout << "\n";
	}

	std::cout << "3.�����˳�����N������, �������1000����, �����˳��ɾ��\n";

	for (int N = 10000; N <= 500000; N += 10000) {
		Random r(N);
		std::vector<int> add_list = r.getRandomList();
		std::vector<int> search_list = r.getRandomSearchList();
		std::vector<int> delete_list = r.getRandomDeleteList();

		// avl ��
		avlTreeTest(add_list, search_list, delete_list);
		// B- ��
		bTreeTest(add_list, search_list, delete_list);
		// �����
		rbTreeTest(add_list, search_list, delete_list);

		std::cout << "\n";
	}
}

int main() {
	test();	
	return 0;
}
