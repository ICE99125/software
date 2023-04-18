#pragma once

#include <vector>

inline void output(std::vector<int>& array, const char* sep = " ") {
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << sep;
    }
}