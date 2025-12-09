//
// Created by wangj on 2025/12/9.
// 日志模块 数据库
#include "dep.h"

std::mutex mtx;
using Mutex = std::mutex;

class Singleton {
public:
    static Singleton *getInstance() {
        static Singleton instance;
        return &instance;
    }

    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

private:
    Singleton() {
    }
};

// 饿汉式单例模式

int main() {
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();
    Singleton *p4 = Singleton::getInstance();
    // p5  = p4;


    cout << p1 << endl << p2 << endl << p3 << endl << p4 << endl;

    return 0;
}
