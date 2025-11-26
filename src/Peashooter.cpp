// Peashooter.cpp
#include "Peashooter.h"
#include "Transform.h"
#include <graphics.h>
#include <iostream>

// 实现draw纯虚函数
void Peashooter::draw() const {
    if (is_dead()) return;

    // 获取Transform
     const Transform* trans = GetTransform();
    // trans = GetTransform();
    if (!trans) return;
    float x = trans->GetPosition().x;
    float y = trans->GetPosition().y;
    int width = 50, height = 50; // 豌豆射手尺寸

    // 绘制主体
    setfillcolor(GREEN);
    solidrectangle(static_cast<int>(x), static_cast<int>(y),
        static_cast<int>(x + width), static_cast<int>(y + height));

    // 绘制炮管
    setfillcolor(RGB(0, 100, 0)); // 深绿色
    solidrectangle(static_cast<int>(x + width - 5), static_cast<int>(y + 15),
        static_cast<int>(x + width + 10), static_cast<int>(y + 35));

    // 绘制血条
    setfillcolor(RED);
    solidrectangle(static_cast<int>(x), static_cast<int>(y - 10),
        static_cast<int>(x + width), static_cast<int>(y - 6));
    float health_ratio = static_cast<float>(get_health()) / get_max_health();
    setfillcolor(GREEN);
    solidrectangle(static_cast<int>(x), static_cast<int>(y - 10),
        static_cast<int>(x + width * health_ratio), static_cast<int>(y - 6));
}

void Peashooter::update() {
    if (is_dead()) return;

    if (current_cooldown > 0) {
        current_cooldown--;
    }
    else {
        shoot();
        current_cooldown = fire_cooldown;
    }
}

void Peashooter::shoot() {
    auto trans = GetTransform();
    if (!trans) return;
    std::cout << "Peashooter at (" << trans->GetPosition().x << ","
        << trans->GetPosition().y << ") shoots a pea!" << std::endl;
}