#include "lab.h"

class Point {
public:
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {};

    // 以坐标 x 升序排列
    static bool compareX(Point& a, Point& b) {
        return a.x < b.x;
    }

    // 以坐标 y 升序排列
    static bool compareY(Point& a, Point& b) {
        return a.y < b.y;
    }
};

class Pair {
public:
    Point a;
    Point b;

    Pair(Point& a, Point& b) : a(a), b(b) {};

    double get_distance() {
        return calc_distance(a, b);
    }

    // 计算两点之间距离
    static double calc_distance(Point& a, Point& b) {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    }
};

// 计算三点之间最短距离
Pair min_distance_3points(Point& a, Point& b, Point& c) {
    double d1 = Pair::calc_distance(a, b);
    double d2 = Pair::calc_distance(a, c);
    double d3 = Pair::calc_distance(b, c);

    if (d1 > d2) {
        if (d2 > d3) {
            return Pair(b, c);
        }
        else {
            return Pair(a, c);
        }
    }
    else {
        if (d1 > d3) {
            return Pair(b, c);
        }
        else {
            return Pair(a, b);
        }
    }
}

// 最接近点对
Pair closet_pair(std::vector<Point>& p) {
    // 两点的情况
    if (p.size() == 2) {
        return Pair(p[0], p[1]);
    }
    
    // 三点的情况
    if (p.size() == 3) {
        return min_distance_3points(p[0], p[1], p[2]);
    }

    // 以垂直线 l 为界将点集分成左右两边(根据点集水平中点来划分)
    std::vector<Point> pls, prs;

    int mid = p.size() / 2;

    for (int i = 0; i < mid; i++) {
        pls.push_back(p[i]);
    }

    for (int i = mid; i < p.size(); i++) {
        prs.push_back(p[i]);
    }

    Pair pl = closet_pair(pls);
    Pair pr = closet_pair(prs);

    // 左右两边最邻近点距离
    double dl = pl.get_distance();
    double dr = pr.get_distance();

    double best = dl < dr ? dl : dr;
    Pair res = dl < dr ? pl : pr; // 当前左右两侧距离最近的点

    // 收集距离垂直线 l 水平距离小于 best 的点
    std::vector<Point> left, right;

    for (int i = 0; i < pls.size(); i++) {
        if (pls[i].x > p[mid].x - best) {
            left.push_back(pls[i]);
        }
    }

    for (int i = 0; i < prs.size(); i++) {
        if (prs[i].x < p[mid].x + best) {
            right.push_back(prs[i]);
        }
    }

    // 右侧点集按照 y 坐标排序
    std::sort(right.begin(), right.end(), Point::compareY);

    // 遍历左边的点, 查看有没有距离右边 best 内的点
    for (int i = 0; i < left.size(); i++) {
        for (int j = 0; j < right.size(); j++) {
            if (right[j].y < left[i].y + best && right[j].y > left[i].y - best) {
                // 仅计算右侧点在 [y - d, y + d] 范围内的
                if (Pair::calc_distance(left[i], right[j]) < best) {
                    res = Pair(left[i], right[j]);
                }
            }
        }
    }

    return res;
}

Pair pair(std::vector<Point>& p) {
    // 以 x 坐标排序
    std::sort(p.begin(), p.end(), Point::compareX);

    return closet_pair(p);
}

void lab04() {
    int num = 0, x, y;

    std::cin >> num;

    std::vector<Point> p;

    for (int i = 0; i < num; i++) {
        std::cin >> x >> y;

        p.push_back(Point(x, y));
    }

    output(pair(p).get_distance(), 4, "");
}