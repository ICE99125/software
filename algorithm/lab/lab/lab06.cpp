#include "lab.h"

int min_matrix_multiple_num(int n, std::vector<int>& a) {
    // 保存最少相乘次数
    std::vector<std::vector<int>> m(n, std::vector<int>(n, 0));

    for (int l = 2; l < n + 1; l++) { // 当前矩阵个数
        for (int i = 0; i < n - l + 1; i++) {
            // 矩阵起始 i, 结束 j
            int j = i + l - 1;

            m[i][j] = std::numeric_limits<int>::max();

            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + a[i] * a[k + 1] * a[j + 1];

                if (q < m[i][j]) {
                    // 存在更小的乘积次数, (Ai, ..., Ak) * (A_{k+1}, ..., Aj)
                    m[i][j] = q;
                }
            }
        }
    }

    // 返回 A0 ~ A_{n-1} 之间最少乘积次数
    return m[0][n - 1];
}

void lab06() {
    int n, temp;

    std::cin >> n;

    std::vector<int> array;
    for (int i = 0; i < n + 1; i++) {
        std::cin >> temp;
        array.push_back(temp);
    }

    std::cout << min_matrix_multiple_num(n, array);
}