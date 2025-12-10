//
// Created by wangj on 2025/12/10.
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
        cout << "get audi car" << _name << endl;
    }
};
class Light {
public:
    virtual ~Light() = default;

    virtual void show() = 0;

    int createCarLight();
};
class BMWLight : public Light {
public:
    void show() override {
        cout << "BMWLight" << endl;
    }
};

class AudiLight : public Light {
public:
    void show() override {
        cout << "AudiLight" << endl;
    }
};

class AbstractFactory {
    public:
    virtual ~AbstractFactory() = default;
    virtual std::unique_ptr<Car> createCar(const string& name) = 0;
    virtual std::unique_ptr<Light> createCarLight() = 0;
};


class BMWFactory : public AbstractFactory {
public:
    std::unique_ptr<Car> createCar(const string& name) override {
        return make_unique<BWM>(name);
    };
    std::unique_ptr<Light> createCarLight() override {
        return make_unique<BMWLight>();
    }
};

class AudiFactory : public AbstractFactory {
public:
    std::unique_ptr<Car> createCar(const string& name) override {
        return make_unique<Audi>(name);
    };
    std::unique_ptr<Light> createCarLight() override {
        return make_unique<AudiLight>();
    }
};

int main() {
    unique_ptr<AbstractFactory> factory = make_unique<BMWFactory>();
    unique_ptr p1(factory->createCar("BWM"));
    unique_ptr p11(factory->createCarLight());
    // p1->show();


    unique_ptr<AbstractFactory> factory2 = make_unique<AudiFactory>();
    unique_ptr p2(factory2->createCar("audi"));
    unique_ptr p22(factory2->createCarLight());

    p1->show();
    p11->show();
    p2->show();
    p22->show();
    return 0;
}