//
// Created by wangj on 2025/12/9.
//

#include <condition_variable>
#include <mutex>
std::mutex mutex;

void func1(std::lock_guard<std::mutex> &lock) {
    // const std::lock_guard<std::mutex> &lock3 = lock;
}

void func2(std::lock_guard<std::mutex> lock) {
    std::lock_guard<std::mutex> &lock3 = lock;
}
class A {
public:
    void run() {};
    int a = 0;
};

void func3(const A &&a) {
    A _a = a;
    _a.a = 10;
    // a.a = 20;
    _a.run();
}
void func4(const A &a) {
    // a.a = 200;
}
int main() {
    A a = A();
    func3(A());
    func4(A());
    func4(a);
    std::lock_guard<std::mutex> lock(mutex);
    func1(lock);
    std::condition_variable cv;
    // std::lock_guard<std::mutex> lock2(mutex);
    // std::lock_guard<std::mutex>  lock3 = lock2;
    return 0;
}
