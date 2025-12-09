//
// Created by wangj on 2025/12/8.
//
// lambda表达式
#include <algorithm>
#include <iostream>
using namespace std;

template<typename T=void>
class TestLambda01 {
public:
    void operator()() {
        cout << "Tes" << endl;
    }
private:
    mutable int a;

    void operator()() const {
        a = 10;
    }

};

void hello(string str1, string str2) {
    cout << str1 << str2 << endl;
}

// [捕获外部变量](形参列表)->返回值{操作代码}
// []捕获外部变量
// [=]以传值 方式捕获外部所有变量
//[&]以 传引用的方式捕获外部变量
//[this] 捕获外部的this指针
//[=,&a] 其他变量传值捕获，a传入引用
//[a,b] a,b变量传值捕获
//[a,&b] a变量传值捕获，b传入引用
int main() {
    auto func = [](int num)-> void {
        cout << num << endl;
    };
    TestLambda01 t1;
    t1();
    func(1);
    int a = 10;
    int b = 20;
    auto fun2 = [=]() mutable -> void {
        int tem = a;
        a =b;
        b = tem;
        cout << b << a << endl;
    };
    fun2();

    // auto func66 = count_if();
    // func66("222");
    return 0;
}
