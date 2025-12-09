#include <condition_variable>
#include <ios>
#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
//
// Created by wangj on 2025/12/9.
//
// 互斥
// 同步通信
std::mutex mtx;
std::condition_variable cv;
void func(std::unique_lock<std::mutex> &lock) {
    lock.lock();
}

void func2(std::lock_guard<std::mutex> &lock) {

}
class Queue {
public:
    void put(int val) {
        // std::lock_guard<std::mutex> lck(mtx);
        // func2(lck);
        std::unique_lock<std::mutex> lk(mtx);
        // func(lk);

        while (!que.empty()) {
            cv.wait(lk);
        }
        que.push(val);
        cv.notify_all();
        std::cout << "push:" << val << std::endl;
    }

    int get() {
        // std::lock_guard<std::mutex> lck(mtx);
        std::unique_lock<std::mutex> lk(mtx);

        while (que.empty()) {
            cv.wait(lk);
        }
        int q = que.front();
        que.pop();
        cv.notify_all();
        std::cout << "get:" << q << std::endl;
        return q;
    }

private:
    std::queue<int> que;
};

void producer(Queue *q) {
    for (int i = 0; i < 10; i++) {
        q->put(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer(Queue *q) {
    for (int i = 0; i < 10; i++) {
        q->get();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    Queue q;
    std::thread t1(producer, &q);
    std::cout << "走了1" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread t2(consumer, &q);
    std::cout << "走了" << std::endl;
    t1.join();
    t2.join();
    return 0;
}
