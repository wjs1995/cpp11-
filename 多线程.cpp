//
// Created by wangj on 2025/12/9.
//
// 语言级别多线程 代码可跨频台
// thread/ mutex/condition_variable
// lock_quard /unique_lock
//atomic 原子类型 基于CAS操作原子类型 线程安全的
// sleep_for
#include <iostream>
#include <list>
#include <thread>
#include <mutex>
using namespace std;
int tickerCount = 100;
std::mutex mtx; //全局互斥锁
void threadHandle1() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "thread 1" << endl;
}

void setTicket(int i) {

    while (tickerCount > 0) {

        // mtx.lock();
        {
            lock_guard<std::mutex> lock(mtx);
            // unique_lock<std::mutex> lck(mtx);  //线程通信中使用
            // lck.lock();
            if (tickerCount > 0) {
                cout << "thread:" << i << "set ticket: " << tickerCount << endl;
                tickerCount--;
            }
            // lck.unlock();
        }
        // mtx.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    // std::thread t1(threadHandle1);
    // t1.join();
    // t1.detach();
    // cout << "main thread done" << endl;

    list<std::thread> tlist;
    for (int i = 0; i < 3; i++) {
        tlist.push_back(std::thread(setTicket, i));
    }

    for (std::thread &thread: tlist) {
        thread.join();
    }
    cout << "ticket end:" << tickerCount << endl;

    return 0;
};
