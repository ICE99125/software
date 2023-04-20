#include "lab.h"

// 求数组的中位数
int find_median(std::vector<int>& array, int left, int right) {
    if (right > array.size()) {
        right = array.size();
    }

    std::sort(array.begin() + left, array.begin() + right);

    return array[(right + left) / 2];
}

int select(std::vector<int>& S, int k) {
    if (S.size() == 1) return S[0];

    std::vector<int> M;

    for (int i = 0; i < S.size(); i += 5) {
        M.push_back(find_median(S, i, i + 5));
    }

    // 从中位数中查找中位数
    int m = select(M, (M.size() + 1) / 2);

    std::vector<int> S1, S2;

    int flags = -1;

    // 将元素分组
    for (int i = 0; i < S.size(); i++) {
        if (S[i] <= m) {
            // 小于等于中位数的放入 S1
            S1.push_back(S[i]);

            if (S[i] == m) {
                // 标记最后一个中位数的位置
                flags = S1.size() - 1;
            }
        }
        else if (S[i] > m) {
            // 大于中位数的放入 S2
            S2.push_back(S[i]);
        }
    }

    S1.erase(S1.begin() + flags); // 删除一个中位数

    if (k == S1.size() + 1) {
        return m;
    }
    else if (k <= S1.size()) {
        return select(S1, k);
    }
    else {
        return select(S2, k - S1.size() - 1);
    }
}

void lab03() {
    std::vector<int> S;

    int temp;

    while (std::cin >> temp) {
        S.push_back(temp);

        //if (std::cin.get() == '\n') {
        //    break;
        //}
    }

    //int k;

    //std::cin >> k;

    // 这里可能需要这样, 否则 oj 无法通过...
    int k = S[S.size() - 1];
    S.pop_back();

    output(select(S, k));
}