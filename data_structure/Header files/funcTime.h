#pragma once

#include<chrono>
#include<iostream>

// ���㺯������ʱ��
class FuncTime {
	std::chrono::steady_clock::time_point start, end;
public:
	FuncTime() {};
	void funcStart() {
		start = std::chrono::steady_clock::now();
	}
	void funcEnd() {
		end = std::chrono::steady_clock::now();
	}
	double funcRunTime() {
		return std::chrono::duration<double, std::milli>(end - start).count();
	}
	void funRunTimeStr() {
		double t = funcRunTime();
		std::cout << "����ʱ��: " << t << "ms" << std::endl;
	}
};