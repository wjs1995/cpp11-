//
// Created by wangj on 2025/12/9.
//

#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>
using namespace std;

// 手写的二元函数对象：Divisible
struct Divisible : public std::binary_function<int, int, bool> {
    // operator() 接受两个 int 参数，返回 bool
    bool operator()(int dividend, int divisor) const {
        return divisor != 0 && divisor % dividend == 0;
    }
};
int main() {

    std::vector<int> v = {1, 2, 3, 4, 5};
     std::cout << *(v.end() -1) << endl;
    auto f = std::find_if(v.begin(), v.end(), [](int i) { return i % 2 == 0; });
    if (f != v.end()) {
        std::cout << *f << std::endl;
    }


    auto f1 = std::find_if(v.begin(), v.end(), bind1st(Divisible(),2));
    if (f != v.end()) {
        std::cout << *f1 << std::endl;
    }
    return 0;
}
