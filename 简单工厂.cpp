//
// Created by wangj on 2025/12/9.
//
#include "dep.h"

class Car {
public:
    virtual ~Car() = default;

    Car(string name) : _name(name) {
    }

    virtual void show() = 0;

protected:
    string _name;
};


class BWM : public Car {
public:
    BWM(const string &name) : Car(name) {
    }

    void show() {
        cout << "get bwm car" << _name << endl;
    };
};


class Audio : public Car {
public:
    Audio(string name) : Car(name) {
    }

    void show() {
        cout << "get audio" << _name << endl;
    }
};

enum CarEnum {
    BMW, AUDI
};

class SimpleFactory {
public:
    Car *createCar(CarEnum ce) {
        switch (ce) {
            case BMW:
                return new BWM("BMW");
            case AUDI:
                return new Audio("AUDI");
            default:
                cerr << "invalid car enum" << endl;
        }
    }
};

int main() {
    // SimpleFactory *f = new SimpleFactory();
    // auto c = f->createCar(BMW);
    // delete c;
    // delete f;
    unique_ptr<SimpleFactory> factory = make_unique<SimpleFactory>();
    unique_ptr<Car> p1 = make_unique<BWM>("BMW");
    unique_ptr<Car> p2(factory->createCar(AUDI));
    p1->show();
    p2->show();
    return 0;
}
