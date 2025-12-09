//
// Created by wangj on 2025/12/9.
//
#include "dep.h"

class Car {
public:
    virtual ~Car() = default;

    // Car(string name) : _name(name) {
    // }
    explicit Car(string name) : _name(std::move(name)) {
    }

    virtual void show() = 0;

protected:
    string _name;
};

class BWM : public Car {
public:
    explicit BWM(const string &name) : Car(name) {
    }

    void show() override {
        cout << "get bwm car" << _name << endl;
    };
};


class Audi : public Car {
public:
    explicit Audi(const string &name) : Car(name) {
    }

    void show() override {
        cout << "get audio" << _name << endl;
    }
};

class Factory {
public:
    virtual ~Factory() = default;

    // virtual Car *createCar(string name) = 0;

    virtual std::unique_ptr<Car> createCar(const string &name) = 0;
};

class BMWFactory : public Factory {
public:
    std::unique_ptr<Car> createCar(const string& name) override {
        return make_unique<BWM>(name);
    };
};

class AudiFactory : public Factory {
public:
    std::unique_ptr<Car> createCar(const string& name) override {
        return make_unique<Audi>(name);
    };
};

int main() {
    unique_ptr<Factory> factory = make_unique<BMWFactory>();
    unique_ptr p1(factory->createCar("BWM"));
    unique_ptr<Factory> factory2 = make_unique<AudiFactory>();
    unique_ptr p2(factory2->createCar("audi"));
    p1->show();
    p2->show();
    return 0;
}
