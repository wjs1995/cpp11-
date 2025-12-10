//
// Created by wangj on 2025/12/10.
//

#include "dep.h"

class Car {
public:
    virtual ~Car() = default;

    virtual void show() = 0;
};

class Benz final : public Car {
public:
    void show() override {
        std::cout << "Benz" << std::endl;
    };
};


class CarDecorator : public Car {
public:
    CarDecorator(Car *car): pcar(car) {};
    virtual void show() = 0;

private:
    Car *pcar = nullptr;
};

class CarDecorator2 : public Car {
    public:
    CarDecorator2(Car *car): pcar(car) {};
    void show() override {
        pcar->show();
        std::cout << "定速巡航" << std::endl;

    };
private:
    Car *pcar = nullptr;

};

class CarDecorator3 : public Car {
public:
    CarDecorator3(Car *car): pcar(car) {};
    void show() override {
        pcar->show();
        std::cout << "自动刹车" << std::endl;

    };
private:
    Car *pcar = nullptr;

};

void func(Car && car) {}
int main() {
    SetConsoleOutputCP(65001); // 65001 是 UTF-8 的代码页编号
    Car *p1 = new CarDecorator2(new Benz());
    Car *p2 = new CarDecorator3(p1);
    func(Benz());
    p1->show();
    p2->show();
    delete p1;
    delete p2;
    return 0;
}
