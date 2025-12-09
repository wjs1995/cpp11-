#include <iosfwd>
//
// Created by wangj on 2025/12/9.
//
#include <thread>
#include "dep.h"

volatile std::atomic_bool isReady = false;
volatile std::atomic_int count = 0;

void task(int i) {
    while (!isReady) {
        std::this_thread::yield();
    }
    std::cout << 1 << std::endl;

    for (int i = 0; i < 100; i++) {
        count++;
    }
};

int main() {
    std::list<std::thread> tlist;
    for (int i = 0; i < 10; i++) {
        tlist.push_back(std::thread(task, i));
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
    isReady = true;
    for (auto &t: tlist) {
        t.join();
    }
    std::cout << "count="<< count << std::endl;

    return 0;
}
