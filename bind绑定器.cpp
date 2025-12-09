//
// Created by wangj on 2025/12/8.
//

#include <functional>
#include <iostream>
#include <string>
using namespace std;
void hello(std::string sr) {
    cout << sr << endl;
};
void hello2(std::string sr,std::string sr1) {
    cout << sr << "sr1=" << sr1 << endl;
};
int main() {
    // bind(hello, "hello")();
    // bind(hello2, "hello", "hello2")();
    // bind(hello,placeholders::_1)("222");
    function<void(string)> func = bind(hello, placeholders::_1);
    func("niha");
    return 0;
}