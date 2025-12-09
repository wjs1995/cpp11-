#include <cstring>
#include <iostream>
#include <typeinfo>
#include <string>
#include <cxxabi.h>
#include <type_traits>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <cstdlib>
#include <cxxabi.h>  // MinGW 支持！
//模板特例化和部分特例化
//模板的实参推演
using namespace std;

template<typename T>
bool compare(T A, T B) {
    return A > B;
}

template<>
bool compare<const char *>(const char *A, const char *B) {
    return strcmp(A, B);
}

int sum(int A, int B) {
    return A + B;
}

typedef int (*FUNC1)(int, int);

typedef int FUNC2(int, int);

template<typename T>
class Vec {
public:
    Vec() {
        std::cout << "VEC:" << typeid(T).name() << std::endl;
    }
};

template<typename T>
void fun1(T t) {
    std::cout << typeid(T).name() << std::endl;
}

template<typename R, typename A, typename B>
class Vec<R(*)(A, B)> {
public:
    Vec() {
        std::cout << "VEC222:" << typeid(R).name() << std::endl;
    }
};


template<typename T, typename R, typename A1, typename A2>
void func(R (T::*a)(A1, A2)) {
    std::cout << typeid(R).name() << std::endl;
    std::cout << typeid(T).name() << std::endl;
    std::cout << typeid(A1).name() << std::endl;
    std::cout << typeid(A2).name() << std::endl;
    // T::a(1,2);
}

template<typename T>
class myfunction {
};


template<typename R, typename ... A>
class myfunction<R(A...)> {
public:
    using FUNC1 = R(*)(A...);

    myfunction(FUNC1 pfunc) : _pfunc(pfunc) {
    }

    R operator()(A... a1) {
        return _pfunc(a1...);
    }

private:
    FUNC1 _pfunc;
};

template<typename R, typename A1>
class myfunction<R(A1)> {
public:
    using FUNC1 = R(*)(A1);

    myfunction(FUNC1 pfunc) : _pfunc(pfunc) {
    }

    R operator()(A1 a1) {
        return _pfunc(a1);
    }

private:
    FUNC1 _pfunc;
};

class Test {
public:
    void sum(int a, int b) {
        std::cout << "a +b=" << a + b << std::endl;
    }
};

void hello(string srt) {
    std::cout << srt << std::endl;
}
void hello2 (string st, string srt) {
    std::cout << st << srt  << std::endl;
}

int main1() {
    myfunction<void(std::string)> func1(hello);
    myfunction<void(string,string)> func2(hello2);
    func2("123","32");
    // std::cout << "Hello, World!" << std::endl;

    // Vec<int> vec;
    // Vec<const char*> vec3;
    // Vec<int(*)(int,int)> vec2;
    // fun1("123");
    // FUNC1 f1 = sum;
    // FUNC2 *f2 = sum;
    // std::cout << f1(1, 2) << std::endl;
    // std::cout << f2(3, 2) << std::endl;

    // func(&Test::sum);

    return 0;
}
