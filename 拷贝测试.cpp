//
// Created by wangj on 2025/12/9.
//
#include "dep.h"
int main() {
    class Car {
        std::string name;
        int* ptr;  // 假设我们手动管理指针
    public:
        Car(const std::string& n) : name(n), ptr(new int(42)) {}
        // ~Car() { delete ptr; }  // 析构函数（略）
    };

    Car c1("BMW");
    Car c2 = c1;  // 默认拷贝：name 被正确拷贝，但 ptr 指向同一块内存！
    return 0;
}