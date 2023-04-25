#include "lab.h"

std::string LCS(std::string& str1, std::string& str2, std::vector<std::vector<int>>& C) {
    std::string res;
    
    int i = str1.length(), j = str2.length();
    
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            res = str1[i - 1] + res;
            i--;
            j--;
        }
        else if (C[i - 1][j] >= C[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    return res;
}

int calcLCS(std::string& str1, std::string& str2) {
    int m = str1.length(), n = str2.length();

    // 保存子问题解的数组
    // C(i, j) 代表 x(1, ..., i) 和 y(1, ..., j) 的最长子序列
    std::vector<std::vector<int>> C(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                // 如果 xi 和 yj 相等, 则可以是 x(1, ..., i) 
                // 和 y(1, ..., j) 的最长子序列最后一个元素
                C[i][j] = C[i - 1][j - 1] + 1;
            }
            // 如果不相等, 则最长子序列是 x(1, ..., i - 1) 与 y(1, ..., j) 或
            // x(1, ..., i) 与 y(1, ..., j - 1) 中最长的那个
            else if (C[i - 1][j] >= C[i][j - 1]) {
                C[i][j] = C[i - 1][j];
            }
            else {
                C[i][j] = C[i][j - 1];
            }
        }
    }

    // std::cout << LCS(str1, str2, C) << std::endl;

    return C[m][n];
}

void lab05() {
    std::string str1;
    std::string str2;

    std::cin >> str1 >> str2;

    std::cout << calcLCS(str1, str2);
}