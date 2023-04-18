#pragma once

#include "stdc++.h"

// lab01: 快速排序
int partition(std::vector<int>& array, int left, int right);
void qSort(std::vector<int>& array, std::vector<int>& base, int left, int right);
void lab01();

// lab02: 快速幂
double getPower(double x, int p);
void lab02();

// lab03: 第 k 小的数
int find_median(std::vector<int>& array, int start, int num);
int search_k(std::vector<int>& array, int k);
void lab03();

// lab04: 平面最邻近点对
void lab04();