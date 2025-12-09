//
// Created by wangj on 2025/12/9.
//
#include "dep.h"

class Bad {

    public:
    int *data;
    Bad(int x) : data(new int(x)) {
    }

    // 未定义析构、拷贝 → 编译器生成浅拷贝！
};


// 析构时 double-free → 崩溃！
int main() {
    Bad b1(42);
    Bad b2 = b1; // 危险！b1.data 和 b2.data 指向同一块内存
    cout << b1.data << endl;
    cout << b2.data << endl;
    cout << 1 << endl;
    return 0;
}
