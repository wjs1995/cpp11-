//
// Created by wangj on 2025/12/10.
//
#include "dep.h"

class Observer {
public:
    virtual ~Observer() = default;

    virtual void handler(int mid) = 0;
};


class MyObserver final : public Observer {
public:
    ~MyObserver() override = default;

    void handler(const int mid) override {
        switch (mid) {
            case 0:
                cout << "MyObserver handler id= " << mid << endl;
                break;
            case 1:
                cout << "MyObserver handler id= " << mid << endl;
                break;
            default:
                cout << "MyObserver handler id= " << mid << endl;
                break;
        }
    }
};


class MyObserver2 final : public Observer {
public:
    ~MyObserver2() override = default;

    void handler(const int mid) override {
        switch (mid) {
            case 2:
                cout << "MyObserver2 handler id= " << mid << endl;
                break;
            default:
                cout << "MyObserver2 handler id= " << mid << endl;
                break;
        }
    }
};


class Subject {
public:
    void addObserver(Observer *obs, int mid) {
        _subjectMap[mid].push_back(obs);
    }
    void dispatch(int mid) {
        // auto it = _subjectMap.find(mid);
        // if (it != _subjectMap.end()) {
        //     for (Observer *obs : it->second) {
        //         obs->handler(mid);
        //     }
        // }
        for (auto ob: _subjectMap[mid]) {
            ob->handler(mid);
        }
    }

private:
    unordered_map<int, list<Observer *> > _subjectMap;
};

int main() {
    Subject subject;
    Observer *p1 = new MyObserver();
    Observer *p3 = new MyObserver2();
    subject.addObserver(p1, 1);
    subject.addObserver(p3, 2);
    subject.dispatch(1);
    subject.dispatch(2);
    delete p1;
    delete p3;
    return 0;
}
