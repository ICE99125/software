#include "stdc++.h"
#include "output.h"
#include "lab.h"

class Test {
    std::map<std::string, void(*)()> map;
    void(*cur)()  = nullptr;
public:
    void add(const std::string& key, void (*func)()) {
        map[key] = func;
    }

    void set(const std::string& key) {
        if (map.find(key) != map.end()) {
            cur = map[key];
        }
        else {
            cur = nullptr;
        }
    }

    void operation() {
        if (cur != nullptr) {
            cur();
        }
    }
};

int main() {

    Test test;

    test.add("lab01", lab01);
    test.add("lab02", lab02);
    test.add("lab03", lab03);
    test.add("lab04", lab04);

    // 设置当前需要执行的方法
    test.set("lab03");
    
    test.operation();

    return 0;
}

