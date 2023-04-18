#include "lab.h"

// 默认五个一组, 求中位数
int find_median(std::vector<int>& array, int start, int num = 5) {
	std::vector<int> temp;

	int len = array.size();

	for (int i = start; i < start + num && i < len; i++) {
		temp.push_back(array[i]);
	}

	std::sort(temp.begin(), temp.end());

	return temp[temp.size() / 2];
}

int search_k(std::vector<int>& array, int k) {
	std::vector<int> M;

	for (int i = 0; i < array.size(); i += 5) {
		// 分组, 每组的中位数放入 M
		M.push_back(find_median(array, i));
	}

	// 从中位数中查找中位数
	int m = find_median(M, 0, M.size());

	std::vector<int> S1, S2;

	int flags = 0;

	// 将元素分组, 小于中位数的放入 S1, 大于中位数的放入 S2
	for (int i = 0; i < array.size(); i++) {
		if (array[i] <= m) {
			S1.push_back(array[i]);

			if (array[i] == m) {
				flags = S1.size() - 1;
			}
		}
		else if (array[i] > m) {
			S2.push_back(array[i]);
		}
	}

	S1.erase(S1.begin() + flags); // 删除最后一个中位数

	if (k == S1.size() + 1) {
		return m;
	}
	else if (k <= S1.size()) {
		return search_k(S1, k);
	}
	else {
		return search_k(S2, k - S1.size() - 1);
	}
}

void lab03() {
	std::vector<int> array;

	int temp;

	while (std::cin >> temp) {
		array.push_back(temp);

		if (std::cin.get() == '\n') {
			break;
		}
	}

	int k;

	std::cin >> k;

	std::cout << search_k(array, k);
}