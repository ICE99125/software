#pragma once

#include <vector>

inline void output(std::vector<int>& array, const std::string& sep = " ") {
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << sep;
    }
}

inline void output(const std::string& str, const std::string& sep = "\n") {
    std::cout << str << sep;
}

inline void output(const double num, const int fix, const std::string& sep = "\n") {
    std::cout << std::fixed << std::setprecision(fix) << num << sep;
}

inline void output(const int num, const std::string& sep = "") {
    std::cout << num << sep;
}