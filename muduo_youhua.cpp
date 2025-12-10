//
// Created by wangj on 2025/12/8.
//
#include <functional>
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

// 使用 std::packaged_task 或 std::future/std::promise 可以实现更高级的返回值/异常处理，
// 但这里我们只用简单的 void() 函数作为任务类型。
using Task = function<void()>;

class ThreadPool {
public:
    // 构造函数：启动指定数量的工作线程
    ThreadPool(int size) : _stop(false) {
        if (size <= 0) {
            size = 1;
        }

        // 直接在 ThreadPool 内部创建和启动工作线程
        for (int i = 0; i < size; i++) {
            _workers.emplace_back(&ThreadPool::runInThread, this, i);
        }
        cout << "ThreadPool started with " << size << " threads." << endl;
    }

    // 析构函数：确保所有线程优雅退出并 join
    ~ThreadPool() {
        {
            // 锁定并设置停止标志
            unique_lock<mutex> lock(_queueMutex);
            _stop = true;
        }

        // 唤醒所有等待中的线程，让它们看到 _stop = true
        _condition.notify_all();

        // 等待所有线程完成
        for (thread &worker : _workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
        cout << "ThreadPool destroyed." << endl;
    }

    // 提交任务到队列
    template<class F>
    void enqueue(F &&task) {
        {
            // cout << "TPY==" << typeid(F).name() << endl;
            unique_lock<mutex> lock(_queueMutex);
            // 将任务包装成 Task 类型并放入队列
            _tasks.emplace(forward<F>(task));
        }
        // 唤醒一个等待中的工作线程
        _condition.notify_one();
    }

private:
    vector<thread> _workers;                     // 工作线程句柄
    queue<Task> _tasks;                          // 任务队列
    mutex _queueMutex;                           // 队列的互斥锁
    condition_variable _condition;               // 条件变量，用于线程等待和唤醒
    bool _stop;                                  // 停止标志，控制线程退出

    // 工作线程的主循环函数
    void runInThread(int id) {
        cout << "Worker thread " << id << " started." << endl;
        while (!_stop) {
            Task task;
            {
                // 1. 锁住队列
                unique_lock<mutex> lock(_queueMutex);

                // 2. 等待条件：队列非空 OR 停止标志为真
                _condition.wait(lock, [this]{
                    return _stop || !_tasks.empty();
                });

                // 3. 检查是否是由于停止标志被唤醒
                if (_stop && _tasks.empty()) {
                    return; // 退出线程
                }

                // 4. 取出任务
                task = move(_tasks.front());
                _tasks.pop();
            }

            // 5. 解锁后执行任务
            // 必须在锁外执行任务，避免任务执行时间过长导致其他线程饥饿
            cout << "Thread " << id << " is executing a task." << endl;
            task(); // 执行任务
        }
        cout << "Worker thread " << id << " exited." << endl;
    }
};

// 示例任务函数
void heavyTask(int n) {
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "Task completed. Input: " << n << endl;
}

// --- 分隔线 ---

int main() {
    // 实例化线程池，启动 4 个工作线程
    ThreadPool tp(4);

    // 提交 10 个任务
    for (int i = 0; i < 10; ++i) {
        // 使用 lambda 表达式或 bind 包装任务
        tp.enqueue([i] { heavyTask(i); });
    }

    // main 函数退出后，tp 的析构函数会被调用，自动关闭并 join 所有线程。
    this_thread::sleep_for(chrono::seconds(3)); // 暂停主线程，给任务执行时间
    return 0;
}