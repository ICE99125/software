#pragma once

#include<vector>
#include<random>
#include<algorithm>

// �����������
class Random {
	int N;
	std::vector<int> random_list; // �������
	std::vector<int> increase_list; // ������еĵ�������
	std::vector<int> decrease_list; // ������еĵݼ�����
	std::vector<int> random_search_list; // �����������
	std::vector<int> random_delete_list; // ���ɾ������
public:
	Random(int n = 1000) :N(n) {
		createRandomList();
		createIncreaseRandomList();
		createDecreaseRandomList();
	};

	std::vector<int>& getRandomList() {
		return random_list;
	}

	std::vector<int>& getIncreaseRandomList() {
		return increase_list;
	}

	std::vector<int>& getDecreaseRandomList() {
		return decrease_list;
	}

	// ���ɷ�ΧΪ 0~1000000 ���������
	void createRandomList() {
		random_list.resize(N);
		std::default_random_engine e;
		std::uniform_int_distribution<int> u(0, 1000000);
		for (int i = 0; i < random_list.size(); i++) {
			random_list[i] = u(e);
		}
	}

	// ��������
	void createIncreaseRandomList() {
		increase_list = random_list;
		// �� increase_list ���е�������
		sort(increase_list.begin(), increase_list.end());
	}

	// �ݼ�����
	void createDecreaseRandomList() {
		decrease_list = increase_list;
		reverse(decrease_list.begin(), decrease_list.end());
	}

	// �����ȡ 1000 ��Ԫ�صĲ�������
	std::vector<int>& getRandomSearchList(int num=1000) {
		random_search_list.resize(num);

		std::default_random_engine e;
		std::uniform_int_distribution<int> u(0, N - 1);
		for (int i = 0; i < random_search_list.size(); i++) {
			// ��ȡ������±�
			random_search_list[i] = random_list[u(e)];
		}
		return random_search_list;
	}

	// ���ɾ������
	std::vector<int>& getRandomDeleteList() {
		random_delete_list = random_list;

		std::default_random_engine e;
		std::uniform_int_distribution<int> u(0, random_delete_list.size() - 1);
		for (int i = 0; i < random_delete_list.size(); i++) {
			// ������±���н���
			std::swap(random_delete_list[i], random_delete_list[u(e)]);
		}
		return random_delete_list;
	}
};