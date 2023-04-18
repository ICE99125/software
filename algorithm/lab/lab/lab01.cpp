#include "lab.h"

int partition(std::vector<int>& array, int left, int right) {
    int begin = left, end = right;

    int b = array[left];

    while (begin < end) {
        while (begin < end && array[end] >= b) {
            end--;
        }

        while (begin < end && array[begin] <= b) {
            begin++;
        }

        std::swap(array[begin], array[end]);
    }

    std::swap(array[left], array[begin]);

    return begin;
}

void qSort(std::vector<int>& array, std::vector<int>& base, int left, int right) {
    if (left > right) {
        return;
    }

    int p = partition(array, left, right);

    base.push_back(array[p]);

    qSort(array, base, left, p - 1);
    qSort(array, base, p + 1, right);
}

void lab01() {
    int num = 0, temp;

    std::cin >> num;

    std::vector<int> array;
    std::vector<int> base;

    for (int i = 0; i < num; i++) {
        std::cin >> temp;

        array.push_back(temp);
    }

    qSort(array, base, 0, array.size() - 1);

    output(base, "\n");

    output(array);
}