//
// Created by wangj on 2025/12/10.
//
#include "dep.h"


class VGA {
public:
    virtual ~VGA() = default;

    virtual void play() = 0;

    // static string getType() {
    //     return "VGA";
    // }
};

class HDMI {
public:
    virtual ~HDMI() = default;

    virtual void play() = 0;

    // static string getType() {
    //     return "VGA";
    // }
};

class TV01 final : public VGA {
public:
    void play() override {
        cout << "VGA - TV01" << endl;
    };
};


class TV02 final : public HDMI {
public:
    void play() override {
        cout << "VGA - TV02" << endl;
    };
};

class Computer final {
public:
    void playVideo(VGA *p) {
        cout << "Computer - ";
        p->play();
    };
};

class VGAToHTMLAdapter : public VGA {
    public:
    explicit VGAToHTMLAdapter(HDMI *pHdmi): pHdmi(pHdmi) {}
    void play() override {
        cout << "VGAToHTMLAdapter - ";
        pHdmi->play();
    }
    void playVideo(VGA *p) {}
private:
    HDMI *pHdmi = nullptr;
};

int main() {
    SetConsoleOutputCP(65001); // 65001 是 UTF-8 的代码页编号
    auto *p = new Computer();
    p->playVideo(new TV01());
    p->playVideo(new VGAToHTMLAdapter(new TV02()));
    delete p;
    return 0;
}
