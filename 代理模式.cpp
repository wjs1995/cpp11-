//
// Created by wangj on 2025/12/10.
//

#include "dep.h"

class VideoSite {
public:
    virtual ~VideoSite() = default;

    virtual void free() = 0;

    virtual void vip() = 0;

    virtual void ticket() = 0;
};

class FixedVideoSite : public VideoSite {
public:
    void free() override {
        cout << "free" << endl;
    };

    void vip() override {
        cout << "vip" << endl;
    };

    void ticket() override {
        cout << "ticket" << endl;
    };
};
class VideoSiteProxy : public VideoSite {
    public:
    VideoSiteProxy() {
        video_site_ = new FixedVideoSite();
    }
        ~VideoSiteProxy() override {
        delete video_site_;
    }
    void free() override {
        video_site_->free();
    }
    void vip() override {
        cout << "pelease up vip 升级吧" << endl;
        video_site_->vip();
    }
    void ticket() override {
        video_site_->ticket();
    }
private:
    VideoSite* video_site_;
};

class VipVideoSiteProxy : public VideoSite {
public:
    VipVideoSiteProxy() {
        video_site_ = new FixedVideoSite();
    }
    ~VipVideoSiteProxy() override {
        delete video_site_;
    }
    void free() override {
        video_site_->free();
    }
    void vip() override {
        video_site_->vip();
    }
    void ticket() override {
        video_site_->ticket();
    }
private:
    VideoSite* video_site_;
};
void watchMv(const unique_ptr<VideoSite> &v) {
    v->free();
    v->vip();
    v->ticket();
}
int main() {
    SetConsoleOutputCP(65001); // 65001 是 UTF-8 的代码页编号
    unique_ptr<VideoSite> v = make_unique<VideoSiteProxy>();
    unique_ptr<VideoSite> v2(new VideoSiteProxy());
    watchMv(v);
    return 0;
}
